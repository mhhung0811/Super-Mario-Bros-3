#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
//#include "Koopas.h"

// Pls sync with other in main.cpp if changes
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 290
#define SCREEN_UI 50
#define	WORLD_CEILING -212

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects0;
	vector<LPGAMEOBJECT> objects1;

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

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	void CreateGameObject(string line);
	void CreateItem(int id, float x, float y);
	void CreateFireBall(float x, float y, int dir);
	void AddObject(CGameObject* obj, int type);
	void SpawnMonster(int id, float x, float y);
};

typedef CPlayScene* LPPLAYSCENE;

