#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "Textures.h"
#include "Utils.h"
#include "Mario.h"
#include "FireBall.h"
#include "PlayScene.h"
#include "debug.h"

#define PIRANHAPLANT_BBOX_WIDTH 16
#define PIRANHAPLANT_BBOX_HEIGHT 31
#define PIRANHAPLANT_SHOOT_BOX_WIDTH 48
#define PIRANHAPLANT_SHOOT_BOX_HEIGHT 64

#define ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0 0
#define ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1 1
#define ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0 2
#define ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1 3
#define ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0 4
#define ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1 5
#define ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0 6
#define ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1 7
#define ID_PIRANHAPLANT_SAFE_BOX 8

#define PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0_X -48
#define PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0_Y 24
#define PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1_X -96
#define PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1_Y 24
#define PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0_X -48
#define PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0_Y -46
#define PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1_X -96
#define PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1_Y -46

#define PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0_X 48
#define PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0_Y 24
#define PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1_X 96
#define PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1_Y 24
#define PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0_X 48
#define PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0_Y -46
#define PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1_X 96
#define PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1_Y -46

#define PIRANHAPLANT_SAFE_BOX_X 0
#define PIRANHAPLANT_SAFE_BOX_Y -46

#define PIRANHAPLANT_APPEAR_SPEED 0.025f
#define PIRANHAPLANT_IDLE_TIME 1000

#define PIRANHAPLANT_STATE_IDLE 100
#define PIRANHAPLANT_STATE_APPEAR 200
#define PIRANHAPLANT_STATE_DISAPPEAR 300

#define ID_ANI_PIRANHAPLANT_APPEAR_LEFT 121100
#define ID_ANI_PIRANHAPLANT_APPEAR_RIGHT 121300

class CPiranhaPlant : public CGameObject
{
protected:
	float fixedX;
	float fixedY;
	unsigned long isIdle;
	int facingDir;	// 0: left down, 1: left up, 2: right down, 3: right up
	bool canShoot;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void RenderBoundingBox();
	void GetShootBox(int id, float& left, float& top, float& right, float& bottom);
	void RenderShootBox(int id);
	int InWhichBox(LPGAMEOBJECT obj);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }	
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CPiranhaPlant(float x, float y);
	virtual void SetState(int state);
};