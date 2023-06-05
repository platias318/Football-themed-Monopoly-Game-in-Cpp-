#include "SpecialCards.h"

void SpecialCards::draw()
{
}

void SpecialCards::update()
{
}

SpecialCards::SpecialCards(specialty spec, int payer, int num,float pos_x , float pos_y) :m_specialty(spec), pay(payer){
	number = num; setPosX(pos_x); setPosY(pos_y);
}


SpecialCards::SpecialCards(specialty spec, int num, float pos_x, float pos_y) : m_specialty(spec), pay(0) {
	number = num; setPosX(pos_x); setPosY(pos_y);

}

SpecialCards::~SpecialCards()
{
}
