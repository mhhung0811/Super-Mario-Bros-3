#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Utils.h"
#include "PlayScene.h"
#include "Koopa.h"
#include "FlyKoopa.h"
#include "NormalKoopa.h"
#include "debug.h"

#define PIRANHAPLANT_BITE_BBOX_WIDTH 16
#define PIRANHAPLANT_BITE_BBOX_HEIGHT 31
#define PIRANHAPLANT_BITE_SHOOT_BOX_WIDTH 48
#define PIRANHAPLANT_BITE_SHOOT_BOX_HEIGHT 64

#define ID_PIRANHAPLANT_BITE_SAFE_BOX 8
#define PIRANHAPLANT_BITE_SAFE_BOX_X 0
#define PIRANHAPLANT_BITE_SAFE_BOX_Y -40

#define PIRANHAPLANT_BITE_APPEAR_SPEED 0.05f
#define PIRANHAPLANT_BITE_IDLE_TIME 500

#define PIRANHAPLANT_BITE_STATE_IDLE 100
#define PIRANHAPLANT_BITE_STATE_APPEAR 200
#define PIRANHAPLANT_BITE_STATE_DISAPPEAR 300
#define PIRANHAPLANT_BITE_STATE_DIE 400

#define ID_ANI_PIRANHAPLANT_BITE 123000

class CPiranhaPlantBite : public CGameObject
{
protected:
	float fixedX;
	float fixedY;

	int point;

	bool isColl = 0;

	unsigned long isIdle;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void RenderBoundingBox();
	void RenderSafeBox();
	void GetSafeBox(float& left, float& top, float& right, float& bottom);
	bool InSafeBox(LPGAMEOBJECT obj);
	
	virtual int IsCollidable() { return isColl; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CPiranhaPlantBite(float x, float y);
	virtual void SetState(int state);
	int GetPoint()
	{
		int res = point;
		point = 0;
		return res;
	}
};