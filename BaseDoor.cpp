#include "BaseDoor.h"

#include "GameResources.h"

#include "ClanLib/display.h"

BaseDoor::BaseDoorAction::BaseDoorAction(std::string source, std::string action, std::string result)
{
	this->source = source;
	this->action = action;
	this->result = result;
}

bool BaseDoor::BaseDoorAction::CheckAction(std::string source, std::string action)
{
	return this->source == source && this->action == action;
}

std::string BaseDoor::BaseDoorAction::GetResult()
{
	return result;
}

BaseDoor::BaseDoor(CL_DomNode xmlInfo):
	surfaceDoorOpen("tiles/doorOpen", &GameResources::Instance().GetResourceManager()),
	surfaceDoorClosed("tiles/doorClosed", &GameResources::Instance().GetResourceManager())
{
	std::stringstream caster;

	caster << xmlInfo.get_attributes().get_named_item("id").get_node_value() << " " ;
	caster << xmlInfo.get_attributes().get_named_item("x").get_node_value() << " " ;
	caster << xmlInfo.get_attributes().get_named_item("y").get_node_value() << " " ;
	caster << xmlInfo.get_attributes().get_named_item("state").get_node_value() << " " ;
	caster << xmlInfo.get_attributes().get_named_item("direction").get_node_value() << " " ;

	std::string state, direction;
	caster >> id >> position.x >> position.y >> state >> direction;
	caster.clear();
	
	isOpen = (state == "open") ;
	isHorizontal = (direction == "horizontal") ;

	// Ahora leemos las acciones
	CL_DomNode actionNode = xmlInfo.get_first_child();
	while ( ! actionNode.is_null() )
	{		
		caster << actionNode.get_attributes().get_named_item("source").get_node_value() << " ";
		caster << actionNode.get_attributes().get_named_item("action").get_node_value() << " ";
		caster << actionNode.get_attributes().get_named_item("result").get_node_value() << " ";

		std::string source, action, result;
		caster >> source >> action >> result ;
		caster.clear();

		actions.push_back( BaseDoorAction(source, action, result) );

		actionNode = actionNode.get_next_sibling();
	}
}

BaseDoor::~BaseDoor(void)
{
}

bool BaseDoor::IsPassable()
{
	return isOpen;
}

bool BaseDoor::ReceiveAction(GameObject *source, std::string action)
{
	bool consumed = false;

	for ( std::list<BaseDoorAction>::iterator i = actions.begin() ;
		i != actions.end();
		++i)
	{
		if ( (*i).CheckAction(source->GetId(), action) )
		{
			std::string result = (*i).GetResult();
			if ( result == "change" )
			{
				isOpen = !isOpen;
			}
			else if ( result == "open" )
			{
				isOpen = true;
			}
			else if ( result == "close" )
			{
				isOpen = false;
			}
			else
			{
				throw CL_Error("Fatal error: Xml should have been checked");
			}
			consumed = true;
		}
	}

	return consumed;
}


void BaseDoor::Update()
{
}

void BaseDoor::Draw(CL_Rect area)
{
	if ( isOpen )
	{
		surfaceDoorOpen.draw(area);
	}
	else
	{
		surfaceDoorClosed.draw(area);
	}
}