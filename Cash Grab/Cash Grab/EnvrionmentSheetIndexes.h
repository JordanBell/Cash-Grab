#include "SDL.h"

// Environment Elemental Types
#define ELEMENT_NORMAL 0
#define ELEMENT_ICE 1
#define ELEMENT_FIRE 2
#define VENDOR_MACHINE 3

// Basic Environment Tile Features
#define FLOOR 0
#define FLOOR_ALT 1
#define WALL_TOP 2
#define WALL 3
#define WALL_BASE 4
#define DOOR_LOCKED_LEFT 5
#define DOOR_LOCKED_RIGHT 6
#define DOOR_LEFT 7
#define DOOR_RIGHT 8
#define WALL_TOP_OPEN_LEFT 9
#define WALL_TOP_OPEN_RIGHT 10
#define WALL_TOPBORDER_BR 11
#define WALL_TOPBORDER_B 12
#define WALL_TOPBORDER_BL 13
#define WALL_TOPBORDER_R 14
#define WALL_TOPBORDER_L 15
#define WALL_TOPBORDER_TR 16
#define WALL_TOPBORDER_T 17
#define WALL_TOPBORDER_TL 18
#define CLOCK_1 19
#define CLOCK_2 20

// Norm-Specific Indices
#define PAPER_1 21
#define PAPER_2 22

// Ice-Specific Indices
#define SNOW_CORNER_LARGE_RIGHT 21
#define SNOW_CORNER_LARGE_LEFT 22
#define SNOW_CORNER_SMALL_RIGHT 23
#define SNOW_CORNER_SMALL_LEFT 24
#define SNOW_PILE_1 25
#define SNOW_PILE_2 26