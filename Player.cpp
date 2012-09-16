#include "Player.h"

#include "Level.h"
#include "GameResources.h"
#include "PlayNode.h"
#include "GameObject.h"

#include <ClanLib/display.h>

Player::Player(Level *level, int x, int y):
	surfacePlayer("player/playerStatic", &GameResources::Instance().GetResourceManager())
{
	this->level = level;
	orgPosition.x = x;
	orgPosition.y = y;
	dstPosition.x = x;
	dstPosition.y = y;
	travelled = 1.0f;
}

Player::~Player(void)
{
}

CL_Point Player::GetOriginPosition()
{
	return orgPosition;
}

CL_Point Player::GetDestinationPosition()
{
	return dstPosition;
}

float Player::GetTravelled()
{
	return travelled;
}

void Player::TeleportTo(CL_Point destination)
{
	orgPosition = destination;
	dstPosition = destination;
	travelled = 1.0f;
	futurePositions.clear();
}

CL_Rect Player::GetDrawingRect(CL_Rect containerArea, int blockSize)
{
	// De momento devolvemos posiciones discretas
	CL_Rect rect;
	rect.left = (int)(containerArea.left + blockSize * (orgPosition.x*(1.0f-travelled) + dstPosition.x*travelled));
	rect.right = rect.left + blockSize;
	rect.top = (int)(containerArea.top + blockSize * (orgPosition.y*(1.0f-travelled) + dstPosition.y*travelled));
	rect.bottom = rect.top + blockSize;
	return rect;
}

void Player::Update()
{
	// Movimiento con teclado
	if ( travelled > 0.5f )
	{
		if ( CL_Keyboard::get_keycode(CL_KEY_UP) )
		{
			futurePositions.clear();
			futurePositions.push_back(CL_Point(dstPosition.x, dstPosition.y-1));
		}
		if ( CL_Keyboard::get_keycode(CL_KEY_DOWN) )
		{
			futurePositions.clear();
			futurePositions.push_back(CL_Point(dstPosition.x, dstPosition.y+1));
		}
		if ( CL_Keyboard::get_keycode(CL_KEY_LEFT) )
		{
			futurePositions.clear();
			futurePositions.push_back(CL_Point(dstPosition.x-1, dstPosition.y));
		}
		if ( CL_Keyboard::get_keycode(CL_KEY_RIGHT) )
		{
			futurePositions.clear();
			futurePositions.push_back(CL_Point(dstPosition.x+1, dstPosition.y));
		}
	}
	
	if ( travelled < 1.0f )
	{
		travelled += 0.05f;
		if ( travelled > 1.0f )
		{
			travelled = 1.0f;
		}
	}
	else
	{
		// Comprobamos si cogemos algún objeto
		std::list<GameObject *> objects = GameResources::Instance().GetPlayNode().GetLevel()->GetObjectsAt(dstPosition);
		for (std::list<GameObject *>::iterator i = objects.begin(); i != objects.end() ; ++i )
		{
			if ( (*i)->IsPickable() )
			{
				(*i)->PickUp();
			}
		}

		if ( futurePositions.empty() ? false : level->IsPassable(futurePositions.front() ) )
		{
			travelled -= 1.0f ;
			orgPosition = dstPosition;
			dstPosition = futurePositions.front();
			futurePositions.pop_front();
		}
		else
		{
			travelled = 1.0f ;
			// It is possible that next future possition is not valid, so we clear future positions
			futurePositions.clear();
		}
	}
}

void Player::Draw(CL_Rect area)
{
	// Hay que darse cuenta que este método no puede realizar el calculo del clipping rect
	// puesto que es necesaria información del mapa (como su posición y tamaño de los tiles)
	// Por ese motivo, es el MapNode el encargado de determinar el drawing rect antes de 
	// llamar a este método, eso sí, llamando al método GetDrawingRect de Player como ayuda.
	surfacePlayer.draw(area);
}

void Player::UseObject(GameObject *object, CL_Point destination)
{
	if ( futurePositions.empty() == false )
	{
		throw CL_Error("Tried to use an object while moving");
	}

	// Comprobamos si es una celda adyacente
	int absdist = abs(destination.x - orgPosition.x) + abs(destination.y - orgPosition.y);
	if (absdist != 1)
	{
		return;
	}

	// Usamos el objeto
	object->Use(destination);
}