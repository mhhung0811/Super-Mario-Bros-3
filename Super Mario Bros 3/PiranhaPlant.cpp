#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
	this->isIdle = 0;
	SetState(PIRANHAPLANT_STATE_DISAPPEAR);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHAPLANT_BBOX_WIDTH / 2;
	top = y - PIRANHAPLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHAPLANT_BBOX_WIDTH;
	bottom = top + PIRANHAPLANT_BBOX_HEIGHT;
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
	if (state == PIRANHAPLANT_STATE_APPEAR && y <= fixedY - PIRANHAPLANT_BBOX_HEIGHT)
	{
		SetState(PIRANHAPLANT_STATE_IDLE);
	}
	if (state == PIRANHAPLANT_STATE_DISAPPEAR && y >= fixedY)
	{
		SetState(PIRANHAPLANT_STATE_IDLE);
	}
	if (state == PIRANHAPLANT_STATE_IDLE)
	{
		if (isIdle > PIRANHAPLANT_IDLE_TIME)
		{
			isIdle = 0;
			if (y < fixedY)
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
	DebugOut(L"idle time: %d\n", isIdle);
	DebugOut(L"state: %d\n", state);
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