#pragma once
#include "graphicnode.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include <deque>

class Level;
class GameObject;

class Player :	public GraphicNode
{
public:
	Player(Level *level, int x, int y);
	~Player(void);

	CL_Point GetOriginPosition();
	CL_Point GetDestinationPosition();
	float GetTravelled();

	void TeleportTo(CL_Point destination);
	void UseObject(GameObject *object, CL_Point destination);

	void Update();
	void Draw(CL_Rect area);
	CL_Rect GetDrawingRect(CL_Rect containerArea, int blockSize);

private:
	Level *level;
	CL_Point dstPosition;
	CL_Point orgPosition;
	float travelled;
	std::deque<CL_Point> futurePositions;
	CL_Surface surfacePlayer;
};
