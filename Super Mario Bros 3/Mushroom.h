#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_APPEAR_SPEED -0.02f
#define	MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_BBOX_WIDTH	16
#define MUSHROOM_BBOX_HEIGHT 14

#define MUSHROOM_STATE_APPEAR 100
#define MUSHROOM_STATE_WALKING 200
#define MUSHROOM_STATE_UNACTIVE	300

class CMushroom : public CGameObject
{
protected:
	float fixedX;
	float fixedY;

	int point;

	float ax;
	float ay;
	int isCollidable = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return isCollidable; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CMushroom(float x, float y);
	virtual void SetState(int state);
	virtual void IsAbsorbed();
	int GetPoint()
	{
		int res = point;
		point = 0;
		return res;
	}
};