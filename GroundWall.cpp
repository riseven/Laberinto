#include "GroundWall.h"

#include "GameResources.h"

#include "ClanLib/display.h"

GroundWall::GroundWall(void):
	surfaceWallTile("tiles/wallNoPerspective", &GameResources::Instance().GetResourceManager())
{
	isPassable = false;
}

GroundWall::~GroundWall(void)
{
}

void GroundWall::Update()
{
}

void GroundWall::Draw(CL_Rect area)
{
	surfaceWallTile.draw(area);
}