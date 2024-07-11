#include "PiranhaPlantBite.h"

CPiranhaPlantBite::CPiranhaPlantBite(float x, float y) :CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
	this->isIdle = 0;	
	SetState(PIRANHAPLANT_BITE_STATE_IDLE);
}

void CPiranhaPlantBite::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHAPLANT_BITE_BBOX_WIDTH / 2;
	top = y - PIRANHAPLANT_BITE_BBOX_HEIGHT / 2;
	right = left + PIRANHAPLANT_BITE_BBOX_WIDTH;
	bottom = top + PIRANHAPLANT_BITE_BBOX_HEIGHT;
}

void CPiranhaPlantBite::GetSafeBox(float& left, float& top, float& right, float& bottom)
{
	left = x + PIRANHAPLANT_BITE_SAFE_BOX_X;
	top = y + PIRANHAPLANT_BITE_SAFE_BOX_Y;
	right = left + PIRANHAPLANT_BITE_BBOX_WIDTH;
	bottom = top + PIRANHAPLANT_BITE_BBOX_HEIGHT;
}

void CPiranhaPlantBite::RenderSafeBox()
{
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;
	GetSafeBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(l - cx, t - cy, bbox, &rect, BBOX_ALPHA);
}

void CPiranhaPlantBite::RenderBoundingBox()
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

	float xx = x - PIRANHAPLANT_BITE_BBOX_WIDTH / 2 + (float)rect.right / 2;
	float yy = y - PIRANHAPLANT_BITE_BBOX_HEIGHT / 2 + (float)rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPiranhaPlantBite::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == PIRANHAPLANT_BITE_STATE_APPEAR && y <= (fixedY)-PIRANHAPLANT_BITE_BBOX_HEIGHT)
	{
		isColl = 1;
		SetState(PIRANHAPLANT_BITE_STATE_IDLE);
	}
	if (state == PIRANHAPLANT_BITE_STATE_DISAPPEAR && y >= (fixedY)+5)
	{
		SetState(PIRANHAPLANT_BITE_STATE_IDLE);
	}
	if (state == PIRANHAPLANT_BITE_STATE_IDLE)
	{
		// Detect Player
		LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		LPGAMEOBJECT player = playScene->GetPlayer();
		if (player == NULL) DebugOut(L"Player is null\n");
		else if (InSafeBox(player))
		{
			isIdle = 0;
		}

		// to Other state
		if (isIdle > PIRANHAPLANT_BITE_IDLE_TIME)
		{
			isIdle = 0;
			if (y < (fixedY))
			{
				isColl = 0;
				SetState(PIRANHAPLANT_BITE_STATE_DISAPPEAR);
			}
			else
			{
				SetState(PIRANHAPLANT_BITE_STATE_APPEAR);
			}
		}
		else
		{
			isIdle += dt;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlantBite::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CPiranhaPlantBite::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CKoopa*>(e->obj))
	{
		CKoopa* p = dynamic_cast<CKoopa*>(e->obj);
		if (p->IsRolled())
		{
			SetState(PIRANHAPLANT_BITE_STATE_DIE);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(x, y, 0);
		}
	}
	if (dynamic_cast<CFlyKoopa*>(e->obj))
	{
		CFlyKoopa* p = dynamic_cast<CFlyKoopa*>(e->obj);
		if (p->IsRolled())
		{
			SetState(PIRANHAPLANT_BITE_STATE_DIE);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(x, y, 0);
		}
	}

	if (dynamic_cast<CNormalKoopa*>(e->obj))
	{
		CNormalKoopa* p = dynamic_cast<CNormalKoopa*>(e->obj);
		if (p->IsRolled())
		{
			SetState(PIRANHAPLANT_BITE_STATE_DIE);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(x, y, 0);
		}
	}
}

void CPiranhaPlantBite::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_PIRANHAPLANT_BITE)->Render(x, y);

	//RenderSafeBox();
	//RenderBoundingBox();
}

void CPiranhaPlantBite::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHAPLANT_BITE_STATE_APPEAR:
		vy = -PIRANHAPLANT_BITE_APPEAR_SPEED;
		break;
	case PIRANHAPLANT_BITE_STATE_DISAPPEAR:
		vy = PIRANHAPLANT_BITE_APPEAR_SPEED;
		break;
	case PIRANHAPLANT_BITE_STATE_IDLE:
		vy = 0;
		break;
	case PIRANHAPLANT_BITE_STATE_DIE:
		isDeleted = true;
		break;
	default:
		break;
	}
}

bool CPiranhaPlantBite::InSafeBox(LPGAMEOBJECT obj)
{
	if (obj == NULL) return -1;
	float l1, t1, r1, b1, l2, t2, r2, b2;
	obj->GetBoundingBox(l2, t2, r2, b2);

	// Is in Safe Box
	GetSafeBox(l1, t1, r1, b1);
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		return true;
	}
	//DebugOut(L"no box found\n");
	return false;
}