#pragma once

#include "CGameUI.h"

class CUIPow : public CGameUI
{
protected:
	bool isActive;
public:
	CUIPow(float x, float y) : CGameUI(x, y)
	{
		isActive = false;
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		if (isActive)
			s->Get(ID_SPR_UI_POW_1)->Draw(x + UI_POW_BBOX_WIDTH / 2, y);
		else
			s->Get(ID_SPR_UI_POW_0)->Draw(x + UI_POW_BBOX_WIDTH / 2, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - UI_POW_BBOX_WIDTH / 2;
		t = y - UI_POW_BBOX_HEIGHT / 2;
		r = l + UI_POW_BBOX_WIDTH;
		b = t + UI_POW_BBOX_HEIGHT;
	}
	void SetActive(bool b) { isActive = b; }
};