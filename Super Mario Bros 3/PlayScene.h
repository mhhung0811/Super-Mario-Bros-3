#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "CGameUI.h"
#include "UINum.h"
#include "UIArrow.h"
#include "UIPow.h"
#include "UIMario.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
//#include "Koopas.h"

// Pls sync with other in main.cpp if changes
#define SCREEN_WIDTH 280
#define SCREEN_HEIGHT 270
#define SCREEN_UI	28
#define	WORLD_CEILING -212
#define CAM_STATIC_Y -454

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	CUIMario* uiPlayer;

	vector<LPGAMEOBJECT> objects0;
	vector<LPGAMEOBJECT> objects1;
	vector<LPGAMEUI> objects2;
	vector<CUINum*> numsObj;
	vector<CUIArrow*> arrsObj;
	CUIPow* pow;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	CUIMario* GetUIPlayer() { return uiPlayer; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	void CreateGameObject(string line);
	void CreateItem(int id, float x, float y);
	void CreateFireBall(float x, float y, int dir);
	void AddObject(CGameObject* obj, int type);
	void SpawnMonster(int id, float x, float y);
	void FlowScore(float x, float y, int scoreId);
	void FlowCoin(float x, float y);
	void BrickToCoin();
	void CoinToBrick();
	void ResetCam();
	void UpdateUILives();
	void UpdateUIScore(int num);
	void UpdateUICoin(int num);
	void UpdateUITime(int num);
	void UpdateUIRuncharge(int num);
	void Restart();
};

typedef CPlayScene* LPPLAYSCENE;

