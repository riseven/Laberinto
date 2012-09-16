#pragma once

#include "MouseEvent.h"

#include <ClanLib/core.h>

class GraphicNode
{
public:
	GraphicNode(void);
	virtual ~GraphicNode(void);
	virtual void Update();
	virtual void Draw(CL_Rect area);
	virtual void OnMouseOver(MouseEvent &e);
	virtual void OnMouseDown(MouseEvent &e);
};
