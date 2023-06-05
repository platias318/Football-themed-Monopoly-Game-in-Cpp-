#include "button.h"
#include "sgg/graphics.h"
#include "defines.h"

void button::draw()
{
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		br.texture = ASSET_PATH + std::string(m_picture);
		if (!m_highlighted) {
			graphics::drawRect(m_pos[0], m_pos[1], m_width, m_height, br);
		}else{
			if (!m_pressed) {
				graphics::drawRect(m_pos[0], m_pos[1], m_width + m_extra_size, m_height + m_extra_size, br);
			}
			else{
				graphics::drawRect(m_pos[0], m_pos[1], m_width, m_height, br);
			}
		}
	return;
}

void button::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	if (distance(m_pos[0], m_pos[1], mx, my) < 50) {
		m_highlighted = true;
	}
	else {
		m_highlighted = false;
	}
	if (m_highlighted && ms.button_left_released) {
		setPressed(true);
		return;
	}
	else {
		setPressed(false);
		return;
	}

}
button::button(const float& mx, const float& my, const float& width, const float& height, const float& extra_size, const std::string& picture)
	:m_width(width), m_height(height),m_picture(picture),m_extra_size(extra_size)
{
	setPosX(mx); setPosY(my);
}

button::~button()
{
}
