#include "Spawner.h"

CSpawner::CSpawner(float x, float y, float bboxWidth, float bboxHeight, vector<int> ids, vector<float> coordinateX, vector<float> coordinateY) : CGameObject(x, y)
{
	this->isTriggered = false;
	this->bboxWidth = bboxWidth;
	this->bboxHeight = bboxHeight;
	this->ids = ids;
	this->coordinateX = coordinateX;
	this->coordinateY = coordinateY;
}

void CSpawner::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}

void CSpawner::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CSpawner::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CSpawner::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CSpawner::Render()
{
	RenderBoundingBox();
}

void CSpawner::Spawn()
{
	if (isTriggered == true) return;
	isTriggered = true;
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	for (int i = 0; i < ids.size(); i++)
	{
		playScene->SpawnMonster(ids[i], coordinateX[i], coordinateY[i]);
	}
}