#pragma once
#include "CoffeeCore.hpp"

enum Comportement
{
	Iddle,
	Attaque,
	Walking,
	Jump,
	HitStun,
	Ejection,
	KnockDown,
	Grab,
	Grabed,
	Died
};

enum MOBE
{
	T, C, S, H
};

enum e_TypeAttackGrab
{
	GrabNeutre,GrabJab, GrabJabFinal,GrabProjection,NULLGrab
};

enum e_TypeAttack
{
	Jab1,Jab2,Jab3,Jab4,JumpAttack,AttackSprint, Charging,AttackCharge,UltimeAttack,NUllattack
};

enum e_LookingCharactereInput
{
	LookRight,
	LookLeft

};

enum StaterPlayer
{
	DamageDoubleTranchant,
	ScoreBonusMalusDegat,
	VieBonusNoUlti,
	BonusUltimeCanceled,
	NoStater
};


class Physique : public GameComponent
{
public:
	//POUR LES IA , Vous pouvais utiliser et faire se que vous vouler MAIS Annuler tout les deplacement et comportement quand le getInKnockDown est true, Sa veux dire que vous devais utiliser le 
	//GetComportement Pour annuler les action et le set speed de l'ia quand le comportement est == a tous se quil y a dans le GetInKnodown();
	sf::Sprite m_SpriteOmbre;
	std::weak_ptr<Texture> p_textureOmbre;
	MOBE m_typeMob;
	e_TypeAttackGrab e_GrabType = GrabNeutre;
	Physique();
	//Set La vitesse de deplacement en X et Y
	Physique(sf::Vector2f _SpeedSet);
	~Physique();

	bool getCanMooved();
	int getLife();
	bool getInKnockDown();
	e_LookingCharactereInput getLook();
	Comportement getComportement();

	void launchEntity(double _ForceJump, Comportement _Jumping, bool _Ejection);
	void setDamageEntity2v(bool _HeavyAttaque, int _DealDamage);
	void setGrabEntity(std::string _GetNameGrabeur, std::string _GetNameGrabed, e_LookingCharactereInput _SetView);

	void setCoupTouched();
	void setLife(int _life);
	void setComportement(Comportement _Comportement);
	void setLook(e_LookingCharactereInput _look);

	void AddParticule(int type);
	void update();
	void draw();
	std::string s_NameTypeGrabed = "uII";

	void checkMask();
	
	//Ultimate
	bool TornadoActive = false;
	bool EndTornado = false;
	bool Aspired = false;

	bool UltimateBlood = false;

	float timerBonusColi = 0;

	void SetAspired(sf::Vector2f _pos);

	StaterPlayer Starter = NoStater;
	//BOOST POUR COLI
	bool BoostVitesseAttack = false;
	bool BoostImortalite = false;
	bool BoostScore = false;

	bool BoostDoubleScore = false;

	bool b_Sprint;


	e_TypeAttack t_Attack;

	float timerSpawn;

	bool B_Dead = false;

	int ChargeUltimate = 0;
	int Revive = 0;


private:
	float tmpZ;
	sf::Vector2f PosDirectionApired;

	bool HoldStick = false;
	int DoubleCheckStick = 0;
	float TimerStick = 0;
	bool PrepareCharge = false;
	int GrabCoup = 0;
	std::string Jab1Anime;
	bool m_MooveHit = false;
	bool b_ReleverAnimation = false;

	float timerCharge = 0;
	float timer;
	int Combo = 0;
	int MassPhysique = 2000;
	float timerForEntityDamage = 0;
	float timerTmp = 0;
	std::string s_NameTypeGrabeur = "uII";
	float timerTornado = 0;
	float timerParticules = 0;
	
	bool EndUltimateBlood = false;
	float colorSetFondu = 3;

	//UpdateForControllerPlayer
	void updateController();
	//UpdateWhenPlayerTombedParTerre
	void updateKnockDown();
	//UpdateWhenManBeatSomUglyMobForPlayerAvecInput
	void updateCombat();
	//UpdateSomeHitstoneForPlayerANDENNEMIS
	void updateHitStone();
	//UpdateGab
	void updateGrab();
	//UpdateProcjectionAndJumpForPlayer,DONT USE SPEED IN YOUR COMPENANTE FOR PLAYER
	void updateJumpAndPorjection();
	
	void updateUltimate();
	
	
	float timerTmpCoup = 0;
	float timerForCoupTouched = 0;

	int m_life = 10;

	sf::Vector2f v2_Speed = { 0,0 };
	e_LookingCharactereInput e_look ;
	float timerKnockDown ;
	float timerHitStun ;
	float timerGrab=0;
	bool t_TimerBool ;
	Comportement CompPhysique ;
	float f_TimerDelay ;
	bool b_Ejected ;
	bool b_Moove ;
	int xPhysique ;
	float f_JumpVitesse ;
	bool b_BougitudeX ;
	bool b_BougitudeY ;



	//posittion des différents écrans 
	sf::Vector2f tmp_soutePos;
	sf::Vector2f tmp_lvlScreen1Pos;
	sf::Vector2f tmp_lvlScreen2Pos;
	sf::Vector2f tmp_lvlScreen3Pos;
	sf::Vector2f tmp_lvlScreen4Pos;
	sf::Vector2f tmp_lvlScreen5Pos;
	sf::Vector2f tmp_lvlScreen6Pos;
	sf::Vector2f tmp_lvlScreen7Pos;
};

