#include "MysteryBox.h"
#include "Mario.h"
#include "debug.h"

CMysteryBox::CMysteryBox(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	SetState(MYSTERYBOX_STATE_ACTIVE);
}

void CMysteryBox::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MYSTERYBOX_BBOX_WIDTDH / 2;
	top = y - MYSTERYBOX_BBOX_HEIGHT / 2;
	right = left + MYSTERYBOX_BBOX_WIDTDH;
	bottom = top + MYSTERYBOX_BBOX_HEIGHT;
}

void CMysteryBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMysteryBox::Render()
{
	int aniId = ID_ANI_MYSTERYBOX_ACTIVE;
	if (state == MYSTERYBOX_STATE_UNACTIVE)
	{
		aniId = ID_ANI_MYSTERYBOX_UNACTIVE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMysteryBox::SetState(int state)
{
	CGameObject::SetState(state);
}

void CMysteryBox::OpenBox()
{
	SetState(MYSTERYBOX_STATE_UNACTIVE);
}