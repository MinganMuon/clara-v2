// ui.cpp

#include "ui.h"

//                        Main UI
// --------------------------------------------------------

bool MainUI::initUI()
{
	initscr();
	keypad(stdscr, TRUE); 
	noecho();
	curs_set(FALSE);

	if (LINES < 51 || COLS < 103) {
		clear();
		mvaddstr(0, 0, "Error: your console should be at least");
		mvaddstr(1, 0, "51x103 characters to run this game.");
		mvaddstr(3, 0, "Press any key to quit.");
		move(4, 0);
		getch();
		return false;
	}

	clear();
	refresh();

	m_loaded = true;
	return true;
}

void MainUI::closeUI()
{
	endwin();
}

void MainUI::drawmainmenu()
{
	clear();

	// window is at least 51x103
	mvaddstr(5,39, "+-----------------+");
	mvaddstr(6,39, "|      Clara      |");
	mvaddstr(7,39, "|                 |");
	mvaddstr(8,39, "|    Main Menu    |");
	mvaddstr(9,39, "+-----------------+");

	mvaddstr(15,42,    "+----------+"    );
	mvaddstr(16,42,    "+  (P)lay  +"    );
	mvaddstr(17,42,    "+----------+"    );
	
	mvaddstr(20,42,    "+----------+"    );
	mvaddstr(21,42,    "+  (Q)uit  +"    );
	mvaddstr(22,42,    "+----------+"    );

	refresh();
}

void MainUI::MainMenu()
{
	if (!m_loaded)
		return;
	
	drawmainmenu();

	bool exit = false;
	while (!exit) {
		char key = getch();
		if (key == 'P')
		{
			GameUI TheGameUI;
			TheGameUI.runUI();
			drawmainmenu();
		}	
		else if (key == 'Q')
			exit = true;
	}
}

//                      Game UI
// --------------------------------------------------------

bool GameUI::initUI()
{
	m_gamecompleted = false;
	m_pos[0] = 0; m_pos[1] = 0;
	return true;
}

void GameUI::closeUI()
{

}

bool GameUI::runUI()
{
	if (initUI()) {
		if (runsetupui())
		{
			if (rungameui())
			{
				if (runfinishedui())
				{
					closeUI();
					return true;
				}
			}
		}
	}
	closeUI();
	return false;
}

void GameUI::drawcolorchoicemenu()
{
	clear();

	// window is at least 51x103
	mvaddstr(5,39, "+----------------+");
	mvaddstr(6,39, "|  Game Options  |");
	mvaddstr(7,39, "|                |");
	mvaddstr(8,39, "|  Color Choice  |");
	mvaddstr(9,39, "+----------------+");

	mvaddstr(15,42,    "+---------+"   );
	mvaddstr(16,42,    "+ (W)hite +"   );
	mvaddstr(17,42,    "+---------+"   );
	
	mvaddstr(20,42,    "+---------+"    );
	mvaddstr(21,42,    "+ (B)lack +"    );
	mvaddstr(22,42,    "+---------+"    );

	refresh();
}

void GameUI::drawaichoicemenu()
{
	clear();

	// window is at least 51x103
	mvaddstr(5,39, "+----------------+");
	mvaddstr(6,39, "|  Game Options  |");
	mvaddstr(7,39, "|                |");
	mvaddstr(8,39, "|   AI  Choice   |");
	mvaddstr(9,39, "+----------------+");

	mvaddstr(15,42,   "+----------+"   );
	mvaddstr(16,42,   "+ (R)andom +"   );
	mvaddstr(17,42,   "+----------+"   );
	
	refresh();
}

bool GameUI::runsetupui()
{
	drawcolorchoicemenu();
	int exit = false;
	while (!exit)
	{
		char key = getch();
		if (key == 'W')
		{
			m_whiteoverblack = false;
			m_board = BlackAboveWhiteBoard;
			exit = true;
		} else if (key == 'B') {
			m_whiteoverblack = true;
			m_board = WhiteAboveBlackBoard;
			exit = true;
		}
	}

	drawaichoicemenu();
	exit = false;
	while (!exit)
	{
		char key = getch();
		if (key == 'R')
		{
			m_selectedAI = "random";
			exit = true;
		}
	}

	return true;
}

bool GameUI::rungameui()
{
	return true;
}

bool GameUI::runfinishedui()
{
	return true;
}

