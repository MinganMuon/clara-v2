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
		endwin();
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
	m_selectedPos[0] = -1; m_selectedPos[1] = -1;
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
			m_player = WHITE;
			exit = true;
		} else if (key == 'B') {
			m_player = BLACK;
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
			m_selectedAI = "Random";
			exit = true;
		}
	}

	return true;
}

void GameUI::drawgameinfo()
{
	std::array<int,2> sul; // start up left
	sul[0] = 5+33+5;
	sul[1] = 5;

	mvaddstr(sul[1],sul[0],   "+-----------------------------------+");
	mvaddstr(sul[1]+1,sul[0], "|             Game Info             |");
	mvaddstr(sul[1]+2,sul[0], "| You:                              |");
	mvaddstr(sul[1]+3,sul[0], "| AI:                               |");
	mvaddstr(sul[1]+4,sul[0], "| Turn                              |");
	mvaddstr(sul[1]+5,sul[0], "|    white pieces,    black pieces  |");
	mvaddstr(sul[1]+6,sul[0], "+-----------------------------------+");

	std::string you = "White";
	if (m_player == BLACK)
		you = "Black";
	mvaddstr(sul[1]+2,sul[0]+7, you.c_str());

	mvaddstr(sul[1]+3,sul[0]+6, m_selectedAI.c_str());

	mvaddstr(sul[1]+4,sul[0]+7, "0, White to move");

	mvaddstr(sul[1]+5,sul[0]+19, (std::to_string(countPieces(m_board, TILE_BLACK) + countPieces(m_board, TILE_BLACK_KING))).c_str());
	mvaddstr(sul[1]+5,sul[0]+2, (std::to_string(countPieces(m_board, TILE_WHITE) + countPieces(m_board, TILE_WHITE_KING))).c_str());
}

void GameUI::drawboardoutline()
{
	// the board is 33 across and 25 down
	for (int i=0; i<8; i++) {
	mvaddstr(5+i*3,5, "+---+---+---+---+---+---+---+---+");
	mvaddstr(6+i*3,5, "|   |   |   |   |   |   |   |   |");
	mvaddstr(7+i*3,5, "|   |   |   |   |   |   |   |   |");
	}
	mvaddstr(5+8*3,5, "+---+---+---+---+---+---+---+---+");
}

void GameUI::drawboardtiles(BoardType theboard)
{
	for (decltype(theboard.size()) i=0; i != theboard.size(); i++)
	{
		if ((theboard[i] != TILE_INVALID) && (theboard[i] != TILE_EMPTY)) {
			std::array<int,2> coords = paddedToCoords(i);
			std::string piecechar = "E"; // e for error
			switch (theboard[i]) {
				case TILE_WHITE:
					piecechar = "w";
					break;
				case TILE_WHITE_KING:
					piecechar = "W";
					break;
				case TILE_BLACK:
					piecechar = "b";
					break;
				case TILE_BLACK_KING:
					piecechar = "B";
					break;
				case TILE_INVALID:
					break;
				case TILE_EMPTY:
					break;
			}
			mvaddstr((5+1+coords[1]*3), (5+2+coords[0]*4), piecechar.c_str());
		}
	}
}

void GameUI::drawcursor()
{
	mvaddstr((5+1+m_pos[1]*3)+1, (5+2+m_pos[0]*4), "*");
}

void GameUI::drawselectedtile()
{
	if (m_selectedPos[0] != -1) {
		mvaddstr((5+1+m_selectedPos[1]*3), (5+2+m_selectedPos[0]*4)-1, "#");
		mvaddstr((5+1+m_selectedPos[1]*3), (5+2+m_selectedPos[0]*4)+1, "#");
		
		int padded = coordsToPadded(m_selectedPos);
		if (padded != -1) {
			std::vector<Move> movelist = MoveGen.getPieceMoves(padded, m_board);
			for (Move m : movelist)
			{
				std::array<int,2> dest = paddedToCoords(m.tileTo);
				mvaddstr((5+1+dest[1]*3)+1, (5+2+dest[0]*4)-1, "^");
				mvaddstr((5+1+dest[1]*3)+1, (5+2+dest[0]*4)+1, "^");

				for (int jt : m.tilesJumped)
				{
					std::array<int,2> jumped = paddedToCoords(jt);
					mvaddstr((5+1+jumped[1]*3)+1, (5+2+jumped[0]*4), "!");
				}
			}
		}
	}
}

void GameUI::drawtilediags()
{
	std::array<int,2> sul; // start up left
	sul[0] = 5+33+5;
	sul[1] = 5+7+2;

	mvaddstr(sul[1],sul[0],   "+-----------------------------------+");
	mvaddstr(sul[1]+1,sul[0], "|             Tile Diag             |");
	mvaddstr(sul[1]+2,sul[0], "|                                   |");
	mvaddstr(sul[1]+3,sul[0], "|                                   |");
	mvaddstr(sul[1]+4,sul[0], "|                                   |");
	mvaddstr(sul[1]+5,sul[0], "|                                   |");
	mvaddstr(sul[1]+6,sul[0], "+-----------------------------------+");

}

void GameUI::drawgamehelp()
{
	std::array<int,2> sul; // start up left
	sul[0] = 5+33+5;
	sul[1] = 5+7+2+7+2;

	mvaddstr(sul[1],sul[0],   "+-----------------------------------+");
	mvaddstr(sul[1]+1,sul[0], "|   Commands           Symbols      |");
	mvaddstr(sul[1]+2,sul[0], "| Q     - Quit    * - Cursor        |");
	mvaddstr(sul[1]+3,sul[0], "| wasd  - Move    # - Selected Tile |");
	mvaddstr(sul[1]+4,sul[0], "| Space - Select  ^ - Destination   |");
	mvaddstr(sul[1]+5,sul[0], "| m     - Move    ! - Jumped Tiles  |");
	mvaddstr(sul[1]+6,sul[0], "+-----------------------------------+");
}

void GameUI::drawui()
{
	clear();

	drawboardoutline();
	drawboardtiles(m_board);
	drawcursor();
	drawselectedtile();

	drawgameinfo();
	drawtilediags();
	drawgamehelp();
}

bool GameUI::rungameui()
{
	drawui();
	int exit = false;
	while (!exit) {
		// process input
		char ch = getch();
		switch (ch) {
			case 'Q':
				exit=true;
				break;

			// movement commands
			case 'w':
				if (m_pos[1] > 0)
					m_pos[1]--;
				break;
			case 's': 
				if (m_pos[1] < 7)
					m_pos[1]++;
				break;
			case 'a':
				if (m_pos[0] > 0)
					m_pos[0]--;
				break;
			case 'd': 
				if (m_pos[0] < 7)
					m_pos[0]++;
				break;

			// selection
			case ' ':
				if (m_pos == m_selectedPos)
				{
					m_selectedPos = {{-1,-1}};
				} else {
					m_selectedPos = m_pos;
				}
				break;
		}

		// draw
		drawui();
	}

	return true;
}

bool GameUI::runfinishedui()
{
	return true;
}

