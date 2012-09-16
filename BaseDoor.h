#pragma once

#include "gameobject.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class BaseDoor : public GameObject
{
public:
	class BaseDoorAction 
	{
	public:
		BaseDoorAction(std::string source, std::string action, std::string result);
		bool CheckAction(std::string source, std::string action);
		std::string GetResult();
	private:
		std::string source, action, result;
	};


	BaseDoor(CL_DomNode xmlInfo);
	~BaseDoor(void);

	bool IsPassable();
	bool ReceiveAction(GameObject *source, std::string action);
	void Update();
	void Draw(CL_Rect area);

private:
	bool isOpen;
	bool isHorizontal;
	std::list<BaseDoorAction> actions;
	CL_Surface surfaceDoorOpen;
	CL_Surface surfaceDoorClosed;

};
