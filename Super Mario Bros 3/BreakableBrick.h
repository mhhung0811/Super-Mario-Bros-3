#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define BREAKABLE_BRICK_GIFT_BREAK 1
#define BREAKABLE_BRICK_GIFT_BUTTON 2
#define BREAKABLE_BRICK_GIFT_MUSHROOM 3

#define BREAKABLE_BRICK_GRAVITY 0.001f

#define BREAKABLE_BRICK_BBOX_HEIGHT 16
#define BREAKABLE_BRICK_BBOX_WIDTH 16
#define BREAKABLE_BRICK_SPEED 0.003f

#define BREAKABLE_BRICK_STATE_ACTIVE 100
#define	BREAKABLE_BRICK_STATE_OPEN 200
#define BREAKABLE_BRICK_STATE_TRY_OPEN 201
#define BREAKABLE_BRICK_STATE_UNACTIVE 300
#define BREAKABLE_BRICK_STATE_BREAK 400

#define ID_ANI_BREAKABLE_BRICK_ACTIVE 211010
#define ID_ANI_BREAKABLE_BRICK_UNACTIVE 212010

class CBreakableBrick : public CGameObject
{
protected:
	bool isCoin;

	float fixedX;
	float fixedY;
	float ax;
	float ay;
	int isOpened;
	int giftId;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void RenderBoundingBox();

	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 1; }
public:
	CBreakableBrick(float x, float y, int giftId);
	virtual void SetState(int state);
	virtual void OpenBox();
	virtual void TryOpenBox();
	bool IsCoin() { return isCoin; }
	void ToCoin();
};