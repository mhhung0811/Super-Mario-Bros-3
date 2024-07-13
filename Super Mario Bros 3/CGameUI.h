#pragma once

#include "GameObject.h"

#define UI_HUD_BBOX_WIDTH 152
#define UI_HUD_BBOX_HEIGHT 28
#define UI_CARD_BBOX_WIDTH 28
#define UI_CARD_BBOX_HEIGHT 30
#define UI_TAG_BBOX_WIDTH 16
#define UI_TAG_BBOX_HEIGHT 8
#define UI_POW_BBOX_WIDTH 16
#define UI_POW_BBOX_HEIGHT 8
#define UI_ARROW_BBOX_WIDTH 8
#define UI_ARROW_BBOX_HEIGHT 8
#define UI_NUM_BBOX_WIDTH 8
#define UI_NUM_BBOX_HEIGHT 8
#define UI_PANEL_BBOX_WIDTH 256
#define UI_PANEL_BBOX_HEIGHT 224
#define UI_PANEL_DARK_BBOX_WIDTH 256
#define UI_PANEL_DARK_BBOX_HEIGHT 186


#define ID_SPR_UI_HUD	230000
#define ID_SPR_UI_CARD	231000
#define ID_SPR_UI_TAG	232000
#define ID_SPR_UI_POW_0	233000
#define ID_SPR_UI_POW_1	233001
#define ID_SPR_UI_ARROW_0	234000
#define ID_SPR_UI_ARROW_1	234001
#define ID_SPR_UI_NUM_0	235000
#define ID_SPR_UI_NUM_1	235001
#define ID_SPR_UI_NUM_2	235002
#define ID_SPR_UI_NUM_3	235003
#define ID_SPR_UI_NUM_4	235004
#define ID_SPR_UI_NUM_5	235005
#define ID_SPR_UI_NUM_6	235006
#define ID_SPR_UI_NUM_7	235007
#define ID_SPR_UI_NUM_8	235008
#define ID_SPR_UI_NUM_9	235009
#define ID_SPR_UI_PANEL	236000
#define ID_SPR_UI_PANEL_DARK 236001	
#define ID_SPR_UI_PANEL_END 236002	
#define ID_SPR_UI_PANEL_PICK 236003

class CGameUI : public CGameObject
{
protected:
	float fixedX;
	float fixedY;
public:
	CGameUI(float x, float y);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void RenderBoundingBox() {};
	virtual int IsBlocking() { return 0; }
	virtual void UIUpdate(float cx, float cy);
};

typedef CGameUI* LPGAMEUI;