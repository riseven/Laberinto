#pragma once

#include "GameObject.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class Teleporter : public GameObject
{
public:
	Teleporter(CL_DomNode xmlInfo);
	~Teleporter(void);
	void Update();
	void Draw(CL_Rect area);

private:
	CL_Point destination;
	CL_Surface surfaceTeleporter;
};
