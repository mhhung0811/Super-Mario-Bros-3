#include "FlowScore.h"
#include "debug.h"

CFlowScore::CFlowScore(float x, float y, int scoreId) : CGameObject(x, y)
{
	this->ay = 0;
	this->scoreId = scoreId;
	appearTimer = -1;
	SetState(FLOW_SCORE_STATE_APPEAR);
}

void CFlowScore::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (GetTickCount64() - appearTimer > FLOW_SCORE_APPEAR_TIME)
	{
		SetState(FLOW_SCORE_STATE_DISAPPEAR);
	}
}

void CFlowScore::Render()
{
	CSprites* s = CSprites::GetInstance();
	switch (scoreId)
	{
	case FLOW_SCORE_100:
		s->Get(ID_SPRITE_FLOW_SCORE_100)->Draw(x, y);
		break;
	case FLOW_SCORE_200:
		s->Get(ID_SPRITE_FLOW_SCORE_200)->Draw(x, y);
		break;
	case FLOW_SCORE_400:
		s->Get(ID_SPRITE_FLOW_SCORE_400)->Draw(x, y);
		break;
	case FLOW_SCORE_800:
		s->Get(ID_SPRITE_FLOW_SCORE_800)->Draw(x, y);
		break;
	case FLOW_SCORE_1000:
		s->Get(ID_SPRITE_FLOW_SCORE_1000)->Draw(x, y);
		break;
	case FLOW_SCORE_2000:
		s->Get(ID_SPRITE_FLOW_SCORE_2000)->Draw(x, y);
		break;
	case FLOW_SCORE_4000:
		s->Get(ID_SPRITE_FLOW_SCORE_4000)->Draw(x, y);
		break;
	case FLOW_SCORE_8000:
		s->Get(ID_SPRITE_FLOW_SCORE_8000)->Draw(x, y);
		break;
	case FLOW_SCORE_1UP:
		s->Get(ID_SPRITE_FLOW_SCORE_1UP)->Draw(x, y);
		break;
	default:
		break;
	}
}

void CFlowScore::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FLOW_SCORE_BBOX_WIDTH / 2;
	top = y - FLOW_SCORE_BBOX_HEIGHT / 2;
	right = left + FLOW_SCORE_BBOX_WIDTH;
	bottom = top + FLOW_SCORE_BBOX_HEIGHT;
}

void CFlowScore::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CFlowScore::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CFlowScore::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOW_SCORE_STATE_APPEAR:
		ay = -FLOW_SCORE_SPEED;
		vy = -FLOW_SCORE_SPEED;
		appearTimer = GetTickCount64();
		break;
	case FLOW_SCORE_STATE_DISAPPEAR:
		isDeleted = true;
		break;
	default:
		break;
	}
}