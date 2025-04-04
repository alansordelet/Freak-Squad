#include "Game.h"
#include "Menu.h"
#include "Camera.h"
#include "Physique.h"
#include "FeedBackScore.h"
#include "IA_Pattern.h"
#include "CheckCollision.h"
#include "Ui.h"
#include "Shake.h"
#include "Blood.h"
#include "AI.h"
#include "Hit.h"
#include "Fumee.h"
#include "IA_PatternT.h"
#include "IA_PatternS.h"
#include "IA_PatternC.h"
#include "IA_PatternH.h"
#include "PauseGameCOMP.h"
#include "Boss_Smoke.h"
#include "Sounds3D.h"
#include "CollisionMap.h"
#include "CollisionMask.h"
#include "Package.h"
#include "TriggerZone.h"
#include "Light_Manager.h"
#include "Starters.h"
#include "Go.h"
#include "Parallax.h"
#include "TriggerZone.h"
#include "Particules.h"
#include "Transition.h"
#include "Package.h"
#include "Ui_Player.h"
#include "Timer.h"

Game::Game()
{
	timer = 0.f;
	timerInput = 0.f;
	m_transitionEndgame = false;
	m_volumeMusic = 0.0f;
	m_volumeSound = 0.0f;
}

Game::Game(std::shared_ptr<Ui> _ui, std::shared_ptr<Input> _inputP1, std::shared_ptr<Input> _inputP2, float _volumeMusic, float _volumeSound)
{
	timer = 0;
	timerInput = 0;

	m_uiTransit = std::move(_ui);

	m_inputP1 = std::move(_inputP1);

	if (_inputP2 != nullptr)
	{
		m_inputP2 = std::move(_inputP2);
	}

	m_volumeMusic = _volumeMusic;
	m_volumeSound = _volumeSound;
}

void Game::init()
{
	m_isReady = true; // Pret a faire l'update
	m_firstPass = true; // Ne fait plus de cinematique
	m_isIntro = true;
	m_isEnding = false;
	m_isCredit = false;

	m_object = std::shared_ptr<GameObject>(new GameObject);
	std::shared_ptr<Identity> idRootWorld = std::shared_ptr<Identity>(new Identity("Game", ROOT));
	m_object->addComponents<Identity>(idRootWorld);

	m_objTransition = std::shared_ptr<GameObject>(new GameObject);
	std::shared_ptr<Identity> idRootTransition = std::shared_ptr<Identity>(new Identity("RootTransition", ROOT));
	std::shared_ptr<Transition> compoTransition = std::shared_ptr<Transition>(new Transition);
	std::shared_ptr<Input>InputTransition = std::shared_ptr<Input>(new Input);
	m_objTransition->addComponents<Identity>(idRootTransition);
	m_objTransition->addComponents<Transition>(compoTransition);
	m_objTransition->addComponents<Input>(InputTransition);

	parallax.initParallax(m_object);
	map.initMap(m_object, m_volumeMusic, m_volumeSound);
	m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("CargoHoldmusic").play();
	fly.initFly(m_object);
	fumee.initFumee(m_object);
	map.initPremierPlan(m_object);
	introending.initRead(m_object);

	initPlayers();
	initLight();
	initBoss();
	initDestructible();
	initTriggerZone();
	initTransition();
	initTimer();

#pragma region Blood
	std::shared_ptr<GameObject> blood = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idblood = std::shared_ptr<Identity>(new Identity("Blood", OBJECT));
	std::shared_ptr<Blood> BLOOD = std::shared_ptr<Blood>(new Blood());

	blood->addComponents<Identity>(idblood);
	blood->addComponents<Blood>(BLOOD);

	m_object->addGameObject(blood);
#pragma endregion Blood

#pragma region Hit
	std::shared_ptr<GameObject> hit = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idHit = std::shared_ptr<Identity>(new Identity("Hit", OBJECT));
	std::shared_ptr<Hit> m_hit = std::shared_ptr<Hit>(new Hit());
	hit->addComponents<Identity>(idHit);
	hit->addComponents<Hit>(m_hit);
	m_object->addGameObject(hit);

	std::shared_ptr<GameObject> bighit = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idbigHit = std::shared_ptr<Identity>(new Identity("BigHit", OBJECT));
	std::shared_ptr<BigHit> m_bighit = std::shared_ptr<BigHit>(new BigHit());
	bighit->addComponents<Identity>(idbigHit);
	bighit->addComponents<BigHit>(m_bighit);
	m_object->addGameObject(bighit);

#pragma endregion Hit

#pragma region BoostEffect
	std::shared_ptr<GameObject> Boost = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idBoost = std::shared_ptr<Identity>(new Identity("BoostEffect", OBJECT));
	std::shared_ptr<Particules> m_Boost = std::shared_ptr<Particules>(new Particules());
	Boost->addComponents<Identity>(idBoost);
	Boost->addComponents<Particules>(m_Boost);
	m_object->addGameObject(Boost);
#pragma endregion
#pragma region Particules
	std::shared_ptr<GameObject> fxBigBoy = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idfxBigBoy = std::shared_ptr<Identity>(new Identity("FxUltiBigBoy", OBJECT));
	std::shared_ptr<Particules> m_fxBigBoyt = std::shared_ptr<Particules>(new Particules());
	fxBigBoy->addComponents<Identity>(idfxBigBoy);
	fxBigBoy->addComponents<Particules>(m_fxBigBoyt);
	m_object->addGameObject(fxBigBoy);
#pragma endregion

	std::shared_ptr<GameObject> PauseGame = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idRootPauseGameCOMP = std::shared_ptr<Identity>(new Identity("RootPauseGameCOMP", ROOT));
	std::shared_ptr<PauseGameCOMP> compoPauseGameCOMP = std::shared_ptr<PauseGameCOMP>(new PauseGameCOMP(m_object));
	PauseGame->addComponents<Identity>(idRootPauseGameCOMP);
	PauseGame->addComponents<PauseGameCOMP>(compoPauseGameCOMP);
	m_object->addGameObject(PauseGame);
}

void Game::update()
{
	timer += tools::GetTimeDelta();
	timerInput += tools::GetTimeDelta();

	// Lance l'intro
	if (m_isIntro)
	{
		introending.getObject()->getComponents<DialogueReader>()->updateIntro();
		if (!introending.getObject()->getComponents<DialogueReader>()->getEndIntro())
			m_isIntro = false;
	}
	else if (m_isEnding) // Lance l'ending
	{
		introending.getObject()->getComponents<DialogueReader>()->updateEnding();
		if (!introending.getObject()->getComponents<DialogueReader>()->getEnding())
		{
			m_objTransition->getComponents<Transition>()->resetStartEnding();
			m_isEnding = false;
			m_isCredit = true;

		}
	}
	else if (m_isCredit) // Lance les crédits
	{
		m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("VictoryMusic").stop();
		m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("text").stop();
		if (m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("CreditMusic").getStatus() == sf::Sound::Stopped)
			m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("CreditMusic").play();

		m_objTransition->getComponents<Transition>()->setStartCredit(true);
		m_objTransition->getComponents<Transition>()->update();
		if (m_objTransition->getComponents<Transition>()->getRetourMenu())
		{
			m_isCredit = false;
		}
	}
	else // Lance le Game/Menu...
	{
		if (!m_object->getObjects("RootPauseGameCOMP")->getComponents<PauseGameCOMP>()->m_activeGame)
			m_object->updateAllObject();

		m_objTransition->updateAllComponents();
		m_object->getObjects("RootPauseGameCOMP")->getComponents<PauseGameCOMP>()->update2();


		if (m_object->getObjects("starters")->getComponents<Starters>()->getSpawnHOLObool() == true)
		{
			creatMonster(TRASHERHOLO, 1600.f, 800.f);
			m_object->getObjects("starters")->getComponents<Starters>()->setSpawnHOLObool(false);
		}
		if (m_objTransition->getComponents<Transition>()->getBoolFinNiveau() == true)
		{
			m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("BossMusic").stop();
			if (m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("VictoryMusic").getStatus() == sf::Sound::Stopped)
				m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("VictoryMusic").play();

		}

		if (m_objTransition->getComponents<Transition>()->getEnd() == true)
		{
			m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("CreditMusic").stop();
		}


		if (GameObject::l_Player.size() > 1)
		{
			std::cout << GameObject::l_Player.size() << std::endl;
			if (m_object->getObjects("Player")->getComponents<ObjectTransform>()->getPosition().x > m_object->getObjects("Player2")->getComponents<ObjectTransform>()->getPosition().x)
			{
				m_object->getObjects("Camera")->getComponents<Camera>()->setPositiontoObjectTransform(m_object->getObjects("Player")->getComponents<ObjectTransform>());
			}
			else
			{
				m_object->getObjects("Camera")->getComponents<Camera>()->setPositiontoObjectTransform(m_object->getObjects("Player2")->getComponents<ObjectTransform>());
			}

			if (m_object->getObjects("Player")->getComponents<Physique>()->B_Dead && m_object->getObjects("Player2")->getComponents<Physique>()->B_Dead)
			{
				m_objTransition->getComponents<Transition>()->DoFonduMORT();

			}
		}
		else
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->setPositiontoObjectTransform(m_object->getObjects(PLAYER)->getComponents<ObjectTransform>());
			if (m_object->getObjects(PLAYER)->getComponents<Physique>()->B_Dead)
			{
				m_objTransition->getComponents<Transition>()->DoFonduMORT();

			}
		}





		if (m_object->getObjects("Player") != nullptr)
		{

			if (m_object->getObjects("Player")->getComponents<Physique>()->TornadoActive)
			{
				m_object->getObjects("Player")->getObjects("PlayerUltimeBB")->setActive(true);
			}
			else
			{
				m_object->getObjects("Player")->getObjects("PlayerUltimeBB")->setActive(false);
			}
		}
		if (m_object->getObjects("Player2") != nullptr)
		{
			if (m_object->getObjects("Player2")->getComponents<Physique>()->t_Attack == UltimeAttack)
			{
				m_object->getObjects("Player2")->getComponents<ObjectTransform>()->setState(STATIC);

				m_object->getObjects("Player2")->getComponents<ObjectTransform>()->setZBuffer(INFINITY);
				m_object->getObjects("Player2")->getObjects("PlayerUltimeBLFond")->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(m_object->getObjects("Camera")->getComponents<Camera>()->getViewPos().x, m_object->getObjects("Camera")->getComponents<Camera>()->getViewPos().y));

			}
			else
			{
				m_object->getObjects("Player2")->getObjects("PlayerUltimeBLFond")->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 255, 0));
			}
			if (m_object->getObjects("Player2")->getComponents<Physique>()->UltimateBlood)
			{

				m_object->getObjects("Player2")->getObjects("PlayerUltimeBL")->setActive(true);
				m_object->getObjects("Player2")->getObjects("PlayerUltimeBL")->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(m_object->getObjects("Camera")->getComponents<Camera>()->getViewPos().x + 1000, m_object->getObjects("Camera")->getComponents<Camera>()->getViewPos().y + 1000));


				m_object->getObjects("Player2")->getObjects("PlayerUltimeBLFond")->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(m_object->getObjects("Camera")->getComponents<Camera>()->getViewPos().x, m_object->getObjects("Camera")->getComponents<Camera>()->getViewPos().y));
			}
			else
			{

				m_object->getObjects("Player2")->getObjects("PlayerUltimeBL")->setActive(false);
			}
		}

		for (auto player : GameObject::l_Player)
		{
			sf::Vector2f pos = player->getComponents<ObjectTransform>()->getPosition();

			if (player->getComponents<Input>()->getType(gp::Gamepad::START) == PRESSED)
			{
				m_object->getObjects("RootPauseGameCOMP")->getComponents<PauseGameCOMP>()->setControlePause(player->getComponents<Input>());
				m_object->getObjects("RootPauseGameCOMP")->getComponents<PauseGameCOMP>()->m_activeGame = true;
				break;
			}
			if (player->getComponents<Input>()->getType(gp::Gamepad::A) == PRESSED && m_object->getObjects("RootPauseGameCOMP")->getComponents<PauseGameCOMP>()->m_NavigationMenu == 4)
			{
				// Ne revient pas au MENU
				m_objTransition->getComponents<Transition>()->m_activeBackMenu = true;
				m_objTransition->getComponents<Transition>()->DoFonduScore(NOIR2);
			}
		}

		if (m_objTransition->getComponents<Transition>()->getStartEnding()) // Permet de lancer l'ending après le score
		{
			introending.getObject()->getComponents<DialogueReader>()->setEnding(true);
			m_isEnding = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
			m_object->getObjects("Boss")->getComponents<Physique>()->setLife(0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_object->getObjects("RootPauseGameCOMP")->getComponents<PauseGameCOMP>()->m_activeGame = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			m_objTransition->getComponents<Transition>()->setBoolFinNiveau(true);

		if (m_object->getObjects("Boss")->getComponents<Physique>()->getLife() <= 0 && !m_transitionEndgame)
		{
			m_objTransition->getComponents<Transition>()->setBoolFinNiveau(true);

			int tmpScore = 0;
			int tmpComboMax = 0;

			for (auto player : GameObject::l_Player)
			{
				tmpScore += player->getObjects("SCORE_ID")->getComponents<Score>()->getScoreTotal();
				if (tmpComboMax < player->getObjects("SCORE_ID")->getComponents<Score>()->getMaxCombo())
					tmpComboMax = player->getObjects("SCORE_ID")->getComponents<Score>()->getMaxCombo();
			}
			m_objTransition->getComponents<Transition>()->setScore(tmpScore);
			m_objTransition->getComponents<Transition>()->setTimer(m_object->getObjects("TIMER")->getComponents<Timer>()->getTimer());
			m_objTransition->getComponents<Transition>()->setCombo(tmpComboMax);
			m_objTransition->getComponents<Transition>()->calculScore();
			m_transitionEndgame = true;
		}

		if (m_objTransition->getComponents<Transition>()->getTransitToMenu())
		{
			m_object->deleteAllObjects();

			GameObject::l_Player.clear();
			GameObject::l_Ennemy.clear();
			GameObject::l_Object.clear();
			GameObject::l_Ui.clear();
			GameObject::l_Collectible.clear();
			WindowManager::getInstance()->getWindow()->getWindow().setView(WindowManager::getInstance()->getWindow()->getWindow().getDefaultView());
			this->p_SceneManager->transitionTo(new Menu());
			return;
		}
	}

	for (auto player : GameObject::l_Player)
	{
		player->getObjects("LIFEBAR_UI")->updateAllComponents();
		player->getObjects("SCORE_ID")->updateAllComponents();

	}

	if ((!m_isIntro && !m_isEnding /*&& !m_object->getObjects("RootPauseGameCOMP")->getComponents<PauseGameCOMP>()->m_activeGame*/) /*|| (m_object->getObjects("Boss")->getComponents<Physique>()->getLife() <= 0 && !m_transitionEndgame)*/)
		m_object->getObjects("TIMER")->updateAllComponents();
}

void Game::display()
{
	if (m_isIntro || m_isEnding) // Affiche l'intro et l'ending
		introending.getObject()->getComponents<DialogueReader>()->display();

	else if (m_isCredit) // Affiche les crédits
	{
		m_objTransition->getComponents<Transition>()->draw();
	}
	else // Lance le reste
	{
		m_object->drawAllObject();

		for (auto player : GameObject::l_Player)
		{
			player->getObjects("LIFEBAR_UI")->drawComponents();
			player->getObjects("SCORE_ID")->drawComponents();
		}
		if (m_object->getObjects("Boss")->isActive())
			m_object->getObjects("Boss")->getObjects("LIFEBAR_UI")->drawComponents();
		//m_objMenuPause->drawComponents();

		m_object->getObjects("TIMER")->drawComponents();

		m_object->getObjects("RootPauseGameCOMP")->drawComponents();
		m_objTransition->drawComponents();

	}


}

void Game::deInit()
{
}

void Game::creatMonster(MOB _mob, float _posX, float _posY)
{
	std::string name;
	if (_mob == MOB::TRASHER)
		name = "trasher" + std::to_string(nbTrasher);
	else if (_mob == TRASHERHOLO)
		name = "trasherH" + std::to_string(nbTrasherH);
	else if (_mob == SPIKER)
		name = "spiker" + std::to_string(nbSpiker);
	else if (_mob == CLEEVER || _mob == CLEEVERZOMBI)
		name = "cleever" + std::to_string(nbCleever);




	std::shared_ptr<GameObject> ObjectOmbre = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> IdOmbre = std::shared_ptr<Identity>(new Identity("OmbreObj", OBJECT));
	std::shared_ptr<Sprite> OmbreSprite = std::shared_ptr<Sprite>(new Sprite("Ombre.png"));
	std::shared_ptr<ObjectTransform> transformOmbre = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 550.f,750.f }, STATIC));
	ObjectOmbre->addComponents<Identity>(IdOmbre);
	ObjectOmbre->addComponents<Sprite>(OmbreSprite);
	ObjectOmbre->addComponents<ObjectTransform>(transformOmbre);
	OmbreSprite->getSprite().setColor(sf::Color(255, 255, 255, 100));


	std::shared_ptr<GameObject> ennemy = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idennemy = std::shared_ptr<Identity>(new Identity(name, ENNEMY));
	std::shared_ptr<ObjectTransform> transformennemy = std::shared_ptr<ObjectTransform>(new ObjectTransform({ _posX,_posY }, NON_STATIC));
	std::shared_ptr<RigidBody> bodyennemy = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Sprite> spriteennemy = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animennemy = std::shared_ptr<Animation>(new Animation());
	std::shared_ptr<Mouvement> mvtEnnemy = std::shared_ptr<Mouvement>(new Mouvement());
	std::shared_ptr<Physique> PhysiqueEnnemis = std::shared_ptr<Physique>(new Physique(sf::Vector2f(500, 300)));
	std::shared_ptr<CheckCollision> checkCollisionennemy = std::shared_ptr<CheckCollision>(new CheckCollision());
	std::shared_ptr<Shake> ShakeMobHolo = std::shared_ptr<Shake>(new Shake());


	//coliderennemy->addCollliderBox(transformennemy, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(300.0f, 300.0f));

	if (_mob == TRASHER)
	{
		/*std::function<const void()> moove = [this, bodyennemy, IATrash]() -> void {IAFonction::mooveToPlay(this, bodyennemy, IATrash); };
		std::function<const void()> back = [this, bodyennemy, IATrash]() -> void {IAFonction::back(this, bodyennemy, IATrash); };
		std::function<const void()> monte = [this, bodyennemy, IATrash]() -> void {IAFonction::monte(this, bodyennemy, IATrash); };
		std::function<const bool()> condition = [this, IATrash]() -> bool {return IAFonction::cMooveToPlayTrash(this, IATrash);};
		std::function<const bool()> conditionC = [this, IATrash]() -> bool {return IAFonction::cMonteTrash(this, IATrash);};

		std::shared_ptr<NodeComposite>racine = std::shared_ptr<NodeComposite>(new NodeComposite(ennemy, SELECTOR));
		std::shared_ptr<NodeComposite>freeMoove = std::shared_ptr<NodeComposite>(new NodeComposite(ennemy, SEQUENCE));
		std::shared_ptr<NodeComposite>test1 = std::shared_ptr<NodeComposite>(new NodeComposite(ennemy, SEQUENCE));
		std::shared_ptr<NodeComposite>test2 = std::shared_ptr<NodeComposite>(new NodeComposite(ennemy, SEQUENCE));

		std::shared_ptr<NodeTask>MoveToPlayer = std::shared_ptr<NodeTask>(new NodeTask(ennemy, moove));
		std::shared_ptr<NodeTask>BackTest = std::shared_ptr<NodeTask>(new NodeTask(ennemy, back));
		std::shared_ptr<NodeTask>monteTest = std::shared_ptr<NodeTask>(new NodeTask(ennemy, monte));
		std::shared_ptr<NodeDecorator>conditiontest = std::shared_ptr<NodeDecorator>(new NodeDecorator(ennemy, condition));
		std::shared_ptr<NodeDecorator>condition2 = std::shared_ptr<NodeDecorator>(new NodeDecorator(ennemy, conditionC));

		test2->add(monteTest);
		test2->addDecorator(condition2);

		freeMoove->add(MoveToPlayer);
		freeMoove->addDecorator(conditiontest);

		test1->add(BackTest);

		racine->add(test1);
		racine->add(freeMoove);
		racine->add(test2);

		std::shared_ptr<AI>ia = std::shared_ptr<AI>(new AI(racine, ennemy));
		ennemy->addComponents<AI>(ia);*/
		std::shared_ptr<IA_TRASHER> IATrash = std::shared_ptr<IA_TRASHER>(new IA_TRASHER());
		std::shared_ptr<Collider> coliderennemy = std::shared_ptr<Collider>(new Collider(transformennemy, animennemy, bodyennemy, "TRASHER"));
		animennemy->addAnimation("IDLEMOB", "1idle_287x452.png", 6, 0.17f, true);
		animennemy->addAnimation("MOVE", "2deplacement_258x399.png", 7, 0.08f, true);
		animennemy->addAnimation("DOUBLEHIT", "3poing_marteau_437x442.png", 10, 0.1f, false);
		animennemy->addAnimation("JAB", "poing_face_466x384.png", 8, 0.1f, false);
		animennemy->addAnimation("SPAWN", "8spawn_287x419.png", 11, 0.12f, false);
		animennemy->addAnimation("HITTRASH", "5gros_degat_488x452.png", 7, 0.12f, false);
		animennemy->addAnimation("DEATH", "7mort_sol_sang_535x451.png", 23, 0.1f, false);
		animennemy->addAnimation("RELEVE", "9releve_482x414.png", 7, 0.13f, true);
		ennemy->addComponents<IA_TRASHER>(IATrash);
		ennemy->addComponents<Collider>(coliderennemy);
		PhysiqueEnnemis->setLife(IATrash->m_life);
		PhysiqueEnnemis->m_typeMob = T;
		nbTrasher++;
	}
	else if (_mob == TRASHERHOLO)
	{
		std::shared_ptr<IA_PatternH> IATrash = std::shared_ptr<IA_PatternH>(new IA_PatternH());
		std::shared_ptr<Collider> coliderennemy = std::shared_ptr<Collider>(new Collider(transformennemy, animennemy, bodyennemy, "TRASHER"));
		animennemy->addAnimation("IDLEMOB", "11idle_287x452.png", 6, 0.17f, true);
		animennemy->addAnimation("MOVE", "12deplacement_258x399.png", 7, 0.08f, true);
		animennemy->addAnimation("DOUBLEHIT", "13poing_marteau_437x442.png", 10, 0.1f, false);
		animennemy->addAnimation("JAB", "14poing_face_466x384.png", 8, 0.1f, false);
		animennemy->addAnimation("SPAWN", "18spawn_287x419.png", 11, 0.12f, false);
		animennemy->addAnimation("HITTRASH", "15gros_degat_488x452.png", 7, 0.12f, false);
		animennemy->addAnimation("DEATH", "17mort_sol_sang_535x451.png", 23, 0.1f, true);
		animennemy->addAnimation("RELEVE", "19releve_482x414.png", 7, 0.13f, true);
		ennemy->addComponents<IA_PatternH>(IATrash);
		ennemy->addComponents<Collider>(coliderennemy);
		PhysiqueEnnemis->setLife(IATrash->m_life);
		PhysiqueEnnemis->m_typeMob = H;
		nbTrasherH++;
	}
	else if (_mob == SPIKER)
	{
		std::shared_ptr<IA_SPIKER> IASpik = std::shared_ptr<IA_SPIKER>(new IA_SPIKER());
		std::shared_ptr<Collider> coliderennemy = std::shared_ptr<Collider>(new Collider(transformennemy, animennemy, bodyennemy, "SPIKER"));
		animennemy->addAnimation("IDLEMOB", "Spiker_Idle_L2268_H369_6F.png", 6, 0.17f, true);
		animennemy->addAnimation("MOVE", "Spiker_Marche_L320_H361_5F.png", 5, 0.08f, true);
		animennemy->addAnimation("SPAWN", "Spawn_Spiker_L578_H931_12F.png", 12, 0.1f, false);
		animennemy->addAnimation("HITTRASH", "Spiker_Projection_L586_H439_10F.png", 10, 0.12f, false);
		animennemy->addAnimation("DEATH", "Spiker_Mort_L572_H244_14F.png", 14, 0.1f, false);
		animennemy->addAnimation("RELEVE", "spiker-se-relève_Sprite_L529_H419_6F.png", 6, 0.13f, true);
		animennemy->addAnimation("LONGHIT", "Spiker-coup-distant-180 centré attaque.png", 8, 0.1f, false);
		animennemy->addAnimation("GRAB", "Spiker_attaque_dash_grab_L660_H656_16F.png", 16, 0.1f, false);
		animennemy->addAnimation("PROJECTION", "Spiker_Projection_L586_H439_10F.png", 10, 0.1f, true);
		ennemy->addComponents<IA_SPIKER>(IASpik);
		ennemy->addComponents<Collider>(coliderennemy);
		PhysiqueEnnemis->setLife(IASpik->m_life);
		PhysiqueEnnemis->m_typeMob = S;
		nbSpiker++;
	}
	else if (_mob == CLEEVER || _mob == CLEEVERZOMBI)
	{
		std::shared_ptr<IA_CLEEVER> IACleev;
		if (_mob == CLEEVER)
			IACleev = std::shared_ptr<IA_CLEEVER>(new IA_CLEEVER());
		else
			IACleev = std::shared_ptr<IA_CLEEVER>(new IA_CLEEVER(true));

		std::shared_ptr<Collider> coliderennemy = std::shared_ptr<Collider>(new Collider(transformennemy, animennemy, bodyennemy, "CLEEVER"));
		animennemy->addAnimation("IDLEMOB", "Idle_T_Red.png", 6, 0.17f, true);
		animennemy->addAnimation("MOVE", "Marche_T_Red.png", 6, 0.12f, true);
		animennemy->addAnimation("SPAWNCORDE", "SpawnCorde.png", 4, 0.1f, false);
		animennemy->addAnimation("SPAWNTOMBE", "SpawnTombe.png", 8, 0.1f, false);
		animennemy->addAnimation("SPAWNSOL", "SpawnSol.png", 5, 0.8f, false);
		animennemy->addAnimation("HITTRASH", "takeDamage.png", 9, 0.12f, false);
		animennemy->addAnimation("PROJECTION", "Proj_T_Red.png", 8, 0.12f, false);
		animennemy->addAnimation("DEATH", "Mort_T_Red.png", 20, 0.1f, false);
		animennemy->addAnimation("RELEVE", "Releve_T_Red.png", 7, 0.08f, false);
		animennemy->addAnimation("JAB", "Att_S_T_Red.png", 8, 0.08f, true);
		animennemy->addAnimation("UPPERCUT", "Att_Hupercut_T_Red.png", 10, 0.07f, false);
		animennemy->addAnimation("DASHAVANT", "Esquive_AV_T_Red.png", 11, 0.07f, true);
		animennemy->addAnimation("DASHARRIERE", "Esquive_AR_T_Red.png", 11, 0.07f, true);
		ennemy->addComponents<IA_CLEEVER>(IACleev);
		ennemy->addComponents<Collider>(coliderennemy);
		PhysiqueEnnemis->setLife(IACleev->m_life);
		PhysiqueEnnemis->m_typeMob = C;
		nbCleever++;
	}

	ennemy->addComponents<Identity>(idennemy);
	ennemy->addComponents<ObjectTransform>(transformennemy);
	ennemy->addComponents<RigidBody>(bodyennemy);
	ennemy->addComponents<Sprite>(spriteennemy);
	ennemy->addComponents<Animation>(animennemy);
	ennemy->addComponents<CheckCollision>(checkCollisionennemy);
	ennemy->addComponents<Mouvement>(mvtEnnemy);
	ennemy->addComponents<Physique>(PhysiqueEnnemis);
	ennemy->addComponents<Shake>(ShakeMobHolo);

	ennemy->addGameObject(ObjectOmbre);
	m_object->addGameObject(ennemy);
	m_object->getObjects(name)->getComponents<Animation>()->playAnim("MOVE", true);
}

void Game::creatMonster(std::string _name, MOB _mob, float _posX, float _posY)
{

	std::shared_ptr<GameObject> ObjectOmbre = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> IdOmbre = std::shared_ptr<Identity>(new Identity("OmbreObj", OBJECT));
	std::shared_ptr<Sprite> OmbreSprite = std::shared_ptr<Sprite>(new Sprite("Ombre.png"));
	std::shared_ptr<ObjectTransform> transformOmbre = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 550.f,750.f }, STATIC));
	ObjectOmbre->addComponents<Identity>(IdOmbre);
	ObjectOmbre->addComponents<Sprite>(OmbreSprite);
	ObjectOmbre->addComponents<ObjectTransform>(transformOmbre);
	OmbreSprite->getSprite().setColor(sf::Color(255, 255, 255, 100));
	std::shared_ptr<GameObject> ennemy = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> idennemy = std::shared_ptr<Identity>(new Identity(_name, ENNEMY));
	std::shared_ptr<ObjectTransform> transformennemy = std::shared_ptr<ObjectTransform>(new ObjectTransform({ _posX,_posY }, NON_STATIC));
	std::shared_ptr<RigidBody> bodyennemy = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Sprite> spriteennemy = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animennemy = std::shared_ptr<Animation>(new Animation());
	std::shared_ptr<Mouvement> mvtEnnemy = std::shared_ptr<Mouvement>(new Mouvement());
	std::shared_ptr<Physique> PhysiqueEnnemis = std::shared_ptr<Physique>(new Physique(sf::Vector2f(500, 300)));
	std::shared_ptr<CheckCollision> checkCollisionennemy = std::shared_ptr<CheckCollision>(new CheckCollision());
	std::shared_ptr<Audio3D_Manager> soundEnnemis = std::shared_ptr<Audio3D_Manager>(new Audio3D_Manager());
	std::shared_ptr<Shake> ShakeMob = std::shared_ptr<Shake>(new Shake());




	//coliderennemy->addCollliderBox(transformennemy, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(300.0f, 300.0f));

	if (_mob == TRASHER)
	{
		/*std::function<const void()> moove = [this, bodyennemy, IATrash]() -> void {IAFonction::mooveToPlay(this, bodyennemy, IATrash); };
		std::function<const void()> back = [this, bodyennemy, IATrash]() -> void {IAFonction::back(this, bodyennemy, IATrash); };
		std::function<const void()> monte = [this, bodyennemy, IATrash]() -> void {IAFonction::monte(this, bodyennemy, IATrash); };
		std::function<const bool()> condition = [this, IATrash]() -> bool {return IAFonction::cMooveToPlayTrash(this, IATrash);};
		std::function<const bool()> conditionC = [this, IATrash]() -> bool {return IAFonction::cMonteTrash(this, IATrash);};

		std::shared_ptr<NodeComposite>racine = std::shared_ptr<NodeComposite>(new NodeComposite(ennemy, SELECTOR));
		std::shared_ptr<NodeComposite>freeMoove = std::shared_ptr<NodeComposite>(new NodeComposite(ennemy, SEQUENCE));
		std::shared_ptr<NodeComposite>test1 = std::shared_ptr<NodeComposite>(new NodeComposite(ennemy, SEQUENCE));
		std::shared_ptr<NodeComposite>test2 = std::shared_ptr<NodeComposite>(new NodeComposite(ennemy, SEQUENCE));

		std::shared_ptr<NodeTask>MoveToPlayer = std::shared_ptr<NodeTask>(new NodeTask(ennemy, moove));
		std::shared_ptr<NodeTask>BackTest = std::shared_ptr<NodeTask>(new NodeTask(ennemy, back));
		std::shared_ptr<NodeTask>monteTest = std::shared_ptr<NodeTask>(new NodeTask(ennemy, monte));
		std::shared_ptr<NodeDecorator>conditiontest = std::shared_ptr<NodeDecorator>(new NodeDecorator(ennemy, condition));
		std::shared_ptr<NodeDecorator>condition2 = std::shared_ptr<NodeDecorator>(new NodeDecorator(ennemy, conditionC));

		test2->add(monteTest);
		test2->addDecorator(condition2);

		freeMoove->add(MoveToPlayer);
		freeMoove->addDecorator(conditiontest);

		test1->add(BackTest);

		racine->add(test1);
		racine->add(freeMoove);
		racine->add(test2);

		std::shared_ptr<AI>ia = std::shared_ptr<AI>(new AI(racine, ennemy));
		ennemy->addComponents<AI>(ia);*/
		std::shared_ptr<IA_TRASHER> IATrash = std::shared_ptr<IA_TRASHER>(new IA_TRASHER());
		std::shared_ptr<Collider> coliderennemy = std::shared_ptr<Collider>(new Collider(transformennemy, animennemy, bodyennemy, "TRASHER"));

		animennemy->addAnimation("IDLEMOB", "1idle_287x452.png", 6, 0.17f, true);
		animennemy->addAnimation("MOVE", "2deplacement_258x399.png", 7, 0.08f, true);
		animennemy->addAnimation("DOUBLEHIT", "3poing_marteau_437x442.png", 10, 0.1f, false);
		animennemy->addAnimation("JAB", "poing_face_466x384.png", 8, 0.1f, false);
		animennemy->addAnimation("SPAWN", "8spawn_287x419.png", 11, 0.12f, false);
		animennemy->addAnimation("HITTRASH", "5gros_degat_488x452.png", 7, 0.12f, false);
		animennemy->addAnimation("DEATH", "7mort_sol_sang_535x451.png", 23, 0.1f, false);
		animennemy->addAnimation("RELEVE", "9releve_482x414.png", 7, 0.13f, true);
		ennemy->addComponents<IA_TRASHER>(IATrash);
		ennemy->addComponents<Collider>(coliderennemy);
		PhysiqueEnnemis->setLife(IATrash->m_life);
		PhysiqueEnnemis->m_typeMob = T;
		nbTrasher++;
		ennemy->addGameObject(ObjectOmbre);
	}
	else if (_mob == TRASHERHOLO)
	{
		std::shared_ptr<IA_PatternH> IATrash = std::shared_ptr<IA_PatternH>(new IA_PatternH());
		std::shared_ptr<Collider> coliderennemy = std::shared_ptr<Collider>(new Collider(transformennemy, animennemy, bodyennemy, "TRASHER"));
		animennemy->addAnimation("IDLEMOB", "11idle_287x452.png", 6, 0.17f, true);
		animennemy->addAnimation("MOVE", "12deplacement_258x399.png", 7, 0.08f, true);
		animennemy->addAnimation("DOUBLEHIT", "13poing_marteau_437x442.png", 10, 0.1f, false);
		animennemy->addAnimation("JAB", "14poing_face_466x384.png", 8, 0.1f, false);
		animennemy->addAnimation("SPAWN", "18spawn_287x419.png", 11, 0.12f, false);
		animennemy->addAnimation("HITTRASH", "15gros_degat_488x452.png", 7, 0.12f, false);
		animennemy->addAnimation("DEATH", "17mort_sol_sang_535x451.png", 23, 0.1f, true);
		animennemy->addAnimation("RELEVE", "19releve_482x414.png", 7, 0.13f, true);
		ennemy->addComponents<IA_PatternH>(IATrash);
		ennemy->addComponents<Collider>(coliderennemy);
		PhysiqueEnnemis->setLife(IATrash->m_life);
		PhysiqueEnnemis->m_typeMob = T;
		nbTrasherH++;
		ennemy->addGameObject(ObjectOmbre);
	}
	else if (_mob == SPIKER)
	{
		std::shared_ptr<IA_SPIKER> IASpik = std::shared_ptr<IA_SPIKER>(new IA_SPIKER());
		std::shared_ptr<Collider> coliderennemy = std::shared_ptr<Collider>(new Collider(transformennemy, animennemy, bodyennemy, "SPIKER"));
		animennemy->addAnimation("IDLEMOB", "Spiker_Idle_L2268_H369_6F.png", 6, 0.17f, true);
		animennemy->addAnimation("MOVE", "Spiker_Marche_L320_H361_5F.png", 5, 0.08f, true);
		animennemy->addAnimation("SPAWN", "Spawn_Spiker_L578_H931_12F.png", 12, 0.1f, false);
		animennemy->addAnimation("HITTRASH", "Spiker_Projection_L586_H439_10F.png", 10, 0.12f, false);
		animennemy->addAnimation("DEATH", "Spiker_Mort_L572_H244_14F.png", 14, 0.1f, false);
		animennemy->addAnimation("RELEVE", "spiker-se-relève_Sprite_L529_H419_6F.png", 6, 0.1f, true);
		animennemy->addAnimation("LONGHIT", "Spiker-coup-distant-180 centré attaque.png", 8, 0.1f, false);
		animennemy->addAnimation("GRAB", "Spiker_attaque_dash_grab_L660_H656_16F.png", 16, 0.1f, false);
		animennemy->addAnimation("PROJECTION", "Spiker_Projection_L586_H439_10F.png", 10, 0.1f, true);
		ennemy->addComponents<IA_SPIKER>(IASpik);
		ennemy->addComponents<Collider>(coliderennemy);
		PhysiqueEnnemis->setLife(IASpik->m_life);
		PhysiqueEnnemis->m_typeMob = S;
		nbSpiker++;
		ennemy->addGameObject(ObjectOmbre);
	}
	else if (_mob == CLEEVER || _mob == CLEEVERZOMBI)
	{
		std::shared_ptr<IA_CLEEVER> IACleev;
		if (_mob == CLEEVER)
			IACleev = std::shared_ptr<IA_CLEEVER>(new IA_CLEEVER());
		else
			IACleev = std::shared_ptr<IA_CLEEVER>(new IA_CLEEVER(true));

		std::shared_ptr<Collider> coliderennemy = std::shared_ptr<Collider>(new Collider(transformennemy, animennemy, bodyennemy, "CLEEVER"));
		animennemy->addAnimation("IDLEMOB", "Idle_T_Red.png", 6, 0.17f, true);
		animennemy->addAnimation("MOVE", "Marche_T_Red.png", 6, 0.12f, true);
		animennemy->addAnimation("SPAWNCORDE", "SpawnCorde.png", 4, 0.1f, false);
		animennemy->addAnimation("SPAWNTOMBE", "SpawnTombe.png", 8, 0.1f, false);
		animennemy->addAnimation("SPAWNSOL", "SpawnSol.png", 5, 0.1f, false);
		animennemy->addAnimation("HITTRASH", "takeDamage.png", 9, 0.12f, false);
		animennemy->addAnimation("PROJECTION", "Proj_T_Red.png", 8, 0.12f, false);
		animennemy->addAnimation("DEATH", "Mort_T_Red.png", 20, 0.1f, false);
		animennemy->addAnimation("RELEVE", "Releve_T_Red.png", 7, 0.08f, false);
		animennemy->addAnimation("JAB", "Att_S_T_Red.png", 8, 0.08f, true);
		animennemy->addAnimation("UPPERCUT", "Att_Hupercut_T_Red.png", 10, 0.07f, false);
		animennemy->addAnimation("DASHAVANT", "Esquive_AV_T_Red.png", 11, 0.07f, true);
		animennemy->addAnimation("DASHARRIERE", "Esquive_AR_T_Red.png", 11, 0.07f, true);
		ennemy->addComponents<IA_CLEEVER>(IACleev);
		ennemy->addComponents<Collider>(coliderennemy);
		PhysiqueEnnemis->setLife(IACleev->m_life);
		PhysiqueEnnemis->m_typeMob = C;
		nbCleever++;
	}
	ennemy->addComponents<Identity>(idennemy);
	ennemy->addComponents<ObjectTransform>(transformennemy);
	ennemy->addComponents<RigidBody>(bodyennemy);
	ennemy->addComponents<Sprite>(spriteennemy);
	ennemy->addComponents<Animation>(animennemy);
	ennemy->addComponents<CheckCollision>(checkCollisionennemy);
	ennemy->addComponents<Mouvement>(mvtEnnemy);
	ennemy->addComponents<Physique>(PhysiqueEnnemis);
	ennemy->addComponents<Audio3D_Manager>(soundEnnemis);
	ennemy->addComponents<Shake>(ShakeMob);

	ennemy->addGameObject(ObjectOmbre);
	m_object->addGameObject(ennemy);

	animennemy->playAnim("MOVE", true);
}

void Game::creatDestructible(EnumAsset _type, float _posX, float _posY)
{
	std::string name;
	if (_type == FRIGO)
		name = "Frigo";
	else if (_type == MACHINELAVER)
		name = "MachineLaver";
	else if (_type == DISTRIBUTEUR)
		name = "Distributeur";

	std::shared_ptr<GameObject> destructible = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> iddestructible = std::shared_ptr<Identity>(new Identity(name, COLLECTIBLE));
	std::shared_ptr<Sprite> spritedestructible = std::shared_ptr<Sprite>(new Sprite());


	if (_type == FRIGO)
	{
		spritedestructible->setTexture(RessourceManager::get()->getSceneTexture("collectibe_frigo1.png"));
	}
	else if (_type == MACHINELAVER)
	{
		spritedestructible->setTexture(RessourceManager::get()->getSceneTexture("collectibe_machine1.png"));
	}
	else if (_type == DISTRIBUTEUR)
	{
		spritedestructible->setTexture(RessourceManager::get()->getSceneTexture("collectible_distributeur1.png"));
	}
	std::shared_ptr<ObjectTransform> transformdestructible = std::shared_ptr<ObjectTransform>(new ObjectTransform({ _posX,_posY }, _posY + spritedestructible->getSprite().getGlobalBounds().height + 30.0f, STATIC));
	//std::shared_ptr<ObjectTransform> transformdestructible = std::shared_ptr<ObjectTransform>(new ObjectTransform({ _posX,_posY }, _posY + spritedestructible->getSprite().getGlobalBounds().height, STATIC));
	std::shared_ptr<Destructible> Colliderdestructible = std::shared_ptr<Destructible>(new Destructible({ static_cast<int>(_posX), static_cast<int>(_posY), static_cast<int>(spritedestructible->getSprite().getGlobalBounds().width), static_cast<int>(spritedestructible->getSprite().getGlobalBounds().height) }, _type));

	destructible->addComponents<Identity>(iddestructible);
	destructible->addComponents<Sprite>(spritedestructible);
	destructible->addComponents<ObjectTransform>(transformdestructible);
	destructible->addComponents<Destructible>(Colliderdestructible);

	m_object->addGameObject(destructible);
}

void Game::initLight() { /////
	std::shared_ptr<GameObject> camera = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Camera> camera1 = std::shared_ptr<Camera>(new Camera());
	std::shared_ptr<Identity> idcamera = std::shared_ptr<Identity>(new Identity("Camera", OBJECT));
	std::shared_ptr<ObjectTransform> transformCamera = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 0.f,0.f }, -INFINITY, STATIC));
	camera1->setSize(sf::Vector2f(1920.f, 1080.f));
	camera->addComponents<Identity>(idcamera);
	camera->addComponents<Camera>(camera1);
	camera->addComponents<ObjectTransform>(transformCamera);

	m_object->addGameObject(camera);

	std::shared_ptr<GameObject> lightObj = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idLight = std::shared_ptr<Identity>(new Identity("Light", OBJECT));
	std::shared_ptr<ObjectTransform> posLight = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY - 5.f, STATIC));
	std::shared_ptr<Light_Manager> lights = std::shared_ptr<Light_Manager>(new Light_Manager());
	//m_object->addGameObject(loser);
	//for (size_t i = 0; i < 20; i++) {
	/*Light enseigne du debut*/
	sf::Vector3f lightpos = (sf::Vector3f(950.f, 100.f, 0.f));

	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.7f, 0.7f, 0.7f }, 0.1f, 400.f, false, false);

	lights->addLight(lightpos, { 1.0f,0.7f,0.1f }, { 0.4f, 0.4f, 0.4f }, 0.1f, 400.f, false, false);


	/*Light enseigne du debut*/
	lightpos = (sf::Vector3f(1800.f, 100.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.7f, 0.7f, 0.7f }, 0.3f, 400.f, false, false);

	/*Light 3e lampadaire*/
	lightpos = (sf::Vector3f(3986.f, 418.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.7f, 0.7f, 0.7f }, 0.7f, 520.f, false, false);

	/*Light 4e lampadaire*/
	lightpos = (sf::Vector3f(5331.f, 1179.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.7f, 0.7f, 0.7f }, 0.7f, 520.f, false, true);

	/*Light 5e lampadaire*/
	lightpos = (sf::Vector3f(6680.f, 1912.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 6e lampadaire*/
	lightpos = (sf::Vector3f(8230.f, 2277.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 7e lampadaire*/
	lightpos = (sf::Vector3f(9532.f, 2277.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, true);

	/*Light 8e lampadaire*/
	lightpos = (sf::Vector3f(10810.f, 2277.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 9e lampadaire*/
	lightpos = (sf::Vector3f(11880.f, 2290.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 10e lampadaire*/
	lightpos = (sf::Vector3f(13200.f, 1540.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 11e lampadaire*/
	lightpos = (sf::Vector3f(14077.f, 1213.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light enseigne toy vendor*/
	lightpos = (sf::Vector3f(14283.f, 1220.f, 0.f));
	lights->addLight(lightpos, { 1.0f,0.7f,0.3f }, { 0.4f, 0.4f, 0.4f }, 0.5f, 250.f, false, false);
	lightpos = (sf::Vector3f(14383.f, 1220.f, 0.f));
	lights->addLight(lightpos, { 1.0f,0.7f,0.3f }, { 0.4f, 0.4f, 0.4f }, 0.5f, 250.f, false, false);

	/*Light 12e lampadaire*/
	lightpos = (sf::Vector3f(15550.f, 1153.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, true);

	/*Light enseigne urban grill*/
	lightpos = (sf::Vector3f(15756.f, 1172.f, 0.f));
	lights->addLight(lightpos, { 1.0f,0.4f,0.3f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 250.f, false, true);
	lightpos = (sf::Vector3f(15856.f, 1172.f, 0.f));
	lights->addLight(lightpos, { 1.0f,0.4f,0.3f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 250.f, false, true);
	lightpos = (sf::Vector3f(15956.f, 1172.f, 0.f));
	lights->addLight(lightpos, { 1.0f,0.4f,0.3f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 250.f, false, true);

	/*Light 13e lampadaire*/
	lightpos = (sf::Vector3f(17000.f, 1159.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 14e lampadaire*/
	lightpos = (sf::Vector3f(17350.f, 1148.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, true);

	/*Light 15e lampadaire*/
	lightpos = (sf::Vector3f(18500.f, 1320.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 16e lampadaire*/
	lightpos = (sf::Vector3f(19720.f, 2000.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 17e lampadaire*/
	lightpos = (sf::Vector3f(21080.f, 2735.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, true);

	/*Light 18e lampadaire*/
	lightpos = (sf::Vector3f(24900.f, 3400.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	/*Light 19e lampadaire*/
	lightpos = (sf::Vector3f(26045.f, 3400.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 520.f, false, false);

	//light dans la soute 1st screen 
	lightpos = (sf::Vector3f(1079.f, -100.f, 0.f));
	lights->addLight(lightpos, { 0.8f,0.8f,0.8f }, { 0.4f, 0.4f, 0.4f }, 0.1f, 800.f, false, false);
	//light dans la soute 2st screen 
	lightpos = (sf::Vector3f(2880.f, -100.f, 0.f));
	lights->addLight(lightpos, { 0.8f,0.8f,0.8f }, { 0.4f, 0.4f, 0.4f }, 0.1f, 700.f, false, false);



	//Light 1st lampadaire dans la zone du boss
	lightpos = (sf::Vector3f(26980.f, 3317.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 650.f, false, true);

	//Light 2nd lampadaire dans la zone du boss
	lightpos = (sf::Vector3f(27590.f, 3317.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 650.f, false, false);

	//Light 3rd lampadaire dans la zone du boss
	lightpos = (sf::Vector3f(28160.f, 3317.f, 0.f));
	lights->addLight(lightpos, { 0.6f,0.4f,0.2f }, { 0.4f, 0.4f, 0.4f }, 0.7f, 650.f, false, true);


	lights->setCamera(camera1);


	lightObj->addComponents<Identity>(idLight);
	lightObj->addComponents<ObjectTransform>(posLight);
	lightObj->addComponents<Light_Manager>(lights);
	m_object->addGameObject(lightObj);
}

void Game::initTriggerZone()
{
#pragma region GoGoGo
	std::shared_ptr<GameObject> uiGo = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> idGo = std::shared_ptr<Identity>(new Identity("GoGoGo", OBJECT));
	std::shared_ptr<ObjectTransform> objUiGo = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));
	std::shared_ptr<Go> goComp = std::shared_ptr<Go>(new Go());

	uiGo->addComponents<Identity>(idGo);
	uiGo->addComponents<ObjectTransform>(objUiGo);
	uiGo->addComponents<Go>(goComp);
	m_object->addGameObject(uiGo);
#pragma endregion

#pragma region ZoneTuto
	//TRIGGER ZONE TUTORIEL
	std::shared_ptr<GameObject> goTriggerTuto = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idTriggerTuto = std::shared_ptr<Identity>(new Identity("TriggerZoneTuto", OBJECT));
	std::shared_ptr<ObjectTransform> posTriggerTuto = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));

	std::shared_ptr<TriggerZone> triggerTuto = std::shared_ptr<TriggerZone>(new TriggerZone());
	triggerTuto->setZone({ 3200, 200, 1000, 1000 });
	bool player1 = false;


	triggerTuto->setTriggeredFunction([]() {});

	triggerTuto->setUpdateFunction([player1, this]() mutable
		{
			for (auto player : GameObject::l_Player)
			{
				if (auto input = player->getComponents<Input>())
				{
					if (GameObject::l_Player.size() > 1)
					{
						if (m_object->getObjects("Player")->getComponents<Physique>()->getComportement() != Attaque && m_object->getObjects("Player")->getComponents<Physique>()->getComportement() != Jump && m_object->getObjects("Player2")->getComponents<Physique>()->getComportement() != Attaque && m_object->getObjects("Player2")->getComponents<Physique>()->getComportement() != Jump)
						{
							if (m_object->getObjects("Player")->getComponents<ObjectTransform>()->getPosition().x > 3100 && m_object->getObjects("Player2")->getComponents<ObjectTransform>()->getPosition().x > 3100)
							{
								m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(true);
								if (input->getType(gp::Gamepad::B) == PRESSED)
								{
									m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(false);
									m_object->getObjects("starters")->getComponents<Starters>()->setSpawnHOLObool(false);
									m_object->getObjects("starters")->getComponents<Starters>()->setStartTutobool(false);
									m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("CargoHoldmusic").stop();
									m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("UrbanJunglemusic").play();
									player1 = true;
								}
							}
						}
					}
					else
					{
						if (m_object->getObjects(PLAYER)->getComponents<Physique>()->getComportement() != Attaque && m_object->getObjects(PLAYER)->getComponents<Physique>()->getComportement() != Jump)
						{

							if (m_object->getObjects(PLAYER)->getComponents<ObjectTransform>()->getPosition().x > 3100)
							{


								m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(true);
								if (input->getType(gp::Gamepad::B) == PRESSED)
								{
									m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(false);
									m_object->getObjects("starters")->getComponents<Starters>()->setSpawnHOLObool(false);
									m_object->getObjects("starters")->getComponents<Starters>()->setStartTutobool(false);
									m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("CargoHoldmusic").stop();
									m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("UrbanJunglemusic").play();
									player1 = true;
								}

							}




						}
					}
				}
			}

			if (player1)
				return true;
			else
				return false;
		});

	triggerTuto->setEndFunction([this]()
		{
			m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(false);
			for (auto player : GameObject::l_Player)
			{
				if (auto objTrans = player->getComponents<ObjectTransform>())
				{
					objTrans->setPosition({ 200.f, 1900.f });
				}
			}

			m_object->getObjects("Camera")->getComponents<Camera>()->setPosition({ 960.f, 1620.f });
		});

	goTriggerTuto->addComponents<Identity>(idTriggerTuto);
	goTriggerTuto->addComponents<ObjectTransform>(posTriggerTuto);
	goTriggerTuto->addComponents<TriggerZone>(triggerTuto);

	m_object->addGameObject(goTriggerTuto);
#pragma endregion

#pragma region Zone1
	std::shared_ptr<GameObject> goTz1 = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> idTz1 = std::shared_ptr<Identity>(new Identity("TZ1", OBJECT));
	std::shared_ptr<ObjectTransform> objTransTz1 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));
	std::shared_ptr<TriggerZone> triggerZ1 = std::shared_ptr<TriggerZone>(new TriggerZone());

	creatMonster("ENNEMY_TZ1-V1-1", TRASHER, 1000.f, 1900.f);
	creatMonster("ENNEMY_TZ1-V1-2", TRASHER, 2550.f, 2100.f);

	creatMonster("ENNEMY_TZ1-V2-3", TRASHER, 1000.f, 2100.f);
	creatMonster("ENNEMY_TZ1-V2-4", TRASHER, 2550.f, 1900.f);
	/*creatMonster("ENNEMY_TZ1-V2-5", TRASHER, 2650.f, 2100.f);*/
	/*creatMonster("ENNEMY_TZ1-V2-6", TRASHER, 800.f, 1900.f);*/

	triggerZ1->setZone({ 1900, 1750, 5150, 3380 });
	triggerZ1->setTriggeredFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(true);
			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ1-V1") != std::string::npos)
					ennemy->setActive(true);
			}
		});


	bool vague2Tz1 = false;
	triggerZ1->setUpdateFunction([vague2Tz1]() mutable
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				return true;

			if (!vague2Tz1)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ1-V1") != std::string::npos
						&& ennemy->getComponents<Physique>()->getLife() > 0)
						return false;
				}
			}

			if (!vague2Tz1)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ1-V2") != std::string::npos)
						ennemy->setActive(true);
				}
				vague2Tz1 = true;
			}


			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ1-V2") != std::string::npos
					&& ennemy->getComponents<Physique>()->getLife() > 0)
					return false;
			}
			return true;
		});

	triggerZ1->setEndFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(false);
			m_object->getObjects("GoGoGo")->setActive(true);
		});
	goTz1->addComponents<Identity>(idTz1);
	goTz1->addComponents<ObjectTransform>(objTransTz1);
	goTz1->addComponents<TriggerZone>(triggerZ1);

	m_object->addGameObject(goTz1);

#pragma endregion

#pragma region Zone2

	std::shared_ptr<GameObject> goTz2 = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> idTz2 = std::shared_ptr<Identity>(new Identity("TZ2", OBJECT));
	std::shared_ptr<ObjectTransform> objTransTz2 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));
	std::shared_ptr<TriggerZone> triggerZ2 = std::shared_ptr<TriggerZone>(new TriggerZone());

	creatMonster("ENNEMY_TZ2-V1-1", CLEEVER, 5650.f + 500.f, 3340.f + 300.f);
	creatMonster("ENNEMY_TZ2-V1-2", TRASHER, 4800.f + 500.f, 2850.f + 300.f);
	creatMonster("ENNEMY_TZ2-V1-3", TRASHER, 4520.f + 500.f, 3000.f + 300.f);

	triggerZ2->setZone({ 5150 + 500, 3380 + 300, 1500, 1500 });
	triggerZ2->setTriggeredFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(true);
			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ2-V1") != std::string::npos)
					ennemy->setActive(true);
			}
		});


	bool vague2Tz2 = false;
	triggerZ2->setUpdateFunction([vague2Tz2]() mutable
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				return true;

			if (!vague2Tz2)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ2-V1") != std::string::npos
						&& ennemy->getComponents<Physique>()->getLife() > 0)
						return false;
				}
			}

			if (!vague2Tz2)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ2-V2") != std::string::npos)
						ennemy->setActive(true);
				}
				vague2Tz2 = true;
			}


			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ2-V2") != std::string::npos
					&& ennemy->getComponents<Physique>()->getLife() > 0)
					return false;
			}
			return true;
		});

	triggerZ2->setEndFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(false);
			m_object->getObjects("GoGoGo")->setActive(true);

		});
	goTz2->addComponents<Identity>(idTz2);
	goTz2->addComponents<ObjectTransform>(objTransTz2);
	goTz2->addComponents<TriggerZone>(triggerZ2);

	m_object->addGameObject(goTz2);
#pragma endregion

#pragma region Zone3

	std::shared_ptr<GameObject> goTz3 = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> idTz3 = std::shared_ptr<Identity>(new Identity("TZ3", OBJECT));
	std::shared_ptr<ObjectTransform> objTransTz3 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));
	std::shared_ptr<TriggerZone> triggerZ3 = std::shared_ptr<TriggerZone>(new TriggerZone());

	creatMonster("ENNEMY_TZ3-V1-1", TRASHER, 9600.f, 4200.f);
	creatMonster("ENNEMY_TZ3-V1-3", CLEEVER, 10700.f, 4000.f);
	creatMonster("ENNEMY_TZ3-V1-2", CLEEVER, 10750.f, 4400.f);

	triggerZ3->setZone({ 10250, 3000, 1500, 1800 });
	triggerZ3->setTriggeredFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(true);
			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ3-V1") != std::string::npos)
					ennemy->setActive(true);
			}
		});


	bool vague2Tz3 = false;
	triggerZ3->setUpdateFunction([vague2Tz3]() mutable
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				return true;

			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ3-V1") != std::string::npos
					&& ennemy->getComponents<Physique>()->getLife() > 0)
					return false;
			}

			return true;
		});

	triggerZ3->setEndFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(false);
			m_object->getObjects("GoGoGo")->setActive(true);
		});
	goTz3->addComponents<Identity>(idTz3);
	goTz3->addComponents<ObjectTransform>(objTransTz3);
	goTz3->addComponents<TriggerZone>(triggerZ3);

	m_object->addGameObject(goTz3);
#pragma endregion

#pragma region Zone4
	std::shared_ptr<GameObject> goTz4 = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> idTz4 = std::shared_ptr<Identity>(new Identity("TZ4", OBJECT));
	std::shared_ptr<ObjectTransform> objTransTz4 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));
	std::shared_ptr<TriggerZone> triggerZ4 = std::shared_ptr<TriggerZone>(new TriggerZone());

	creatMonster("ENNEMY_TZ4-1", SPIKER, 15000.f, 3150.f);
	creatMonster("ENNEMY_TZ4-2", TRASHER, 15400.f, 3300.f);
	creatMonster("ENNEMY_TZ4-3", TRASHER, 15450.f, 2900.f);

	triggerZ4->setZone({ 15750, 2400, 1500, 1800 });
	triggerZ4->setTriggeredFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(true);
			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ4-") != std::string::npos)
					ennemy->setActive(true);
			}
		});

	triggerZ4->setUpdateFunction([this]() mutable
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				return true;

			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ4-") != std::string::npos
					&& ennemy->getComponents<Physique>()->getLife() > 0)
					return false;
			}
			return true;
		});

	triggerZ4->setEndFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(false);
			m_object->getObjects("GoGoGo")->setActive(true);
		});
	goTz4->addComponents<Identity>(idTz4);
	goTz4->addComponents<ObjectTransform>(objTransTz4);
	goTz4->addComponents<TriggerZone>(triggerZ4);

	m_object->addGameObject(goTz4);
#pragma endregion

#pragma region Zone5
	std::shared_ptr<GameObject> goTz5 = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> idTz5 = std::shared_ptr<Identity>(new Identity("TZ5", OBJECT));
	std::shared_ptr<ObjectTransform> objTransTz5 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));
	std::shared_ptr<TriggerZone> triggerZ5 = std::shared_ptr<TriggerZone>(new TriggerZone());

	creatMonster("ENNEMY_TZ5-V1-1", TRASHER, 17225, 3000.f);
	creatMonster("ENNEMY_TZ5-V1-2", SPIKER, 17000.f, 3200.f);
	creatMonster("ENNEMY_TZ5-V1-3", CLEEVER, 18120.f, 3300.f);
	if (GameObject::l_Player.size() > 1)
		creatMonster("ENNEMY_TZ5-V1-4", SPIKER, 18470.f, 3140.f);

	creatMonster("ENNEMY_TZ5-V2-1", TRASHER, 17225, 3000.f);
	creatMonster("ENNEMY_TZ5-V2-2", TRASHER, 17500.f, 3400.f);

	triggerZ5->setZone({ 17800, 2380, 1500, 1500 });
	triggerZ5->setTriggeredFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(true);
			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ5-V1") != std::string::npos)
					ennemy->setActive(true);
			}

		});


	bool vague2Tz5 = false;
	triggerZ5->setUpdateFunction([vague2Tz5]() mutable
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				return true;

			if (!vague2Tz5)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ5-V1") != std::string::npos
						&& ennemy->getComponents<Physique>()->getLife() > 0)
						return false;
				}
			}

			if (!vague2Tz5)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ5-V2") != std::string::npos)
						ennemy->setActive(true);
				}
				vague2Tz5 = true;
			}


			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ5-V2") != std::string::npos
					&& ennemy->getComponents<Physique>()->getLife() > 0)
					return false;
			}

			return true;

		});

	triggerZ5->setEndFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(false);

			m_object->getObjects("GoGoGo")->setActive(true);
		});
	goTz5->addComponents<Identity>(idTz5);
	goTz5->addComponents<ObjectTransform>(objTransTz5);
	goTz5->addComponents<TriggerZone>(triggerZ5);

	m_object->addGameObject(goTz5);
#pragma endregion

#pragma region Zone6
	std::shared_ptr<GameObject> goTz6 = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> idTz6 = std::shared_ptr<Identity>(new Identity("TZ6", OBJECT));
	std::shared_ptr<ObjectTransform> objTransTz6 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));
	std::shared_ptr<TriggerZone> triggerZ6 = std::shared_ptr<TriggerZone>(new TriggerZone());

	creatMonster("ENNEMY_TZ6-V1-2", SPIKER, 24150.f, 5150.f);
	creatMonster("ENNEMY_TZ6-V1-1", SPIKER, 24350.f, 5400.f);
	creatMonster("ENNEMY_TZ6-V1-3", CLEEVER, 25000.f, 5350.f);

	creatMonster("ENNEMY_TZ6-V2-1", CLEEVER, 25150, 5100.f);
	creatMonster("ENNEMY_TZ6-V2-2", CLEEVER, 25100.f, 5400.f);
	creatMonster("ENNEMY_TZ6-V2-3", CLEEVER, 25720.f, 5200.f);
	creatMonster("ENNEMY_TZ6-V2-4", SPIKER, 26500.f, 5200.f);

	creatMonster("ENNEMY_TZ6-V3-2", SPIKER, 25100.f, 5400.f);
	creatMonster("ENNEMY_TZ6-V3-4", SPIKER, 26500.f, 5200.f);
	if (GameObject::l_Player.size() > 1)
		creatMonster("ENNEMY_TZ6-V3-3", SPIKER, 25720.f, 5200.f);

	triggerZ6->setZone({ 25500, 4900, 1000, 1000 });
	triggerZ6->setTriggeredFunction([this]()
		{
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(true);
			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ6-V1") != std::string::npos)
					ennemy->setActive(true);
			}

		});


	bool vague2Tz6 = false;
	bool vague3Tz6 = false;
	triggerZ6->setUpdateFunction([vague2Tz6, vague3Tz6]() mutable
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				return true;

			if (!vague2Tz6 && !vague3Tz6)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ6-V1") != std::string::npos
						&& ennemy->getComponents<Physique>()->getLife() > 0)
						return false;
				}
			}

			if (!vague2Tz6 && !vague3Tz6)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ6-V2") != std::string::npos)
						ennemy->setActive(true);
				}
				vague2Tz6 = true;
			}

			if (vague2Tz6 && !vague3Tz6)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ6-V2") != std::string::npos
						&& ennemy->getComponents<Physique>()->getLife() > 0)
						return false;
				}
				vague2Tz6 = false;
				vague3Tz6 = true;
			}

			if (!vague2Tz6 && vague3Tz6)
			{
				for (auto ennemy : GameObject::l_Ennemy)
				{
					if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ6-V3") != std::string::npos)
						ennemy->setActive(true);
				}
				vague2Tz6 = true;
				vague3Tz6 = true;
			}

			for (auto ennemy : GameObject::l_Ennemy)
			{
				if (ennemy->getComponents<Identity>()->getName().find("ENNEMY_TZ6-V3") != std::string::npos
					&& ennemy->getComponents<Physique>()->getLife() > 0)
					return false;
			}
			return true;
		});


	triggerZ6->setEndFunction([this]()
		{
			m_BoosUnlock = true;
			m_object->getObjects("Camera")->getComponents<Camera>()->lockCamera(false);
			m_object->getObjects("GoGoGo")->setActive(true);
		});
	goTz6->addComponents<Identity>(idTz6);
	goTz6->addComponents<ObjectTransform>(objTransTz6);
	goTz6->addComponents<TriggerZone>(triggerZ6);

	m_object->addGameObject(goTz6);
#pragma endregion

#pragma region ZoneBoss

	std::shared_ptr<GameObject> goTriggerBoss = std::shared_ptr<GameObject>(new GameObject(true));
	std::shared_ptr<Identity> idTriggerBoss = std::shared_ptr<Identity>(new Identity("TriggerZoneTuto", OBJECT));
	std::shared_ptr<ObjectTransform> posTriggerBoss = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), INFINITY, STATIC));

	std::shared_ptr<TriggerZone> triggerBoss = std::shared_ptr<TriggerZone>(new TriggerZone());
	triggerBoss->setZone({ 25500, 4900, 1000, 1000 });
	triggerBoss->setTriggeredFunction([]() {});
	triggerBoss->setUpdateFunction([player1, this]() mutable
		{
			for (auto player : GameObject::l_Player)
			{
				if (auto input = player->getComponents<Input>())
				{
					if (GameObject::l_Player.size() > 1)
					{
						if (m_object->getObjects("Player")->getComponents<ObjectTransform>()->getPosition().x > 25500 && m_object->getObjects("Player2")->getComponents<ObjectTransform>()->getPosition().x > 25500)
						{
							if (m_BoosUnlock == true)
							{
								m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(true);
								if (input->getType(gp::Gamepad::B) == PRESSED)
								{
									m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(false);
									m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("UrbanJunglemusic").stop();
									m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("BossMusic").play();
									player1 = true;
								}
							}

						}
						else
						{
							m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(false);
						}
					}
					else
					{
						if (m_object->getObjects(PLAYER)->getComponents<ObjectTransform>()->getPosition().x > 25500)
						{
							if (m_BoosUnlock == true)
							{
								m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(true);
								if (input->getType(gp::Gamepad::B) == PRESSED)
								{
									m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(false);
									m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("UrbanJunglemusic").stop();
									m_object->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getMusic("BossMusic").play();
									player1 = true;
								}
							}

						}
						else
						{
							m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(false);
						}
					}
				}
			}

			if (player1)
				return true;
			else
				return false;
		});

	triggerBoss->setEndFunction([this]()
		{
			m_object->getObjects("starters")->getComponents<Starters>()->setBforZoneTrigger(false);
			for (auto player : GameObject::l_Player)
			{
				if (auto objTrans = player->getComponents<ObjectTransform>())
				{
					objTrans->setPosition({ 27650.f, 5500.f });

				}
			}

			m_object->getObjects("Boss")->setActive(true);
			m_object->getObjects("Camera")->getComponents<Camera>()->setPosition({ 27844.f, 5100.f });
			m_object->getObjects("Camera")->getComponents<Camera>()->setFixedLine({ 27844.f, 5100.f });
		});

	goTriggerBoss->addComponents<Identity>(idTriggerBoss);
	goTriggerBoss->addComponents<ObjectTransform>(posTriggerBoss);
	goTriggerBoss->addComponents<TriggerZone>(triggerBoss);

	m_object->addGameObject(goTriggerBoss);
#pragma endregion

}

void Game::initBoss()
{

#pragma region initBoss
	std::shared_ptr<GameObject> boss = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> idBoss = std::shared_ptr<Identity>(new Identity("Boss", ENNEMY));
	//std::shared_ptr<ObjectTransform> transformBoss = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 300, 2000.f }, NON_STATIC));
	std::shared_ptr<ObjectTransform> transformBoss = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 28600.f, 5500.f }, NON_STATIC));
	std::shared_ptr<RigidBody> bodyBoss = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Sprite> spriteBoss = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animBoss = std::shared_ptr<Animation>(new Animation());
	std::shared_ptr<Physique> physiqueBoss = std::shared_ptr<Physique>(new Physique({ 0.f,0.f }));
	std::shared_ptr<Collider> coliderBoss = std::shared_ptr<Collider>(new Collider(transformBoss, animBoss, bodyBoss, "KimpahPlayer"));
	std::shared_ptr<AI> AIBoss = std::make_shared<AI>(boss);
	std::shared_ptr<CheckCollision> checkCollisionBoss = std::shared_ptr<CheckCollision>(new CheckCollision());
	std::shared_ptr<Mouvement> mvtBoss = std::shared_ptr<Mouvement>(new Mouvement());
	std::shared_ptr<Audio3D_Manager> SoundBoss = std::shared_ptr<Audio3D_Manager>(new Audio3D_Manager());
	std::shared_ptr<Shake> ShakeBoss = std::shared_ptr<Shake>(new Shake());

	physiqueBoss->setLife(300);
#pragma endregion

#pragma region AnimBoss
	animBoss->addAnimation("IDLE", "1342.1220..10738.1220.png", 8, 0.1, true);
	animBoss->addAnimation("SPRINT", "boss_sprint_397_363_8f.png", 8, 0.1, true);
	animBoss->addAnimation("CHARGED", "charged_att_3.png", 10, 0.1, false);
	animBoss->addAnimation("Jab1KP", "Combo_1_4_T_Red.png", 3, 0.1, false);
	animBoss->addAnimation("Jab2", "Combo_2_4_T_Red.png", 2, 0.1, false);
	animBoss->addAnimation("Jab3", "Combo_3_4_T_Red.png", 3, 0.1, false);
	animBoss->addAnimation("Jab4", "Combo_4_4_T_Red.png", 4, 0.1, false);
	animBoss->addAnimation("FALLING", "falling_4025_480_8f.png", 7, 0.1, false);
	animBoss->addAnimation("HIT", "hit-kimpah.png", 1, 1.1, true);
	animBoss->addAnimation("ATTACKJUMP", "jump_att_4606_651_7f.png", 7, 0.1, false);
	animBoss->addAnimation("JUMP", "jump-boss_F7.png", 7, 0.1, false);
	animBoss->addAnimation("MOVE", "marche_F8.png", 8, 0.1, true);
	animBoss->addAnimation("DEATH", "mort_8850_546_15f.png", 15, 0.1, true);
	animBoss->addAnimation("SPAWN", "spawn kimpah.png", 3, 0.1, false);
	animBoss->addAnimation("STANDUP", "stand-up--kimpah_F18.png", 18, 0.05, false);
	SoundBoss->addSceneSound("gethit1", "GoodHit_1.wav", 100);
	SoundBoss->addSceneSound("gethit2", "GoodHit_2.wav", 100);
	SoundBoss->addSceneSound("gethit3", "GoodHit_3.wav", 100);
	SoundBoss->addSceneSound("gethit4", "GoodHit_4.wav", 100);
#pragma endregion
#pragma region addComponents
	boss->addComponents<Identity>(idBoss);
	boss->addComponents<ObjectTransform>(transformBoss);
	boss->addComponents<RigidBody>(bodyBoss);
	boss->addComponents<Sprite>(spriteBoss);
	boss->addComponents<Animation>(animBoss);
	boss->addComponents<Physique>(physiqueBoss);
	boss->addComponents<Collider>(coliderBoss);
	boss->addComponents<CheckCollision>(checkCollisionBoss);
	boss->addComponents<Mouvement>(mvtBoss);
	boss->addComponents<AI>(AIBoss);
	boss->addComponents<Shake>(ShakeBoss);
	boss->addComponents<Audio3D_Manager>(SoundBoss);
	animBoss->playAnim("IDLE", false);
	physiqueBoss->setComportement(Iddle);
#pragma endregion
#pragma region UI_Boss
	//--------------------------------------------------------//

		//GameObject & ID
	std::shared_ptr<GameObject> uiBossObject = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> uiBossID = std::shared_ptr<Identity>(new Identity("LIFEBAR_UI", Type::UI));
	uiBossObject->addComponents<Identity>(uiBossID);
	// TRANSFORM
	std::shared_ptr<ObjectTransform> uiBossTransform = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f{ 100.f,875.f }, INFINITY, STATIC));
	// LIFEBAR
	std::shared_ptr<Lifebar> uiBoss = std::shared_ptr<Lifebar>(new Lifebar(Personnage::UI_KIMPAH));
	uiBossObject->addComponents<ObjectTransform>(uiBossTransform);
	uiBossObject->addComponents<Lifebar>(uiBoss);

	uiBossObject->getComponents<Lifebar>()->initAllSpritePos();

	///////////////////////////////SCORE///////////////////////////////
	boss->addGameObject(uiBossObject);
#pragma endregion
#pragma region IABoss


	std::shared_ptr<NodeTask> fleeTask = std::make_shared<NodeTask>(boss);
	std::function<const void()> fleeFunction = [this, fleeTask, transformBoss, bodyBoss, animBoss, physiqueBoss, AIBoss]() {
		std::shared_ptr<GameObject> target;

		float distance = 10000.f;
		sf::Vector2f posBoss = transformBoss->getPosition();
		AIBoss->addDeltaTimeToTimer();
		for (auto& it : GameObject::l_Player)
		{
			if ((it)->isActive())
			{
				sf::Vector2f tmpPos = (it)->getComponents<ObjectTransform>()->getPosition();
				float tmp = std::sqrtf(((tmpPos.x - posBoss.x) * (tmpPos.x - posBoss.x)) + ((tmpPos.y - posBoss.y) * (tmpPos.y - posBoss.y)));
				if (distance > tmp) {
					distance = tmp;
					target = it;
				}
			}
		}
		if (distance > 700 || AIBoss->getTimer() < 2.f)
		{
			bodyBoss->setSpeed({ 0.f,0.f });
			fleeTask->setResult(SUCCEEDED);
			animBoss->playAnim("IDLE", true);
			physiqueBoss->setComportement(Iddle);
			AIBoss->resetTimer();
			return;
		}
		sf::Vector2f speed{ 0.f, 0.f };
		sf::Vector2f posPlayer = target->getComponents<ObjectTransform>()->getPosition();
		if (physiqueBoss->getComportement() != HitStun && !physiqueBoss->getInKnockDown())
		{
			if (posBoss.x > posPlayer.x)
				speed.x = 400.f;
			else if (posBoss.x < posPlayer.x)
				speed.x = -400.f;
			if (posBoss.y > posPlayer.y)
				speed.y = 400.f;
			else if (posBoss.y < posPlayer.y)
				speed.y = -400.f;
			bodyBoss->setSpeed(speed);
		}
		physiqueBoss->b_Sprint = false;
		animBoss->playAnim("MOVE", true);
		physiqueBoss->setComportement(Walking);
	};
	fleeTask->setFunction(fleeFunction);

	std::shared_ptr<NodeTask> seekTask = std::make_shared<NodeTask>(boss);
	std::function<const void()> seekFunction = [this, seekTask, transformBoss, bodyBoss, animBoss, physiqueBoss]() {
		std::shared_ptr<GameObject> target;

		float distance = 10000.f;
		sf::Vector2f posBoss = transformBoss->getPosition();

		for (auto& it : GameObject::l_Player)
		{
			if ((it)->isActive())
			{
				sf::Vector2f tmpPos = (it)->getComponents<ObjectTransform>()->getPosition();
				float tmp = std::sqrtf(((tmpPos.x - posBoss.x) * (tmpPos.x - posBoss.x)) + ((tmpPos.y - posBoss.y) * (tmpPos.y - posBoss.y)));
				if (distance > tmp)
				{
					distance = tmp;
					target = it;
				}
			}
		}
		if (distance < 200)
		{
			physiqueBoss->b_Sprint = false;
			bodyBoss->setSpeed({ 0.f,0.f });
			seekTask->setResult(SUCCEEDED);
			animBoss->playAnim("IDLE", true);
			physiqueBoss->setComportement(Iddle);
			return;
		}

		if (physiqueBoss->getComportement() != HitStun && !physiqueBoss->getInKnockDown())
		{
			sf::Vector2f speed{ 0.f, 0.f };
			sf::Vector2f posPlayer = target->getComponents<ObjectTransform>()->getPosition();

			if (posBoss.x > posPlayer.x)
				speed.x = -600.f;
			else if (posBoss.x < posPlayer.x)
				speed.x = 600.f;
			if (posBoss.y > posPlayer.y)
				speed.y = -600.f;
			else if (posBoss.y < posPlayer.y)
				speed.y = 600.f;

			physiqueBoss->b_Sprint = true;
			animBoss->playAnim("SPRINT", true);
			physiqueBoss->setComportement(Walking);
			bodyBoss->setSpeed(speed);
		}
	};
	seekTask->setFunction(seekFunction);

	std::shared_ptr<NodeTask> attackTask = std::make_shared<NodeTask>(boss);
	std::function<const void()> attackFunction = [this, attackTask, animBoss, physiqueBoss]() {
		auto anim = animBoss->getCurrentAnimInfo();
		std::string nameAnim = anim->m_nameAnimation;
		int currentFrameAnim = animBoss->getCurrentFrame();
		int maxFrameAnim = anim->m_maxAnimFrame;

		if (nameAnim != "Jab1KP" && nameAnim != "Jab2" && nameAnim != "Jab3" && nameAnim != "Jab4")
		{
			animBoss->playAnim("Jab1KP", false);
			physiqueBoss->setComportement(Attaque);
		}
		else if (currentFrameAnim == maxFrameAnim)
		{
			if (nameAnim == "Jab1KP")
				animBoss->playAnim("Jab2", false);
			else if (nameAnim == "Jab2")
				animBoss->playAnim("Jab3", false);
			else if (nameAnim == "Jab3")
				animBoss->playAnim("Jab4", false);
			else if (nameAnim == "Jab4")
			{
				attackTask->setResult(SUCCEEDED);
				physiqueBoss->setComportement(Walking);
				animBoss->playAnim("MOVE", false);
			}
		}
	};
	attackTask->setFunction(attackFunction);

	std::function<const bool()> conditionHit = [this, physiqueBoss, animBoss]() {
		if (physiqueBoss->getComportement() == HitStun)
			animBoss->playAnim("HIT", true);

		if (physiqueBoss->getComportement() == HitStun || physiqueBoss->getComportement() == Ejection || physiqueBoss->getComportement() == KnockDown || physiqueBoss->getLife() <= 0) return false;
		else return true;

	};
	std::shared_ptr<NodeTask> hitTask = std::make_shared<NodeTask>(boss);
	std::function<const void()> hitFunction = [this, animBoss, hitTask, physiqueBoss, transformBoss]() {
		if (physiqueBoss->getComportement() == HitStun && physiqueBoss->getComportement() == Grabed)
		{
			animBoss->playAnim("HIT", true);
			hitTask->setResult(SUCCEEDED);
		}
		else if (physiqueBoss->getComportement() == Ejection)
		{
			animBoss->playAnim("FALLING", false);
			hitTask->setResult(SUCCEEDED);
		}
		if (physiqueBoss->getComportement() == KnockDown)
		{
			animBoss->playAnim("STANDUP", false);
			hitTask->setResult(SUCCEEDED);
		}
		if (physiqueBoss->getLife() <= 0)
			animBoss->playAnim("DEATH", false);
		auto anim = animBoss;
		std::string nameAnim = anim->getCurrentAnimInfo()->m_nameAnimation;
		int currentFrameAnim = anim->getCurrentFrame();
		int maxFrameAnim = anim->getCurrentAnimInfo()->m_maxAnimFrame;

		if (nameAnim == "STANDUP" && currentFrameAnim == 5)
		{
			anim->play();
		}
		if (maxFrameAnim == currentFrameAnim)
		{
			if (nameAnim == "KNOCKOUT")
			{
				anim->playAnim("STANDUP", false);
				hitTask->setResult(SUCCEEDED);
				return;
			}
			else if (nameAnim == "STANDUP")
			{
				transformBoss->setState(NON_STATIC);
				anim->playAnim("MOVE", false);
				physiqueBoss->setComportement(Walking);
				hitTask->setResult(SUCCEEDED);
				return;
			}
			else if (nameAnim == "DEATH")
			{
				m_object->getObjects("Boss")->setActive(false);
				hitTask->setResult(SUCCEEDED);
				return;
			}
		}
		hitTask->setResult(SUCCEEDED);
	};
	hitTask->setFunction(hitFunction);

	std::shared_ptr<NodeComposite> compositeHit = std::make_shared<NodeComposite>(boss, SEQUENCE);
	compositeHit->add(hitTask);

	std::shared_ptr<NodeDecorator> decoratorMouvement = std::make_shared<NodeDecorator>(boss, conditionHit);

	std::shared_ptr<NodeTask> flee2Task = std::make_shared<NodeTask>(boss);
	std::function<const void()> flee2Function = [this, flee2Task, transformBoss, bodyBoss, animBoss, physiqueBoss, AIBoss]()
	{
		std::shared_ptr<GameObject> target;

		float distance = 10000.f;
		sf::Vector2f posBoss = transformBoss->getPosition();
		for (auto& it : GameObject::l_Player)
		{
			if ((it)->isActive())
			{
				sf::Vector2f tmpPos = (it)->getComponents<ObjectTransform>()->getPosition();
				float tmp = std::sqrtf(((tmpPos.x - posBoss.x) * (tmpPos.x - posBoss.x)) + ((tmpPos.y - posBoss.y) * (tmpPos.y - posBoss.y)));
				if (distance > tmp) {
					distance = tmp;
					target = it;
				}
			}
		}
		AIBoss->addDeltaTimeToTimer();
		sf::Vector2f speed;
		sf::Vector2f posPlayer = target->getComponents<ObjectTransform>()->getPosition();
		if (distance < 250 || AIBoss->getTimer() < 0.8f)
		{
			sf::Vector2f speed{ 0.f, 0.f };
			sf::Vector2f posPlayer = target->getComponents<ObjectTransform>()->getPosition();

			if (posBoss.x > posPlayer.x)
				speed.x = 400.f;
			else if (posBoss.x < posPlayer.x)
				speed.x = -400.f;

			physiqueBoss->b_Sprint = false;
			animBoss->playAnim("MOVE", true);
			physiqueBoss->setComportement(Walking);
			bodyBoss->setSpeed(speed);
		}
		else {
			if (bodyBoss->getSpeed().y >= 0.f && transformBoss->getZBuffer() == posBoss.y)
			{
				physiqueBoss->b_Sprint = true;
				bodyBoss->setSpeed({ 700, bodyBoss->getSpeed().y });
				physiqueBoss->launchEntity(-800, Jump, false);
				animBoss->playAnim("JUMP", false);

			}
			if (posBoss.y > transformBoss->getZBuffer())
			{
				physiqueBoss->b_Sprint = false;
				transformBoss->setZBuffer(transformBoss->getPosition().y);
				flee2Task->setResult(SUCCEEDED);
				AIBoss->resetTimer();
				animBoss->playAnim("MOVE", false);
				return;
			}
		}
	};
	flee2Task->setFunction(flee2Function);

	std::shared_ptr<NodeTask> seek2Task = std::make_shared<NodeTask>(boss);
	std::function<const void()> seek2Function = [this, seek2Task, transformBoss, bodyBoss, animBoss, physiqueBoss, AIBoss]()
	{
		std::shared_ptr<GameObject> target;
		float distance = 10000.f;
		sf::Vector2f posBoss = transformBoss->getPosition();

		for (auto& it : GameObject::l_Player)
		{
			if ((it)->isActive())
			{
				sf::Vector2f tmpPos = (it)->getComponents<ObjectTransform>()->getPosition();
				float tmp = std::sqrtf(((tmpPos.x - posBoss.x) * (tmpPos.x - posBoss.x)) + ((tmpPos.y - posBoss.y) * (tmpPos.y - posBoss.y)));
				if (distance > tmp)
				{
					distance = tmp;
					target = it;
				}
			}
		}
		if (distance < 700.f)
		{
			seek2Task->setResult(SUCCEEDED);
			animBoss->playAnim("MOVE", false);
			physiqueBoss->setComportement(Walking);
			return;
		}
		else
		{
			if (physiqueBoss->getComportement() != HitStun && !physiqueBoss->getInKnockDown())
			{
				sf::Vector2f speed{ 0.f, 0.f };
				sf::Vector2f posPlayer = target->getComponents<ObjectTransform>()->getPosition();

				if (posBoss.x - 50.f > posPlayer.x)
					speed.x = -600.f;
				else if (posBoss.x + 50.f < posPlayer.x)
					speed.x = 600.f;
				if (posBoss.y - 50.f > posPlayer.y)
					speed.y = -600.f;
				else if (posBoss.y + 50.f < posPlayer.y)
					speed.y = 600.f;
				physiqueBoss->b_Sprint = true;
				animBoss->playAnim("SPRINT", true);
				physiqueBoss->setComportement(Walking);
				bodyBoss->setSpeed(speed);
			}
		}
	};
	seek2Task->setFunction(seek2Function);

	std::shared_ptr<NodeTask> waitTask = std::make_shared<NodeTask>(boss);
	std::function<const void()> waitFunction = [this, waitTask, AIBoss, bodyBoss, animBoss, physiqueBoss]()
	{
		AIBoss->addDeltaTimeToTimer();
		animBoss->playAnim("IDLE", true);
		physiqueBoss->setComportement(Iddle);
		bodyBoss->resetSpeed();
		if (AIBoss->getTimer() > 1.5f) {
			AIBoss->resetTimer();
			waitTask->setResult(SUCCEEDED);
			return;
		}
	};
	waitTask->setFunction(waitFunction);

	seek2Task->setFunction(seek2Function);
	std::shared_ptr<NodeComposite> compositeMouvement = std::make_shared<NodeComposite>(boss, SEQUENCE);
	compositeMouvement->addDecorator(decoratorMouvement);
	compositeMouvement->add(fleeTask);
	compositeMouvement->add(waitTask);// INGENIEUR INFORMATICIEN
	compositeMouvement->add(seekTask);
	compositeMouvement->add(attackTask);
	compositeMouvement->add(flee2Task);
	compositeMouvement->add(seek2Task);


	std::shared_ptr<NodeComposite> rootBoss = std::make_shared<NodeComposite>(boss, SELECTOR);
	std::function<const bool()> conditionBoss = [this, transformBoss, animBoss]() {
		float distance = 10000.f;
		sf::Vector2f posBoss = transformBoss->getPosition();

		for (auto& it : GameObject::l_Player)
		{
			sf::Vector2f tmpPos = (it)->getComponents<ObjectTransform>()->getPosition();
			float tmp = std::sqrtf(((tmpPos.x - posBoss.x) * (tmpPos.x - posBoss.x)) + ((tmpPos.y - posBoss.y) * (tmpPos.y - posBoss.y)));
			if (distance > tmp)
				distance = tmp;
		}
		if (distance < 1800.f) return true;
		else return false;
	};
	std::shared_ptr<NodeDecorator> decoratorBoss = std::make_shared<NodeDecorator>(boss, conditionBoss);
	rootBoss->addDecorator(decoratorBoss);
	rootBoss->add(compositeHit);
	rootBoss->add(compositeMouvement);
	rootBoss->add(compositeMouvement);
	AIBoss->setTree(rootBoss);

	m_object->addGameObject(boss);

#pragma endregion
#pragma region SmokeBoss
	std::shared_ptr<GameObject> smoke = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idsmoke = std::shared_ptr<Identity>(new Identity("Boss_Smoke", OBJECT));
	std::shared_ptr<Boss_Smoke> m_smoke = std::shared_ptr<Boss_Smoke>(new Boss_Smoke());
	smoke->addComponents<Identity>(idsmoke);
	smoke->addComponents<Boss_Smoke>(m_smoke);
	m_object->addGameObject(smoke);
#pragma endregion
}

void Game::initTransition()
{
}

void Game::initFly()
{
}

void Game::initDestructible()
{
	m_object->addGameObject(Destructible::createDestructible(DISTRIBUTEUR, 3103.0f, 1312.0f));
	m_object->addGameObject(Destructible::createDestructible(MACHINELAVER, 9900.0f, 3700.0f));
	m_object->addGameObject(Destructible::createDestructible(FRIGO, 17100.0f, 2400.0f));
}

void Game::initPauseMenu()
{
	/*std::shared_ptr<GameObject> fond = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idfond = std::shared_ptr<Identity>(new Identity("fond", UI));
	std::shared_ptr<PauseGameCOMP> pauseGame = std::shared_ptr<PauseGameCOMP>(new PauseGameCOMP());

	fond->addComponents<Identity>(idfond);
	fond->addComponents<PauseGameCOMP>(pauseGame);

	m_object->addGameObject(fond);
	pauseGame->setActive(false);*/
}

void Game::initPlayers()
{
	switch (m_uiTransit.get()->getFirstPlayerType())
	{
	case (1):
		player.initPlayer(m_object, m_inputP1);
		break;
	case (2):
		player.initBloodLust(m_object, m_inputP1);
		break;
	case(3):
		player.initFinalPlayableBoss(m_object, m_inputP1);
		break;
	default:
		break;
	}

	if (m_inputP2 != nullptr)
	{
		switch (m_uiTransit.get()->getSecondPlayerType())
		{
		case (1):
			player.initPlayer(m_object, m_inputP2);
			break;
		case (2):
			player.initBloodLust(m_object, m_inputP2);
			break;
		case(3):
			player.initFinalPlayableBoss(m_object, m_inputP2);
			break;
		default:
			break;
		}
	}
}

void Game::initTimer()
{
	std::shared_ptr<GameObject> timerGO = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> idGO = std::shared_ptr<Identity>(new Identity("TIMER", UI));
	std::shared_ptr<ObjectTransform> transformTimer = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 0.0f,0.f }, STATIC));
	std::shared_ptr<Timer> timer = std::shared_ptr<Timer>(new Timer());

	timerGO->addComponents<Identity>(idGO);
	timerGO->addComponents<ObjectTransform>(transformTimer);
	timerGO->addComponents<Timer>(timer);

	m_object->addGameObject(timerGO);
}

std::shared_ptr<Input> Game::getInput1()
{
	return m_inputP1;
}

std::shared_ptr<Input> Game::getInput2()
{
	return m_inputP2;
}
