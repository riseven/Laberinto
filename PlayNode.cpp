#include "PlayNode.h"
#include "MapNode.h"
#include "InventoryNode.h"
#include "Level.h"

#include <ClanLib/display.h>
#include <ClanLib/core.h>

PlayNode::PlayNode(int levelIndex)
{
	// Cargamos el nivel
	level = new Level(levelIndex);

	// Creamos el nodo del mapa
	mapNode = new MapNode(this);

	// Creamos el nodo del inventario
	inventoryNode = new InventoryNode();

	// Comprobamos que todo ha ido bien
	if ( !level || !mapNode || !inventoryNode )
	{
		throw CL_Error("Error: PlayNode::PlayNode");
	}
}

PlayNode::~PlayNode(void)
{
	if (mapNode)
	{
		delete mapNode;
		mapNode = 0;
	}

	if (inventoryNode)
	{
		delete inventoryNode;
		inventoryNode = 0;
	}

	if (level)
	{
		delete level;
		level = 0;
	}
}

Level * PlayNode::GetLevel()
{
	return level;
}

void PlayNode::Update()
{
	mapNode->Update();
}

void PlayNode::Draw(CL_Rect area)
{
	CL_Display::fill_rect(area, CL_Gradient(CL_Color(0,0,54), CL_Color(54,0,100), CL_Color(100, 50, 0), CL_Color(100, 0, 55)));
	
	mapRect = CL_Rect(area.left + 300, area.top + 100, area.right - 100, area.bottom - 100);
	mapNode->Draw(mapRect);

	inventoryRect = CL_Rect(area.left + 50, area.top + 100, area.left + 250, area.bottom - 100);
	inventoryNode->Draw(inventoryRect);
}

void PlayNode::OnMouseOver(MouseEvent &e)
{	
	if ( mapRect.is_inside( e.GetMousePosition() ) )
	{
		mapNode->OnMouseOver(e);
	}

	if ( inventoryRect.is_inside( e.GetMousePosition() ) )
	{
		inventoryNode->OnMouseOver(e);
	}
}

void PlayNode::OnMouseDown(MouseEvent &e)
{	
	if ( mapRect.is_inside( e.GetMousePosition() ) )
	{
		mapNode->OnMouseDown(e);
	}

	if ( inventoryRect.is_inside( e.GetMousePosition() ) )
	{
		inventoryNode->OnMouseDown(e);
	}
}
