#include "EmptyObject.h"

CEmptyObject::CEmptyObject(float x, float y, float bboxWidth, float bboxHeight) : CGameObject(x, y)
{
	this->bboxWidth = bboxWidth;
	this->bboxHeight = bboxHeight;
}

void CEmptyObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}

void CEmptyObject::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CEmptyObject::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CEmptyObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEmptyObject::Render()
{
	RenderBoundingBox();
}