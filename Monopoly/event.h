#pragma once
#include "sgg/graphics.h"
#include <string>
class Event
{
protected:
	float m_pos_x; // x position
	float m_pos_y; // y position

	float m_duration = 2.0f;
	float m_delay = 0.0f;
	float m_elapsed_time = 0.0f;
	float m_elapsed_delay = 0.0f;
	bool m_active = true;
public:
	virtual void draw();
	virtual void update();
	virtual ~Event() {};
	bool active() { return m_active; }
	void disable() { m_active = false; }
	bool waiting();
	Event(const float& x = 0.0f,const float& y = 0.0f, const float& dur = 2.0f, const float& del = 0.0f);
};

class PlayerMotionEvent : public Event {
	class Player* m_player=nullptr;
	float m_start_x;
	float m_start_y;
	float m_stop_x;
	float m_stop_y;
public:
	void update() override;
	~PlayerMotionEvent(){};
	PlayerMotionEvent(const float&  start_x, const float& start_y, const float& end_x,const  float& end_y, class Player* p);
};

class PlayerScoreEvent : public Event {//used for the score of each player
	class Player* m_player=nullptr;
public:
	void update()override;
	void draw()override;
	~PlayerScoreEvent() {};
	PlayerScoreEvent(const float& x , const float& y,class Player* pl);
};

class GameMessages : public Event { // used for the game messages when a task is completed on the game
	class Player* m_player=nullptr; // the current player that the game message is referring to
	class GameCards* m_card = nullptr; // the current card it is being called upon
	const std::string m_message; // the message we want to be printed
public:
	void update() override;
	void draw() override;
	~GameMessages(){};
	GameMessages(class Player* pl,class GameCards* card,const std::string& Message);
};