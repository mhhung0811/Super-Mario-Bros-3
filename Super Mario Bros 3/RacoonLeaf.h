#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define RACOON_LEAF_GRAVITY 0.0005f
#define RACOON_LEAF_APPEAR_SPEED 0.2f
#define RACOON_LEAF_DROP_SPEED_MAX 0.01f
#define RACOON_LEAF_FLOW_SPEED_MAX 0.15f
#define RACOON_LEAF_FLOW_AC 0.0005f

#define RACOON_LEAF_BBOX_WIDTH 16
#define RACOON_LEAF_BBOX_HEIGHT 14

#define RACOON_LEAF_STATE_APPEAR 100
#define RACOON_LEAF_STATE_FLOW_LEFT 200
#define RACOON_LEAF_STATE_FLOW_RIGHT 300
#define RACOON_LEAF_STATE_UNACTIVE 400

class CRacoonLeaf : public CGameObject
{
protected:
	float fixedX, fixedY;
	float ax, ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CRacoonLeaf(float x, float y);
	virtual void SetState(int state);
	virtual void IsAbsorbed();
};