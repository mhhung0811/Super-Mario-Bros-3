#pragma once
#include "CGameUI.h"
#include "debug.h"
#define UI_MARIO_SPEED 0.1f
#define UI_MARIO_FIXED_X1 44
#define UI_MARIO_FIXED_X2 76
#define UI_MARIO_FIXED_Y1 44
#define UI_MARIO_FIXED_Y2 76

class CUIMario : public CGameUI
{
protected:
	bool isMoving;
	bool canLeft;
	bool canTop;
	bool canRight;
	bool canBottom;
public:
	CUIMario(float x, float y) : CGameUI(x, y)
	{
		isMoving = false;
		canLeft = false;
		canTop = false;
		canRight = true;
		canBottom = false;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		y += vy * dt;
		x += vx * dt;
		
		if (canLeft && isMoving && abs(x - UI_MARIO_FIXED_X1) < 4 && abs(y - UI_MARIO_FIXED_Y2) < 4)
		{
			isMoving = false;
			canLeft = false;
			canTop = false;
			canRight = true;
			canBottom = false;
			x = UI_MARIO_FIXED_X1;
			y = UI_MARIO_FIXED_Y2;
			vx = 0;
			vy = 0;
		}
		if ((canRight || canBottom) && isMoving && abs(x - UI_MARIO_FIXED_X2) < 4 && abs(y - UI_MARIO_FIXED_Y2) < 4)
		{
			isMoving = false;
			canLeft = true;
			canTop = true;
			canRight = false;
			canBottom = false;
			x = UI_MARIO_FIXED_X2;
			y = UI_MARIO_FIXED_Y2;
			vx = 0;
			vy = 0;
		}
		if (canTop && isMoving && abs(x - UI_MARIO_FIXED_X2) < 4 && abs(y - UI_MARIO_FIXED_Y1) < 4)
		{
			isMoving = false;
			canLeft = false;
			canTop = false;
			canRight = false;
			canBottom = true;
			x = UI_MARIO_FIXED_X2;
			y = UI_MARIO_FIXED_Y1;
			vx = 0;
			vy = 0;
		}
	}
	void Render()
	{
		CAnimations::GetInstance()->Get(ID_ANI_UI_MARIO)->Render(x, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - UI_MARIO_BBOX_WIDTH / 2;
		t = y - UI_MARIO_BBOX_HEIGHT / 2;
		r = l + UI_MARIO_BBOX_WIDTH;
		b = t + UI_MARIO_BBOX_HEIGHT;
	}
	void UIUpdate(float cx, float cy)
	{

	}
	bool IsMoving() { return isMoving; }
	void GoLeft()
	{
		if (!canLeft) return;
		vx = -UI_MARIO_SPEED;
		isMoving = true;
	}
	void GoTop()
	{
		if (!canTop) return;
		vy = -UI_MARIO_SPEED;
		isMoving = true;
	}
	void GoRight()
	{
		if (!canRight) return;
		vx = UI_MARIO_SPEED;
		isMoving = true;
	}
	void GoBottom()
	{
		if (!canBottom) return;
		vy = UI_MARIO_SPEED;
		isMoving = true;
	}
	bool Click()
	{
		return abs(x - UI_MARIO_FIXED_X2) < 4 && abs(y - UI_MARIO_FIXED_Y1) < 4;
	}
};