#pragma once
#include "CGameUI.h"

class CUINum : public CGameUI
{
protected:
	int num;
public:
	CUINum(float x, float y) : CGameUI(x, y)
	{
		num = 0;
	}
	void Render()
	{
		int idSpr = ID_SPR_UI_NUM_0;
		switch (num)
		{
		case 0:
			idSpr = ID_SPR_UI_NUM_0;
			break;
		case 1:
			idSpr = ID_SPR_UI_NUM_1;
			break;
		case 2:
			idSpr = ID_SPR_UI_NUM_2;
		case 3:
			idSpr = ID_SPR_UI_NUM_3;
			break;
		case 4:
			idSpr = ID_SPR_UI_NUM_4;
			break;
		case 5:
			idSpr = ID_SPR_UI_NUM_5;
			break;
		case 6:
			idSpr = ID_SPR_UI_NUM_6;
			break;
		case 7:
			idSpr = ID_SPR_UI_NUM_7;
			break;
		case 8:
			idSpr = ID_SPR_UI_NUM_8;
			break;
		case 9:
			idSpr = ID_SPR_UI_NUM_9;
			break;
		default:
			break;
		}
		CSprites* s = CSprites::GetInstance();
		s->Get(idSpr)->Draw(x + UI_NUM_BBOX_WIDTH / 2, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - UI_NUM_BBOX_WIDTH / 2;
		t = y - UI_NUM_BBOX_HEIGHT / 2;
		r = l + UI_NUM_BBOX_WIDTH;
		b = t + UI_NUM_BBOX_HEIGHT;
	}
	int GetNum() { return num; }
	void SetNum(int num) { this->num = num; }
};