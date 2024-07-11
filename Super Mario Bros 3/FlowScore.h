#pragma once

#include "GameObject.h"
#include "AssetIDs.h"

#define FLOW_SCORE_SPEED 0.05f
#define FLOW_SCORE_APPEAR_TIME 500

#define FLOW_SCORE_BBOX_WIDTH 14
#define FLOW_SCORE_BBOX_HEIGHT 8

#define FLOW_SCORE_100 0
#define FLOW_SCORE_200 1
#define FLOW_SCORE_400 2
#define FLOW_SCORE_800 3
#define FLOW_SCORE_1000 4
#define FLOW_SCORE_2000 5
#define FLOW_SCORE_4000 6
#define FLOW_SCORE_8000 7
#define FLOW_SCORE_1UP 8

#define FLOW_SCORE_STATE_APPEAR 100
#define FLOW_SCORE_STATE_DISAPPEAR 200

class CFlowScore : public CGameObject
{
protected:
	float ay;

	int scoreId;
	int appearTimer;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
public:
	CFlowScore(float x, float y, int scoreId);
	virtual void SetState(int state);
};

