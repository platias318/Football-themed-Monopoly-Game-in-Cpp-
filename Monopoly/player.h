#pragma once
#include "GameObjects.h"
#include "defines.h"
#include <list>
class Player: public GameObjects {

	const std::string m_name;
	bool m_active = false; // if he is active
	float money = 700;
	unsigned int curr_table_pos = 1;//the current position he is on the table

	bool played = false; // if he has played
	bool moved = false; // if he has moved
	bool Rolled = false; // if he has rolled
public:
	Player(const std::string& name);
	~Player();

	bool Played() { return played; }
	void setPlayed(const bool& h) { played = h; }

	float getMoney() { return money; }
	void setMoney(const int& x) { money = x; }
	float m_color[3];//his color r,g,b

	int getCurrPos() { return curr_table_pos; }
	void setCurrPos(unsigned int x) { curr_table_pos = x; }

	bool isActive() { return m_active; }
	void setActive(const bool& a) { m_active = a; }
	std::string getName()const { return m_name; }

	std::list< class GameCards*> m_cards;

	bool contains(const float& mx,const float& my);

	bool hasRolled() { return Rolled; }
	void setRolled(const bool& h) { Rolled = h; }

	bool hasMoved() { return moved; }
	void setMoved(const bool& h) { moved = h; }


	void draw() override;
	void update()override;
};