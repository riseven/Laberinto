#pragma once
#include "groundinfo.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class GroundClear :
	public GroundInfo
{
public:
	GroundClear(void);
	~GroundClear(void);

	void Update();
	void Draw(CL_Rect area);

private:
	CL_Surface surfaceClearTile;
};
