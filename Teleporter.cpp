#include "Teleporter.h"

#include "ClanLib/display.h"
#include "GameResources.h"
#include "PlayNode.h"
#include "Level.h"
#include "Player.h"

Teleporter::Teleporter(CL_DomNode xmlInfo):
	surfaceTeleporter("tiles/teleporter", &GameResources::Instance().GetResourceManager())
{
	std::stringstream sstemp;

	sstemp << xmlInfo.get_attributes().get_named_item("id").get_node_value() << " ";
	sstemp << xmlInfo.get_attributes().get_named_item("x").get_node_value() << " ";
	sstemp << xmlInfo.get_attributes().get_named_item("y").get_node_value() << " ";
	sstemp << xmlInfo.get_attributes().get_named_item("dstX").get_node_value() << " ";
	sstemp << xmlInfo.get_attributes().get_named_item("dstY").get_node_value() << " ";

	sstemp >> id >> position.x >> position.y >> destination.x >> destination.y;
}

Teleporter::~Teleporter(void)
{
}

void Teleporter::Update()
{
	Player * player = GameResources::Instance().GetPlayNode().GetLevel()->GetPlayer();

	if ( player->GetDestinationPosition() == position && player->GetTravelled() == 1.0f )
	{
		// Activamos el teletransporte
		player->TeleportTo(destination);
	}
}

void Teleporter::Draw(CL_Rect area)
{
	surfaceTeleporter.draw(area);
}