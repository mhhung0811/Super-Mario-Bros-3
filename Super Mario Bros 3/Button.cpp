#include "Button.h"

CButton::CButton(float x, float y) : CGameObject(x, y)
{
	time_out = 0;
	SetState(BUTTON_STATE_ACTIVE);
}

void CButton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BUTTON_BBOX_WIDTH / 2;
	top = y - ((state == BUTTON_STATE_ACTIVE) ? BUTTON_BBOX_HEIGHT : BUTTON_PRESS_BBOX_HEIGHT) / 2 + ((state == BUTTON_STATE_ACTIVE) ? 2 : 4);
	right = left + BUTTON_BBOX_WIDTH;
	bottom = top + ((state == BUTTON_STATE_ACTIVE) ? BUTTON_BBOX_HEIGHT : BUTTON_PRESS_BBOX_HEIGHT);
}

void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (time_out > 0)
	{
		time_out -= dt;
		if (time_out <= 0)
		{
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->CoinToBrick();
			time_out = 0;
		}
	}
}

void CButton::Render()
{
	int aniId = ID_ANI_BUTTON_ACTIVE;
	if (state == BUTTON_STATE_PRESS)
	{
		aniId = ID_ANI_BUTTON_PRESS;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CButton::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - MYSTERYBOX_BBOX_WIDTH / 2 + (float)rect.right / 2;
	float yy = y - ((state == BUTTON_STATE_ACTIVE) ? BUTTON_BBOX_HEIGHT : BUTTON_PRESS_BBOX_HEIGHT) / 2 + (float)rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy + ((state == BUTTON_STATE_ACTIVE) ? 2 : 4), bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CButton::OnNoCollision(DWORD dt)
{

}

void CButton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BUTTON_STATE_ACTIVE:
		break;
	case BUTTON_STATE_PRESS:
		break;
	default:
		break;
	}
}

void CButton::PressButton()
{
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->BrickToCoin();
	SetState(BUTTON_STATE_PRESS);
	time_out = BUTTON_TIME_OUT;
}