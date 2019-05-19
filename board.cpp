// board.cpp

#include "board.h"

/*
 * Converts a tile number from padded array representation (see board.h) to
 * an 8x8 representation (in (x,y) format from top left)
 *
 * Inputs:
 * tile: tile number to convert, in padded array representation
 *
 * Note: no error-checking is done here, garbage results will result if tile is not between 0 and 45 and not an invalid tile.
 *
 * Taken from the old clara with some modifications to fit the new codebase.
 *
 */
std::array<int,2> paddedToCoords(int tile)
{
	std::array<int,2> coords = {0,0};

	// this is ugly but I can't think of a better way...
	if (tile < 9) {
		coords[1] = 7;
		coords[0] = (tile - 5)*2;
	} else if (tile < 14) {
		coords[1] = 6;
		coords[0] = (tile - 10)*2 + 1;
	} else if (tile < 18) {
		coords[1] = 5;
		coords[0] = (tile - 14)*2;
	} else if (tile < 23) {
		coords[1] = 4;
		coords[0] = (tile - 19)*2 + 1;
	} else if (tile < 27) {
		coords[1] = 3;
		coords[0] = (tile - 23)*2;
	} else if (tile < 32) {
		coords[1] = 2;
		coords[0] = (tile - 28)*2 + 1;
	} else if (tile < 36) {
		coords[1] = 1;
		coords[0] = (tile - 32)*2;
	} else {
		coords[1] = 0;
		coords[0] = (tile - 37)*2 + 1;
	}

	return coords;
}

/*
 * Converts a tile from an 8x8 representation (in (x,y) format from top left) to
 * a padded array representation (see board.h).
 *
 * Input:
 * coords: array with coords
 *
 * Outputs the tile in padded array representation,
 * or -1 if coords doesn't describe a valid tile.
 *
 * Taken from the old clara with some modifications to fit the new codebase.
 *
 */
int coordsToPadded(std::array<int,2> coords)
{
	// test for light squares (assuming pieces are on black squares)
	if (coords[0] % 2 == 0) {
		if (coords[1] % 2 == 0) {
			return -1;
		}
	} else {
		if (coords[1] % 2 != 0) {
			return -1;
		}
	}
	
	int tile = 0;
	int rows = 8 - coords[1]; /* how many rows are we from the bottom? */

	// I just reasoned out these formulae using the board diagram in checkers.h (now board.h)
	if (coords[1] % 2 == 0) {
		tile = rows*4 + rows/2;
		tile += (coords[0]-1)/2 + 1;

	} else {
		tile = rows*4 + (rows-1)/2;
		tile += (coords[0])/2 + 1;
	}

	return tile;
}

/*
 * Counts the pieces of type targetTileType on the board sourceBoard
 *
 * Returns the number of pieces.
 *
 */
int countPieces(BoardType sourceBoard, TileType targetTileType)
{
	int count=0;

	for (TileType &tile : sourceBoard) {
		if (tile == targetTileType)
			count++;
	}

	return count;
}

bool isPieceWhite(int tile, BoardType board)
{
	if ((board[tile] == TILE_WHITE) || (board[tile] == TILE_WHITE_KING))
		return true;
	return false;
}

bool isPieceBlack(int tile, BoardType board)
{
	if ((board[tile] == TILE_BLACK) || (board[tile] == TILE_BLACK_KING))
		return true;
	return false;
}

bool isTileOnWhiteKingLine(int tile)
{
	if ((tile > 36) && (tile < 41))
		return true;
	return false;
}

bool isTileOnBlackKingLine(int tile)
{
	if ((tile > 4) && (tile < 9))
		return true;
	return false;
}

