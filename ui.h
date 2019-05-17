// ui.h

#ifndef UI_H
#define UI_H

#include "board.h"

#include <curses.h>
#include <ncurses.h>
#include <string>
#include <array>

enum UIState {MAIN_MENU, GAME_UI, UI_LOADED, UI_NOT_LOADED};
enum GameUIState {GAME_UI_NOT_LOADED, GAME_UI_LOADED};

class GameUI {
	public:
		void initGameUI();
		void closeGameUI();
		void runGameUI(); // runs the ui in whatever state it is in
		GameUIState getGameUIState();
	private:
		GameUIState m_gameuistate;

		// setup options
		bool m_whiteoverblack = false;
		
		std::array<int,2> m_pos = {{0,0}}; // cursor position
		BoardType m_board = BlackAboveWhiteBoard;

		void drawGameSetupMenu();
		bool runGameSetup();
		void runGame();
};

class MainUI {
	public:
		bool initUI();
		void closeUI();
		void MainMenu();
		UIState getUIState();
	private:
		UIState m_uistate;

		void drawMainMenu();

		GameUI TheGameUI;
};

#endif

