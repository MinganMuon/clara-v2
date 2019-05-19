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
#include <vector>

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
		void drawselectedtile();
		void drawtilediags();
		void drawgamehelp();
		void drawui();
		bool rungameui();
		
		bool runfinishedui();
		
		void closeUI();

		bool m_gamecompleted = false;
		bool m_playerwon;
		
		PlayerType m_player = WHITE;
		std::string m_selectedAI;

		std::array<int,2> m_pos = {{0,0}}; // cursor position
		std::array<int,2> m_selectedPos = {{-1,-1}};
		BoardType m_board = BlackAboveWhiteBoard;

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

