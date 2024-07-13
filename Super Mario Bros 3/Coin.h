#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "PlayScene.h"
#include "AssetIDs.h"

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_ACTIVE 100
#define COIN_STATE_STATIC 200

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_STATIC 11002
class CCoin : public CGameObject {
protected:
	bool isStatic;

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
public:
	CCoin(float x, float y);
	virtual void SetState(int state);
	void ToBrick();
};