// ui.h

#ifndef UI_H
#define UI_H

#include "board.h"
#include "move.h"
#include "gamestate.h"

#include <curses.h>
#include <ncurses.h>
#include <string>
#include <array>

class GameUI {
	public:
		bool runUI();
	private:
		bool initUI();
		
		void drawcolorchoicemenu();
		void drawaichoicemenu();
		bool runsetupui();

		void drawgameinfo();
		void drawboardoutline();
		void drawboardtiles(BoardType theboard);
		void drawcursor();
		void drawtilediags();
		void drawgamehelp();
		void drawui();
		bool rungameui();
		
		bool runfinishedui();
		
		void closeUI();

		bool m_gamecompleted = false;
		bool m_playerwon;
		
		// setup options
		PlayerType m_player = WHITE;
		std::array<int,2> m_pos = {{0,0}}; // cursor position
		BoardType m_board = BlackAboveWhiteBoard;

		std::string m_selectedAI;
};

class MainUI {
	public:
		bool initUI();
		void closeUI();
		void MainMenu();
	private:
		void drawmainmenu();

		bool m_loaded = false;
		GameUI TheGameUI;
};

#endif

