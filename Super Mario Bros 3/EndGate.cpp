#include "EndGate.h"

CEndGate::CEndGate(float x, float y, float bboxWidth, float bboxHeight) : CGameObject(x, y)
{
	this->bboxWidth = bboxWidth;
	this->bboxHeight = bboxHeight;
}

void CEndGate::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}

void CEndGate::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CEndGate::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CEndGate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEndGate::Render()
{
	RenderBoundingBox();
}

void CEndGate::End()
{
	DebugOut(L"end\n");
	CGame::GetInstance()->InitiateSwitchScene(30);
}