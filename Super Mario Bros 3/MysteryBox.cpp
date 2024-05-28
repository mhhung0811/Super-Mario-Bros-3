#include "MysteryBox.h"
#include "Mario.h"
#include "debug.h"

CMysteryBox::CMysteryBox(float x, float y) : CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
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
	vy += ay * dt;
	vx += ax * dt;

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

void CMysteryBox::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	if (y < fixedY + 1)
	{
		ay = MYSTERYBOX_GRAVITY;
	}
	if (y > fixedY)
	{
		ay = 0;
		vy = 0;
		y = fixedY;
	}
}

void CMysteryBox::SetState(int state)
{
	CGameObject::SetState(state);
}

void CMysteryBox::OpenBox()
{
	if (state == MYSTERYBOX_STATE_ACTIVE)
	{
		ay = -0.005f;
		SetState(MYSTERYBOX_STATE_UNACTIVE);		
	}
}