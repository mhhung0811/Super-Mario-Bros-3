#include "RacoonLeaf.h"

CRacoonLeaf::CRacoonLeaf(float x, float y) : CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
	this->ax = 0;
	this->ay = 0;
	SetState(RACOON_LEAF_STATE_APPEAR);
}

void CRacoonLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - RACOON_LEAF_BBOX_WIDTH / 2;
	top = y - RACOON_LEAF_BBOX_HEIGHT / 2;
	right = left + RACOON_LEAF_BBOX_WIDTH;
	bottom = top + RACOON_LEAF_BBOX_HEIGHT;
}

void CRacoonLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CRacoonLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CRacoonLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (vy > RACOON_LEAF_DROP_SPEED_MAX) vy = RACOON_LEAF_DROP_SPEED_MAX;
	else vy += ay * dt;
	vx += ax * dt;

	if (vx >= RACOON_LEAF_FLOW_SPEED_MAX || vx <= -RACOON_LEAF_FLOW_SPEED_MAX)
	{
		ax = -ax;
	}
	if (x < fixedX && vx < 0)
	{
		vx = 0;
		ax = RACOON_LEAF_FLOW_AC;
	}
	if (x > fixedX + RACOON_LEAF_BBOX_WIDTH * 3 && vx > 0)
	{
		vx = 0;
		ax = -RACOON_LEAF_FLOW_AC;
	}

	if (state == RACOON_LEAF_STATE_APPEAR && y < fixedY - RACOON_LEAF_BBOX_HEIGHT * 3)
	{
		ax = RACOON_LEAF_FLOW_AC;
		SetState(RACOON_LEAF_STATE_FLOW_RIGHT);
	}
	if (state == RACOON_LEAF_STATE_FLOW_RIGHT && vx < 0)
	{
		SetState(RACOON_LEAF_STATE_FLOW_LEFT);
	}
	if (state == RACOON_LEAF_STATE_FLOW_LEFT && vx > 0)
	{
		SetState(RACOON_LEAF_STATE_FLOW_RIGHT);
	}

	if (y > 250)
	{
		SetState(RACOON_LEAF_STATE_UNACTIVE);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRacoonLeaf::Render()
{
	CSprites* s = CSprites::GetInstance();
	if (state == RACOON_LEAF_STATE_FLOW_RIGHT)
		s->Get(ID_SPRITE_RACOONLEAF_RIGHT)->Draw(x, y);
	else s->Get(ID_SPRITE_RACOONLEAF_LEFT)->Draw(x, y);

	//RenderBoundingBox();
}

void CRacoonLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case RACOON_LEAF_STATE_APPEAR:
		vy = -RACOON_LEAF_APPEAR_SPEED;
		break;
	case RACOON_LEAF_STATE_FLOW_LEFT:
		vy = 0;
		ay = RACOON_LEAF_GRAVITY;
		break;
	case RACOON_LEAF_STATE_FLOW_RIGHT:
		vy = 0;
		ay = RACOON_LEAF_GRAVITY;
		break;
	case RACOON_LEAF_STATE_UNACTIVE:
		isDeleted = true;
		break;
	default:
		break;
	}
}

void CRacoonLeaf::IsAbsorbed()
{
	SetState(RACOON_LEAF_STATE_UNACTIVE);
}