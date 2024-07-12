#pragma once
#include "Mushroom.h"

class CMushroomGreen : public CMushroom
{
public:
	CMushroomGreen(float x, float y) : CMushroom(x, y)
	{
		point = 10000;
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_MUSHROOM_GREEN)->Draw(x, y);
	}
};