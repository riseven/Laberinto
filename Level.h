#pragma once

#include "GroundInfo.h"

#include <vector>

class Player;
class GameObject;

class Level
{
public:
	Level(int level);
	~Level(void);
	int GetWidth();
	int GetHeight();
	GroundInfo * GetLevelGround(int x, int y);
	std::list<GameObject *> GetObjects();
	std::list<GameObject *> GetObjectsAt(CL_Point pos);
	std::list<GameObject *> GetInventory();
	void MoveToInventory(GameObject *object);
	void RemoveObject(GameObject *object);
	GameObject & GetObjectById(std::string id);
	Player * GetPlayer();
	bool IsPassable(CL_Point pos);
	void SelectInventoryObject(GameObject *object);
	GameObject * GetSelectedInventoryObject();
	void UnselectInventoryObject();

private:
	int width;
	int height;
	std::vector<std::vector<GroundInfo *> > levelGround;
	std::list<GameObject *> objects;
	std::list<GameObject *> inventory;
	GameObject *selectedInventory;

	Player *player;
};
