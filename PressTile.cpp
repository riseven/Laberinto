#include "PressTile.h"

#include "Player.h"
#include "GameResources.h"
#include "PlayNode.h"
#include "Level.h"

#include "ClanLib/display.h"

PressTile::PressTile(CL_DomNode xmlInfo):
	surfacePressTile("tiles/pressTile", &GameResources::Instance().GetResourceManager())
{
	wasPressed = false;

	std::stringstream caster;

	caster << xmlInfo.get_attributes().get_named_item("id").get_node_value() << " ";
	caster << xmlInfo.get_attributes().get_named_item("x").get_node_value() << " ";
	caster << xmlInfo.get_attributes().get_named_item("y").get_node_value() << " ";
	caster << xmlInfo.get_attributes().get_named_item("target").get_node_value() << " ";
	caster << xmlInfo.get_attributes().get_named_item("action").get_node_value() << " ";

	caster >> id >> position.x >> position.y >> target >> action;
	caster.clear();
}

PressTile::~PressTile(void)
{
}

void PressTile::Update()
{
	Player * player = GameResources::Instance().GetPlayNode().GetLevel()->GetPlayer();

	if ( player->GetDestinationPosition() == position && player->GetTravelled() == 1.0f )
	{
		if ( ! wasPressed )
		{
			wasPressed = true;
			
			// Buscamos el target y le enviamos la accion
			GameResources::Instance().GetPlayNode().GetLevel()->GetObjectById(target).ReceiveAction(this, action);			
		}
	}
	else
	{
		wasPressed = false;
	}
}

void PressTile::Draw(CL_Rect area)
{
	surfacePressTile.draw(area);
}