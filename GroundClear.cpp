#include "GroundClear.h"

#include "GameResources.h"

#include "ClanLib/display.h"

GroundClear::GroundClear(void) :
	surfaceClearTile("tiles/ground", &GameResources::Instance().GetResourceManager())
{
}

GroundClear::~GroundClear(void)
{
}

void GroundClear::Update()
{
}

void GroundClear::Draw(CL_Rect area)
{
	surfaceClearTile.draw(area);
}
