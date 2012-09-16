#pragma once

#include <ClanLib/core.h>

class PlayNode;

class GameResources
{
public:
	inline static GameResources & Instance()
	{
		static bool needsInstantiate = true;
		if ( needsInstantiate )
		{
			needsInstantiate = false;
			instance = new GameResources();
		}
		return *instance;
	}

	void SetPlayNode(PlayNode *playNode);
	PlayNode & GetPlayNode();
	CL_ResourceManager & GetResourceManager();

	~GameResources(void);

private:
	static GameResources *instance;
	GameResources(void);

	PlayNode *playNode;
	CL_ResourceManager resourceManager;
};
