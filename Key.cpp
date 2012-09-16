#include "Key.h"

#include "GameResources.h"
#include "PlayNode.h"
#include "Level.h"

Key::Key(CL_DomNode xmlInfo):
	surfaceKeyMap("tiles/key", &GameResources::Instance().GetResourceManager()),
	surfaceKeyInventory("inventory/key", &GameResources::Instance().GetResourceManager())
{
	std::stringstream sstemp;

	sstemp << xmlInfo.get_attributes().get_named_item("id").get_node_value() << " ";
	sstemp << xmlInfo.get_attributes().get_named_item("x").get_node_value() << " ";
	sstemp << xmlInfo.get_attributes().get_named_item("y").get_node_value() << " ";

	sstemp >> id >> position.x >> position.y ;

	isInMap = true;
	isInInventory = false;


	if (xmlInfo.get_attributes().get_named_item("tile").is_attr() )
	{
		surfaceKeyMap = CL_Surface(
							xmlInfo.get_attributes().get_named_item("tile").get_node_value(), 
							&GameResources::Instance().GetResourceManager());
	}

	if (xmlInfo.get_attributes().get_named_item("inventory").is_attr() )
	{
		surfaceKeyInventory = CL_Surface(
							xmlInfo.get_attributes().get_named_item("inventory").get_node_value(), 
							&GameResources::Instance().GetResourceManager());
	}
}

Key::~Key(void)
{
}

void Key::Update()
{

}

void Key::Draw(CL_Rect area)
{
	surfaceKeyMap.draw(area);
}

void Key::DrawInventory(CL_Rect area)
{
	surfaceKeyInventory.draw(area);
}

bool Key::IsPickable()
{
	return true;
}

void Key::Use(CL_Point dest)
{
	std::list<GameObject *> objects = GameResources::Instance().GetPlayNode().GetLevel()->GetObjectsAt(dest);

	for ( std::list<GameObject *>::iterator i = objects.begin() ; i != objects.end() ; ++i )
	{
		if ( (*i)->ReceiveAction(this, "Use") )
		{
			// Key is consumed
			GameResources::Instance().GetPlayNode().GetLevel()->RemoveObject(this);

			return;
		}
	}
}