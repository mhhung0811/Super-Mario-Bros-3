#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define MYSTERYBOX_GIFT_COIN 1
#define MYSTERYBOX_GIFT_LEVELUP 2

#define MYSTERYBOX_GRAVITY 0.001f

#define MYSTERYBOX_BBOX_HEIGHT 16
#define MYSTERYBOX_BBOX_WIDTH 16
#define MYSTERYBOX_SPEED 0.003f

#define MYSTERYBOX_STATE_ACTIVE 100
#define	MYSTERYBOX_STATE_OPEN 200
#define MYSTERYBOX_STATE_UNACTIVE 300

#define ID_ANI_MYSTERYBOX_ACTIVE 101010
#define ID_ANI_MYSTERYBOX_UNACTIVE 102010

class CMysteryBox : public CGameObject
{
protected:
	float fixedX;
	float fixedY;

	int isOpened;
	int giftId;

	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void RenderBoundingBox();

	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 1; }
public:
	CMysteryBox(float x, float y, int giftId);
	virtual void SetState(int state);
	virtual void OpenBox();
};