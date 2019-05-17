// ui.h

#ifndef BOARD_H
#define BOARD_H

#include "board.h"

#include <curses.h>
#include <ncurses.h>
#include <string>
#include <array>

enum UIState {MAIN_MENU, GAME_UI, UI_LOADED};
enum GameUIState {GAME_IN_PROGRESS, GAME_FINISHED, GAME_NOT_STARTED, GAME_UI_NOT_LOADED};

class MainUI {
	public:
		bool initUI();
		void closeUI();
		void MainMenu();
	private:
		UIState m_uistate;
		GameUIState m_gameuistate;

		void drawMainMenu();
}

#endif

