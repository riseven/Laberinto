#include "InventoryNode.h"

#include "GameResources.h"
#include "PlayNode.h"
#include "Level.h"
#include "GameObject.h"
#include "MouseEvent.h"

#include "ClanLib/display.h"

InventoryNode::InventoryNode(void):
	surfaceSelection("inventory/selection", &GameResources::Instance().GetResourceManager())
{
	surfaceSelection.set_alpha(0.5f);
}

InventoryNode::~InventoryNode(void)
{
}

void InventoryNode::Update()
{
}

void InventoryNode::Draw(CL_Rect area)
{
	lastArea = area;

	CL_Display::fill_rect(area, CL_Color(255,255,255,25));

	// Ahora pintamos los objetos del inventario
	// En primer lugar calculamos el tamaño con el que se pintarán

	int sizeItem = 0;
	int border = 10;
	int w = area.right - area.left - 2*border;
	int h = (area.bottom - area.top - 4*border) / 3;
	sizeItem = (w < h) ? w : h ;
	
	std::list<GameObject *> inventory = GameResources::Instance().GetPlayNode().GetLevel()->GetInventory();
	int pos = 0;
	for ( std::list<GameObject *>::iterator i = inventory.begin();
		i != inventory.end() && pos < 3;
		++i, pos++)
	{
		CL_Rect itemArea;
		itemArea.left = area.left + border;
		itemArea.right = area.right - border;
		itemArea.top = area.top + border + pos * ( sizeItem + border );
		itemArea.bottom = area.top + border + sizeItem + pos * (sizeItem + border);
		(*i)->DrawInventory(itemArea);

		// Comprobamos si está seleccionado
		if ( GameResources::Instance().GetPlayNode().GetLevel()->GetSelectedInventoryObject() == (*i) )
		{
			surfaceSelection.draw(itemArea);
		}
	}
}

void InventoryNode::OnMouseOver(MouseEvent &e)
{
}

void InventoryNode::OnMouseDown(MouseEvent &e)
{
	if ( e.GetKey() == CL_MOUSE_LEFT )
	{
		CL_Rect area = lastArea;

		int sizeItem = 0;
		int border = 10;
		int w = area.right - area.left - 2*border;
		int h = (area.bottom - area.top - 4*border) / 3;
		sizeItem = (w < h) ? w : h ;

		// Ahora calculamos pos
		int pos = ( e.GetMousePosition().y - area.top ) / sizeItem;
		if ( pos < 0 || pos >= GameResources::Instance().GetPlayNode().GetLevel()->GetInventory().size() )
		{
			// No ha seleccionado nada
			return;
		}

		// Seleccionamos el item en pos
		std::list<GameObject *> objects = GameResources::Instance().GetPlayNode().GetLevel()->GetInventory();
		for ( std::list<GameObject *>::iterator i = objects.begin(); i != objects.end() ; ++i, --pos )
		{
			if ( pos == 0 )
			{
				GameResources::Instance().GetPlayNode().GetLevel()->SelectInventoryObject( *i );
			}
		}
	}
}