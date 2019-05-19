// gamestate.h

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "board.h"
#include "move.h"

#include <vector>

enum WinnerType : short {BLACK_WON, WHITE_WON, DRAW, IN_PROGRESS};

class GameState {
	public:
		void initGameState(int numMovesWithoutCaptureLimit=100);
		BoardType getBoard();
		PlayerType whoIsToMove();
		int getTurnNumber();
		WinnerType getWinStatus();
		std::vector<Move> getListOfMoves();
		int getMovesWithoutCapture();

		bool makeMove(Move themove);
		void agreeToADraw();
	private:
		BoardType m_board;
		PlayerType m_playertomove;
		int m_turnnumber;
		WinnerType m_winner;
		std::vector<Move> m_listofmoves;
		int m_movesWithoutCapture;
		int m_movesWithoutCaptureLimit;

		void updateWinStatus();
};

WinnerType findWinnerStatus(BoardType board);

#endif

