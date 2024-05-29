#include "PiranhaPlant.h"
#include "Textures.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
	this->isIdle = 0;
	SetState(PIRANHAPLANT_STATE_IDLE);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHAPLANT_BBOX_WIDTH / 2;
	top = y - PIRANHAPLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHAPLANT_BBOX_WIDTH;
	bottom = top + PIRANHAPLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::RenderBoundingBox()
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

	float xx = x - PIRANHAPLANT_BBOX_WIDTH / 2 + (float)rect.right / 2;
	float yy = y - PIRANHAPLANT_BBOX_HEIGHT / 2 + (float)rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	if (state == PIRANHAPLANT_STATE_APPEAR && y <= (fixedY - cy)-PIRANHAPLANT_BBOX_HEIGHT)
	{
		SetState(PIRANHAPLANT_STATE_IDLE);
	}
	if (state == PIRANHAPLANT_STATE_DISAPPEAR && y >= (fixedY - cy))
	{
		SetState(PIRANHAPLANT_STATE_IDLE);
	}
	if (state == PIRANHAPLANT_STATE_IDLE)
	{
		if (isIdle > PIRANHAPLANT_IDLE_TIME)
		{
			isIdle = 0;
			if (y < (fixedY - cy))
			{
				SetState(PIRANHAPLANT_STATE_DISAPPEAR);
			}
			else
			{
				SetState(PIRANHAPLANT_STATE_APPEAR);
			}
		}
		else
		{
			isIdle += dt;
		}
	}
	/*DebugOut(L"idle time: %d\n", isIdle);
	DebugOut(L"state: %d\n", state);*/
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
	CSprites* s = CSprites::GetInstance();
	int aniId = ID_ANI_PIRANHAPLANT_APPEAR_LEFT;
	if (state == PIRANHAPLANT_STATE_IDLE)
	{
		s->Get(ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_LEFT_UP + 1)->Draw(x, y);
	}
	else
	{
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}

	RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHAPLANT_STATE_APPEAR:
		vy = -PIRANHAPLANT_APPEAR_SPEED;
		break;
	case PIRANHAPLANT_STATE_DISAPPEAR:
		vy = PIRANHAPLANT_APPEAR_SPEED;
		break;
	case PIRANHAPLANT_STATE_IDLE:
		vy = 0;
		break;
	default:
		break;
	}
}