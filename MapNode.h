#pragma once
#include "graphicnode.h"

class PlayNode;

class MapNode : public GraphicNode
{
public:
	MapNode(PlayNode *playNode);
	~MapNode(void);
	void Update();
	void Draw(CL_Rect area);
	void OnMouseDown(MouseEvent &e);
	void ClickCell(CL_Point cell);

private:
	PlayNode *playNode;
	CL_Rect lastArea;
};
