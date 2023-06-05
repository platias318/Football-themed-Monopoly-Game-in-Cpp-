#include "player.h"
#include "GameCards.h"
#include "sgg/graphics.h"
#include "game.h"

void Player::draw()
{
	graphics::Brush br;
	if (m_highlighted == true){
		br.outline_opacity = 0.0f;
		br.outline_width = 2.0f;
		SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
		graphics::drawDisk(m_pos[0], m_pos[1] + 0.8f, PLAYER_SIZE * 0.57f, br);

		SETCOLOR(br.fill_color, 1.0f,1.0f,1.0f);
		graphics::drawDisk(m_pos[0], m_pos[1] + 0.8f, PLAYER_SIZE * 0.53f, br);

		SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
		graphics::drawDisk(m_pos[0], m_pos[1] +0.8f, PLAYER_SIZE * 0.47f, br);

		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawRect(m_pos[0] +5, m_pos[1] + 30, 84, 20, br);

		SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
		graphics::setFont(std::string(ASSET_PATH) + "name.ttf");
		graphics::drawText(m_pos[0] - 30, m_pos[1] + 35, PLAYER_SIZE / 2.5, getName(), br);
	}
	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.outline_opacity=0.0f;
	br.texture = ASSET_PATH + std::string("piece.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);

}
void Player :: update()
{}
Player::Player(const std::string& name) :m_name(name){
	SETCOLOR(m_color,0.3f, RAND0TO1(), RAND0TO1());
	float mx = m_color[0];
	if (m_color[1] > mx)mx = m_color[1];
	if (m_color[2] > mx)mx = m_color[2];
	m_color[0] /= mx;
	m_color[1] /= mx;
}

bool Player::contains( const float& mx,const float& my)
{
	return distance(m_pos[0], m_pos[1], mx, my) < PLAYER_SIZE / 1.9f;
}
Player::~Player()
{}


