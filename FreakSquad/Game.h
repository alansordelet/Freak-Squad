#pragma once
#include "Map.h"
#include "CoffeeCore.hpp"
#include "Player.h"
#include "IADictionnary.h"
#include "Destructible.h"
#include "Fly.h"
#include "Fumee.h"
#include "Parallax.h"
#include "Ui.h"
#include "DialogueReader.h"

enum MOB
{
	TRASHER, TRASHERHOLO, CLEEVER, CLEEVERZOMBI, SPIKER
};


class Game : public Scene {
private :
	Map map;
	Player player;
	Fly fly;
	Parallax parallax;
	Fumee fumee;
	DialogueReader introending;


	float timer;
	bool m_bPause;
	bool m_isIntro;
	bool m_isEnding;
	bool m_isCredit;

	int nbTrasher = 0;

	int  nbTrasherH, nbCleever, nbSpiker;

	std::shared_ptr<Input> m_inputP1, m_inputP2;
	std::shared_ptr<Ui> m_uiTransit;

	float timerInput;
	
	bool m_transitionEndgame;
	bool m_BoosUnlock;

	std::shared_ptr<GameObject> m_object;
	std::shared_ptr<GameObject> m_objTransition;

	float m_volumeMusic, m_volumeSound;
	bool afficheTruc;
public:
	Game();
	Game(std::shared_ptr<Ui> _ui, std::shared_ptr<Input> _inputP1, std::shared_ptr<Input> _inputP2, float _volumeMusic, float _volumeSound);
	void init();
	void update();
	void display();
	void deInit();

	void creatMonster(MOB _mob, float _posX, float _posY);
	void creatMonster(std::string _name, MOB _mob, float _posX, float _posY);
	void creatDestructible(EnumAsset _type, float _posX, float _posY);

	void initLight();
	void initTriggerZone();
	void initBoss();
	void initTransition();
	void initFly();
	void initDestructible();
	void initPauseMenu();
	void initPlayers();
	void initTimer();

	std::shared_ptr<Input> getInput1();
	std::shared_ptr<Input> getInput2();

};