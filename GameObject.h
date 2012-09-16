#pragma once

#include "GraphicNode.h"

class GameObject : public GraphicNode
{
public:
	GameObject();
	virtual ~GameObject(void);

	std::string GetId();
	CL_Point GetPosition();
	virtual bool IsPassable();
	virtual bool IsPickable();
	virtual bool ReceiveAction(GameObject *source, std::string action);
	bool IsInMap();
	bool IsInInventory();
	virtual void DrawInventory(CL_Rect area);
	virtual void PickUp();
	virtual void Use(CL_Point dest);

protected:
	std::string id;
	CL_Point position;
	bool isInMap;
	bool isInInventory;
};
