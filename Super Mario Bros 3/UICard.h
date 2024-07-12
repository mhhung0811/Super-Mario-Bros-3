#pragma once
#include "CGameUI.h"

class CUICard : public CGameUI
{
public:
	CUICard(float x, float y) : CGameUI(x, y)
	{

	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPR_UI_CARD)->Draw(x + UI_CARD_BBOX_WIDTH / 2, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - UI_CARD_BBOX_WIDTH / 2;
		t = y - UI_CARD_BBOX_HEIGHT / 2;
		r = l + UI_CARD_BBOX_WIDTH;
		b = t + UI_CARD_BBOX_HEIGHT;
	}
};