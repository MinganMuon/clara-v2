// move.h

#ifndef MOVE_H
#define MOVE_H

#include "board.h"

#include <vector>

enum PlayerType : short; // forward def

class Move {
	public:
		int tileFrom;
		int tileTo;
		std::vector<int> tilesJumped;
		bool pieceKinged;
};

class MoveGenerator {
	public:
		std::vector<Move> getPieceMoves(int tile, BoardType board);
		std::vector<Move> getPlayerMoves(PlayerType player);
};

extern MoveGenerator MoveGen;

#endif

