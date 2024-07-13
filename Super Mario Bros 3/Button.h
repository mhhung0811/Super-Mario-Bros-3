#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define BUTTON_BBOX_HEIGHT 8
#define BUTTON_PRESS_BBOX_HEIGHT 4
#define BUTTON_BBOX_WIDTH 16

#define BUTTON_TIME_OUT 5000

#define BUTTON_STATE_ACTIVE 100
#define BUTTON_STATE_PRESS 200

#define ID_ANI_BUTTON_ACTIVE 221010
#define ID_ANI_BUTTON_PRESS 222010

class CButton : public CGameObject
{
protected:
	long time_out;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void RenderBoundingBox();

	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 1; }
public:
	CButton(float x, float y);
	virtual void SetState(int state);
	virtual void PressButton();
};