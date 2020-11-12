
#include "../Commons/config.h"

struct Player{
	int32_t id;
	int32_t role;
	int32_t status;

	float posx;
	float posy;
	float posz;

	float facex;
	float facey;
	float facez;

	int64_t timestamp;
};


class PlayerMgr {

public :
	std::map<int,Player > m_players;
	PlayerMgr() {

	};


	~PlayerMgr() {
		m_players.clear();
	};


	int32_t applyOp(Message msg){
		//先检测是否有该玩家,没有就创建
		if (m_players.count(msg.id()) <=0 ){
			Player newPlayer;
			newPlayer.id = msg.id();
			newPlayer.role = msg.role();
			newPlayer.status = msg.status();
			newPlayer.posx = msg.posx();
			newPlayer.posy = msg.posy();
			newPlayer.posz = msg.posz();
			newPlayer.facex = msg.facex();
			newPlayer.facey = msg.facey();
			newPlayer.facez = msg.facez();
			m_players[newPlayer.id] = newPlayer;
		} else {
			//更新
			m_players[msg.id()].status = msg.status();
			m_players[msg.id()].posx = msg.posx();
			m_players[msg.id()].posy = msg.posy();
			m_players[msg.id()].posz = msg.posz();
			m_players[msg.id()].facex = msg.facex();
			m_players[msg.id()].facey = msg.facey();
			m_players[msg.id()].facez = msg.facez();
		}
		return msg.id();
	};
};