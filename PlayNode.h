#pragma once
#include "graphicnode.h"

class MapNode;
class InventoryNode;
class Level;

class PlayNode : public GraphicNode
{
public:
	PlayNode(int levelIndex);
	~PlayNode(void);
	void Update();
	void Draw(CL_Rect area);
	void OnMouseOver(MouseEvent &e);
	void OnMouseDown(MouseEvent &e);
	Level * GetLevel();

private:
	MapNode *mapNode;
	InventoryNode *inventoryNode;
	Level *level;
	CL_Rect mapRect;
	CL_Rect inventoryRect;
};
