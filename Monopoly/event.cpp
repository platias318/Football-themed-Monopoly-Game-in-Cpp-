#include "event.h"
#include "player.h"
#include "GameCards.h"


void Event::draw()
{}

void Event::update()
{
	if (!m_active) { return; }
	if (waiting()) {
		m_elapsed_delay += graphics::getDeltaTime() / 1000.0f;
		return;
	}
	m_elapsed_time += graphics::getDeltaTime() / 1000.0f;
	if (m_elapsed_time > m_duration) {
		m_active = false;
	}
}

bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}

Event::Event(const float& x, const float& y, const float& dur,const  float& del)
	:m_pos_x(x), m_pos_y(y), m_duration(dur), m_delay(del)
{}


void PlayerMotionEvent::update(){
	Event::update();
	if (!m_player) {
		m_active = false;
		return;
	}
	if (waiting()) {
		return;
	}
	float s = m_elapsed_time / m_duration;
	float x = m_start_x * (1.0f - s) + m_stop_x * s;
	float y = m_start_y * (1.0f - s) + m_stop_y * s;
	m_player->setPosX(x);
	m_player->setPosY(y);
}

PlayerMotionEvent::PlayerMotionEvent(const float& start_x, const float& start_y, const float& end_x, const  float& end_y, class Player* p)
	:Event(0.0f, 0.0f, 1.0f, 0.0f), m_start_x(start_x), m_stop_x(end_x),m_start_y(start_y),m_stop_y(end_y),m_player(p)
{}





void PlayerScoreEvent::update()
{
	Event::update();
	if (!m_player) {
		m_active = false;
		return;
	}
	if (waiting()) {
		return;
	}
}

void PlayerScoreEvent::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("ScoreBoard.png");
	graphics::drawRect(m_pos_x+110, m_pos_y+30, 750, 200, br);
	
	SETCOLOR(br.fill_color,1.19f, 1.04f, 1.04f);
	graphics::setFont(ASSET_PATH + std::string("Aroma.ttf"));
	graphics::drawText(m_pos_x+80, m_pos_y, 25,std::string(m_player->getName()), br);
	char info[40];
	sprintf_s(info,"%.2lf", m_player->getMoney());
	graphics::drawText(m_pos_x+40, m_pos_y+30, 25, std::string("Money : ") + info, br);
}

PlayerScoreEvent::PlayerScoreEvent(const float& x ,const float& y,Player* pl)
	:Event(x,y,2.0f,0.0f),  m_player(pl)
{}

void GameMessages::update()
{
	Event::update();
	if (!m_player) {
		m_active = false;
		return;
	}
	if (waiting()) {
		return;
	}
}

void GameMessages::draw()
{
	graphics::Brush br;
	br.outline_opacity = 1.0f;
	SETCOLOR(br.outline_color, 0.0f, 0.0f, 0.0f);
	br.fill_opacity = 0.95f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 0.8f);
	graphics::drawRect(m_pos_x, m_pos_y,600, 50, br);
	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	graphics::setFont(ASSET_PATH + std::string("Aroma.ttf"));
	graphics::drawText(m_pos_x-150, m_pos_y,25,m_message,br); 

}
GameMessages::GameMessages(Player* pl, GameCards* card,const std::string& message)
	:Event(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 5.5, 2.0f, 0.0f), m_player(pl),m_card(card),m_message(message)
{}

