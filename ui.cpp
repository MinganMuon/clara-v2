// ui.cpp

#include "ui.h"

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
	m_selectedmainmenuitem = 0;
	drawMainMenu();

	bool exit = false;
	while (!exit) {
		char ch = getch();
		switch (ch) {
			case 'q':
				exit=true;
				break;
			case 'a':
				exit=true;
				break;	
		}
	}
}

