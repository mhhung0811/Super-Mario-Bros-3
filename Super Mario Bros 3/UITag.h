#pragma once
#include "CGameUI.h"

class CUITag : public CGameUI
{
public:
	CUITag(float x, float y) : CGameUI(x, y)
	{

	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPR_UI_TAG)->Draw(x + UI_TAG_BBOX_WIDTH / 2, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - UI_TAG_BBOX_WIDTH / 2;
		t = y - UI_TAG_BBOX_HEIGHT / 2;
		r = l + UI_TAG_BBOX_WIDTH;
		b = t + UI_TAG_BBOX_HEIGHT;
	}
};