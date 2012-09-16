#pragma once
#include "graphicnode.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class GameObject;

class InventoryNode :
	public GraphicNode
{
public:
	InventoryNode(void);
	~InventoryNode(void);

	void Update();
	void Draw(CL_Rect area);
	void OnMouseOver(MouseEvent &e);
	void OnMouseDown(MouseEvent &e);
	bool IsAnySelected();
	GameObject * GetSelectedObject();
	void Unselect();

private:
	CL_Surface surfaceSelection;
	CL_Rect lastArea;
};
