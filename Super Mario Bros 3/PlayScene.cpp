#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "PlatformOneWay.h"
#include "Decor.h"
#include "CubeOneWay.h"
#include "MysteryBox.h"
#include "Mushroom.h"
#include "Cube.h"
#include "PiranhaPlant.h"
#include "FireBall.h"
#include "Koopa.h"
#include "RacoonLeaf.h"
#include "FlyGoomba.h"
#include "Wing.h"
#include "Spawner.h"
#include "WorldWall.h"
#include "FlyKoopa.h"
#include "NormalKoopa.h"
#include "PiranhaPlantBite.h"
#include "FlowScore.h"
#include "FLowCoin.h"
#include "BreakableBrick.h"
#include "MushroomGreen.h"
#include "Button.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");

		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	case OBJECT_TYPE_GOOMBA: 
		obj = new CGoomba(x,y); 
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	case OBJECT_TYPE_KOOPA:
	{
		obj = new CKoopa(x, y);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}
	case OBJECT_TYPE_BRICK: 
		obj = new CBrick(x,y); 
		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	case OBJECT_TYPE_COIN: 
		obj = new CCoin(x, y); 
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	}
	case OBJECT_TYPE_PLATFORM_ONE_WAY:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatformOneWay(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}

	case OBJECT_TYPE_DECOR:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new Decor(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}

	case OBJECT_TYPE_CUBE_ONE_WAY:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int sprite_top_begin = atoi(tokens[7].c_str());
		int sprite_top_middle = atoi(tokens[8].c_str());
		int sprite_top_end = atoi(tokens[9].c_str());
		int sprite_mid_begin = atoi(tokens[10].c_str());
		int sprite_mid_middle = atoi(tokens[11].c_str());
		int sprite_mid_end = atoi(tokens[12].c_str());
		int sprite_bottom_begin = atoi(tokens[13].c_str());
		int sprite_bottom_middle = atoi(tokens[14].c_str());
		int sprite_bottom_end = atoi(tokens[15].c_str());

		obj = new CCubeOneWay(
			x, y,
			cell_width, cell_height, length, height,
			sprite_top_begin, sprite_top_middle, sprite_top_end,
			sprite_mid_begin, sprite_mid_middle, sprite_mid_end,
			sprite_bottom_begin, sprite_bottom_middle, sprite_bottom_end
		);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}

	case OBJECT_TYPE_MYSTERY_BOX:
	{
		int gift = -1;
		if (tokens.size() > 3)
		{
			gift = (int)atoi(tokens[3].c_str());
		}
		obj = new CMysteryBox(x, y, gift);
		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	}

	case OBJECT_TYPE_MUSHROOM:
	{
		obj = new CMushroom(x, y);
		obj->SetPosition(x, y);
		// mushroom should be the first
		objects1.insert(objects1.begin(), obj);
		break;
	}

	case OBJECT_TYPE_CUBE:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int sprite_top_begin = atoi(tokens[7].c_str());
		int sprite_top_middle = atoi(tokens[8].c_str());
		int sprite_top_end = atoi(tokens[9].c_str());
		int sprite_mid_begin = atoi(tokens[10].c_str());
		int sprite_mid_middle = atoi(tokens[11].c_str());
		int sprite_mid_end = atoi(tokens[12].c_str());
		int sprite_bottom_begin = atoi(tokens[13].c_str());
		int sprite_bottom_middle = atoi(tokens[14].c_str());
		int sprite_bottom_end = atoi(tokens[15].c_str());

		obj = new CCube(
			x, y,
			cell_width, cell_height, length, height,
			sprite_top_begin, sprite_top_middle, sprite_top_end,
			sprite_mid_begin, sprite_mid_middle, sprite_mid_end,
			sprite_bottom_begin, sprite_bottom_middle, sprite_bottom_end
		);
		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	}

	case OBJECT_TYPE_PIRANHAPLANT:
	{
		obj = new CPiranhaPlant(x, y);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}

	case OBJECT_TYPE_FIREBALL:
	{
		int dir = -1;
		if (tokens.size() > 3)
		{
			dir = (int)atoi(tokens[3].c_str());
		}
		obj = new CFireBall(x, y, dir);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}
	case OBJECT_TYPE_RACOONLEAF:
	{
		obj = new CRacoonLeaf(x, y);
		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	}
	case OBJECT_TYPE_FLY_GOOMBA:
	{
		obj = new CFlyGoomba(x, y);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}
	case OBJECT_TYPE_WING:
	{
		obj = new CWing(x, y, -1);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}
	case OBJECT_TYPE_SPAWNER:
	{
		vector<int> ids;
		vector<float> coordinateX;
		vector<float> coordinateY;
		int bboxWidth = atoi(tokens[3].c_str());
		int bboxHeight = atoi(tokens[4].c_str());
		for (int i = 5; i < tokens.size(); i += 3)  
		{
			int id = atoi(tokens[i].c_str());
			float coX = atof(tokens[i + 1].c_str());
			float coY = atof(tokens[i + 2].c_str());
			
			ids.push_back(id);
			coordinateX.push_back(coX);
			coordinateY.push_back(coY);
		}
		obj = new CSpawner(x, y, bboxWidth, bboxHeight, ids, coordinateX, coordinateY);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}
	
	case OBJECT_TYPE_WORLDWALL:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int sprite_top_begin = atoi(tokens[7].c_str());
		int sprite_top_middle = atoi(tokens[8].c_str());
		int sprite_top_end = atoi(tokens[9].c_str());
		int sprite_mid_begin = atoi(tokens[10].c_str());
		int sprite_mid_middle = atoi(tokens[11].c_str());
		int sprite_mid_end = atoi(tokens[12].c_str());
		int sprite_bottom_begin = atoi(tokens[13].c_str());
		int sprite_bottom_middle = atoi(tokens[14].c_str());
		int sprite_bottom_end = atoi(tokens[15].c_str());

		obj = new CWorldWall(
			x, y,
			cell_width, cell_height, length, height,
			sprite_top_begin, sprite_top_middle, sprite_top_end,
			sprite_mid_begin, sprite_mid_middle, sprite_mid_end,
			sprite_bottom_begin, sprite_bottom_middle, sprite_bottom_end
		);
		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	}

	case OBJECT_TYPE_FLY_KOOPA:
	{
		obj = new CFlyKoopa(x, y);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}

	case OBJECT_TYPE_NORMAL_KOOPA:
	{
		obj = new CNormalKoopa(x, y);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}

	case OBJECT_TYPE_PIRANHAPLANT_BITE:
	{
		obj = new CPiranhaPlantBite(x, y);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
		break;
	}

	case OBJECT_TYPE_FLOW_SCORE:
	{
		int scoreId = atoi(tokens[3].c_str());
		obj = new CFlowScore(x, y, scoreId);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}

	case OBJECT_TYPE_FLOW_COIN:
	{
		obj = new CFlowCoin(x, y);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}

	case OBJECT_TYPE_BREAKABLE_BRICK:
	{
		int gift = 1;
		if (tokens.size() > 3)
		{
			gift = (int)atoi(tokens[3].c_str());
		}
		obj = new CBreakableBrick(x, y, gift);
		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	}

	case OBJECT_TYPE_MUSHROOM_GREEN:
	{
		obj = new CMushroomGreen(x, y);
		obj->SetPosition(x, y);
		// mushroom should be the first
		objects1.insert(objects1.begin(), obj);
		break;
	}

	case OBJECT_TYPE_BUTTON:
	{
		obj = new CButton(x, y);
		obj->SetPosition(x, y);
		objects1.push_back(obj);
		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		obj->SetPosition(x, y);
		objects0.push_back(obj);
		break;
	}	

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	/*obj->SetPosition(x, y);*/


	/*objects.push_back(obj);*/
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 	

	
	vector<LPGAMEOBJECT> coObjects0;
	
	for (size_t i = 0; i < objects0.size(); i++)
	{
		coObjects0.push_back(objects0[i]);
	}
	
	// Now Mario is the last
	vector<LPGAMEOBJECT> coObjects1;
	for (size_t i = 0; i < objects1.size() - 1; i++)
	{
		coObjects1.push_back(objects1[i]);
	}

	vector<LPGAMEOBJECT> coAllObjects;
	coAllObjects.reserve(coObjects0.size() + coObjects1.size());
	coAllObjects.insert(coAllObjects.begin(), coObjects0.begin(), coObjects0.end());
	coAllObjects.insert(coAllObjects.begin(), coObjects1.begin(), coObjects1.end());

	for (size_t i = 0; i < objects0.size(); i++)
	{
		objects0[i]->Update(dt, &coAllObjects);
	}
	for (size_t i = 0; i < objects1.size(); i++)
	{
		objects1[i]->Update(dt, &coAllObjects);
	}

	// Update objects0
	/*for (size_t i = 0; i < objects0.size(); i++)
	{
		objects0[i]->Update(dt, &coObjects0);
	}*/
	// Update objects1
	/*for (size_t i = 0; i < objects1.size(); i++)
	{
		objects1[i]->Update(dt, &coObjects1);
	}*/

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	CMario* mario = dynamic_cast<CMario*>(player);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	
	if (cx < 0) cx = 0;
	if (cy > 0) cy = 0;

	if (mario->IsCamStaticY())
	{
		CGame::GetInstance()->SetCamPos(cx, CAM_STATIC_Y, mario->FaceDirection(), -1);
	}
	else if (cy < (SCREEN_HEIGHT - SCREEN_UI) / 2 && mario->IsCamFollowY())
	{
		if (cy < (SCREEN_HEIGHT - SCREEN_UI) / 3 * 2 && mario->IsCamFollowY())
		{
			cy -= game->GetBackBufferHeight() / 2;
		}
		if (cy < WORLD_CEILING) cy = WORLD_CEILING;
		CGame::GetInstance()->SetCamPos(cx, cy, mario->FaceDirection(), mario->IsUp());
	}
	else
	{
		CGame::GetInstance()->SetCamPos(cx, 0, mario->FaceDirection(), mario->IsUp());
	}

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects0.size(); i++)
		objects0[i]->Render();

	for (int i = 0; i < objects1.size(); i++)
		objects1[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it0;
	for (it0 = objects0.begin(); it0 != objects0.end(); it0++)
	{
		delete (*it0);
	}
	objects0.clear();

	vector<LPGAMEOBJECT>::iterator it1;
	for (it1 = objects1.begin(); it1 != objects1.end(); it1++)
	{
		delete (*it1);
	}
	objects1.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects0.size(); i++)
		delete objects0[i];
	objects0.clear();

	for (int i = 0; i < objects1.size(); i++)
		delete objects1[i];
	objects1.clear();

	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it0;
	for (it0 = objects0.begin(); it0 != objects0.end(); it0++)
	{
		LPGAMEOBJECT o = *it0;
		if (o->IsDeleted())
		{
			delete o;
			*it0 = NULL;
		}
	}
	objects0.erase(
		std::remove_if(objects0.begin(), objects0.end(), CPlayScene::IsGameObjectDeleted),
		objects0.end());

	vector<LPGAMEOBJECT>::iterator it1;
	for (it1 = objects1.begin(); it1 != objects1.end(); it1++)
	{
		LPGAMEOBJECT o = *it1;
		if (o->IsDeleted())
		{
			delete o;
			*it1 = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects1.erase(
		std::remove_if(objects1.begin(), objects1.end(), CPlayScene::IsGameObjectDeleted),
		objects1.end());
}

void CPlayScene::CreateGameObject(string line)
{
	_ParseSection_OBJECTS(line);
}

void CPlayScene::CreateItem(int id, float x, float y)
{
	CGameObject* obj;
	switch (id)
	{
	case OBJECT_TYPE_MUSHROOM:
		obj = new CMushroom(x, y);
		obj->SetPosition(x, y);
		// mushroom should be the first
		objects1.insert(objects1.begin(), obj);
		break;
	case OBJECT_TYPE_RACOONLEAF:
		obj = new CRacoonLeaf(x, y);
		obj->SetPosition(x, y);
		// racoon leaf should be the last but still after mario
		objects1.insert(objects1.end() - 1, obj);
		break;
	case OBJECT_TYPE_MUSHROOM_GREEN:
		obj = new CMushroomGreen(x, y);
		obj->SetPosition(x, y);
		// mushroom should be the first
		objects1.insert(objects1.begin(), obj);
		break;
	case OBJECT_TYPE_BUTTON:
		obj = new CButton(x, y - 16);
		obj->SetPosition(x, y - 16);
		objects1.insert(objects1.end() - 1, obj);
		break;
	case OBJECT_TYPE_COIN:
		obj = new CCoin(x, y);
		obj->SetPosition(x, y);
		obj->SetState(COIN_STATE_STATIC);
		objects0.push_back(obj);
		break;
	default:
		break;
	}	
}

void CPlayScene::CreateFireBall(float x, float y, int dir)
{
	CGameObject* obj = new CFireBall(x, y, dir);
	obj->SetPosition(x, y);
	objects0.push_back(obj);
}

void CPlayScene::AddObject(CGameObject* obj, int type)
{
	switch (type)
	{
	case 0:
		objects0.push_back(obj);
		break;
	case 1:
		objects1.push_back(obj);
		break;
	default:
		break;
	}
}

void CPlayScene::SpawnMonster(int id, float x, float y)
{
	CGameObject* obj;
	switch (id)
	{
	case OBJECT_TYPE_GOOMBA:
		obj = new CGoomba(x, y);
		obj->SetPosition(x, y);
		/*objects0.push_back(obj);*/
		objects0.insert(objects0.end(), obj);
		break;
	case OBJECT_TYPE_FLY_GOOMBA:
		obj = new CFlyGoomba(x, y);
		obj->SetPosition(x, y);
		/*objects0.push_back(obj);*/
		objects0.insert(objects0.end(), obj);
		break;
	case OBJECT_TYPE_KOOPA:
		obj = new CKoopa(x, y);
		obj->SetPosition(x, y);
		/*objects0.push_back(obj);*/
		objects0.insert(objects0.end(), obj);
		break;
	case OBJECT_TYPE_FLY_KOOPA:
		obj = new CFlyKoopa(x, y);
		obj->SetPosition(x, y);
		/*objects0.push_back(obj);*/
		objects0.insert(objects0.end(), obj);
		break;
	case OBJECT_TYPE_NORMAL_KOOPA:
		obj = new CNormalKoopa(x, y);
		obj->SetPosition(x, y);
		/*objects0.push_back(obj);*/
		objects0.insert(objects0.end(), obj);
		break;
	default:
		break;
	}
}

void CPlayScene::FlowScore(float x, float y, int score)
{
	int scoreId = -1;
	switch (score)
	{
	case 100:
		scoreId = FLOW_SCORE_100;
		break;
	case 200:
		scoreId = FLOW_SCORE_200;
		break;
	case 400:
		scoreId = FLOW_SCORE_400;
		break;
	case 800:
		scoreId = FLOW_SCORE_800;
		break;
	case 1000:
		scoreId = FLOW_SCORE_1000;
		break;
	case 2000:
		scoreId = FLOW_SCORE_2000;
		break;
	case 4000:
		scoreId = FLOW_SCORE_4000;
		break;
	case 8000:
		scoreId = FLOW_SCORE_8000;
		break;
	case 10000:
		scoreId = FLOW_SCORE_1UP;
		break;
	default:
		return;
	}
	CGameObject* obj = new CFlowScore(x, y, scoreId);
	obj->SetPosition(x, y);
	objects0.push_back(obj);
}

void CPlayScene::FlowCoin(float x, float y)
{
	CGameObject* obj = new CFlowCoin(x, y);
	obj->SetPosition(x, y);
	objects0.push_back(obj);
}

void CPlayScene::BrickToCoin()
{
	for (int i = 0; i < objects1.size(); i++)
	{
		if (dynamic_cast<CBreakableBrick*>(objects1.at(i)))
		{
			CBreakableBrick* p = dynamic_cast<CBreakableBrick*>(objects1.at(i));
			if (p->IsCoin())
			{
				p->ToCoin();
			}
		}
	}
}