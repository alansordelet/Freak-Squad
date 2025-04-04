#pragma once
#include "CoffeeCore.hpp"
#include"Ombre.h"
#include"tools2.h"
#include<math.h>
class Physique;
#define RANDOMCHARGETIMER  (tools::iRand(50,70))/10.f
#define ATTTRASH int a = tools::iRand(0, 2);if (a == 0)action = ACTION::DOUBLEHIT;else action = ACTION::JAB;
#define ATTCLEEV int a = tools::iRand(0, 4);if (a == 0)action = ACTION::UPPERCUT;else action = ACTION::JAB;
#define ATTSPIK int a = tools::iRand(0, 12);if (a == 0)action = ACTION::TROLL;else if(a == 1 || a == 2)action = ACTION::GOBACK;else if(a == 3 || a == 4)action = ACTION::TURNAROUND;else{if (physicsTarget->getLook() == physics->getLook()){action = ACTION::GRAB; }else{action = ACTION::LONGHIT;}}
#define randGD int a = tools::iRand(0, 40); m_dGD = 1 + (float)a/10;
#define CONDITIONCHARGEY transform->getZBuffer() - 50 < TransTarget->getZBuffer() && transform->getZBuffer() + 60 > TransTarget->getZBuffer()
#define CONDITIONFRAPPEC transform->getPosition().y > TransTarget->getPosition().y - 100.f && TransTarget->getPosition().y + 100.f > transform->getPosition().y
#define ESTTOUCHE  (physics->getComportement() == HitStun || physics->getComportement() != Ejection || physics->getComportement() != KnockDown || physics->getComportement() != Grabed)

#define DGOBACK float a = (tools::iRand(0,50))/100.f; m_dGoBack = 1.3f + a;
// ENUM SELECTION DU PATTERN
enum E_PATTERN
{
	SPAWN, MOVE, JABB, DOUBLEJAAB, DOUBLEHIIT, HIIT, DEAD, TURNED, CHARGEE, CHARGING,
	NONEE, GD, LONGHIIT, GRAAB, UUPERCUT, TROOLL, GOBACKING, IDLEE, GOTOPLAYEER, 
	TURNAROUNDD, DASSH, REPOSITIIONNE, AVANCCE, DASHAVANTT, DASHAARRIER, AVANCECRABBE,
	DASHANDJAAB, DASHANDBAACK, BAACKT, DASHAARR, GOTOUPPERCUUT, TURNAROUNDREMAKEE,
	BACKTOSPANWN
};
// MALEABLE

enum ACTION
{
	WALKTOPLAYER, BACK, JAB, DOUBLEJAB, UPPERCUT, DOUBLEHIT, GRAB, LONGHIT,
	NONE, CHARGE, HIT, GAUCHEDROITE, BREAK, GDFOLLOW, TROLL, GOBACK, IDLE, GOTOPLAYER, 
	TURNAROUND, DASH, REPOSITIONNE, AVANCE, DASHAVANT, DASHARRIER, AVANCECRABE,
	DASHANDJAB, DASHANDBACK, BACKT, DASHARR, GOTOUPPERCUT, TURNAROUNDREMAKE,
	BACKTOSPAWN
};

// EXEMPLE 

class IAMOTHER : public GameComponent
{
public:
	IAMOTHER();
	~IAMOTHER();

	void update();
	void draw();
	void walkToPlayer(float _spd);
	void backPlayer(float _spd);
	void gaucheDroite(float _spd);
	void GDFollow(float _spd);
	void chargeInit();
	void charge(float _spd);
	void dead();
	void hit();
	void jab();
	void uppercut();
	void doubleHit();
	void dash_Grab();
	void longHit();
	void dontMove();
	void AllPointeur();
	void acting();
	void InitGD();
	void duringLongHit();
	void duringGrab();
	void fourberie();
	void duringFourberie();
	void goBack();
	void goingtoObj(float _spd);
	void goToPlayer();
	bool arrived();
	void idle();
	void initTurnAround();
	void turnAournd();
	void dash();
	void isDashing();
	void getGrab();
	void mapCollision();
	void updatePakage();
	virtual void behaviourTree();
	virtual void GestionAnim();
	void initReposi();
	void initAvance();
	void avance();
	void doubleJab();
	void initDash(bool _av);
	void initAvCrabe();
	void avCrabe();
	void initDashAndJab();
	void dashAndJab();
	void initBackT();
	void backT();
	void initGoUppercut();
	void goUppercut();
	void initTurnAroundRe();
	void initBack2Spawn();

	float m_timer;
	E_PATTERN m_pattern;
	ACTION action;
	bool m_desactivation;
	int m_life;
	float t_stun;
	float m_tReleve;
	bool m_CGetHit;
protected:
	float m_TPA;
	float m_dGoBack;
	float m_tTurnAround;
	sf::Vector2f m_sCenter;
	float m_sRayon;
	float m_sAngle;
	int m_sensD;
	float m_tGoBack;
	/// <summary>
	/// ////////////////////////////////////////////////
	/// </summary>
	std::shared_ptr<ObjectTransform> transform;
	std::shared_ptr<RigidBody> body;
	std::shared_ptr<ObjectTransform> transPlayer;
	std::shared_ptr<ObjectTransform> transPlayer2;
	std::shared_ptr<Animation> animator;
	std::shared_ptr<Sprite>sprite;
	std::shared_ptr<Physique>physics;
	std::shared_ptr<Physique>physicsPlayer;
	std::shared_ptr<Physique>physicsPlayer2;
	std::shared_ptr<ObjectTransform> TransTarget;
	std::shared_ptr<Physique> physicsTarget;
	std::shared_ptr<Collider>collid;
	std::shared_ptr<Sprite>ombre;
	float c_timeSpawn;
	bool m_attacking;
	//float radius;
	float c_spdWalk;
	float c_spdBack;
	float m_dChargAtt;
	float m_tCharg;
	float m_distanceGo;
	float m_distanceFlee;
	bool m_frappeAct;
	float m_dGD;
	sf::RectangleShape m_frappe;
	float m_distanceToPlayer;
	sf::Vector2f m_saveCharPos;
	sf::Vector2f m_dirToPos;
	float m_dirGD, m_tTurn;
	bool m_turnL;
	bool m_initLHit; bool feinte;
	bool attFourb;
	float m_timerIdle;
	float m_goAttack;
	//-----------------------
	sf::Vector2f m_position;
	sf::Vector2f m_target;
	sf::Vector2f m_distance;
	sf::Vector2f m_repos1;
	sf::Vector2f m_repos2;
	sf::Vector2f m_savePosGo;
	bool m_esquive;
	float m_dStun;
	float t_avEjecL;
	float t_lockReleve;
	float t_dead;
	float m_tLockAtt;
	float m_timerAtt;
	float m_addLongAtt;
	bool m_initP;
	bool m_lockP;
	bool m_asDASH;
	bool m_lHitGo; // Reine des neiges
	bool m_doTour;
	bool m_dashG;
	float m_tDash;
	float m_tRelev;
	float m_spdLent;

	float m_spdModif;
	float m_tKnock;
	bool m_goUppercut;
	bool m_fuitePatt;
	bool m_2PLayer;

	int m_randReposi;
	float m_randIdle;

	float m_timerTurn;
	float m_timerTurn2;
	bool same;
	//----------------------
private:

};



