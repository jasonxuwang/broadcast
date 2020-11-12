#pragma once
#include <map>
#include "PlayerMgr.h"


class GameController
{
public:
	GameController() {};
	~GameController() {};

	std::map<int32_t, int32_t> m_IdSocketMap; //
	PlayerMgr playermgr; //

	void processBytes(char* in, char*out) {
		
	
	
	}; 

	void processStatus(Player& playerInfo) {

		playermgr.applyNewStatus(playerInfo);
	}
};

