#include "Mushroom.h"

CMushroom::CMushroom(float x, float y) :CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
	this->ax = 0;
	this->ay = 0;
	SetState(MUSHROOM_STATE_APPEAR);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_WIDTH / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (state == MUSHROOM_STATE_APPEAR && y < fixedY - MUSHROOM_BBOX_HEIGHT)
	{
		SetState(MUSHROOM_STATE_WALKING);
	}
	if (state == MUSHROOM_STATE_UNACTIVE)
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_MUSHROOM_RED)->Draw(x, y);

	/*RenderBoundingBox();*/
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_APPEAR:
		isCollidable = 0;
		vx = 0;
		vy = MUSHROOM_APPEAR_SPEED;
		break;
	case MUSHROOM_STATE_WALKING:
		isCollidable = 1;
		vx = MUSHROOM_WALKING_SPEED;
		vy = 0;
		ay = MUSHROOM_GRAVITY;
		break;
	case MUSHROOM_STATE_UNACTIVE:
		isDeleted = true;
		break;
	default:
		break;
	}
}

void CMushroom::IsAbsorbed()
{
	SetState(MUSHROOM_STATE_UNACTIVE);
}