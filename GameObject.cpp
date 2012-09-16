#include "GameObject.h"

#include "Level.h"
#include "GameResources.h"
#include "PlayNode.h"

GameObject::GameObject() : position(0,0)
{
}

GameObject::~GameObject(void)
{
}

std::string GameObject::GetId()
{
	return id;
}

bool GameObject::IsPassable()
{
	return true;
}

bool GameObject::IsPickable()
{
	return false;
}

bool GameObject::ReceiveAction(GameObject *source, std::string action)
{
	return false;
}

CL_Point GameObject::GetPosition()
{
	return position;
}

void GameObject::DrawInventory(CL_Rect area)
{
}

bool GameObject::IsInMap()
{
	return isInMap;
}

bool GameObject::IsInInventory()
{
	return isInInventory;
}

void GameObject::PickUp()
{
	if ( ! IsPickable() )
	{
		throw CL_Error("Tried to pick up an object that is not pickable");
	}

	GameResources::Instance().GetPlayNode().GetLevel()->MoveToInventory(this);

	isInMap = false;
	isInInventory = true;
}

void GameObject::Use(CL_Point dest)
{
}
