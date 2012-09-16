#pragma once

#include "gameobject.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class PressTile : public GameObject
{
public:
	PressTile(CL_DomNode xmlInfo);
	~PressTile(void);
	void Update();
	void Draw(CL_Rect area);

private:
	std::string target;
	std::string action;
	bool wasPressed;
	CL_Surface surfacePressTile;
};
