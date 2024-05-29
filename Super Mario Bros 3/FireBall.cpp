#include "FireBall.h"

CFireBall::CFireBall(float x, float y, int dir) : CGameObject(x, y)
{
	this->direction = dir;
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
	
}

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * FIREBALL_SPEED * dt;
	y += vy * FIREBALL_SPEED * dt;

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
}

void CFireBall::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_FIREBALL_FLY)->Render(x, y);
	RenderBoundingBox();
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