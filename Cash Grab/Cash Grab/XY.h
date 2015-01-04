#pragma once
struct XY 
{ 
	// Default Constructor
	XY(void) 
		: x(0), y(0) {}

	// Standard Constructor - set values for x and y
	XY(float _x, float _y) 
		: x(_x), y(_y) {}

	// X and Y Coordinates
	float x, y; 
}; 

// Common XY contexts
typedef XY Position;
typedef XY Dimensions;
typedef XY Vector2;
