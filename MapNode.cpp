#include "MapNode.h"

#include "Level.h"
#include "PlayNode.h"
#include "GroundInfo.h"
#include "Player.h"
#include "GameObject.h"
#include "GameResources.h"

#include <ClanLib/display.h>

MapNode::MapNode(PlayNode *playNode)
{
	this->playNode = playNode;

	// playNode no debería ser null
	if ( !playNode )
	{
		throw CL_Error("Error: MapNode::MapNode");
	}
}

MapNode::~MapNode(void)
{
	playNode = 0;
}

void MapNode::Update()
{
	playNode->GetLevel()->GetPlayer()->Update();

	// Ahora updateamos los objetos
	std::list<GameObject *> objects = playNode->GetLevel()->GetObjects();
	for ( std::list<GameObject *>::iterator i = objects.begin() ;
		i != objects.end();
		++i)
	{
		(*i)->Update();
	}
}

void MapNode::Draw(CL_Rect area)
{
	lastArea = area;

	// Dibujamos el contenedor
	CL_Display::fill_rect(area, CL_Color(255,255,255,25));

	// Dibujamos los GroundInfos
	// En primer lugar obtenemos el tamaño de bloque
	int blockW = (area.right-area.left) / playNode->GetLevel()->GetWidth();
	int blockH = (area.bottom-area.top) / playNode->GetLevel()->GetHeight();

	int blockSize = blockW < blockH ? blockW : blockH ;

	// Ahora dibujamos todos los groundInfos
	for (int x = 0; x < playNode->GetLevel()->GetWidth() ; x++)
	{
		for (int y = 0; y < playNode->GetLevel()->GetHeight() ; y++)
		{
			CL_Rect cellArea;
			cellArea.left = area.left + x*blockSize;
			cellArea.right = cellArea.left + blockSize;
			cellArea.top = area.top + y*blockSize;
			cellArea.bottom = cellArea.top + blockSize;

			playNode->GetLevel()->GetLevelGround(x,y)->Draw( cellArea );
		}
	}

	// Ahora pintamos los objetos
	std::list<GameObject *> objects = playNode->GetLevel()->GetObjects();
	for ( std::list<GameObject *>::iterator i = objects.begin() ;
		i != objects.end();
		++i )
	{
		GameObject *tempObject = *i;

		if ( tempObject->IsInMap() )
		{
			CL_Rect cellArea;
			cellArea.left = area.left + (int)(tempObject->GetPosition().x * blockSize);
			cellArea.right = cellArea.left + blockSize;
			cellArea.top = area.top + (int)(tempObject->GetPosition().y * blockSize);
			cellArea.bottom = cellArea.top + blockSize;

			tempObject->Draw(cellArea);
		}
	}


	// Ahora pintamos el jugador
	Player *player = playNode->GetLevel()->GetPlayer();
	player->Draw( player->GetDrawingRect(area, blockSize) );
}

void MapNode::OnMouseDown(MouseEvent &e)
{
	if ( e.GetKey() != CL_MOUSE_LEFT )
	{
		return;
	}

	CL_Rect area = lastArea;

	// En primer lugar obtenemos el tamaño de bloque
	int blockW = (area.right-area.left) / playNode->GetLevel()->GetWidth();
	int blockH = (area.bottom-area.top) / playNode->GetLevel()->GetHeight();

	int blockSize = blockW < blockH ? blockW : blockH ;

	// Ahora vemos donde cae el raton
	int x = (int)((e.GetMousePosition().x - area.left) / blockSize);
	int y = (int)((e.GetMousePosition().y - area.top) / blockSize);

	// Comprobamos si es una posicion valida
	if ( x < 0 || y < 0 ||
		x >= GameResources::Instance().GetPlayNode().GetLevel()->GetWidth() ||
		y >= GameResources::Instance().GetPlayNode().GetLevel()->GetHeight() )
	{
		// No pasa nada, se ha hecho click en borde o algo
		return;
	}

	// Hacemos click en la posicion
	ClickCell(CL_Point(x,y));
}

void MapNode::ClickCell(CL_Point cell)
{
	// Comprobamos si hay algún objeto seleccionado en el inventario
	if ( GameResources::Instance().GetPlayNode().GetLevel()->GetSelectedInventoryObject() != 0)
	{
		// Le decimos al player que tiene que usar el objeto (el comprobará si está en condiciones de usarlo)
		GameResources::Instance().GetPlayNode().GetLevel()->GetPlayer()->UseObject(
			GameResources::Instance().GetPlayNode().GetLevel()->GetSelectedInventoryObject(),
			cell);

		// Deseleccionamos el objeto
		GameResources::Instance().GetPlayNode().GetLevel()->UnselectInventoryObject();
	}
}