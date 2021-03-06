// move.cpp

#include "move.h"

MoveGenerator MoveGen;

Move::Move(int fromTile, int toTile, std::vector<int> jumpedTiles, bool kingedPiece)
{
	tileFrom = fromTile;
	tileTo = toTile;
	tilesJumped = jumpedTiles;
	pieceKinged = kingedPiece;
}

std::vector<Move> MoveGenerator::getMoveMoves(int tile, BoardType board)
{
	// this is so ugly...
	std::vector<Move> movelist;
	if (isPieceWhite(tile,board)) {
		if (board[tile+5] == TILE_EMPTY) {
			if (isTileOnWhiteKingLine(tile+5)) {
				movelist.push_back(Move(tile,tile+5,std::vector<int>(),true));
			} else {
				movelist.push_back(Move(tile,tile+5,std::vector<int>(),false));
			}
		}
		if (board[tile+4] == TILE_EMPTY) {
			if (isTileOnWhiteKingLine(tile+4)) {
				movelist.push_back(Move(tile,tile+4,std::vector<int>(),true));
			} else {
				movelist.push_back(Move(tile,tile+4,std::vector<int>(),false));
			}
		}
		if (board[tile] == TILE_WHITE_KING) {
			if (board[tile-5] == TILE_EMPTY) {
				movelist.push_back(Move(tile,tile-5,std::vector<int>(),false));
			}
			if (board[tile-4] == TILE_EMPTY) {
				movelist.push_back(Move(tile,tile-4,std::vector<int>(),false));
			}
		}
	} else if (isPieceBlack(tile,board)) {
		if (board[tile-5] == TILE_EMPTY) {
			if (isTileOnBlackKingLine(tile-5)) {
				movelist.push_back(Move(tile,tile-5,std::vector<int>(),true));
			} else {
				movelist.push_back(Move(tile,tile-5,std::vector<int>(),false));
			}
		}
		if (board[tile-4] == TILE_EMPTY) {
			if (isTileOnBlackKingLine(tile-4)) {
				movelist.push_back(Move(tile,tile-4,std::vector<int>(),true));
			} else {
				movelist.push_back(Move(tile,tile-4,std::vector<int>(),false));
			}
		}
		if (board[tile] == TILE_BLACK_KING) {
			if (board[tile+5] == TILE_EMPTY) {
				movelist.push_back(Move(tile,tile+5,std::vector<int>(),false));
			}
			if (board[tile+4] == TILE_EMPTY) {
				movelist.push_back(Move(tile,tile+4,std::vector<int>(),false));
			}
		}
	}
	return movelist;
}

std::vector<Move> MoveGenerator::getJumpMoves(int tile, BoardType board)
{
	// trying to do the iterator thing manually because I think my overall algorithm is sound
	// haha it seems to work!
	std::vector<Move> movelist;
	movelist.push_back(Move(tile,tile,{},false));
	unsigned int l = movelist.size();
	unsigned int i = 0;
	while (i != l)
	{
		bool newjump = false;
		int tt = movelist[i].tileTo;
		if (isPieceWhite(tile,board) && ((board[tt+5] == TILE_BLACK) || (board[tt+5] == TILE_BLACK_KING)) && (board[tt+5+5] == TILE_EMPTY))
		{
			std::vector<int> tj = movelist[i].tilesJumped;
			tj.push_back(tt+5);
			movelist.push_back(Move(tile,tt+5+5,tj,false));
			l++;
			newjump = true;
		}
		if (isPieceWhite(tile,board) && ((board[tt+4] == TILE_BLACK) || (board[tt+4] == TILE_BLACK_KING)) && (board[tt+4+4] == TILE_EMPTY))
		{
			std::vector<int> tj = movelist[i].tilesJumped;
			tj.push_back(tt+4);
			movelist.push_back(Move(tile,tt+4+4,tj,false));
			l++;
			newjump = true;
		}
		if ((board[tile] == TILE_WHITE_KING) && ((board[tt-5] == TILE_BLACK) || (board[tt-5] == TILE_BLACK_KING)) && (board[tt-5-5] == TILE_EMPTY))
		{
			std::vector<int> tj = movelist[i].tilesJumped;
			tj.push_back(tt-5);
			movelist.push_back(Move(tile,tt-5-5,tj,false));
			l++;
			newjump = true;
		}
		if ((board[tile] == TILE_WHITE_KING) && ((board[tt-4] == TILE_BLACK) || (board[tt-4] == TILE_BLACK_KING)) && (board[tt-4-4] == TILE_EMPTY))
		{
			std::vector<int> tj = movelist[i].tilesJumped;
			tj.push_back(tt-4);
			movelist.push_back(Move(tile,tt-4-4,tj,false));
			l++;
			newjump = true;
		}
		if (newjump) {
			movelist.erase(movelist.begin() + i);
			l--;
		} else {
			i++;
		}
	}

	// check to make sure any jumps were found; i.e. see if we changed movelist at all
	if (!movelist.empty() && (movelist[0].tileTo == movelist[0].tileFrom))
		return {};

	// king everyone that can be kinged
	for (unsigned int i = 0; i != movelist.size(); i++)
	{
		if ((board[movelist[i].tileTo] == TILE_WHITE) && isTileOnWhiteKingLine(movelist[i].tileTo))
			movelist[i].pieceKinged = true;
		if ((board[movelist[i].tileTo] == TILE_BLACK) && isTileOnBlackKingLine(movelist[i].tileTo))
			movelist[i].pieceKinged = true;
	}

	return movelist;

	// old code
	/*
	// fix this mess later
	// general idea: iterate over an expanding movelist, finding all the jumps that can be made from it, adding those moves to the end of the list, and then deleting the move at the iterator if any jumps from the ending position of that move were found; repeat this until we reach the end of the list, i.e. no more jumps are possible
	std::vector<Move> movelist;
	movelist.push_back(Move(tile,tile,{},false));
	auto enditer = std::end(movelist);
	auto iter = std::begin(movelist);
	while (iter != enditer)
	{
		bool newjump = false;
		int tt = (*iter).tileTo;
		if (isPieceWhite(tt,board) && ((board[tt+5] == TILE_BLACK) || (board[tt+5] == TILE_BLACK_KING)) && (board[tt+5+5] == TILE_EMPTY))
		{
			std::vector<int> tj = (*iter).tilesJumped;
			tj.push_back(tt+5);
			movelist.push_back(Move(tile,tt+5+5,tj,false));
			enditer = std::end(movelist); // this doesn't seem to help anything
			// and I don't think the end iterator is invalidated by anything anyway
			// been stuck on this for like two hours...
			newjump = true;
			mvaddstr(0,0,"n");
			getch();
		}
		if (isPieceWhite(tt,board) && ((board[tt+4] == TILE_BLACK) || (board[tt+4] == TILE_BLACK_KING)) && (board[tt+4+4] == TILE_EMPTY))
		{
			std::vector<int> tj = (*iter).tilesJumped;
			tj.push_back(tt+4);
			movelist.push_back(Move(tile,tt+4+4,tj,false));
			enditer = std::end(movelist);
			newjump = true;
			mvaddstr(0,0,"n");
			getch();
		}
		if (newjump) {
			iter = movelist.erase(iter);
		} else {
			++iter;
		}
	}
	*/
}

// disregards the possibility of another piece's jump possibilities limiting what this tile can do
std::vector<Move> MoveGenerator::getPieceMoves(int tile, BoardType board)
{
	std::vector<Move> movelist;
	
	// get jumps
	std::vector<Move> toaddjumps = getJumpMoves(tile, board);
	for (Move m : toaddjumps)
		movelist.push_back(m);

	// if there are possible jumps then one has to take them
	if (movelist.empty()) {
		// get regular moves
		std::vector<Move> toadd = getMoveMoves(tile, board);
		for (Move m : toadd)
			movelist.push_back(m);
	}	

	return movelist;
}

std::vector<Move> MoveGenerator::getPlayerMoves(PlayerType player, BoardType board)
{
	std::vector<Move> movelist;
	bool jumps = false;
	if (player == WHITE) {
		for (decltype(board.size()) i=0; i != board.size(); i++)
		{
			if (isPieceWhite(i,board)) {
				std::vector<Move> toadd = getPieceMoves(i, board);
				for (Move m : toadd)
				{
					if (!m.tilesJumped.empty())
						jumps = true;
					movelist.push_back(m);
				}
			}
		}
	} else if (player == BLACK) {
		for (decltype(board.size()) i=0; i != board.size(); i++)
		{
			if (isPieceBlack(i,board)) {
				std::vector<Move> toadd = getPieceMoves(i, board);
				for (Move m : toadd)
				{
					if (!m.tilesJumped.empty())
						jumps = true;
					movelist.push_back(m);
				}
			}
		}
	}
	
	// if there is a possible jump, remove all non-jumps
	// I wish I could wrangle iterators into submission for this...
	if (jumps) {
		int l = movelist.size();
		int i = 0;
		while (i != l)
		{
			if (movelist[i].tilesJumped.empty())
			{
				movelist.erase(movelist.begin() + i);
				l--;
			}
			i++;
		}
	}	

	return movelist;
}

