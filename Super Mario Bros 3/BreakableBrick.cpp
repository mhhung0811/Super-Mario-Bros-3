#include "BreakableBrick.h"
#include "Mario.h"
#include "debug.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include "debug.h"

CBreakableBrick::CBreakableBrick(float x, float y, int gift) : CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
	this->ax = 0;
	this->ay = 0;
	this->isOpened = 0;
	this->giftId = gift;
	this->isCoin = (giftId == BREAKABLE_BRICK_GIFT_BREAK) ? true : false;
	SetState(BREAKABLE_BRICK_STATE_ACTIVE);
}

void CBreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BREAKABLE_BRICK_BBOX_WIDTH / 2;
	top = y - BREAKABLE_BRICK_BBOX_HEIGHT / 2;
	right = left + BREAKABLE_BRICK_BBOX_WIDTH;
	bottom = top + BREAKABLE_BRICK_BBOX_HEIGHT;
}

void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	LPGAMEOBJECT player = playScene->GetPlayer();
	CMario* mario = dynamic_cast<CMario*>(player);

	if (state == BREAKABLE_BRICK_STATE_OPEN || state == BREAKABLE_BRICK_STATE_TRY_OPEN)
	{
		// break
		if (isOpened == BREAKABLE_BRICK_GIFT_BREAK)
		{
			SetState(BREAKABLE_BRICK_STATE_BREAK);
			isOpened = -1;
		}
		if (y <= (fixedY)+5)
		{
			ay = BREAKABLE_BRICK_GRAVITY;
		}
		if (y > (fixedY))
		{
			ay = 0;
			vy = 0;
			y = fixedY;
			// open mushroom/button
			if (isOpened == BREAKABLE_BRICK_GIFT_MUSHROOM)
			{
				playScene->CreateItem(OBJECT_TYPE_MUSHROOM_GREEN, x, y);
				isOpened = -1;
			}
			else if (isOpened == BREAKABLE_BRICK_GIFT_BUTTON)
			{
				playScene->CreateItem(OBJECT_TYPE_BUTTON, x, y);
				isOpened = -1;
			}

			// done open
			if (isOpened == -1)
				SetState(BREAKABLE_BRICK_STATE_UNACTIVE);
			else
				SetState(BREAKABLE_BRICK_STATE_ACTIVE);
		}
	}
	if (state == BREAKABLE_BRICK_STATE_UNACTIVE && y != fixedX - cy)
	{
		y = fixedY;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBreakableBrick::Render()
{
	int aniId = ID_ANI_BREAKABLE_BRICK_ACTIVE;
	if (state == BREAKABLE_BRICK_STATE_UNACTIVE || state == BREAKABLE_BRICK_STATE_OPEN)
	{
		aniId = ID_ANI_BREAKABLE_BRICK_UNACTIVE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBreakableBrick::RenderBoundingBox()
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

	float xx = x - BREAKABLE_BRICK_BBOX_WIDTH / 2 + (float)rect.right / 2;
	float yy = y - BREAKABLE_BRICK_BBOX_HEIGHT / 2 + (float)rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CBreakableBrick::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CBreakableBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAKABLE_BRICK_STATE_ACTIVE:
		break;
	case BREAKABLE_BRICK_STATE_OPEN:
		ay = -BREAKABLE_BRICK_SPEED;
		isOpened = giftId;
		break;
	case BREAKABLE_BRICK_STATE_TRY_OPEN:
		ay = -BREAKABLE_BRICK_SPEED;
		break;
	case BREAKABLE_BRICK_STATE_UNACTIVE:
		break;
	case BREAKABLE_BRICK_STATE_BREAK:
		isDeleted = true;
		break;
	default:
		break;
	}
}

void CBreakableBrick::OpenBox()
{
	if (state == BREAKABLE_BRICK_STATE_ACTIVE)
	{
		SetState(BREAKABLE_BRICK_STATE_OPEN);
	}
}

void CBreakableBrick::TryOpenBox()
{
	if (state == BREAKABLE_BRICK_STATE_ACTIVE)
	{
		SetState(BREAKABLE_BRICK_STATE_TRY_OPEN);
	}
}

void CBreakableBrick::ToCoin()
{
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->CreateItem(OBJECT_TYPE_COIN, x, y);
	isDeleted = true;
}