#pragma once
#include "GameObjects.h"
#include <string>
class button : public GameObjects {
	const float m_width; //the width of the button for drawing
	const float m_height; //the height of the button for drawing
	const float m_extra_size; //the size of the button when its hightlighted
	const std::string m_picture; // the picture that will be drawn
public:
	void draw() override;
	void update()override;
	button(const float& mx,const float& my,const float& width,const float& height ,const float& extra_size,const std::string& picture);
	~button();
};
