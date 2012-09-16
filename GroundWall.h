#pragma once
#include "groundinfo.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class GroundWall : public GroundInfo
{
public:
	GroundWall(void);
	~GroundWall(void);

	void Update();
	void Draw(CL_Rect area);

private:
	CL_Surface surfaceWallTile;
};
