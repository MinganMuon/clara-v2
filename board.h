// board.h
// Board representation:
// ---------------------
// 
// Checkers boards are represented via a padded array inside the checkers subsystem.
// The padded array is an int array of length 46, and maps to a checkerboard as follows:
// 
//    37  38  39  40
//  32  33  34  35
//    28  29  30  31
//  23  24  25  26
//    19  20  21  22
//  14  15  16  17
//    10  11  12  13
//  05  06  07  08  
//
// This way, incrementing the array by +5/+4/-4/-5 moves to the space up right/up left/down left/down right or a space that isn't on the board if the move is invalid.

#ifndef BOARD_H
#define BOARD_H

#include <array>

enum TileType {
	TILE_BLACK, TILE_BLACK_KING, TILE_WHITE, TILE_WHITE_KING, TILE_EMPTY, TILE_INVALID
};

typedef std::array<TileType,46> BoardType;

const BoardType BlackAboveWhiteBoard = {TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_INVALID, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_INVALID, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_INVALID, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_INVALID, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID};
// const BoardType WhiteAboveBlackBoard = {TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_INVALID, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_INVALID, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_INVALID, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_INVALID, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID};

std::array<int,2> paddedToCoords(int tile);
int coordsToPadded(std::array<int,2> coords);
int countPieces(BoardType sourceBoard, TileType targetTileType);

#endif

