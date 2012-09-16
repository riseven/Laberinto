#pragma once

class Event
{
public:
	Event(void);
	~Event(void);
	void Consume();
	bool IsConsumed();

private:
	bool consumed;
};
