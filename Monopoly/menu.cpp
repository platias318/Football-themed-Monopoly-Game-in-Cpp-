#include "menu.h"

menu::menu():m_width(CANVAS_WIDTH / 21),m_height(CANVAS_HEIGHT / 21)
{
	setPosX(CANVAS_WIDTH / 4.6 + 18); setPosY(CANVAS_HEIGHT / 5.8 + 18);
}

void menu::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("list.png");
	graphics::drawRect(m_pos[0],m_pos[1],m_width,m_height, br);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	if (getHighlighted() == true) {
		graphics::Brush br1;
		br1.outline_opacity = 0.0f;
		SETCOLOR(br1.fill_color, 1.0f, 1.0f, 1.0f);
		SETCOLOR(br1.fill_secondary_color, 0.5f, 0.5f, 0.2f);
		br1.gradient = true;
		br1.gradient_dir_u = 0.0f;
		br1.gradient_dir_v = 1.0f;
		br1.fill_opacity = 0.7f;
		br1.fill_secondary_opacity = 0.8f;
		graphics::drawRect(m_pos[0],m_pos[1],m_width + 28, m_height + 12, br1);
		br.texture = ASSET_PATH + std::string("list.png");
		graphics::drawRect(m_pos[0], m_pos[1],m_width + 5, m_height + 5,br);
		graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

		graphics::setFont(std::string(ASSET_PATH) + "Brick Comic.ttf");
		SETCOLOR(br1.fill_color, 0.0f, 0.0f, 0.0f);
		br1.gradient = false;
		br1.fill_opacity = 1.0f;
		graphics::drawText(m_pos[0]+ 50, m_pos[1]+ 10, 30, "MENU", br1);

	}
	if (isPressed() == true) {

		graphics::Brush br;
		SETCOLOR(br.fill_color, 0.8f, 1.02f, 0.3f);
		SETCOLOR(br.fill_secondary_color, 1.02f, 0.255f, 1.02f);
		br.gradient = true;
		br.gradient_dir_u = 0.74f;
		br.gradient_dir_v = 0.74f;
		graphics::drawRect(MAIN_MENU_X, MAIN_MENU_Y, MAIN_MENU_SIZEX, MAIN_MENU_SIZEY, br);
		graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

		if (m_select != RULES) {
			drawMenuOptions("play-button.png", "RESUME", -130, -210, br);
			drawMenuOptions("restart.png", "RESTART", -130, -90, br);
			drawMenuOptions("book.png", "RULES", -130, 40, br);
			drawMenuOptions("logout.png", "EXIT", -125, 170, br);
		}
		if (m_select == menu::menu_selection::RULES) {
			drawRules();
			return;
		}
		for (int i = 0; i <= 3; i++) {
			if (OptionsHighlighted[i] == true) {
				graphics::Brush br;
				br.outline_opacity = 0.0f;
				br.texture = ASSET_PATH + std::string("right-arrow.png");
				if (i == 0) {
					graphics::drawRect(MAIN_MENU_X - 230, MAIN_MENU_Y - 210, 110, 90, br);
				}else if (i == 1) {
					graphics::drawRect(MAIN_MENU_X - 230, MAIN_MENU_Y - 90, 110, 90, br);
				}else if (i == 2) {
					graphics::drawRect(MAIN_MENU_X - 230, MAIN_MENU_Y + 40, 110, 90, br);
				}else {
					graphics::drawRect(MAIN_MENU_X - 230, MAIN_MENU_Y + 170, 110, 90, br);
				}
				return;
			}
		}
	}
}

void menu::update()
{	
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	if (distance(m_pos[0],m_pos[1], mx, my) < 30) {
		setHighlighted(true);
	}else {
		setHighlighted(false);
	}

	if (getHighlighted() && ms.button_left_released) {
			setPressed(true);
			return;
	}
	if (isPressed()) {
		setHighlighted(false);
		graphics::MouseState ms;
		graphics::getMouseState(ms);

		if (distance(MAIN_MENU_X - 130, MAIN_MENU_Y - 210, mx, my) <90 ){
			setAllOtherOptionsFalse(0);

			if(ms.button_left_released)
				m_select = RESUME;
			return;
		}else if (distance(MAIN_MENU_X - 130, MAIN_MENU_Y -90, mx, my) <90){
			setAllOtherOptionsFalse(1);
			 if(ms.button_left_released)
				m_select = RESTART;
			 return;
		}else if (distance(MAIN_MENU_X - 130, MAIN_MENU_Y + 40, mx, my) <90) {
			setAllOtherOptionsFalse(2);
			if (ms.button_left_released)
				m_select = RULES;
			return;

		}else if (distance(MAIN_MENU_X - 130, MAIN_MENU_Y + 170, mx, my) < 90) {
			setAllOtherOptionsFalse(3);
			if(ms.button_left_released)
				m_select = EXIT;
			return;	
		}
		return;
	}
}

menu::~menu()
{
}

void menu::setAllOtherOptionsFalse(unsigned int cur_pos)
{
	for (int i = 0; i <= 3; i++) {
		if (i == cur_pos) {
			setOptionHighlighted(true, i);
			continue;
		}
		setOptionHighlighted(false, i);
	}
}

void menu::drawMenuOptions(const std::string& path_icon, const std::string& text, const float& x, const  float& Y, graphics::Brush br)
{
	SETCOLOR(br.fill_secondary_color, 0.0f, 0.0f, 0.0f);
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	br.gradient == false;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string(path_icon);
	graphics::drawRect(MAIN_MENU_X +x, MAIN_MENU_Y + Y, MAIN_MENU_SIZEX / 7, MAIN_MENU_SIZEY / 7, br);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	graphics::setFont(std::string(ASSET_PATH) + "Text.ttf");
	graphics::drawText(MAIN_MENU_X +x+50, MAIN_MENU_Y + Y+20, PLAYER_SIZE * 2, text, br);

}

void menu::drawRules() {
	graphics::Brush br;
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	br.texture= ASSET_PATH + std::string("Rules.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, MAIN_MENU_SIZEX + 45, MAIN_MENU_SIZEY + 35, br);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
}


