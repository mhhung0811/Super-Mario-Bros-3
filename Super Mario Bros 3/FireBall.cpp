#include "FireBall.h"

CFireBall::CFireBall(float x, float y, int dir) : CGameObject(x, y)
{
	this->direction = dir;
	switch (direction)
	{
	case FIREBALL_DIRECTION_LEFT_LOW_0:
		vx = -1;
		vy = 1;
		break;
	case FIREBALL_DIRECTION_LEFT_LOW_1:
		vx = -5 / sqrtf(29);
		vy = 2 / sqrtf(29);
		break;
	case FIREBALL_DIRECTION_LEFT_HIGH_0:
		vx = -1;
		vy = -1;
		break;
	case FIREBALL_DIRECTION_LEFT_HIGH_1:
		vx = -5 / sqrtf(29);
		vy = -2 / sqrtf(29);
		break;
	case FIREBALL_DIRECTION_RIGHT_LOW_0:
		vx = 1;
		vy = 1;
		break;
	case FIREBALL_DIRECTION_RIGHT_LOW_1:
		vx = 5 / sqrtf(29);
		vy = 2 / sqrtf(29);
		break;
	case FIREBALL_DIRECTION_RIGHT_HIGH_0:
		vx = 1;
		vy = -1;
		break;
	case FIREBALL_DIRECTION_RIGHT_HIGH_1:
		vx = 5 / sqrtf(29);
		vy = -2 / sqrtf(29);
		break;
	default:
		vx = 0;
		vy = 0;
		break;
	}
	vx *= FIREBALL_SPEED;
	vy *= FIREBALL_SPEED;
}

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_BBOX_WIDTH / 2;
	top = y - FIREBALL_BBOX_HEIGHT / 2;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::OnNoCollision(DWORD dt)
{
	// Better put x, y modification here

	x += vx * dt;
	y += vy * dt;
}

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_FIREBALL_FLY)->Render(x, y);
	/*RenderBoundingBox();*/
}

void CFireBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBALL_STATE_FLYING:
		break;
	case FIREBALL_STATE_VANISH:
		break;
	default:
		break;
	}
}