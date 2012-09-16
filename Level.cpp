#include "Level.h"

#include "GroundWall.h"
#include "GroundClear.h"
#include "Player.h"

#include "Teleporter.h"
#include "BaseDoor.h"
#include "PressTile.h"
#include "Key.h"

using std::vector;

Level::Level(int level)
{
	// Se carga el nivel
	std::stringstream sstemp;
	sstemp << "level" << level << ".xml" ;

	std::string path;
	sstemp >> path;

	CL_InputSourceProvider_File levelProvider("data/levels");
	CL_InputSource * levelFile = levelProvider.open_source(path);

	CL_DomDocument levelXmlDoc(levelFile);
	CL_DomElement levelNode = levelXmlDoc.get_document_element();
	CL_DomNode groundNode = levelNode.named_item("Ground");

	CL_DomNode rowNode = groundNode.named_item("Row");
	std::vector<std::string> rowStrings;
	
	unsigned int width = 0;

	while ( ! rowNode.is_null() )
	{
		std::string strTemp = rowNode.get_attributes().get_named_item("tiles").get_node_value();
		rowStrings.push_back( strTemp );
		if ( strTemp.length() > width )
		{
			width = strTemp.length();
		}
		
		rowNode = rowNode.get_next_sibling();
	}

	unsigned int height = rowStrings.size();

	// Ahroa creamos el level
	levelGround.assign(width, vector<GroundInfo *>(height, 0));

	for ( unsigned int x = 0 ; x < width ; x++ )
	{
		for ( unsigned int y = 0 ; y < height ; y++ )
		{
			GroundInfo * groundTemp = 0;
			switch ( rowStrings.at(y).at(x) )
			{
			case '#':
				groundTemp = new GroundWall();
				break;
			case ' ':
				groundTemp = new GroundClear();
				break;
			default:
				throw CL_Error("Formato del nivel incorrecto");
			}

			levelGround.at(x).at(y) = groundTemp;
		}
	}
	
	this->width = width;
	this->height = height;

	// Creamos el jugador
	int playerX, playerY;
	CL_DomNode playerNode = levelNode.named_item("Player");
	sstemp.clear();
	sstemp << playerNode.get_attributes().get_named_item("x").get_node_value() << " ";
	sstemp << playerNode.get_attributes().get_named_item("y").get_node_value() << " ";
	sstemp >> playerX >> playerY;
	
	player = new Player(this, playerX, playerY);

	// Por último procesamos la conectividad de paredes, para que determinen el grafico a utilizar
	// TODO

	// Ahora cargamos las paredes
	CL_DomNode objectsNode = levelNode.named_item("Objects");
	CL_DomNode currentObjectNode = objectsNode.get_first_child();

	while ( ! currentObjectNode.is_null() )
	{
		GameObject * tempObject = 0;

		// Comprobamos el tipo de objeto
		std::string objectType = currentObjectNode.get_node_name();
		if ( objectType == "Teleporter" )
		{
			tempObject = new Teleporter(currentObjectNode);
		}
		else if ( objectType == "BaseDoor" )
		{
			tempObject = new BaseDoor(currentObjectNode);
		}
		else if ( objectType == "PressTile" )
		{
			tempObject = new PressTile(currentObjectNode);
		}
		else if ( objectType == "Key" )
		{
			tempObject = new Key(currentObjectNode);
		}
		else
		{
			throw CL_Error("Level Xml Format Error");
		}

		objects.push_back(tempObject);

		currentObjectNode = currentObjectNode.get_next_sibling();
	}
}

Level::~Level(void)
{
	// Hay que eliminar los GroundInfos
	for ( vector<vector<GroundInfo *> >::iterator x = levelGround.begin() ; x != levelGround.end() ; ++x )
	{
		for ( vector<GroundInfo *>::iterator y = x->begin() ; y != x->end() ; ++y )
		{
			delete (*y);
		}
	}

	// Hay que eliminar al player
	if ( player )
	{
		delete player;
	}
}

int Level::GetWidth()
{
	return width;
}

int Level::GetHeight()
{
	return height;
}

GroundInfo * Level::GetLevelGround(int x, int y)
{
	return levelGround.at(x).at(y);
}

std::list<GameObject *> Level::GetObjects()
{
	return objects;
}

std::list<GameObject *> Level::GetObjectsAt(CL_Point pos)
{
	std::list<GameObject *> objectsAt;

	for (std::list<GameObject *>::iterator i = objects.begin() ; i != objects.end() ; ++i )
	{
		GameObject * temp = *i;

		if ( temp->IsInMap() && temp->GetPosition() == pos )
		{
			objectsAt.push_back(temp);
		}
	}

	return objectsAt;
}

std::list<GameObject *> Level::GetInventory()
{
	return inventory;
}

void Level::MoveToInventory(GameObject *object)
{
	if ( inventory.size() >= 3 )
	{
		throw CL_Error("Invetory overflow");
	}

	// Lo quitamos del mapa
	objects.remove(object);

	// Lo ponemos en el inventario
	inventory.push_back(object);
}

GameObject & Level::GetObjectById(std::string id)
{
	// Buscamos el objeto
	for ( std::list<GameObject *>::iterator i = objects.begin() ;
		i != objects.end() ;
		++i )
	{
		if ( (*i)->GetId() == id )
		{
			return **i;
		}
	}

	throw CL_Error("Object id do not found");
}

Player * Level::GetPlayer()
{
	return player;
}

bool Level::IsPassable(CL_Point pos)
{
	// Si nos vamos fuera del mapa lanzamos una excepción (NO debería ni llegar a preguntarse)
	if ( pos.x < 0 || pos.x > width || pos.y < 0 || pos.y > height )
	{
		throw CL_Error("Fatal error: Level::IsPassable");
	}

	// Comprobamos que el tile sea passable
	if ( ! levelGround.at((int)pos.x).at((int)pos.y)->IsPassable() )
	{
		return false;
	}

	// Comprobamos que no haya ningún objeto bloqueando el camino
	for (std::list<GameObject *>::iterator i = objects.begin();
		i != objects.end();
		++i)
	{
		if ( (*i)->GetPosition() == pos )
		{
			if ( ! (*i)->IsPassable() )
			{
				return false;
			}
		}
	}

	return true;
}

void Level::RemoveObject(GameObject *object)
{
	objects.remove(object);
	inventory.remove(object);
}

void Level::SelectInventoryObject(GameObject *object)
{
	// Comprobamos que el objeto está en el inventario
	for ( std::list<GameObject *>::iterator i = inventory.begin() ; i != inventory.end() ; ++i )
	{
		if ( (*i) == object )
		{
			selectedInventory = object;
			return;
		}
	}

	throw CL_Error("Object selected is not in inventory");
}

GameObject * Level::GetSelectedInventoryObject()
{
	return selectedInventory;
}

void Level::UnselectInventoryObject()
{
	selectedInventory = 0;
}