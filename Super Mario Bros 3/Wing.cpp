#include "Wing.h"

CWing::CWing(float x, float y, int dir) : CGameObject(x, y)
{
	this->dir = dir;
	this->vx = 0;
	this->vy = 0;
	SetState(WING_STATE_CLOSE);
}

void CWing::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - WING_BBOX_WIDTH / 2;
	top = y - WING_BBOX_HEIGHT / 2;
	right = left + WING_BBOX_WIDTH;
	bottom = top + WING_BBOX_HEIGHT;
}

void CWing::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CWing::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CWing::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CWing::Render()
{
	int aniId = ID_ANI_WING_CLOSE_LEFT;
	switch (state)
	{
	case WING_STATE_CLOSE:
		aniId = (dir < 0) ? ID_ANI_WING_CLOSE_LEFT : ID_ANI_WING_CLOSE_RIGHT;
		break;
	case WING_STATE_FLAP_SLOW:
		aniId = (dir < 0) ? ID_ANI_WING_FLAP_SLOW_LEFT : ID_ANI_WING_FLAP_SLOW_RIGHT;
		break;
	case WING_STATE_FLAP_FAST:
		aniId = (dir < 0) ? ID_ANI_WING_FLAP_FAST_LEFT : ID_ANI_WING_FLAP_FAST_RIGHT;
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	/*RenderBoundingBox();*/
}

void CWing::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WING_STATE_CLOSE:
		break;
	case WING_STATE_FLAP_SLOW :
		break;
	case WING_STATE_FLAP_FAST:
		break;
	default:
		break;
	}
}