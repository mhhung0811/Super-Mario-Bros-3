#include "CGameUI.h"
#include "debug.h"

CGameUI::CGameUI(float x, float y) : CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
}

void CGameUI::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPR_UI_HUD)->Draw(x + UI_HUD_BBOX_WIDTH / 2, y);
}

void CGameUI::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CGameUI::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - UI_HUD_BBOX_WIDTH / 2;
	t = y - UI_HUD_BBOX_HEIGHT / 2;
	r = l + UI_HUD_BBOX_WIDTH;
	b = t + UI_HUD_BBOX_HEIGHT;
}

void CGameUI::UIUpdate(float cx, float cy)
{
	x = cx + fixedX;
	y = cy + fixedY;
}