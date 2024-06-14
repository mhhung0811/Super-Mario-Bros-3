#pragma once
#include "GameObject.h"
#include "PlayScene.h"

class CSpawner : public CGameObject
{
protected:
	float bboxWidth;
	float bboxHeight;

	float isTriggered;

	vector<int> ids;
	vector<float> coordinateX;
	vector<float> coordinateY;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CSpawner(float x, float y, float bboxWidth, float bboxHeight, vector<int> ids, vector<float> coordinateX, vector<float> coordinateY);
	void Spawn();
};