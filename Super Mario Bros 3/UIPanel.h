#pragma once
#include "CGameUI.h"

class CUIPanel : public CGameUI
{
protected:
	int type;
public:
	CUIPanel(float x, float y, int type) : CGameUI(x, y)
	{
		this->type = type;
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		if (type == 1)
			s->Get(ID_SPR_UI_PANEL)->Draw(x + UI_PANEL_BBOX_WIDTH / 2, y + UI_PANEL_BBOX_HEIGHT / 2);
		else if (type == 2)
			s->Get(ID_SPR_UI_PANEL_END)->Draw(x + UI_PANEL_BBOX_WIDTH / 2, y + UI_PANEL_BBOX_HEIGHT / 2);
		else if (type == 3)
			s->Get(ID_SPR_UI_PANEL_PICK)->Draw(x + UI_PANEL_PICK_BBOX_WIDTH / 2, y + UI_PANEL_PICK_BBOX_HEIGHT / 2);
		else
			s->Get(ID_SPR_UI_PANEL_DARK)->Draw(x + UI_PANEL_DARK_BBOX_WIDTH / 2, y + UI_PANEL_DARK_BBOX_HEIGHT / 2);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		int w, h;
		if (type == 1)
		{
			w = UI_PANEL_BBOX_WIDTH;
			h = UI_PANEL_BBOX_HEIGHT;
		}
		else
		{
			w = UI_PANEL_DARK_BBOX_WIDTH;
			h = UI_PANEL_DARK_BBOX_HEIGHT;
		}
		l = x - w / 2;
		t = y - h / 2;
		r = l + w;
		b = t + h;
	}
};