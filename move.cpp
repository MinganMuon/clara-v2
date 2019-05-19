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
		if (board[tile+5] == TILE_EMPTY) {
			if (isTileOnBlackKingLine(tile+5)) {
				movelist.push_back(Move(tile,tile+5,std::vector<int>(),true));
			} else {
				movelist.push_back(Move(tile,tile+5,std::vector<int>(),false));
			}
		}
		if (board[tile+4] == TILE_EMPTY) {
			if (isTileOnBlackKingLine(tile+4)) {
				movelist.push_back(Move(tile,tile+4,std::vector<int>(),true));
			} else {
				movelist.push_back(Move(tile,tile+4,std::vector<int>(),false));
			}
		}
		if (board[tile] == TILE_BLACK) {
			if (board[tile-5] == TILE_EMPTY) {
				movelist.push_back(Move(tile,tile-5,std::vector<int>(),false));
			}
			if (board[tile-4] == TILE_EMPTY) {
				movelist.push_back(Move(tile,tile-4,std::vector<int>(),false));
			}
		}
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

