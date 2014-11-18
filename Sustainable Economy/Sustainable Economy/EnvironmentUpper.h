#pragma once
#include "environment.h"

class EnvironmentUpper :
	public Environment
{
public:
	EnvironmentUpper(const int x, const int y) : Environment(x, y) {}
	void render(void) override final;
protected:
	virtual void BuildWalls(void) override final {}; // Do nothing. No walls on upper layer
	virtual void BuildStationRest(const int _x, const int _y) override final;
};

extern EnvironmentUpper* g_environmentUpper;
