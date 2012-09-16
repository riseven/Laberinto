#pragma once

#include "Event.h"

#include <ClanLib/core.h>

class MouseEvent : public Event
{
public:
	MouseEvent(void);
	~MouseEvent(void);
	void SetMousePosition(CL_Point mousePosition);
	CL_Point GetMousePosition();
	void SetKey(int key);
	int GetKey();
private:
	CL_Point mousePosition;
	int key;
};
