#pragma once
#include "defines.h"
#include "GameObjects.h"
#include "sgg/graphics.h" 
class Dice : public GameObjects {
	unsigned int number; //the current number on the dice
public:
	unsigned int getNumber() { return number; }
	void setNumber(unsigned int n) { number = n; }

	Dice() {}
	~Dice() {}

	void draw() override;
	void update() override;

	void drawDiceNumber(unsigned int x);//used for drawing the dice with the current number x 
};