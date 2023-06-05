#include "dice.h"
#include "game.h"
#include "player.h"

Game* game= Game::getInstance();
void Dice::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("RedDice.png");
	graphics::drawRect(DICE_ICON_X, DICE_ICON_Y, DICE_ICON_WIDTH, DICE_ICON_HEIGHT, br);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	if (getHighlighted() == true) {
		br.texture = ASSET_PATH + std::string("RedDice.png");
		graphics::drawRect(DICE_ICON_X, DICE_ICON_Y, DICE_ICON_WIDTH + 10, DICE_ICON_HEIGHT + 10, br);
		graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
		graphics::setFont(std::string(ASSET_PATH) + "Brick Comic.ttf");
		SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
		graphics::drawText(DICE_ICON_X + 45, DICE_ICON_Y, 20, "Tap to roll!", br);
	}
}

void Dice::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	if (distance(DICE_ICON_X, DICE_ICON_Y, mx, my) < 20) {
		setHighlighted(true);
	}
	else {
		setHighlighted(false);
	}
}

void Dice::drawDiceNumber(unsigned int x)
{
	graphics::Brush br2;
	br2.outline_opacity = 0.0f;
	br2.texture = ASSET_PATH + std::string("dice") + std::to_string(x) + std::string(".png");
	graphics::drawRect(CANVAS_WIDTH / 4.5+18, CANVAS_HEIGHT / 2.8 + 18, 67,67, br2);
}
