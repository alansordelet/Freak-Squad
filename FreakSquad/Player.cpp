#include "Player.h"
#include "Camera.h"
#include "CheckCollision.h"
#include"Sounds3D.h"
#include"Ui_Player.h"
#include"Shake.h"
Player::Player()
{
}
Player::~Player()
{
}
void Player::initPlayer(std::shared_ptr<GameObject> _m_object, std::shared_ptr<Input> _input)
{


	std::shared_ptr<GameObject> ObjectOmbre = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> IdOmbre = std::shared_ptr<Identity>(new Identity("OmbreObj", OBJECT));
	std::shared_ptr<Sprite> OmbreSprite = std::shared_ptr<Sprite>(new Sprite("Ombre.png"));
	std::shared_ptr<ObjectTransform> transformOmbre = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 700.f,750.f }, STATIC));
	ObjectOmbre->addComponents<Identity>(IdOmbre);
	ObjectOmbre->addComponents<Sprite>(OmbreSprite);
	ObjectOmbre->addComponents<ObjectTransform>(transformOmbre);

	OmbreSprite->getSprite().setColor(sf::Color(255, 255, 255, 100));

	std::shared_ptr<GameObject> PlayerUltimate = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> IdPlayerUltimateBB = std::shared_ptr<Identity>(new Identity("PlayerUltimeBB", OBJECT));
	std::shared_ptr<Sprite> PlayerUltimateSprite = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<ObjectTransform> transformPlayerUltimate = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 200.f,400.f }, NON_STATIC));
	//std::shared_ptr<RigidBody> bodyPlayerUltimate = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Animation> animUltime = std::shared_ptr<Animation>(new Animation());

	animUltime->addAnimation("Tornado", "1repetable_1866x1070_6F.png", 6, 0.05f, true);
	animUltime->addAnimation("TornadoEnd", "2fin_1140x969_4F.png", 6, 0.05f, true);

	std::shared_ptr<GameObject> player = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idPlayerBB = std::shared_ptr<Identity>(new Identity("Player", PLAYER));
	std::shared_ptr<ObjectTransform> transformPlayer = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 700.f,750.f }, NON_STATIC));
	std::shared_ptr<RigidBody> bodyPlayer = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Sprite> spritePlayer = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animPlayer = std::shared_ptr<Animation>(new Animation());
	std::shared_ptr<Shake> ShakePlayer = std::shared_ptr<Shake>(new Shake());

	std::shared_ptr<Input> inputPlayer = std::move(_input);
	//--------------------------------------------------------//

	//GameObject & ID
	std::shared_ptr<GameObject> uiObject = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> uiID = std::shared_ptr<Identity>(new Identity("LIFEBAR_UI", Type::UI));
	uiObject->addComponents<Identity>(uiID);
	// TRANSFORM
	std::shared_ptr<ObjectTransform> uiTransformP1 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 50.f,25.f }, INFINITY + 1.f, STATIC));
	std::shared_ptr<ObjectTransform> uiTransformP2 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 1300.f - 50.f,25.f }, INFINITY + 1.f, STATIC));
	// LIFEBAR
	std::shared_ptr<Lifebar> uiPlayer = std::shared_ptr<Lifebar>(new Lifebar(Personnage::UI_BIGBOY));
	uiObject->addComponents<Lifebar>(uiPlayer);
	if (uiPlayer->getPlayerNbr() == 0)
		uiObject->addComponents<ObjectTransform>(uiTransformP1);
	else
		uiObject->addComponents<ObjectTransform>(uiTransformP2);

	uiObject->getComponents<Lifebar>()->initAllSpritePos();

	///////////////////////////////SCORE///////////////////////////////

	//GameObject & ID
	std::shared_ptr<GameObject> scoreObject = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> scoreID = std::shared_ptr<Identity>(new Identity("SCORE_ID", Type::UI));
	scoreObject->addComponents<Identity>(scoreID);
	// TRANSFORM
	std::shared_ptr<ObjectTransform> scoreTransform1 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 415.f,40.f }, INFINITY, STATIC));
	std::shared_ptr<ObjectTransform> scoreTransform2 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 1613,40.f }, INFINITY + 1.f, STATIC));


	std::shared_ptr<Score> scoreUI = std::shared_ptr<Score>(new Score());

	if (scoreUI->getNbrPlayer() == 0)
		scoreObject->addComponents<ObjectTransform>(scoreTransform1);
	else
		scoreObject->addComponents<ObjectTransform>(scoreTransform2);


	scoreObject->addComponents<Score>(scoreUI);

	scoreUI->initAllPos();
	//--------------------------------------------------------//

	std::shared_ptr<Physique> PhysiquePlayerBB = std::shared_ptr<Physique>(new Physique(sf::Vector2f(350.f, 250.f)));
	//std::shared_ptr<Physique> PhysiquePlayerBB = std::shared_ptr<Physique>(new Physique(sf::Vector2f(400.f, 300.f)));
	//std::shared_ptr<Physique> PhysiquePlayerBB = std::shared_ptr<Physique>(new Physique(sf::Vector2f(2000.f, 2000.f)));
	std::shared_ptr<Collider> coliderPlayer = std::shared_ptr<Collider>(new Collider(transformPlayer, animPlayer, bodyPlayer, "BigBoy"));

	std::shared_ptr<CheckCollision> checkCollisionPlayer = std::shared_ptr<CheckCollision>(new CheckCollision());
	std::shared_ptr<Mouvement> mvtPlayer = std::shared_ptr<Mouvement>(new Mouvement());
	//std::shared_ptr<Audio3D_Manager> soundPlayer = std::shared_ptr<Audio3D_Manager>(new Audio3D_Manager());

	//float newvolume = _m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").getVolume();
	//soundPlayer->addSceneSound("HitOne", "punch_wind.wav", newvolume);
	//soundPlayer->addSceneSound("HitTwo", "punch_wind2.wav", newvolume);
	//soundPlayer->addSceneSound("HitThree", "hit_2.wav", newvolume);
	//soundPlayer->addSceneSound("HitFour", "final_bigboyhit.wav", newvolume);
	//soundPlayer->addSceneSound("Jump", "BigBoyJump.wav", newvolume);
	//soundPlayer->addSceneSound("JumpAttack", "jump_kick_bb.wav", newvolume);
	//soundPlayer->addSceneSound("AtackMitraillette", "Blaster Machine_Gun-01-Burst-03.wav", newvolume);
	//soundPlayer->addSceneSound("AtackFinalCharge", "Resistance-AssaultRifle_03-Single_Shot-04.wav", newvolume);
	//soundPlayer->addSceneSound("AtackDash", "AttackDash.wav", newvolume);
	////soundPlayer->addSceneSound("gethit1", "GoodHit_1.wav");
	////soundPlayer->addSceneSound("gethit2", "GoodHit_2.wav");
	////soundPlayer->addSceneSound("gethit3", "GoodHit_3.wav");


	//coliderPlayer->addColliderBox(transformPlayer, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(300.0f, 300.0f));

	animPlayer->addAnimation("IDLE", "idle_225x497.png", 8, 0.17f, true);
	animPlayer->addAnimation("MOVE", "walk_300x472.png", 8, 0.1f, true);
	animPlayer->addAnimation("SPRINT", "sprint_432x464.png", 8, 0.1f, true);
	animPlayer->addAnimation("JUMP", "jump_299x568.png", 9, 0.06f, true);


	animPlayer->addAnimation("GrabIdle", "idle_grab_366x521.png", 1, 0.06f, true);
	animPlayer->addAnimation("GrabJab", "grab_coup_366x521_4F.png", 4, 0.08f, false);
	animPlayer->addAnimation("GrabJabFinal", "grab_morsure_366x521_5F.png", 5, 0.08f, false);
	animPlayer->addAnimation("GrabJet", "grab_jetavant_366x521_6F.png", 6, 0.11f, false);

	animPlayer->addAnimation("Hit", "prise_degat_296x489.png", 1, 0.06f, false);
	animPlayer->addAnimation("Ejection", "tomber_600x498_7F.png", 7, 0.1f, false);
	animPlayer->addAnimation("Relever", "relever_730x509_6F.png", 6, 0.11f, false);
	animPlayer->addAnimation("Dying", "mort1_847x683_10F.png", 10, 0.11f, false);


	animPlayer->addAnimation("ATTACKJump", "jump_att_670x484.png", 9, 0.06f, false);

	animPlayer->addAnimation("sprintATTACK", "sprint_att_944x489.png", 12, 0.05f, false);


	animPlayer->addAnimation("AttackCharge", "att_lancer_575x557_14F.png", 14, 0.1f, false);
	animPlayer->addAnimation("Charging", "charge2repet_575x557_2F.png", 2, 0.08f, true);
	animPlayer->addAnimation("PrepareCharging", "charge1_575x557_5F.png", 5, 0.08f, false);

	animPlayer->addAnimation("Jab1BB", "x1_419x477_5F.png", 5, 0.05f, false);
	animPlayer->addAnimation("Jab2", "x2_493x457_6F.png", 6, 0.07f, false);
	animPlayer->addAnimation("Jab3", "x3_665x759_7F.png", 7, 0.06f, false);
	animPlayer->addAnimation("Jab4", "x4_393x585_8F.png", 8, 0.06f, false);

	animPlayer->addAnimation("UltimateAttackDebut", "1debut_790x893_5F.png", 5, 0.1f, false);
	animPlayer->addAnimation("UltimateAttackBoucle", "2repetable_790x893_4F.png", 4, 0.08f, true);
	animPlayer->addAnimation("UltimateAttackEnd", "3fin_790x893_16F.png", 16, 0.09f, false);

	PhysiquePlayerBB->setLife(100);



	//Ombre->addComponents<RigidBody>(bodyPlayer);
	PlayerUltimate->addComponents<Identity>(IdPlayerUltimateBB);
	PlayerUltimate->addComponents<Sprite>(PlayerUltimateSprite);
	PlayerUltimate->addComponents<ObjectTransform>(transformPlayerUltimate);
	PlayerUltimate->addComponents<Animation>(animUltime);
	//PlayerUltimate->addComponents<RigidBody>(bodyPlayerUltimate);


	player->addComponents<Identity>(idPlayerBB);
	player->addComponents<ObjectTransform>(transformPlayer);
	player->addComponents<RigidBody>(bodyPlayer);
	player->addComponents<Physique>(PhysiquePlayerBB);
	player->addComponents<Sprite>(spritePlayer);
	player->addComponents<Animation>(animPlayer);
	player->addComponents<Input>(inputPlayer);
	player->addComponents<Collider>(coliderPlayer);
	player->addComponents<CheckCollision>(checkCollisionPlayer);
	player->addComponents<Mouvement>(mvtPlayer);
	player->addComponents<Shake>(ShakePlayer);
	//player->addComponents<Audio3D_Manager>(soundPlayer);


	//_m_object->addGameObject(Ombre);
	player->addGameObject(ObjectOmbre);
	player->addGameObject(PlayerUltimate);
	player->addGameObject(uiObject);
	player->addGameObject(scoreObject);
	_m_object->addGameObject(player);

	_m_object->getObjects("Player")->getComponents<Animation>()->playAnim("IDLE", true);

	//_m_object->getObjects("Player")->getObjects("PlayerUltimeBB")->getComponents<Animation>()->playAnim("Tornado", true);
	//std::cout
}


void Player::initBloodLust(std::shared_ptr<GameObject> _m_object, std::shared_ptr<Input> _input)
{

	std::shared_ptr<GameObject> ObjectOmbre = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> IdOmbre = std::shared_ptr<Identity>(new Identity("OmbreObj", OBJECT));
	std::shared_ptr<Sprite> OmbreSprite = std::shared_ptr<Sprite>(new Sprite("Ombre.png"));
	std::shared_ptr<ObjectTransform> transformOmbre = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 750.f,750.f }, STATIC));
	ObjectOmbre->addComponents<Identity>(IdOmbre);
	ObjectOmbre->addComponents<Sprite>(OmbreSprite);
	ObjectOmbre->addComponents<ObjectTransform>(transformOmbre);

	OmbreSprite->getSprite().setColor(sf::Color(255, 255, 255, 100));

	std::shared_ptr<GameObject> PlayerUltimateFond = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> IdPlayerUltimateBLFond = std::shared_ptr<Identity>(new Identity("PlayerUltimeBLFond", OBJECT));
	std::shared_ptr<ObjectTransform> transformPlayerUltimateFond = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 200.f,1900.f }, STATIC));
	std::shared_ptr<Sprite> PlayerUltimateBlackScreenFond = std::shared_ptr<Sprite>(new Sprite("BlackScreenBloodLust.png"));

	std::shared_ptr<GameObject> PlayerUltimate = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> IdPlayerUltimateBL = std::shared_ptr<Identity>(new Identity("PlayerUltimeBL", OBJECT));
	std::shared_ptr<Sprite> PlayerUltimateSprite = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<ObjectTransform> transformPlayerUltimate = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 200.f,1900.f }, STATIC));
	std::shared_ptr<Shake> ShakePlayerBloodLust = std::shared_ptr<Shake>(new Shake());


	//std::shared_ptr<RigidBody> bodyPlayerUltimate = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Animation> animUltime = std::shared_ptr<Animation>(new Animation());

	animUltime->addAnimation("YeuxAnnim", "sprite_yeux_f12.png", 12, 0.1f, false);
	animUltime->addAnimation("EnchainementAnim", "sprite_fx_f9.png", 9, 0.2f, false);

	std::shared_ptr<GameObject> player = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idPlayerBL = std::shared_ptr<Identity>(new Identity("Player2", PLAYER));


	std::shared_ptr<ObjectTransform> transformPlayer = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 800.f,750.f }, NON_STATIC));


	std::shared_ptr<RigidBody> bodyPlayer = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Sprite> spritePlayer = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animPlayerBL = std::shared_ptr<Animation>(new Animation());
	std::shared_ptr<Mouvement> mvtPlayer = std::shared_ptr<Mouvement>(new Mouvement());
	//std::shared_ptr<Camera> cameraPlayer = std::shared_ptr<Camera>(new Camera());
	std::shared_ptr<Input> inputPlayer = std::move(_input);
	std::shared_ptr<Physique> PhysiquePlayerBL = std::shared_ptr<Physique>(new Physique(sf::Vector2f(400, 300)));
	std::shared_ptr<Collider> coliderPlayer = std::shared_ptr<Collider>(new Collider(transformPlayer, animPlayerBL, bodyPlayer, "BloodLust"));
	std::shared_ptr<CheckCollision> checkCollisionPlayer = std::shared_ptr<CheckCollision>(new CheckCollision());

	//--------------------------------------------------------//

	//GameObject & ID
	std::shared_ptr<GameObject> uiObject = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> uiID = std::shared_ptr<Identity>(new Identity("LIFEBAR_UI", Type::UI));
	uiObject->addComponents<Identity>(uiID);
	// TRANSFORM
	std::shared_ptr<ObjectTransform> uiTransformP1 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 50.f,25.f }, INFINITY + 1.f, STATIC));
	std::shared_ptr<ObjectTransform> uiTransformP2 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 1300.f - 50.f,25.f }, INFINITY + 1.f, STATIC));
	// LIFEBAR
	std::shared_ptr<Lifebar> uiPlayer = std::shared_ptr<Lifebar>(new Lifebar(Personnage::UI_BLOODLUST));
	uiObject->addComponents<Lifebar>(uiPlayer);
	if (uiPlayer->getPlayerNbr() == 0)
		uiObject->addComponents<ObjectTransform>(uiTransformP1);
	else
		uiObject->addComponents<ObjectTransform>(uiTransformP2);

	uiObject->getComponents<Lifebar>()->initAllSpritePos();

	///////////////////////////////SCORE///////////////////////////////

	//GameObject & ID
	std::shared_ptr<GameObject> scoreObject = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> scoreID = std::shared_ptr<Identity>(new Identity("SCORE_ID", Type::UI));
	scoreObject->addComponents<Identity>(scoreID);
	// TRANSFORM
	std::shared_ptr<ObjectTransform> scoreTransform1 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 415.f,40.f }, INFINITY, STATIC));
	std::shared_ptr<ObjectTransform> scoreTransform2 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 1613,40.f }, INFINITY + 1.f, STATIC));


	std::shared_ptr<Score> scoreUI = std::shared_ptr<Score>(new Score());
	if (scoreUI->getNbrPlayer() == 0)
		scoreObject->addComponents<ObjectTransform>(scoreTransform1);
	else
		scoreObject->addComponents<ObjectTransform>(scoreTransform2);

		scoreObject->addComponents<Score>(scoreUI);

	scoreUI->initAllPos();
	//--------------------------------------------------------//

	std::shared_ptr<Audio3D_Manager> soundPlayer = std::shared_ptr<Audio3D_Manager>(new Audio3D_Manager());
	float newvolume = _m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").getVolume();
	soundPlayer->addSceneSound("Poussin", "Poussin.ogg", newvolume);
	soundPlayer->addSceneSound("HitOne", "hit_1_et_2.wav", newvolume);
	soundPlayer->addSceneSound("HitTwo", "hit_3.wav", newvolume);
	soundPlayer->addSceneSound("HitThree", "hit_4.wav", newvolume);
	soundPlayer->addSceneSound("HitThree", "GoodHit_1.wav", newvolume);

	//coliderPlayer->addColliderBox(transformPlayer, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(300.0f, 300.0f));



	animPlayerBL->addAnimation("IDLE", "Sprite_Idle.png", 9, 0.17f, true);
	animPlayerBL->addAnimation("MOVE", "Sprite_Marche.png", 8, 0.12f, true);
	animPlayerBL->addAnimation("SPRINT", "Sprite_Course.png", 10, 0.07f, true);
	animPlayerBL->addAnimation("JUMP", "Sprite_saut.png", 7, 0.07f, true);

	animPlayerBL->addAnimation("GrabIdle", "sprite_idle_f1.png", 1, 0.06f, true);
	animPlayerBL->addAnimation("GrabJab", "sprite_charge_f3.png", 3, 0.09f, false);
	animPlayerBL->addAnimation("GrabJabFinal", "sprite_attaque_f4.png", 4, 0.07f, false);
	animPlayerBL->addAnimation("GrabJet", "Sprite_chop.png", 4, 0.11f, false);

	animPlayerBL->addAnimation("Hit", "Sprite-prise-de-degats.png", 1, 0.06f, false);
	animPlayerBL->addAnimation("Ejection", "Sprite_Chute.png", 6, 0.1f, false);
	animPlayerBL->addAnimation("Relever", "Sprite_relever.png", 8, 0.11f, false);
	animPlayerBL->addAnimation("Dying", "Sprite_Mort_Apres_Chute.png", 7, 0.11f, false);

	animPlayerBL->addAnimation("ATTACKJump", "Sprit_Saut_Attaque.png", 7, 0.06f, false);

	animPlayerBL->addAnimation("sprintATTACK", "Sprite-Attaque-sprint.png", 8, 0.05f, false);

	animPlayerBL->addAnimation("AttackCharge", "Proute.png", 9, 0.1f, false);

	animPlayerBL->addAnimation("Charging", "sprite_tourner_f8_v2.png", 8, 0.08f, true);
	animPlayerBL->addAnimation("PrepareCharging", "sprite_tourner_f8_v2.png", 8, 0.08f, false);

	animPlayerBL->addAnimation("Jab1BL", "Sprite_combo_1.png", 8, 0.04f, false);
	animPlayerBL->addAnimation("Jab2", "Sprite_combo_2.png", 8, 0.04f, false);
	animPlayerBL->addAnimation("Jab3", "Sprite-combo-3.png", 7, 0.05f, false);
	animPlayerBL->addAnimation("Jab4", "Sprite-combo-4.png", 7, 0.06f, false);

	animPlayerBL->addAnimation("UltimateAttackDebut", "sprite_idle_f4.png", 4, 0.1f, false);
	animPlayerBL->addAnimation("UltimateAttackEnd", "sprite_fin_ulti_f4.png", 4, 0.2f, false);

	PhysiquePlayerBL->setLife(100);
	PlayerUltimate->addComponents<Identity>(IdPlayerUltimateBL);

	PlayerUltimate->addComponents<Sprite>(PlayerUltimateSprite);
	PlayerUltimate->addComponents<ObjectTransform>(transformPlayerUltimate);
	PlayerUltimate->addComponents<Animation>(animUltime);

	//transformPlayerUltimateFond->setZBuffer(INFINITY *2);

	PlayerUltimateBlackScreenFond->getSprite().setColor(sf::Color(255, 255, 255, 0));

	PlayerUltimateFond->addComponents<Identity>(IdPlayerUltimateBLFond);
	PlayerUltimateFond->addComponents<ObjectTransform>(transformPlayerUltimateFond);
	PlayerUltimateFond->addComponents<Sprite>(PlayerUltimateBlackScreenFond);


	player->addComponents<Identity>(idPlayerBL);
	player->addComponents<ObjectTransform>(transformPlayer);
	player->addComponents<RigidBody>(bodyPlayer);
	player->addComponents<Sprite>(spritePlayer);
	player->addComponents<Animation>(animPlayerBL);
	player->addComponents<Mouvement>(mvtPlayer);
	//player->addComponents<Camera>(cameraPlayer);
	player->addComponents<Input>(inputPlayer);
	player->addComponents<Physique>(PhysiquePlayerBL);
	player->addComponents<Collider>(coliderPlayer);
	player->addComponents<CheckCollision>(checkCollisionPlayer);
	player->addComponents<Audio3D_Manager>(soundPlayer);
	player->addComponents<Shake>(ShakePlayerBloodLust);

	player->addGameObject(ObjectOmbre);
	player->addGameObject(PlayerUltimateFond);
	player->addGameObject(PlayerUltimate);
	player->addGameObject(uiObject);
	player->addGameObject(scoreObject);
	_m_object->addGameObject(player);
	PhysiquePlayerBL->setLife(100);
	_m_object->getObjects("Player2")->getComponents<Animation>()->playAnim("IDLE", true);
}
void Player::initFinalPlayableBoss(std::shared_ptr<GameObject> _m_object, std::shared_ptr<Input> _input)
{

	std::shared_ptr<GameObject> player = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idPlayerKP = std::shared_ptr<Identity>(new Identity("Player3", PLAYER));
	std::shared_ptr<ObjectTransform> transformPlayer = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 300.f,1900.f }, NON_STATIC));
	std::shared_ptr<RigidBody> bodyPlayer = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Sprite> spritePlayer = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animPlayerKP = std::shared_ptr<Animation>(new Animation());
	std::shared_ptr<Mouvement> mvtPlayer = std::shared_ptr<Mouvement>(new Mouvement());
	//std::shared_ptr<Camera> cameraPlayer = std::shared_ptr<Camera>(new Camera());
	std::shared_ptr<Input> inputPlayer = std::move(_input);
	std::shared_ptr<Physique> PhysiquePlayerBL = std::shared_ptr<Physique>(new Physique(sf::Vector2f(400, 300)));
	std::shared_ptr<Collider> coliderPlayer = std::shared_ptr<Collider>(new Collider(transformPlayer, animPlayerKP, bodyPlayer, "KimpahPlayer"));
	std::shared_ptr<CheckCollision> checkCollisionPlayer = std::shared_ptr<CheckCollision>(new CheckCollision());

	//coliderPlayer->addColliderBox(transformPlayer, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(300.0f, 300.0f));

	animPlayerKP->addAnimation("IDLE", "IdlePos.png", 8, 0.17f, true);
	animPlayerKP->addAnimation("MOVE", "sheetMARCHE_F8.png", 8, 0.12f, true);
	animPlayerKP->addAnimation("SPRINT", "boss_sprint_397_363_8f.png", 8, 0.07f, true);
	animPlayerKP->addAnimation("JUMP", "sheetjump-boss_F7.png", 7, 0.07f, true);

	//animPlayerKP->addAnimation("GrabIdle", "sprite_idle_f1.png", 1, 0.06f, true);
	//animPlayerKP->addAnimation("GrabJab", "sprite_charge_f3.png", 3, 0.09f, false);
	// 

	//animPlayerKP->addAnimation("GrabJabFinal", "sprite_attaque_f4.png", 4, 0.07f, false);
	//animPlayerKP->addAnimation("GrabJet", "Sprite_chop.png", 4, 0.11f, false);


	animPlayerKP->addAnimation("Hit", "hit-kimpah.png", 1, 0.06f, false);
	animPlayerKP->addAnimation("Ejection", "falling_4025_480_8f.png", 7, 0.1f, false);
	animPlayerKP->addAnimation("Relever", "stand-up--kimpah_F9.png", 9, 0.06f, false);
	animPlayerKP->addAnimation("Dying", "Sprite_Mort_Apres_Chute.png", 7, 0.11f, false);

	animPlayerKP->addAnimation("ATTACKJump", "jump_att_player_4606_651_7f.png", 7, 0.08f, false);

	animPlayerKP->addAnimation("sprintATTACK", "Att_S_T_Red_F5.png", 5, 0.08f, false);

	animPlayerKP->addAnimation("AttackCharge", "charged_att-3.png", 10, 0.06f, false);

	animPlayerKP->addAnimation("Charging", "charged_att_2.png", 3, 0.08f, true);
	animPlayerKP->addAnimation("PrepareCharging", "charged_att_1.png", 4, 0.08f, false);

	animPlayerKP->addAnimation("Jab1KP", "Combo_1_4_T_Red.png", 3, 0.11f, false);
	animPlayerKP->addAnimation("Jab2", "Combo_2_4_T_Red.png", 2, 0.08f, false);
	animPlayerKP->addAnimation("Jab3", "Combo_3_4_T_Red.png", 3, 0.1f, false);
	animPlayerKP->addAnimation("Jab4", "Combo_4_4_T_Red.png", 4, 0.1f, false);

	player->addComponents<Identity>(idPlayerKP);
	player->addComponents<ObjectTransform>(transformPlayer);
	player->addComponents<RigidBody>(bodyPlayer);
	player->addComponents<Sprite>(spritePlayer);
	player->addComponents<Animation>(animPlayerKP);
	player->addComponents<Mouvement>(mvtPlayer);
	//player->addComponents<Camera>(cameraPlayer);
	player->addComponents<Input>(inputPlayer);
	player->addComponents<Physique>(PhysiquePlayerBL);
	player->addComponents<Collider>(coliderPlayer);
	player->addComponents<CheckCollision>(checkCollisionPlayer);

	_m_object->addGameObject(player);

	_m_object->getObjects("Player3")->getComponents<Animation>()->playAnim("IDLE", true);

}
void Player::Update(std::shared_ptr<GameObject> _m_object)
{

	//_m_object->getObjects("PlayerUltimeBB")->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 255, 100));

}
