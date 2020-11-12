#pragma once
#include <map>
#include "Player.h"

#define MAX_PLAYER 64

class PlayerMgr
{

public:
	PlayerMgr() {
		m_Players = std::map<int, Player>();
	};

	~PlayerMgr() {
		m_Players.clear();
	};

	std::map<int, Player> m_Players; 


	int32_t applyNewStatus(const struct Player& newstat) {
		m_Players[newstat.id] = newstat;
	};
};

