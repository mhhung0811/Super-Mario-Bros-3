#pragma once
#pragma once

#include "GameObject.h"
#include "PlayScene.h"
#include "AssetIDs.h"

#define FLOW_COIN_SPEED_MAX 0.2f
#define FLOW_COIN_ACCEL 0.002f
#define FLOW_COIN_APPEAR_TIME 1000
#define FLOW_COIN_MAX_HEIGHT 48

#define FLOW_COIN_BBOX_WIDTH 8
#define FLOW_COIN_BBOX_HEIGHT 8

#define FLOW_COIN_STATE_APPEAR 100
#define FLOW_COIN_STATE_DROP 200
#define FLOW_COIN_STATE_DISAPPEAR 300

#define ID_ANI_FLOW_COIN 11001

class CFlowCoin : public CGameObject
{
protected:
	float fixedY;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
public:
	CFlowCoin(float x, float y);
	virtual void SetState(int state);
};

