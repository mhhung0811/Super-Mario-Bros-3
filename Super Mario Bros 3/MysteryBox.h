#pragma once
#include "GameObject.h"

#define MYSTERYBOX_BBOX_HEIGHT 16
#define MYSTERYBOX_BBOX_WIDTDH 16

#define MYSTERYBOX_STATE_ACTIVE 100
#define MYSTERYBOX_STATE_UNACTIVE 200

#define ID_ANI_MYSTERYBOX_ACTIVE 101010
#define ID_ANI_MYSTERYBOX_UNACTIVE 102010

class CMysteryBox : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
public:
	CMysteryBox(float x, float y);
	virtual void SetState(int state);
	virtual void OpenBox();
};