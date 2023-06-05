#pragma once
#include "defines.h"
#include "GameObjects.h"
#include "sgg/graphics.h"
#include <string>
class menu:public GameObjects{
public:
	enum menu_selection { UNPRESSED, RESUME, EXIT, RESTART,RULES};
private:
	bool OptionsHighlighted[4] = { false,false,false,false };//array that keeps track of which menu option is highlighted
	menu_selection m_select = UNPRESSED; // the current menu selection
	float m_width;
	float m_height;
public:
	menu();
	~menu();
	void draw() override;
	void update() override;

	void setOptionHighlighted(bool h,unsigned int i) { OptionsHighlighted[i] = h; }
	void setAllOtherOptionsFalse(unsigned int cur_pos); 

	void drawMenuOptions(const std::string& path_icon,const std::string& text,const float& x,const  float& Y,graphics::Brush br);

	inline menu_selection getMenuSelection() { return m_select; }
	inline void setMenuSelection(const menu_selection& option) { m_select = option; }
	void drawRules();
};