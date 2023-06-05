#pragma once
#include "sgg/graphics.h"
#include "defines.h"
#include <list>
#include "GameObjects.h"

class GameCards : public  GameObjects {
public:
	enum Color{green,yellow,red,blue,orange};
protected:
	const unsigned int number; // the specific number on the card(where it is placed on the table)-used for finding reasons
	const Color m_color; // the color of the card on the table
	const std::string m_name; // the name of the club-card

	const float m_buyPrice; // the price to buy the card
	const float m_rent; // the price someone pays the owner when he steps on to the card
	class Player* m_owner = nullptr;  // the owner of the card, if there isnt one he is null
	
public:
	std::list<class Player*>PlayersOn;//the players currently sitting on the card

	std::string getName()const{ return m_name; }
	int getNum()const { return number; };

	void setOwner(Player* p) { m_owner = p; }
	Player* getOwner() { return m_owner; }

	float getPrice()const { return m_buyPrice; }
	float getRent()const { return m_rent; }

	void draw()override;
	void update()override;

	GameCards(const std::string& Club, Color color,const float& buyPrice,const float& rent,const float& pos_x,const float& pos_y,const int& num);
	GameCards();
	~GameCards();
};