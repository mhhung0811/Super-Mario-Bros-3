#include "MysteryBox.h"
#include "Mario.h"
#include "debug.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include "debug.h"

CMysteryBox::CMysteryBox(float x, float y, int gift) : CGameObject(x, y)
{	
	this->fixedX = x;
	this->fixedY = y;
	this->ax = 0;
	this->ay = 0;
	this->isOpened = 0;
	this->giftId = gift;
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
		y = fixedY; /*this cause bug where box drop when move screen*/
		// open mushroom
		if (isOpened == OBJECT_TYPE_MUSHROOM)
		{
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->CreateGameObject(std::to_string(isOpened) + "\t" + std::to_string(x) + "\t" + std::to_string(y));
			isOpened = 0;
		}
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
		isOpened = giftId;
	}
}