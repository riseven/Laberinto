#include "MouseEvent.h"

MouseEvent::MouseEvent(void)
{
}

MouseEvent::~MouseEvent(void)
{
}

void MouseEvent::SetMousePosition(CL_Point mousePosition)
{
	this->mousePosition = mousePosition;
}

CL_Point MouseEvent::GetMousePosition()
{
	return mousePosition;
}

void MouseEvent::SetKey(int key)
{
	this->key = key;
}

int MouseEvent::GetKey()
{
	return key;
}