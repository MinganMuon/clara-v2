// ui.cpp

#include "ui.h"

//                        Main UI
// --------------------------------------------------------

// note: no error checking, screen size checking, or anything like that is happening here
// perhaps add it in later
bool MainUI::initUI()
{
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);

	m_uistate = UI_LOADED;
	return true; // obviously change this when error checking is included
}

void MainUI::closeUI()
{
	delwin(stdscr);
	endwin();
	m_uistate = UI_NOT_LOADED;
}

void MainUI::drawMainMenu()
{
	clear();
	
	// later make sure that everything will fit on screen...
	mvaddstr(5,5, "Main Menu:");
	mvaddstr(6,5, "----------");
	mvaddstr(8,5, "a) Play a game");
	mvaddstr(9,5, "q) Quit");

	refresh();
}

void MainUI::MainMenu()
{
	m_uistate = MAIN_MENU;
	drawMainMenu();

	bool exit = false;
	while (!exit) {
		char ch = getch();
		switch (ch) {
			case 'q':
				exit=true;
				break;
			case 'a':
				m_uistate = GAME_UI;
				TheGameUI.initGameUI();
				TheGameUI.runGameUI();
				TheGameUI.closeGameUI();
				m_uistate = MAIN_MENU;
				drawMainMenu();
				break;	
		}
	}
}

UIState MainUI::getUIState()
{
	return m_uistate;
}

//                      Game UI
// --------------------------------------------------------

void GameUI::initGameUI()
{
	m_gameuistate = GAME_UI_LOADED;
}

void GameUI::closeGameUI()
{
	m_gameuistate = GAME_UI_NOT_LOADED;
}

void GameUI::runGameUI()
{
	if (m_gameuistate == GAME_UI_LOADED) {
		if (runGameSetup())
		{
			runGame();
		}
	}
}

void GameUI::drawGameSetupMenu()
{
	clear();
	
	// later make sure that everything will fit on screen...
	mvaddstr(5,5, "Setup A Game:");
	mvaddstr(6,5, "-------------");
	mvaddstr(8,5, "a) Play as White");
	mvaddstr(9,5, "b) Play as Black");
	mvaddstr(10,5, "q) Quit");

	refresh();
}

// returns false if user quit the process, true if game was properly set up
bool GameUI::runGameSetup()
{
	drawGameSetupMenu();

	while (true) {
		char ch = getch();
		switch (ch) {
			case 'q':
				return false;
			case 'a':
				m_whiteoverblack = false;
				m_board = WhiteAboveBlackBoard;
				return true;
			case 'b':
				m_whiteoverblack = true;
				m_board = BlackAboveWhiteBoard;
				return true;
		}
	}
}

void GameUI::runGame()
{
	return;
}

GameUIState GameUI::getGameUIState()
{
	return m_gameuistate;
}

