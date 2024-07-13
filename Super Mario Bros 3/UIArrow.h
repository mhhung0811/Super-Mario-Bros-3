#pragma once
#include "CGameUI.h"

class CUIArrow : public CGameUI
{
protected:
	bool isActive;
public:
	CUIArrow(float x, float y) : CGameUI(x, y)
	{
		isActive = false;
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		if (isActive)
			s->Get(ID_SPR_UI_ARROW_1)->Draw(x + UI_ARROW_BBOX_WIDTH / 2, y);
		else
			s->Get(ID_SPR_UI_ARROW_0)->Draw(x + UI_ARROW_BBOX_WIDTH / 2, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - UI_CARD_BBOX_WIDTH / 2;
		t = y - UI_CARD_BBOX_HEIGHT / 2;
		r = l + UI_CARD_BBOX_WIDTH;
		b = t + UI_CARD_BBOX_HEIGHT;
	}
	void SetActive(bool b) { isActive = b; }
};