// gamestate.cpp

#include "gamestate.h"

// does not take into account turns without capture; that's left for GameState's functions to handle
// that means that this function will never announce a draw
// and that its possible return value of IN_PROGRESS doesn't rule out the possibility of a draw
WinnerType findWinnerStatus(BoardType board)
{
	if (countPieces(board, TILE_WHITE) + countPieces(board, TILE_WHITE_KING) == 0)
		return BLACK_WON;

	if (countPieces(board, TILE_BLACK) + countPieces(board, TILE_BLACK_KING) == 0)
		return WHITE_WON;

	std::vector<Move> whitemoves = MoveGen.getPlayerMoves(WHITE, board);
	if (whitemoves.empty())
		return BLACK_WON;

	std::vector<Move> blackmoves = MoveGen.getPlayerMoves(BLACK, board);
	if (blackmoves.empty())
		return WHITE_WON;

	return IN_PROGRESS;
}

// this function does no error checking
BoardType applyMove(Move themove, BoardType theboard)
{
	BoardType board = theboard;
	board[themove.tileTo] = theboard[themove.tileFrom];
	board[themove.tileFrom] = TILE_EMPTY;
	for (int jt : themove.tilesJumped)
	{
		board[jt] = TILE_EMPTY;
	}
	if (themove.pieceKinged)
	{
		if (board[themove.tileTo] == TILE_WHITE) {
			board[themove.tileTo] = TILE_WHITE_KING;
		} else if (board[themove.tileTo] == TILE_BLACK) {
			board[themove.tileTo] = TILE_BLACK_KING;
		}
	}
	return board;
}

void GameState::initGameState(int numMovesWithoutCaptureLimit)
{
	m_board = BlackAboveWhiteBoard;
	m_playertomove = WHITE;
	m_turnnumber = 0;
	m_winner = IN_PROGRESS;
	m_listofmoves = {};
	m_movesWithoutCapture = 0;
	m_movesWithoutCaptureLimit = numMovesWithoutCaptureLimit;
}

BoardType GameState::getBoard()
{
	return m_board;
}

PlayerType GameState::whoIsToMove()
{
	return m_playertomove;
}

int GameState::getTurnNumber()
{
	return m_turnnumber;
}

WinnerType GameState::getWinStatus()
{
	if (m_winner == IN_PROGRESS)
	{
		m_winner = findWinnerStatus(m_board);
		if (m_winner == IN_PROGRESS)
		{
			if (m_movesWithoutCapture > m_movesWithoutCaptureLimit)
			{
				m_winner = DRAW;
				return m_winner;
			} else {
				return m_winner;
			}
		} else {
			return m_winner;
		}
	}
	return m_winner;
}

std::vector<Move> GameState::getListOfMoves()
{
	return m_listofmoves;
}

int GameState::getMovesWithoutCapture()
{
	return m_movesWithoutCapture;
}

bool GameState::makeMove(Move themove)
{
	if (isPieceWhite(themove.tileFrom, m_board))
	{
		if (m_playertomove == WHITE) {
			m_listofmoves.push_back(themove);
			m_board = applyMove(themove, getBoard());
			m_playertomove = BLACK;
			if (themove.tilesJumped.empty()) {
				m_movesWithoutCapture++;	
			} else {
				m_movesWithoutCapture = 0;
			}
			getWinStatus(); // update win status, really
			return true;
		}
	}
	if (isPieceBlack(themove.tileFrom, m_board))
	{
		if (m_playertomove == BLACK) {
			m_listofmoves.push_back(themove);
			m_board = applyMove(themove, getBoard());
			m_playertomove = WHITE;
			m_turnnumber++;
			if (themove.tilesJumped.empty()) {
				m_movesWithoutCapture++;	
			} else {
				m_movesWithoutCapture = 0;
			}
			getWinStatus(); // update win status, really
			return true;
		}
	}
	return false;
}

void GameState::agreeToADraw()
{
	m_winner = DRAW;
}

