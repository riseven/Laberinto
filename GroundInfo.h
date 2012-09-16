#pragma once

#include "GraphicNode.h"

class GroundInfo : public GraphicNode
{
public:
	GroundInfo(void);
	virtual ~GroundInfo(void);

	virtual bool IsPassable();
	virtual void Update();
	virtual void Draw(CL_Rect area);

protected:
	bool isPassable;
};
