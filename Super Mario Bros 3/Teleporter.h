#pragma once
#include "GameObject.h"
#include "PlayScene.h"


class CTeleporter : public CGameObject
{
protected:
	float bboxWidth;
	float bboxHeight;

	float desX;
	float desY;
	bool isUp;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CTeleporter();
	CTeleporter(float x, float y, float bboxWidth, float bboxHeight, float desX, float desY, bool isUp);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	float GetDesX() { return desX; }
	float GetDesY() { return desY; }
	bool IsUp() { return isUp; }
	void Teleport();
};