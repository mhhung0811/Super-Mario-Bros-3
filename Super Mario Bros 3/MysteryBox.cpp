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
	left = x - MYSTERYBOX_BBOX_WIDTH / 2;
	top = y - MYSTERYBOX_BBOX_HEIGHT / 2;
	right = left + MYSTERYBOX_BBOX_WIDTH;
	bottom = top + MYSTERYBOX_BBOX_HEIGHT;
}

void CMysteryBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	LPGAMEOBJECT player = playScene->GetPlayer();
	CMario* mario = dynamic_cast<CMario*>(player);

	if (state == MYSTERYBOX_STATE_OPEN)
	{
		if (y <= (fixedY - cy) + 5)
		{
			ay = MYSTERYBOX_GRAVITY;
		}
		if (y > (fixedY - cy))
		{
			ay = 0;
			vy = 0;
			y = fixedY - cy;
			// open mushroom
			if (isOpened == MYSTERYBOX_GIFT_LEVELUP)
			{
				if (mario->GetLevel() == MARIO_LEVEL_SMALL) playScene->CreateItem(OBJECT_TYPE_MUSHROOM, x, y);
				if (mario->GetLevel() == MARIO_LEVEL_BIG) playScene->CreateItem(OBJECT_TYPE_RACOONLEAF, x, y);
			}
			// done open
			isOpened = 0;
			SetState(MYSTERYBOX_STATE_UNACTIVE);
		}
	}
	if (state == MYSTERYBOX_STATE_UNACTIVE && y != fixedX - cy)
	{
		y = fixedY - cy;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMysteryBox::Render()
{
	int aniId = ID_ANI_MYSTERYBOX_ACTIVE;
	if (state == MYSTERYBOX_STATE_UNACTIVE || state == MYSTERYBOX_STATE_OPEN)
	{
		aniId = ID_ANI_MYSTERYBOX_UNACTIVE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMysteryBox::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - MYSTERYBOX_BBOX_WIDTH / 2 + (float)rect.right / 2;
	float yy = y - MYSTERYBOX_BBOX_HEIGHT / 2 + (float)rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CMysteryBox::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CMysteryBox::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MYSTERYBOX_STATE_ACTIVE:
		break;
	case MYSTERYBOX_STATE_OPEN:
		ay = -MYSTERYBOX_SPEED;
		isOpened = giftId;
		break;
	case MYSTERYBOX_STATE_UNACTIVE:
		break;
	default:
		break;
	}
}

void CMysteryBox::OpenBox()
{
	if (state == MYSTERYBOX_STATE_ACTIVE)
	{
		SetState(MYSTERYBOX_STATE_OPEN);
	}
}