#include "FlowCoin.h"
#include "debug.h"

CFlowCoin::CFlowCoin(float x, float y) : CGameObject(x, y)
{
	this->fixedY = y;
	this->ay = 0;
	SetState(FLOW_COIN_STATE_APPEAR);
}

void CFlowCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	vy += ay * dt;

	if (abs(vy) > FLOW_COIN_SPEED_MAX) vy = (vy > 0) ? FLOW_COIN_SPEED_MAX : -FLOW_COIN_SPEED_MAX;

	if (state == FLOW_COIN_STATE_APPEAR && y < (fixedY - FLOW_COIN_MAX_HEIGHT))
	{
		SetState(FLOW_COIN_STATE_DROP);
	}
	if (state == FLOW_COIN_STATE_DROP && y > (fixedY - 5))
	{
		LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		playScene->UpdateUICoin(1);
		SetState(FLOW_COIN_STATE_DISAPPEAR);
	}
}

void CFlowCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FLOW_COIN)->Render(x, y);
}

void CFlowCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FLOW_COIN_BBOX_WIDTH / 2;
	top = y - FLOW_COIN_BBOX_HEIGHT / 2;
	right = left + FLOW_COIN_BBOX_WIDTH;
	bottom = top + FLOW_COIN_BBOX_HEIGHT;
}

void CFlowCoin::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CFlowCoin::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FLOW_COIN)->Render(x, y);
}

void CFlowCoin::SetState(int state)
{
	CGameObject::SetState(state);
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	switch (state)
	{
	case FLOW_COIN_STATE_APPEAR:
		ay = -FLOW_COIN_ACCEL;
		break;
	case FLOW_COIN_STATE_DROP:
		vy = 0;
		ay = FLOW_COIN_ACCEL;
		break;
	case FLOW_COIN_STATE_DISAPPEAR:
		playScene->FlowScore(x, y, 100);
		isDeleted = true;
		break;
	default:
		break;
	}
}