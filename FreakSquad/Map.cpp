#include "Map.h"
#include "CollisionMask.h"
#include "Starters.h"
#include "Sounds3D.h"

Map::Map()
{
}

Map::~Map()
{
}
#define SOUTE "soute"
#define SOUTE_SHADOW "souteShadow"
#define SOUTE_PP "soutePP"

#define MAP1 "map1"
#define MAP1_ASSET "map1Asset"
#define MAP1_ROAD "map1Road"

#define MAP2 "map2"
#define MAP2_ASSET "map2Asset"
#define MAP2_ROAD "map2Road"

#define MAP3 "map3"
#define MAP3_ASSET "map3Asset"
#define MAP3_ROAD1 "map3Road1"
#define MAP3_ROAD2 "map3Road2"

#define MAP4 "map4"
#define MAP4_ASSET "map4Asset"
#define MAP4_ROAD "map4Road"

#define MAP5 "map5"
#define MAP5_ASSET "map5Asset"
#define MAP5_ROAD "map5Road"


#define MAP6 "map6"
#define MAP6_ASSET "map6Asset"

#define MAP7 "map7"
#define MAP7_ASSET "map7Asset"
#define MAP7_ROAD1 "map7Road1"
#define MAP7_ROAD2 "map7Road2"
#define MAP7_ROAD3 "map7Road3"
#define MAP7_ROAD4 "map7Road4"



void Map::initMap(std::shared_ptr<GameObject> _object, float _volumeMusic, float _volumeSound)
{
	sf::Vector2f tmp_soutePos{ 0.f,0.f };
	sf::Vector2f tmp_lvlScreen1Pos{ 0.f,SCREENSIZE_Y };
	sf::Vector2f tmp_lvlScreen2Pos{ tmp_lvlScreen1Pos.x + SCREENSIZE_X - 1,tmp_lvlScreen1Pos.y };
	sf::Vector2f tmp_lvlScreen3Pos{ tmp_lvlScreen2Pos.x + SCREENSIZE_X * (3),tmp_lvlScreen2Pos.y + SCREENSIZE_Y * 2 };
	sf::Vector2f tmp_lvlScreen4Pos{ tmp_lvlScreen3Pos.x + SCREENSIZE_X * 2 - 1,  tmp_lvlScreen3Pos.y - SCREENSIZE_Y - 1 };
	sf::Vector2f tmp_lvlScreen5Pos{ tmp_lvlScreen4Pos.x + SCREENSIZE_X * 2 - 1,  tmp_lvlScreen4Pos.y };
	sf::Vector2f tmp_lvlScreen6Pos{ tmp_lvlScreen5Pos.x + SCREENSIZE_X * 1 - 8,  tmp_lvlScreen5Pos.y };
	sf::Vector2f tmp_lvlScreen7Pos{ tmp_lvlScreen6Pos.x + SCREENSIZE_X * 3.0f - 7,  tmp_lvlScreen6Pos.y + SCREENSIZE_Y * 2.0f + 1 };
	sf::Vector2f tmp_ZoneBoss{ tmp_lvlScreen7Pos.x + SCREENSIZE_X * 2.f +20,  tmp_lvlScreen7Pos.y};//il y a un décalage de -11 sur la taille d'écran pour alligner

	_object->addGameObject(MapFactory::createMap(SOUTE, "soute.png", tmp_soutePos));
	_object->addGameObject(MapFactory::createMap(SOUTE_SHADOW, "souteShadow.png", tmp_soutePos));

	_object->addGameObject(MapFactory::createMap(MAP1, "screen1.png", tmp_lvlScreen1Pos));
	_object->addGameObject(MapFactory::createMap(MAP1_ASSET, "screen1assets.png", tmp_lvlScreen1Pos));

	_object->addGameObject(MapFactory::createMap(MAP2, "screen2.png", tmp_lvlScreen2Pos));
	_object->addGameObject(MapFactory::createMap(MAP2_ASSET, "screen2assets.png", tmp_lvlScreen2Pos));

	_object->addGameObject(MapFactory::createMap(MAP3, "screen3.png", tmp_lvlScreen3Pos));
	_object->addGameObject(MapFactory::createMap(MAP3_ASSET, "screen3assets.png", tmp_lvlScreen3Pos));

	_object->addGameObject(MapFactory::createMap(MAP4, "screen4.png", tmp_lvlScreen4Pos));
	_object->addGameObject(MapFactory::createMap(MAP4_ASSET, "screen4assets.png", tmp_lvlScreen4Pos));

	_object->addGameObject(MapFactory::createMap(MAP5, "screen5.png", tmp_lvlScreen5Pos));
	_object->addGameObject(MapFactory::createMap(MAP5_ASSET, "screen5assets.png", tmp_lvlScreen5Pos));

	_object->addGameObject(MapFactory::createMap(MAP6, "screen6.png", tmp_lvlScreen6Pos));
	_object->addGameObject(MapFactory::createMap(MAP6_ASSET, "screen6assets.png", tmp_lvlScreen6Pos));

	_object->addGameObject(MapFactory::createMap(MAP7, "screen7.png", tmp_lvlScreen7Pos));
	_object->addGameObject(MapFactory::createMap(MAP7_ASSET, "screen7assets.png", tmp_lvlScreen7Pos));
	
	_object->addGameObject(MapFactory::createMap("zoneBoss", "zoneBoss.png", tmp_ZoneBoss));
	_object->addGameObject(MapFactory::createMap("zoneBossLamp", "zoneBossLamp.png", tmp_ZoneBoss));
	_object->addGameObject(MapFactory::createMap("zoneBossAsset", "zoneBossAssets.png", tmp_ZoneBoss));

	std::shared_ptr<GameObject> mapCol = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idMapCol = std::shared_ptr<Identity>(new Identity("MapCollision", OBJECT));
	std::shared_ptr<CollisionMask> mask = std::shared_ptr<CollisionMask>(new CollisionMask());
	std::shared_ptr<ObjectTransform> transformMapCol = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), -INFINITY, STATIC));


	mapCol->addComponents<Identity>(idMapCol);
	mapCol->addComponents<CollisionMask>(mask);
	mapCol->addComponents<ObjectTransform>(transformMapCol);
	_object->addGameObject(mapCol);

	std::shared_ptr<GameObject> MusicObject = std::shared_ptr<GameObject>(new GameObject);
	std::shared_ptr<Identity> idsoundObject = std::shared_ptr<Identity>(new Identity("gameMusic", OBJECT));
	std::shared_ptr<Audio3D_Manager> MusicPlayer = std::shared_ptr<Audio3D_Manager>(new Audio3D_Manager());	
	std::shared_ptr<ObjectTransform> transformMusic = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), -INFINITY + 50.f, STATIC));


	
	MusicPlayer->addSceneMusic("CargoHoldmusic", "Stage_Militaire_44Hz_16bits.wav", _volumeMusic);
	MusicPlayer->addSceneMusic("UrbanJunglemusic", "Jungle_Urbaine_44Hz_16bits.wav", _volumeMusic);
	MusicPlayer->addSceneMusic("BossMusic", "BossPhase1_44Hz_16bits.wav", _volumeMusic);
	MusicPlayer->addSceneMusic("VictoryMusic", "Victory_44Hz_16bits.wav", _volumeMusic);
	MusicPlayer->addSceneMusic("CreditMusic", "NightOfRage_Single_44Hz_16bit.wav", _volumeMusic);
	MusicPlayer->addSceneSound("characterswitch", "switch_character.wav", _volumeSound);

	MusicPlayer->addSceneSound("destruction", "Destruction.wav", _volumeSound);
	MusicPlayer->addSceneSound("text", "text.wav", _volumeSound);
	MusicPlayer->addSceneSound("pickupitem", "pickupitem.wav", _volumeSound);
	MusicPlayer->addSceneSound("pickuppackage", "pickuppackage.wav", _volumeSound);
	MusicPlayer->addSceneSound("breakdestructable", "breakDestructable.wav", _volumeSound);
	MusicPlayer->addSceneSound("HitOne", "punch_wind.wav", _volumeSound);
	MusicPlayer->addSceneSound("HitTwo", "punch_wind2.wav", _volumeSound);
	MusicPlayer->addSceneSound("HitThree", "hit_2.wav", _volumeSound);
	MusicPlayer->addSceneSound("HitFour", "final_bigboyhit.wav", _volumeSound);
	MusicPlayer->addSceneSound("Jump", "BigBoyJump.wav", _volumeSound);
	MusicPlayer->addSceneSound("JumpAttack", "jump_kick_bb.wav", _volumeSound);
	MusicPlayer->addSceneSound("AtackMitraillette", "Blaster Machine_Gun-01-Burst-03.wav", _volumeSound);
	MusicPlayer->addSceneSound("AtackFinalCharge", "Resistance-AssaultRifle_03-Single_Shot-04.wav", _volumeSound);
	MusicPlayer->addSceneSound("AtackDash", "AttackDash.wav", _volumeSound);
	MusicPlayer->addSceneSound("chargeattackBL", "BL_charged.wav", _volumeSound);
	MusicPlayer->addSceneSound("gethit1", "GoodHit_1.wav", _volumeSound);
	MusicPlayer->addSceneSound("gethit2", "GoodHit_2.wav", _volumeSound);
	MusicPlayer->addSceneSound("gethit3", "GoodHit_3.wav", _volumeSound);
	MusicPlayer->addSceneSound("gethit4", "GoodHit_4.wav", _volumeSound);
	MusicPlayer->addSceneSound("starttuto", "spawnholo.wav", _volumeSound);
	MusicPlayer->addSceneSound("deadholo", "mortholo.wav", _volumeSound);
	MusicPlayer->addSceneSound("switchscreen", "switch_screen.wav", _volumeSound);
	MusicPlayer->addSceneSound("boost", "boost2.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_1", "attack_BL_1.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_2", "attack_BL_22.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_3", "attack_BL_3.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_4", "attack_BL_4.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_jump", "attack_BL_jump.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_jumphit", "attack_BL_jump2.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_charge", "attack_BL_charge.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bb_charging", "attack_BB_charging2.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bb_ulti", "attack_BB_ulti2.wav", _volumeSound);
	MusicPlayer->addSceneSound("vaccum", "vaccum.wav", _volumeSound);
	MusicPlayer->addSceneSound("chainsaw", "chainsaw.wav", _volumeSound);
	MusicPlayer->addSceneSound("flesh", "flesh.wav", _volumeSound);
	MusicPlayer->addSceneSound("gush", "gush2.wav", _volumeSound);
	MusicPlayer->addSceneSound("knockdown", "knockdown.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_charging", "attack_BL_charging.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_ulti", "attack_BL_ulti.wav", _volumeSound);
	MusicPlayer->addSceneSound("attack_bl_ulti2", "attack_BL_ulti2.wav", _volumeSound);
	MusicPlayer->addSceneSound("getup", "stand_up.wav", _volumeSound);
	MusicPlayer->addSceneSound("grab", "grab.wav", _volumeSound);
	MusicPlayer->addSceneSound("throw", "throw.wav", _volumeSound);
	MusicPlayer->addSceneSound("woodhit", "woodhit.wav", _volumeSound);
	MusicPlayer->addSceneSound("woodhit2", "woodhit2.wav", _volumeSound);
	MusicPlayer->setLoop(true, "music", "CargoHoldmusic");
	MusicPlayer->setLoop(true, "music", "UrbanJunglemusic");
	MusicPlayer->setLoop(true, "music", "BossMusic");
	MusicPlayer->setLoop(true, "music", "CreditMusic");
	MusicPlayer->setLoop(true, "music", "VictoryMusic");
	MusicPlayer->setAllMusicVolume(_volumeMusic);
	MusicPlayer->setAllGlobalVolume(_volumeSound);
	MusicObject->addComponents<Identity>(idsoundObject);
	MusicObject->addComponents<Audio3D_Manager>(MusicPlayer);
	MusicObject->addComponents<ObjectTransform>(transformMusic);

	_object->addGameObject(MusicObject);
	
	

	std::shared_ptr<GameObject> starterObject = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idstarter = std::shared_ptr<Identity>(new Identity("starters", OBJECT));
	std::shared_ptr<Starters> starter = std::shared_ptr<Starters>(new Starters());
	std::shared_ptr<ObjectTransform> transformMap = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), -INFINITY + 10.f, STATIC));


	starterObject->addComponents<Identity>(idstarter);
	starterObject->addComponents<Starters>(starter);
	starterObject->addComponents<ObjectTransform>(transformMap);

	_object->addGameObject(starterObject);
}

void Map::initPremierPlan(std::shared_ptr<GameObject> _object)
{
	sf::Vector2f tmp_soutePos{ 0.f,0.f };
	sf::Vector2f tmp_lvlScreen1Pos{ 0.f,SCREENSIZE_Y };
	sf::Vector2f tmp_lvlScreen2Pos{ tmp_lvlScreen1Pos.x + SCREENSIZE_X - 1,tmp_lvlScreen1Pos.y };
	sf::Vector2f tmp_lvlScreen3Pos{ tmp_lvlScreen2Pos.x + SCREENSIZE_X * (3),tmp_lvlScreen2Pos.y + SCREENSIZE_Y * 2 };
	sf::Vector2f tmp_lvlScreen4Pos{ tmp_lvlScreen3Pos.x + SCREENSIZE_X * 2 - 1,  tmp_lvlScreen3Pos.y - SCREENSIZE_Y - 1 };
	sf::Vector2f tmp_lvlScreen5Pos{ tmp_lvlScreen4Pos.x + SCREENSIZE_X * 2 - 1,  tmp_lvlScreen4Pos.y };
	sf::Vector2f tmp_lvlScreen6Pos{ tmp_lvlScreen5Pos.x + SCREENSIZE_X * 1 - 1,  tmp_lvlScreen5Pos.y };
	sf::Vector2f tmp_lvlScreen7Pos{ tmp_lvlScreen6Pos.x + SCREENSIZE_X * 3.0f - 7,  tmp_lvlScreen6Pos.y + SCREENSIZE_Y * 2.0f + 1 };
	sf::Vector2f tmp_ZoneBoss{ tmp_lvlScreen7Pos.x + SCREENSIZE_X * 2.f + 20,  tmp_lvlScreen7Pos.y };//il y a un décalage de -11 sur la taille d'écran pour alligner

	
	_object->addGameObject(MapFactory::createFrontMap(SOUTE_PP, "soutePP.png", tmp_soutePos));

	_object->addGameObject(MapFactory::createFrontMap("map1PP", "screen1premierplan.png", sf::Vector2f(tmp_lvlScreen1Pos.x, tmp_lvlScreen1Pos.y/* + 20.0f*/)));

	_object->addGameObject(MapFactory::createFrontMap("map3PP", "screen3assets_premierplan.png", sf::Vector2f(tmp_lvlScreen3Pos.x, tmp_lvlScreen3Pos.y /*+ 20.0f*/)));

	_object->addGameObject(MapFactory::createFrontMap("map7PP", "screen7_premierplan.png", sf::Vector2f(tmp_lvlScreen7Pos.x, tmp_lvlScreen7Pos.y/* + 20.0f*/)));

	//la zone du boss
	_object->addGameObject(MapFactory::createFrontMap("zoneBossPP", "zoneBossPP.png", sf::Vector2f(tmp_ZoneBoss.x, tmp_ZoneBoss.y)));
	_object->addGameObject(MapFactory::createFrontMap("zoneBossShader1", "zoneBossShader1.png", sf::Vector2f(tmp_ZoneBoss.x-8, tmp_ZoneBoss.y)));
	_object->addGameObject(MapFactory::createFrontMap("zoneBossShader2", "zoneBossShader2.png", sf::Vector2f(tmp_ZoneBoss.x-8, tmp_ZoneBoss.y)));
	_object->addGameObject(MapFactory::createFrontMap("zoneBossShader3", "zoneBossShader3.png", sf::Vector2f(tmp_ZoneBoss.x-8, tmp_ZoneBoss.y)));
	_object->getObjects("zoneBossShader2")->getComponents<Sprite>()->getSprite().setColor(sf::Color(255.f, 255.f, 255.f,128.f));

}

std::shared_ptr<GameObject> MapFactory::createMap(std::string _nameObject, std::string _fileName, sf::Vector2f _pos)
{
	std::shared_ptr<GameObject> screen = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idScreen = std::shared_ptr<Identity>(new Identity(_nameObject, OBJECT));
	std::shared_ptr<ObjectTransform> transformScreen = std::shared_ptr<ObjectTransform>(new ObjectTransform(_pos, -INFINITY + 50.f, STATIC));
	//std::shared_ptr<RigidBody> bodyScreen = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Sprite> spriteScreen = std::shared_ptr<Sprite>(new Sprite());
	//spriteScreen->setActive(false);
	spriteScreen->setTexture(RessourceManager::get()->getSceneTexture(_fileName));
	//spriteScreen->setScale(sf::Vector2f(0.33, 0.33));
	//std::shared_ptr<Mouvement> mvtScreen = std::shared_ptr<Mouvement>(new Mouvement());
	//std::shared_ptr<Input> inputScreen = std::shared_ptr<Input>(new Input());

	screen->addComponents<Identity>(idScreen);
	screen->addComponents<ObjectTransform>(transformScreen);
	//screen->addComponents<RigidBody>(bodyScreen);
	screen->addComponents<Sprite>(spriteScreen);
	/*screen->addComponents<Mouvement>(mvtScreen);
	screen->addComponents<Input>(inputScreen);*/

	
	return screen;
}

std::shared_ptr<GameObject> MapFactory::createFrontMap(std::string _nameObject, std::string _fileName, sf::Vector2f _pos)
{
	std::shared_ptr<GameObject> screen = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idScreen = std::shared_ptr<Identity>(new Identity(_nameObject, OBJECT));
	std::shared_ptr<Sprite> spriteScreen = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<ObjectTransform> transformScreen = std::shared_ptr<ObjectTransform>(new ObjectTransform(_pos, INFINITY - 50.f, STATIC));

	spriteScreen->setTexture(RessourceManager::get()->getSceneTexture(_fileName));

	screen->addComponents<Identity>(idScreen);
	screen->addComponents<ObjectTransform>(transformScreen);
	screen->addComponents<Sprite>(spriteScreen);

	return screen;
}
