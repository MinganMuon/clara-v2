// gamestate.h

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "board.h"
#include "move.h"

#include <vector>

enum PlayerType : short {BLACK, WHITE};
enum WinnerType : short {BLACK_WON, WHITE_WON, DRAW, IN_PROGRESS};

class GameState {
	public:
		void initGameState();
		BoardType getBoard();
		PlayerType whoIsToMove();
		int getTurnNumber();
		WinnerType getWinStatus();
		std::vector<Move> getListOfMoves();

		bool makeMove(Move themove, bool force=false);
	private:
		BoardType m_board;
		PlayerType m_playertomove;
		int m_turnnumber;
		WinnerType m_winner;
		std::vector<Move> m_listofmoves;
};

WinnerType findWinnerStatus(BoardType board);

#endif

