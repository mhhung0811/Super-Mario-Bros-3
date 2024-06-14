#include "FlyGoomba.h"

CFlyGoomba::CFlyGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = FLY_GOOMBA_GRAVITY;
	die_start = -1;
	SetState(FLY_GOOMBA_STATE_WALKING);
}

void CFlyGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLY_GOOMBA_STATE_DIE)
	{
		left = x - FLY_GOOMBA_BBOX_WIDTH / 2;
		top = y - FLY_GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + FLY_GOOMBA_BBOX_WIDTH;
		bottom = top + FLY_GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - FLY_GOOMBA_BBOX_WIDTH / 2;
		top = y - FLY_GOOMBA_BBOX_HEIGHT / 2;
		right = left + FLY_GOOMBA_BBOX_WIDTH;
		bottom = top + FLY_GOOMBA_BBOX_HEIGHT;
	}
}

void CFlyGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFlyGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFlyGoomba*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CFlyGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == FLY_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > FLY_GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlyGoomba::Render()
{
	int aniId = ID_ANI_FLY_GOOMBA_WALKING;
	if (state == FLY_GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_FLY_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFlyGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLY_GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (FLY_GOOMBA_BBOX_HEIGHT - FLY_GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case FLY_GOOMBA_STATE_WALKING:
		vx = -FLY_GOOMBA_WALKING_SPEED;
		break;
	}
}
