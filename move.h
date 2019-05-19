// move.h

#ifndef MOVE_H
#define MOVE_H

#include "board.h"

#include <vector>

class Move {
	public:
		Move(int fromTile, int toTile, std::vector<int> jumpedTiles, bool kingedPiece);
		int tileFrom;
		int tileTo;
		std::vector<int> tilesJumped;
		bool pieceKinged;
};

class MoveGenerator {
	public:
		std::vector<Move> getPieceMoves(int tile, BoardType board);
		std::vector<Move> getPlayerMoves(PlayerType player, BoardType board);
	private:
		std::vector<Move> getMoveMoves(int tile, BoardType board);
		std::vector<Move> getJumpMoves(int tile, BoardType board);
};

extern MoveGenerator MoveGen;

BoardType applyMove(Move themove, BoardType theboard);

#endif

