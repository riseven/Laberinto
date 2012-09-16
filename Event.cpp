#include "Event.h"

Event::Event(void)
{
	consumed = false;
}

Event::~Event(void)
{
}

bool Event::IsConsumed()
{
	return consumed;
}

void Event::Consume()
{
	consumed= true;
}
