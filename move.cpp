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

#include <curses.h>
#include <ncurses.h>

std::vector<Move> MoveGenerator::getJumpMoves(int tile, BoardType board)
{
	// fix this mess later
	// general idea: iterate over an expanding movelist, finding all the jumps that can be made from it, adding those moves to the end of the list, and then deleting the move at the iterator if any jumps from the ending position of that move were found; repeat this until we reach the end of the list, i.e. no more jumps are possible
	std::vector<Move> movelist;
	movelist.push_back(Move(tile,tile,{},false));
	auto iter = std::begin(movelist);
	while (iter != std::end(movelist)) {
		bool newjump = false;
		int tt = (*iter).tileTo;
		if (isPieceWhite(tt,board) && ((board[tt+5] == TILE_BLACK) || (board[tt+5] == TILE_BLACK_KING)) && (board[tt+5+5] == TILE_EMPTY))
		{
			std::vector<int> tj = (*iter).tilesJumped;
			tj.push_back(tt+5);
			movelist.push_back(Move(tile,tt+5+5,tj,false));
			newjump = true;
		}
		if (isPieceWhite(tt,board) && ((board[tt+4] == TILE_BLACK) || (board[tt+4] == TILE_BLACK_KING)) && (board[tt+4+4] == TILE_EMPTY))
		{
			std::vector<int> tj = (*iter).tilesJumped;
			tj.push_back(tt+4);
			movelist.push_back(Move(tile,tt+4+4,tj,false));
			newjump = true;
		}
		if (newjump) {
			iter = movelist.erase(iter);
			mvaddstr(0,0,"n");
			getch();
		} else {
			++iter;
		}
	}

	// check to make sure any jumps were found; i.e. see if we changed movelist at all
	if (!movelist.empty() && (movelist[0].tileTo == movelist[0].tileFrom))
		return {};

	// king everyone that can be kinged
	for (Move &m : movelist)
	{
		if ((board[m.tileTo] == TILE_WHITE) && isTileOnWhiteKingLine(m.tileTo))
			m.pieceKinged = true;
		if ((board[m.tileTo] == TILE_BLACK) && isTileOnBlackKingLine(m.tileTo))
			m.pieceKinged = true;
	}
	return movelist;
}

std::vector<Move> MoveGenerator::getPieceMoves(int tile, BoardType board)
{
	std::vector<Move> movelist;

	// get regular moves
	std::vector<Move> toadd = getMoveMoves(tile, board);
	for (Move m : toadd)
		movelist.push_back(m);
	
	// get jumps
	std::vector<Move> toaddjumps = getJumpMoves(tile, board);
	for (Move m : toaddjumps)
		movelist.push_back(m);
	
	return movelist;
}

std::vector<Move> MoveGenerator::getPlayerMoves(PlayerType player, BoardType board)
{
	std::vector<Move> movelist;
	if (player == WHITE) {
		for (decltype(board.size()) i=0; i != board.size(); i++)
		{
			if (isPieceWhite(i,board)) {
				std::vector<Move> toadd = getPieceMoves(i, board);
				for (Move m : toadd)
					movelist.push_back(m);
			}
		}
	} else if (player == BLACK) {
		for (decltype(board.size()) i=0; i != board.size(); i++)
		{
			if (isPieceBlack(i,board)) {
				std::vector<Move> toadd = getPieceMoves(i, board);
				for (Move m : toadd)
					movelist.push_back(m);
			}
		}
	}
	return movelist;
}

