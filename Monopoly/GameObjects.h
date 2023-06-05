#pragma once

class GameObjects{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	float m_pos[2];
	bool m_highlighted = false;
	bool m_pressed = false;
	inline float getPosX() { return m_pos[0]; }//returns his position on x
	inline float getPosY() { return  m_pos[1]; }//returns his position on y
    inline void  setPosX(const float& x) { m_pos[0] = x; }//sets his posotion x tou X
	inline void setPosY(const float& y) { m_pos[1] = y; }//sets his position y to Y
	inline void setHighlighted(const bool& h) { m_highlighted = h; }
	inline bool getHighlighted() {	return m_highlighted;}
	inline void setPressed(const bool& h) { m_pressed = h; }
	inline bool isPressed() { return m_pressed; }
	virtual ~GameObjects() {};
};