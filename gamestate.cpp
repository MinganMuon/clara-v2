// gamestate.cpp

#include "gamestate.h"

// does not take into account turns without capture; that's left for GameState's functions to handle
// that means that this function will never announce a draw
// and that its possible return value of IN_PROGRESS doesn't rule out the possibility of a draw
WinnerType findWinnerStatus(BoardType board)
{
	if (countPieces(board, TILE_WHITE) + countPieces(board, TILE_WHITE_KING) == 0)
		return BLACK_WON;

	if (countPieces(board, TILE_BLACK) + countPieces(board, TILE_BLACK_KING) == 0)
		return WHITE_WON;

	std::vector<Move> whitemoves = MoveGen.getPlayerMoves(WHITE, board);
	if (whitemoves.empty())
		return BLACK_WON;

	std::vector<Move> blackmoves = MoveGen.getPlayerMoves(BLACK, board);
	if (blackmoves.empty())
		return WHITE_WON;

	return IN_PROGRESS;
}

