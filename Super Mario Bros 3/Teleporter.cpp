#include "Teleporter.h"

CTeleporter::CTeleporter(float x, float y, float bboxWidth, float bboxHeight, float desX, float desY, bool isUp) : CGameObject(x, y)
{
	this->bboxWidth = bboxWidth;
	this->bboxHeight = bboxHeight;
	this->desX = desX;
	this->desY = desY;
	this->isUp = isUp;
}

void CTeleporter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}

void CTeleporter::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CTeleporter::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CTeleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTeleporter::Render()
{
	RenderBoundingBox();
}

void CTeleporter::Teleport()
{
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	LPGAMEOBJECT player = playScene->GetPlayer();
	player->SetPosition(desX, desY);
}