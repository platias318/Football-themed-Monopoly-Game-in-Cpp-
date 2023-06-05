#include "GameCards.h"
#include "player.h"
#include <string>
void GameCards::update() {

}
void GameCards::draw() {
	graphics::Brush br;
	if (m_owner) {
		SETCOLOR(br.fill_color, m_owner->m_color[0], m_owner->m_color[1], m_owner->m_color[2]);
		br.outline_opacity = 0.0f;
		br.texture = ASSET_PATH + std::string("piece.png");
		if (number >= 1 && number<= 7) {// drawing the owner of each card 
			graphics::drawRect(m_pos[0] + 110, m_pos[1] - 3, 20, 20, br);
		}else if (number >= 8 && number <= 13){
			graphics::drawRect(m_pos[0], m_pos[1] - 60, 20, 20, br);
		}else if (number >= 14 && number <= 18) {
			graphics::drawRect(m_pos[0]-88, m_pos[1], 20, 20, br);
		}else {
			graphics::drawRect(m_pos[0] , m_pos[1]+88, 20, 20, br);
		}
	}

}
GameCards::GameCards(const std::string& Club, Color color, const float& buyPrice, const float& rent, const float& pos_x, const float& pos_y, const int& num) :
	m_name(Club), m_color(color), m_buyPrice(buyPrice), m_rent(rent),number(num) {
	setPosX(pos_x); setPosY(pos_y);
}

GameCards::~GameCards()
{	}
