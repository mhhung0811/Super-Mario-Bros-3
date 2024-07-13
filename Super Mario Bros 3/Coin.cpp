#include "Coin.h"

CCoin::CCoin(float x, float y) : CGameObject(x, y)
{
	SetState(COIN_STATE_ACTIVE);
}

void CCoin::Render()
{
	if (state == COIN_STATE_ACTIVE)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_COIN)->Render(x, y);
	}
	else
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_COIN_STATIC)->Render(x, y);
	}

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_ACTIVE:
		break;
	case COIN_STATE_STATIC:
		break;
	default:
		break;
	}
}

void CCoin::ToBrick()
{
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->CreateItem(OBJECT_TYPE_BREAKABLE_BRICK, x, y);
	isDeleted = true;
}