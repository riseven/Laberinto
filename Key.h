#pragma once

#include "GameObject.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class Key : public GameObject
{
public:
	Key(CL_DomNode xmlInfo);
	~Key(void);
	void Update();
	void Draw(CL_Rect area);
	void DrawInventory(CL_Rect area);
	bool IsPickable();
	void Use(CL_Point dest);

private:
	CL_Surface surfaceKeyMap;
	CL_Surface surfaceKeyInventory;
};