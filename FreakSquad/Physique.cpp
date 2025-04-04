#include "Physique.h"
#include "Score.h"
#include "FeedBackScore.h"
#include "IA_Pattern.h"
#include "Ui_Player.h"
#include "Blood.h"
#include "CheckCollision.h"
#include"Hit.h"
#include"Sounds3D.h"
#include"Boss_Smoke.h"
#include"IA_PatternT.h"
#include"IA_PatternS.h"
#include"IA_PatternC.h"
#include"IA_PatternH.h"
#include "collisionMask.h"
#include "Package.h"
#include "Particules.h"
#include "Starters.h"
#include "Camera.h"
#include "Shake.h"

Physique::Physique()
{
}
//Vitesse pour deplacement X et Y

Physique::Physique(sf::Vector2f _SpeedSet)
{
	v2_Speed = _SpeedSet;
	e_look = LookLeft;
	timerKnockDown = 0;
	timerHitStun = 0;
	t_TimerBool = false;
	b_Sprint = false;
	CompPhysique = Iddle;
	f_TimerDelay = 0;
	b_Ejected = false;
	b_Moove = false;
	xPhysique = 0;
	f_JumpVitesse = 0;
	b_BougitudeX = false;
	b_BougitudeY = false;
	timerSpawn = 0.f;
	timer = 0.f;
	p_textureOmbre = RessourceManager::get()->bindSharedToTexture("Ombre.png");
	m_SpriteOmbre.setTexture(p_textureOmbre.lock()->getTexture());
}

Physique::~Physique()
{
}

int Physique::getLife()
{
	return m_life;
}

void Physique::setCoupTouched()
{
	if (timerForCoupTouched == 0)
	{
		if (auto p = getParents().lock())
			if (auto parent = p->getObjects("SCORE_ID"))
			{
				if (auto score = parent->getComponents<Score>())
				{
					int BonusScoreTmp;
					int tmpScoreStarter;

					if (BoostScore)
					{

						BonusScoreTmp = 150;
					}
					else
					{
						BonusScoreTmp = 0;
					}

					if (Starter != ScoreBonusMalusDegat)
					{
						tmpScoreStarter = 0;
					}
					else
					{
						tmpScoreStarter = 100;
					}

					score->scoreAdd(0,150 + tmpScoreStarter + BonusScoreTmp);
				}
			}


		int tmpCharge;

		if (Starter == BonusUltimeCanceled)
		{
			tmpCharge = 5;

		}
		else
		{
			tmpCharge = 2;
		}
		if (Revive != 1)
		{
			ChargeUltimate += tmpCharge;
		}


		if (ChargeUltimate >= 100)
		{
			ChargeUltimate = 100;
		}
		//LLLLLLAAAA KELVIN PT DE MERDE

	}
	timerForCoupTouched += tools::GetTimeDelta();
}

void Physique::setLife(int _life)
{
	m_life = _life;

}

bool Physique::getInKnockDown() {

	if (CompPhysique == Ejection || CompPhysique == KnockDown || CompPhysique == Died)
	{
		return true;
	}
	else
	{
		return false;
	}
}

e_LookingCharactereInput Physique::getLook()
{
	return e_look;
}

void Physique::setDamageEntity2v(bool _HeavyAttaque, int _DealDamage)
{
	if (auto Parent = getParents().lock())
	{
		if (!_HeavyAttaque)
		{
			if (timerForEntityDamage == 0)
			{
				if (getComportement() == HitStun)
				{
					if (auto Parent = getParents().lock())
					{
						auto animator = Parent->getComponents<Animation>();
						animator->resetCurrentAnim();
					}
				}

				AddParticule(1);

				int TakingDamageBonus;

				if (Starter == BonusUltimeCanceled)
				{
					ChargeUltimate = 0;
				}

				if (Starter == DamageDoubleTranchant)
				{
					TakingDamageBonus = 10;
				}
				else
				{
					TakingDamageBonus = 0;
				}

				if (auto Ennemuis = Parent->getParent()->getObjects("gameMusic"))
				{
					int rand = tools::iRand(1, 3);

					if (rand == 1)
					{
						Ennemuis->getComponents<Audio3D_Manager>()->getSound3D("gethit1").play();

						////std::cout << "Coup1";
					}
					if (rand == 2)
					{

						Ennemuis->getComponents<Audio3D_Manager>()->getSound3D("gethit2").play();

						////std::cout << "Coup2";
					}
					if (rand == 3)
					{

						Ennemuis->getComponents<Audio3D_Manager>()->getSound3D("gethit3").play();

						////std::cout << "Coup3";
					}

				}



				if (auto Parent = getParents().lock())
				{

					auto dirPlayer = Parent->getParent()->getObjects(PLAYER)->getComponents<Physique>()->getLook();
					auto pos = Parent->getComponents<ObjectTransform>()->getPosition();
					auto blood = Parent->getParent()->getObjects("Blood");
					blood->getComponents<Blood>()->GoPushBlood(sf::Vector2f(pos.x, pos.y - 300.0f), dirPlayer);

					if (m_typeMob == C)
					{
						if (Parent->getComponents<IA_CLEEVER>()->m_CGetHit)
						{
							Parent->getComponents<IA_CLEEVER>()->m_CGetHit = false;
						}
						else
						{
							Parent->getComponents<IA_CLEEVER>()->m_CGetHit = true;
						}
					}
				}
				timerHitStun = 0;
				Combo++;

				if (!Aspired && !BoostImortalite)
				{
					m_life -= _DealDamage + TakingDamageBonus;
					if (CompPhysique != Grabed)
					{
						if (m_life <= 0 || CompPhysique == Jump || t_Attack == JumpAttack)
						{
							launchEntity(-700, Ejection, true);
						}
						else
						{
							CompPhysique = HitStun;
						}
					}
				}

			}
			timerForEntityDamage += tools::GetTimeDelta();
			//timerTmp = timerFonction;
		}
		else
		{
			/*tmp = score->ajoutChoixScore();
			score->hitJ1(&tmp);*/
			if (!Aspired && !BoostImortalite)
			{
				m_life -= _DealDamage;

				if (CompPhysique != Grabed)
				{
					AddParticule(2);
					if (Parent->getParent()->getObjects("Player"))
					{
						if (Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("gethit4").getStatus() == sf::Sound::Stopped)
							Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("gethit4").play();
					}
					if (Parent->getParent()->getObjects("Player2"))
					{
						if (Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_jumphit").getStatus() == sf::Sound::Stopped)
							Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_jumphit").play();
					}
					//AddHit(2);

				}



				launchEntity(-700, Ejection, true);
			}

		}
	}
}

void Physique::setGrabEntity(std::string _GetNameGrabeur, std::string _GetNameGrabed, e_LookingCharactereInput _SetView)
{
	if (CompPhysique != Grabed)
	{
		int tmpDirection;
		s_NameTypeGrabeur = _GetNameGrabeur;

		if (auto ForEnnemis = getParents().lock()) {
			if (ForEnnemis->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("grab").getStatus() == sf::Sound::Stopped)
				ForEnnemis->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("grab").play();
			if (auto ForPlayer = getParents().lock()->getParent()->getObjects(s_NameTypeGrabeur)) {
				CompPhysique = Grabed;
				ForPlayer->getComponents<Physique>()->s_NameTypeGrabed = _GetNameGrabed;
				if (_SetView == LookRight)
				{
					tmpDirection = 100;
				}
				else
				{
					tmpDirection = -100;
				}
				ForEnnemis->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(ForPlayer->getComponents<ObjectTransform>()->getPosition().x + tmpDirection, ForPlayer->getComponents<ObjectTransform>()->getPosition().y));

			}
		}
	}
}

void Physique::setComportement(Comportement _Comportement)
{
	CompPhysique = _Comportement;
}

Comportement Physique::getComportement() {
	return CompPhysique;
}

void Physique::setLook(e_LookingCharactereInput _look)
{
	e_look = _look;
}

void Physique::launchEntity(double _ForceJump, Comportement _Jumping, bool _Ejection)
{
	f_JumpVitesse = _ForceJump; CompPhysique = _Jumping;  t_TimerBool = true;

	if (auto parent = getParents().lock())
	{
		parent->getComponents<ObjectTransform>()->setState(STATIC);
		tmpZ = parent->getComponents<ObjectTransform>()->getZBuffer();
	}
}

void Physique::updateController()
{
	if (auto parent = getParents().lock()) {
		if (auto InputComp = parent->getComponents<Input>())
		{

			auto collisionComp = parent->getComponents<CheckCollision>();
			if (!getCanMooved())
			{
				parent->getComponents<RigidBody>()->resetSpeed();

				if (InputComp->moveDirection(gpDirection::UP))
				{
					parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ parent->getComponents<RigidBody>()->getSpeed().x, -v2_Speed.y });
					b_BougitudeY = true;
				}

				else if (InputComp->moveDirection(gpDirection::DOWN))
				{
					parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ parent->getComponents<RigidBody>()->getSpeed().x, v2_Speed.y });
					b_BougitudeY = true;
				}
				else
				{
					b_BougitudeY = false;
				}
				float tmpMultipleSprint;
				if (!b_Sprint)
				{
					tmpMultipleSprint = 1;
				}
				else
				{
					tmpMultipleSprint = 2;
				}
				if (InputComp->moveDirection(gpDirection::LEFT))
				{
					parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ -v2_Speed.x * tmpMultipleSprint, parent->getComponents<RigidBody>()->getSpeed().y });
					b_BougitudeX = true;
					e_look = LookLeft;
				}
				else if (InputComp->moveDirection(gpDirection::RIGHT))
				{
					parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ v2_Speed.x * tmpMultipleSprint, parent->getComponents<RigidBody>()->getSpeed().y });
					b_BougitudeX = true;
					e_look = LookRight;
				}
				else
				{
					b_BougitudeX = false;
				}

				if (InputComp->getStickLeft().y > 80 || InputComp->getStickLeft().y < -80)
				{

					b_Sprint = false;
				}

				if (!b_BougitudeX && !b_BougitudeY)
				{
					setComportement(Iddle);
					b_Sprint = false;
				}
				else
				{
					setComportement(Walking);
				}
			}

		}
	}
}

void Physique::updateKnockDown()
{
	if (auto parent = getParents().lock())
	{
		if (CompPhysique == KnockDown)
		{
			/*parent->getComponents<Sprite>()->getSprite().setRotation(150);*/

			timerKnockDown += tools::GetTimeDelta();
			if (timerKnockDown > 0.8 && !b_ReleverAnimation)
			{
				b_ReleverAnimation = true;
			}
			if (timerKnockDown > 1.3)
			{
				timerKnockDown = 0;
				parent->getComponents<ObjectTransform>()->setState(NON_STATIC);
				CompPhysique = Iddle;
			}
		}
	}
}

void Physique::updateCombat()
{

	if (BoostVitesseAttack)
	{
		timerBonusColi += tools::GetTimeDelta();

		//Parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(200, 255, 100, 255));
		AddParticule(4);

		if (timerBonusColi > 5)
		{

			//Parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 255, 255));

			BoostVitesseAttack = false;
			timerBonusColi = 0;
		}
	}
	if (BoostScore)
	{
		timerBonusColi += tools::GetTimeDelta();

		//Parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(200, 255, 100, 255));
		AddParticule(8);

		if (timerBonusColi > 11)
		{

			//Parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 255, 255));

			BoostScore = false;
			timerBonusColi = 0;
		}
	}
	if (BoostImortalite)
	{
		timerBonusColi += tools::GetTimeDelta();

		//Parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 0, 255));
		AddParticule(5);

		if (timerBonusColi > 10)
		{
			timerBonusColi += tools::GetTimeDelta();
			BoostImortalite = false;
			//Parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 0, 255));
			AddParticule(5);
			timerBonusColi = 0;
		
		}
	}

	if (auto inputControler = getParents().lock()->getComponents<Input>())
	{

		if (inputControler->getType(gp::Gamepad::Y) == PRESSED && !getCanMooved() && ChargeUltimate >= 100)
		{
			CompPhysique = Attaque;
			t_Attack = UltimeAttack;

			if (getParents().lock()->getParent()->getObjects("Player"))
			{
				TornadoActive = false;
			}
			if (getParents().lock()->getParent()->getObjects("Player2"))
			{
				UltimateBlood = false;
			}
			ChargeUltimate = 0;
		}
		if (inputControler->getType(gp::Gamepad::X) == PRESSED && !getInKnockDown())
		{
			if (CompPhysique == Jump)
			{
				CompPhysique = Attaque;
				t_Attack = JumpAttack;
			}
			else
			{
				if ((CompPhysique == Iddle || CompPhysique == Walking) && !b_Sprint)
				{
					CompPhysique = Attaque;
					t_Attack = Jab1;
				}
				if (b_Sprint && CompPhysique != Attaque && CompPhysique != Grab)
				{
					CompPhysique = Attaque;
					t_Attack = AttackSprint;
					if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
					{
						BigBoy->getComponents<Audio3D_Manager>()->getSound3D("AtackDash").play();
					}
					b_Sprint = false;
				}

			}

		}
		if (inputControler->getType(gp::Gamepad::X) == HOLD && !getInKnockDown() && CompPhysique != Jump && t_Attack != JumpAttack && CompPhysique != Grab)
		{
			timerCharge += tools::GetTimeDelta();
			if (timerCharge > 0.5)
			{
				CompPhysique = Attaque;
				t_Attack = Charging;
			}
		}

		if (inputControler->getType(gp::Gamepad::X) == RELEASED && !getInKnockDown() && CompPhysique != Jump && t_Attack != JumpAttack && CompPhysique != Grab)
		{
			if (timerCharge > 0.5 && timerCharge < 1 && t_Attack == Charging && CompPhysique == Attaque)
			{

				t_Attack = NUllattack;
				CompPhysique = Iddle;
			}

			if (timerCharge > 1 && t_Attack == Charging)
			{
				t_Attack = AttackCharge;
				if (auto parent = getParents().lock())
				{
					if (parent->getParent()->getObjects("Player"))
						parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("AtackMitraillette").play();

					if (parent->getParent()->getObjects("Player2"))
						parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_charge").play();
				}
			}
			timerCharge = 0;
		}



	}

	if (auto ForPlayer = getParents().lock()) {

		sf::Vector2f Jabs1Frame;
		sf::Vector2f Jabs2Frame;
		sf::Vector2f Jabs3Frame;
		sf::Vector2f Jabs4Frame;
		int AttackJumpFrame;
		int SprintAttackFrame;
		int AttackChargeFrame;
		int PrepareAtackCharge = 5;
		float VitesseAttack = 0.03;

		if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
			Jabs1Frame = { 4,4 };
			Jabs2Frame = { 5,5 };
			Jabs3Frame = { 5,6 };
			Jabs4Frame = { 7,7 };
			AttackJumpFrame = 8;
			SprintAttackFrame = 11;
			AttackChargeFrame = 14;
			Jab1Anime = "Jab1BB";
		}
		if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
			Jabs1Frame = { 6,7 };
			Jabs2Frame = { 6,6 };
			Jabs3Frame = { 6,6 };
			Jabs4Frame = { 6,6 };
			AttackJumpFrame = 6;
			SprintAttackFrame = 6;
			AttackChargeFrame = 8;
			Jab1Anime = "Jab1BL";
		}

		if (ForPlayer->getComponents<Identity>()->getName() == "Player3") {
			Jabs1Frame = { 2,2 };
			Jabs2Frame = { 1,1 };
			Jabs3Frame = { 2,2 };
			Jabs4Frame = { 3,3 };
			AttackJumpFrame = 3;
			SprintAttackFrame = 4;
			AttackChargeFrame = 10;
			PrepareAtackCharge = 3;
			Jab1Anime = "Jab1KP";
		}


		if (CompPhysique == Attaque)
		{
			if (auto Animator = getParents().lock()->getComponents<Animation>()) {

				if (t_Attack == Charging)
				{

					if (!PrepareCharge)
					{
						Animator->playAnim("PrepareCharging", false);
						if (Animator->getCurrentFrame() >= PrepareAtackCharge)
						{
							if (ForPlayer->getComponents<Identity>()->getName() == "Player")
								ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bb_charging").stop();

							if (ForPlayer->getComponents<Identity>()->getName() == "Player2")
								ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_charging").stop();

							PrepareCharge = true;
						}
						else
						{
							if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bb_charging").getStatus() == sf::Sound::Stopped)
								ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bb_charging").play();

							if (ForPlayer->getComponents<Identity>()->getName() == "Player2" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_charging").getStatus() == sf::Sound::Stopped)
								ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_charging").play();
						}

					}
					else
					{
						Animator->playAnim("Charging", true);
					}
				}
				else
				{
					PrepareCharge = false;
				}

				if (t_Attack == AttackCharge)
				{
					Animator->playAnim("AttackCharge", false);

					if (ForPlayer->getComponents<Identity>()->getName() == "Player3") {


						if (Animator->getCurrentFrame() == 4)
						{
							AddParticule(3);
						}
					}
					if (Animator->getCurrentFrame() == 11)
					{

						ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("AtackMitraillette").stop();
						if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("AtackFinalCharge").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("AtackFinalCharge").play();

						if (ForPlayer->getComponents<Identity>()->getName() == "Player2" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_charge").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_charge").play();

					}
					if (Animator->getCurrentFrame() >= AttackChargeFrame)
					{
						t_Attack = NUllattack;
						CompPhysique = Iddle;
						if (auto sound = getParents().lock()->getParent()->getObjects("gameMusic"))
						{
							if (ForPlayer->getComponents<Identity>()->getName() == "Player")
							{
								ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("AtackFinalCharge").stop();
							}
						}
					}
				}
				if (t_Attack == JumpAttack)
				{
					if (Animator->getCurrentFrame() == 1)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("JumpAttack").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("JumpAttack").play();

						if (ForPlayer->getComponents<Identity>()->getName() == "Player2" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_jump").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_jump").play();
					}



					Animator->playAnim("ATTACKJump", false);

					if (Animator->getCurrentFrame() == AttackJumpFrame)
					{

						Animator->pause();
					}
				}
				if (t_Attack == AttackSprint)
				{
					Animator->playAnim("sprintATTACK", false);

					if (Animator->getCurrentFrame() > SprintAttackFrame)
					{
						if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
						{
							BigBoy->getComponents<Audio3D_Manager>()->getSound3D("AtackDash").stop();
						}
						t_Attack = NUllattack;
						CompPhysique = Iddle;
					}
				}
				if (t_Attack == Jab1)
				{
					if (Animator->getCurrentFrame() == 1)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("HitOne").getStatus() == sf::Sound::Stopped)
						{
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("HitOne").play();
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_1").getStatus() == sf::Sound::Stopped)
						{
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_1").play();
						}
					}
					Animator->playAnim(Jab1Anime, false);
					if (BoostVitesseAttack)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.04f;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.02f;
						}
					}
					else
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.05f;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.04f;
						}
					}

					if (auto InputPlayer = getParents().lock()->getComponents<Input>()) {
						if (Animator->getCurrentFrame() == Jabs1Frame.x && InputPlayer->getCombo() > 1)
						{
							t_Attack = Jab2;
							m_MooveHit = false;
						}
					}
					if (Animator->getCurrentFrame() > Jabs1Frame.y)
					{
						t_Attack = NUllattack;
						CompPhysique = Iddle;
						m_MooveHit = false;
					}
				}
				if (t_Attack == Jab2)
				{
					if (Animator->getCurrentFrame() == 1)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("HitTwo").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("HitTwo").play();

						if (ForPlayer->getComponents<Identity>()->getName() == "Player2" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_2").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_2").play();

					}

					Animator->playAnim("Jab2", false);
					if (BoostVitesseAttack)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.04f;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.02f;
						}
					}
					else
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.07f;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.04f;
						}
					}
					if (auto InputPlayer = getParents().lock()->getComponents<Input>()) {
						if (Animator->getCurrentFrame() == Jabs2Frame.x && InputPlayer->getCombo() > 2)
						{
							if (BoostVitesseAttack)
							{
								t_Attack = Jab4;
							}
							else
							{
								t_Attack = Jab3;

							}
							/*CompPhysique = Iddle;*/
						}
					}
					if (Animator->getCurrentFrame() > Jabs2Frame.y)
					{
						t_Attack = NUllattack;
						CompPhysique = Iddle;
					}
				}
				if (t_Attack == Jab3)
				{
					if (Animator->getCurrentFrame() == 1)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("HitThree").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("HitThree").play();

						if (ForPlayer->getComponents<Identity>()->getName() == "Player2" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_1").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_3").play();
					}
					Animator->playAnim("Jab3", false);


					if (auto InputPlayer = getParents().lock()->getComponents<Input>()) {
						if (Animator->getCurrentFrame() == Jabs3Frame.x && InputPlayer->getCombo() > 3)
						{
							t_Attack = Jab4;
							/*CompPhysique = Iddle;*/
						}
					}
					if (Animator->getCurrentFrame() > Jabs3Frame.y)
					{
						t_Attack = NUllattack;
						CompPhysique = Iddle;
					}
				}
				if (t_Attack == Jab4)
				{
					if (Animator->getCurrentFrame() == 1)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("HitFour").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("HitFour").play();

						if (ForPlayer->getComponents<Identity>()->getName() == "Player2" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_4").getStatus() == sf::Sound::Stopped)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_4").play();
					}
					Animator->playAnim("Jab4", false);
					//BOOST DATTACK
					if (BoostVitesseAttack)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.04f;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.04f;
						}
					}
					else
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.06f;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
							Animator->getCurrentAnimInfo()->m_timePerFrame = 0.06f;
						}
					}
					if (Animator->getCurrentFrame() > Jabs4Frame.y)
					{
						if (BoostVitesseAttack)
						{
							t_Attack = Jab1;
						}
						else
						{
							t_Attack = NUllattack;
							CompPhysique = Iddle;

						}

					}
				}
			}

		}

	}
}

void Physique::updateHitStone()
{
	if (auto parent = getParents().lock())
	{
		if (CompPhysique == HitStun)
		{
			timerHitStun += tools::GetTimeDelta();
			parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 0, 0, 255));
			if (timerHitStun > 1)
			{
				timerHitStun = 0;
				CompPhysique = Iddle;
				Combo = 0;
			}
			else if (Combo > 7)
			{
				timerHitStun = 0;
				launchEntity(-400, Ejection, true);
				Combo = 0;
			}
		}
		else
		{
			parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 255, 255));
			Combo = 0;
		}
	}
}

void Physique::updateGrab()
{
	if (auto parent = getParents().lock())
	{

		if (CompPhysique == Grab)
		{

			timerGrab += tools::GetTimeDelta();

			if (CompPhysique == Ejection || CompPhysique == HitStun)
			{


			}

			if (auto inputControler = getParents().lock()->getComponents<Input>())
			{

				if (inputControler->getType(gp::Gamepad::X) == PRESSED && e_GrabType == GrabNeutre)
				{
					if (auto Animator = getParents().lock()->getComponents<Animation>()) {

						if (inputControler->getStickLeft().x == 0)
						{

							GrabCoup++;
							if (GrabCoup < 3)
							{
								Animator->playAnim("GrabJab", false);
								e_GrabType = GrabJab;
							}
							else
							{
								Animator->playAnim("GrabJabFinal", false);
								e_GrabType = GrabJabFinal;
							}
						}
						else if (inputControler->getStickLeft().x > 0)
						{
							if (auto Parent = getParents().lock())
							{
								if (Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("throw").getStatus() == sf::Sound::Stopped)
									Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("throw").play();
							}
							Animator->playAnim("GrabJet", false);

							e_GrabType = GrabProjection;
							e_look = LookRight;
						}
						else
						{
							if (auto Parent = getParents().lock())
							{
								if (Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("throw").getStatus() == sf::Sound::Stopped)
									Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("throw").play();
							}
							Animator->playAnim("GrabJet", false);
							e_GrabType = GrabProjection;
							e_look = LookLeft;
						}
					}
				}

			}

			int frameFinProjection;
			int frameJab;
			if (parent->getComponents<Identity>()->getName() == "Player") {
				frameFinProjection = 6;
				frameJab = 4;
			}
			if (parent->getComponents<Identity>()->getName() == "Player2") {
				frameFinProjection = 4;
				frameJab = 3;
			}

			if (e_GrabType == GrabProjection)
			{
				if (auto Animator = getParents().lock()->getComponents<Animation>()) {
					if (Animator->getCurrentFrame() == 1)
					{
						if (auto ForEnnemis = getParents().lock()->getParent()->getObjects(s_NameTypeGrabed)) {
							int tmpPosX;
							if (e_look == LookRight)
							{
								tmpPosX = 183;
								ForEnnemis->getComponents<Physique>()->setLook(LookLeft);
							}
							else
							{
								tmpPosX = -183;
								ForEnnemis->getComponents<Physique>()->setLook(LookRight);
							}
							ForEnnemis->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(parent->getComponents<ObjectTransform>()->getPosition().x - tmpPosX, parent->getComponents<ObjectTransform>()->getPosition().y));
						}
					}
					if (Animator->getCurrentFrame() == 2)
					{
						if (auto ForEnnemis = getParents().lock()->getParent()->getObjects(s_NameTypeGrabed)) {

							ForEnnemis->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(parent->getComponents<ObjectTransform>()->getPosition().x, parent->getComponents<ObjectTransform>()->getPosition().y - 100));
						}
					}
					//EJECTION DU MOB
					if (Animator->getCurrentFrame() == 3)
					{
						int tmpPosX;
						if (e_look == LookRight)
						{

							tmpPosX = 100;
						}
						else
						{
							tmpPosX = -100;
						}
						if (auto ForEnnemis = getParents().lock()->getParent()->getObjects(s_NameTypeGrabed)) {
							if (ForEnnemis->getComponents<Physique>()->getComportement() == Grabed)
							{
								ForEnnemis->getComponents<ObjectTransform>()->setZBuffer(parent->getComponents<ObjectTransform>()->getZBuffer());
								ForEnnemis->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(parent->getComponents<ObjectTransform>()->getPosition().x + tmpPosX, parent->getComponents<ObjectTransform>()->getPosition().y - 100));
								ForEnnemis->getComponents<Physique>()->setDamageEntity2v(true, 20);
								//ForEnnemis->getComponents<Shake>()->m_activeET = true;
							}
						}
					}

					if (Animator->getCurrentFrame() == frameFinProjection)
					{
						GrabCoup = 0;
						timerGrab = 0;
						e_GrabType = GrabNeutre;
						t_Attack = NUllattack;
						CompPhysique = Iddle;
						
					}
				}

			}
			if (e_GrabType == GrabJab)
			{
				if (auto Animator = getParents().lock()->getComponents<Animation>()) {

					if (Animator->getCurrentFrame() >= frameJab)
					{
						if (auto ForEnnemis = getParents().lock()->getParent()->getObjects(s_NameTypeGrabed)) {

							ForEnnemis->getComponents<Physique>()->setDamageEntity2v(false, 10);
							setCoupTouched();
							
						}
						e_GrabType = GrabNeutre;

					}
				}
			}
			if (e_GrabType == GrabJabFinal)
			{
				if (auto Animator = getParents().lock()->getComponents<Animation>()) {
					if (Animator->getCurrentFrame() >= 4)
					{
						e_GrabType = GrabNeutre;
						t_Attack = NUllattack;
						CompPhysique = Iddle;
						GrabCoup = 0;
						timerGrab = 0;
						if (auto ForEnnemis = getParents().lock()->getParent()->getObjects(s_NameTypeGrabed)) {

							ForEnnemis->getComponents<Physique>()->setDamageEntity2v(true, 10);
						}
					}
				}
			}


			if (timerGrab > 5)
			{
				if (auto ForEnnemis = getParents().lock()->getParent()->getObjects(s_NameTypeGrabed)) {

					ForEnnemis->getComponents<Physique>()->setComportement(Iddle);
				}
				t_Attack = NUllattack;
				CompPhysique = Iddle;
				e_GrabType = GrabNeutre;
				timerGrab = 0;
			}
		}

		if (CompPhysique == Grabed)
		{
			if (auto ForPlayer = getParents().lock()->getParent()->getObjects(s_NameTypeGrabeur)) {

				if (ForPlayer->getComponents<Physique>()->getComportement() == HitStun || ForPlayer->getComponents<Physique>()->getComportement() == Ejection)
				{
					CompPhysique = Iddle;
				}
			}

		}
	}
}

void Physique::updateJumpAndPorjection()
{
	if (auto parent = getParents().lock())
	{
		if (t_TimerBool)
		{
			f_TimerDelay += tools::GetTimeDelta();
			if (f_TimerDelay > 0.2)
			{
				t_TimerBool = false;
				f_TimerDelay = 0;
			}
		}

		if (CompPhysique == Jump || CompPhysique == Ejection || t_Attack == JumpAttack)
		{
			if (CompPhysique == Ejection)
			{
				if (e_look == LookLeft)
				{
					xPhysique = 700;
					//parent->getComponents<Sprite>()->getSprite().setRotation(90);
				}
				else if (e_look == LookRight)
				{
					//parent->getComponents<Sprite>()->getSprite().setRotation(-90);
					xPhysique = -700;

				}
			}

			if (CompPhysique == Jump)
			{
				if (parent->getComponents<RigidBody>()->getSpeed().x > 0.1)
				{
					if (!b_Sprint)
					{
						xPhysique = 300;
					}
					else
					{
						xPhysique = 700;
					}
				}
				else if (parent->getComponents<RigidBody>()->getSpeed().x < -0.1)
				{
					if (!b_Sprint)
					{
						xPhysique = -300;
					}
					else
					{
						xPhysique = -700;
					}
				}
				else
				{
					if (CompPhysique != Ejection)
					{
						xPhysique = 0;
					}
				}
			}
			parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ static_cast<float>(xPhysique), f_JumpVitesse });
			f_JumpVitesse += MassPhysique * tools::GetTimeDelta();
		}
		else
		{

			if (CompPhysique == Attaque && t_Attack == AttackSprint)
			{
				if (auto Animator = parent->getComponents<Animation>()) {
					int SpeedDash;
					int frameDashAttack;
					if (parent->getComponents<Identity>()->getName() == "Player") {
						frameDashAttack = 6;
						SpeedDash = 900;

					}
					if (parent->getComponents<Identity>()->getName() == "Player2") {
						frameDashAttack = 6;
						SpeedDash = 1400;
					}
					if (parent->getComponents<Identity>()->getName() == "Player3") {
						frameDashAttack = 3;
						SpeedDash = 1200;
					}

					if (Animator->getCurrentFrame() >= frameDashAttack)
					{
						parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ 0,0 });
					}
					else
					{

						if (e_look == LookRight)
						{
							parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ v2_Speed.x + SpeedDash,0 });

						}
						else
						{
							parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ -v2_Speed.x - SpeedDash,0 });
						}
					}

				}
			}
			else
			{
				if (CompPhysique != KnockDown && CompPhysique != HitStun && CompPhysique != Attaque && CompPhysique != Died && CompPhysique != Grab && CompPhysique != Grabed)
				{

					parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ parent->getComponents<RigidBody>()->getSpeed().x,parent->getComponents<RigidBody>()->getSpeed().y });
				}
				else
				{
					if (!Aspired)
					{
						parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ 0,0 });
					}

				}
			}
		}


		//COLLIDER TEMPORAIRE
		//Atterrissage

		if (parent->getComponents<ObjectTransform>()->getPosition().y >= tmpZ)
		{
			if ((CompPhysique == Ejection) || (CompPhysique == Ejection && t_Attack == JumpAttack))
			{
				if (!t_TimerBool)
				{
					if (m_typeMob == T)
					{
						if (auto IA = parent->getComponents<IA_TRASHER>())
						{
							IA->m_tReleve = 0;

						}
					}
					else if (m_typeMob == S)
					{
						if (auto IA = parent->getComponents<IA_SPIKER>())
						{
							IA->m_tReleve = 0;

						}
					}
					else if (m_typeMob == C)
					{
						if (auto IA = parent->getComponents<IA_CLEEVER>())
						{
							IA->m_tReleve = 0;
						}
					}
					else
					{
						if (auto IA = parent->getComponents<IA_PatternH>())
						{
							IA->m_tReleve = 0;
						}
					}
					timerKnockDown = 0;
					if (m_life <= 0)
					{
						if (Revive < 1)
						{
							CompPhysique = Died;

						}
						else
						{
							m_life = 100;
							Revive--;
							CompPhysique = KnockDown;
						}
					}
					else
					{
						if (parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("knockdown").getStatus() == sf::Sound::Stopped)
							parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("knockdown").play();
						CompPhysique = KnockDown;
					}

					t_Attack = NUllattack;
					parent->getComponents<RigidBody>()->resetSpeed();
					parent->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(parent->getComponents<ObjectTransform>()->getPosition().x, tmpZ));
					parent->getComponents<ObjectTransform>()->setZBuffer(tmpZ);
					parent->getComponents<ObjectTransform>()->setState(NON_STATIC);
					parent->getComponents<Shake>()->m_activeET = true;
					t_TimerBool = true;
				}
			}
			if ((CompPhysique == Jump || t_Attack == JumpAttack) && !t_TimerBool)
			{
				t_Attack = NUllattack;
				CompPhysique = Iddle;
				t_TimerBool = true;
				parent->getComponents<RigidBody>()->resetSpeed();
				parent->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(parent->getComponents<ObjectTransform>()->getPosition().x, tmpZ));
				parent->getComponents<ObjectTransform>()->setZBuffer(tmpZ);
				parent->getComponents<ObjectTransform>()->setState(NON_STATIC);


			}
		}
	}
}

void Physique::update()
{

	if (m_active)
	{
		if (timerTmpCoup < timerForCoupTouched)
		{
			timerTmpCoup = timerForCoupTouched;
		}
		else if (timerTmpCoup == timerForCoupTouched)
		{
			timerForCoupTouched = 0;
			timerTmpCoup = 0;
		}

		//timerTmp = timerFonction;
		if (timerTmp < timerForEntityDamage)
		{
			timerTmp = timerForEntityDamage;
		}
		else if (timerTmp == timerForEntityDamage)
		{
			timerForEntityDamage = 0;
			timerTmp = 0;
		}

		/*	if (auto AutoPlayer = getParents().lock()->getParent()->getObjects(PLAYER)) {

				AutoPlayer->getObjects("OmbreObj")->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(AutoPlayer->getComponents<ObjectTransform>()->getPosition().x - 149.f, AutoPlayer->getComponents<ObjectTransform>()->getZBuffer() - 65));
				AutoPlayer->getObjects("OmbreObj")->getComponents<ObjectTransform>()->setZBuffer(AutoPlayer->getComponents<ObjectTransform>()->getZBuffer() - 1000);

			}*/


		if (auto AutoEnnemis = getParents().lock()) {
			if (AutoEnnemis->getComponents<Identity>()->getName() != "Boss")
			{
				
				if (m_life <= 0)
				{
					AutoEnnemis->getObjects("OmbreObj")->setActive(false);
				}
				else
				{
					AutoEnnemis->getObjects("OmbreObj")->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(AutoEnnemis->getComponents<ObjectTransform>()->getPosition().x - 149.f, AutoEnnemis->getComponents<ObjectTransform>()->getZBuffer() - 65));

					AutoEnnemis->getObjects("OmbreObj")->getComponents<ObjectTransform>()->setZBuffer(AutoEnnemis->getComponents<ObjectTransform>()->getZBuffer() - 1000);
				}

			}


		}



		updateController();
		updateJumpAndPorjection();
		updateKnockDown();
		updateHitStone();
		updateCombat();
		updateGrab();
		updateUltimate();
		if (auto inputControler = getParents().lock()->getComponents<Input>())
		{
			if (inputControler->getType(gp::Gamepad::X) == PRESSED && !getInKnockDown())
			{
				if (CompPhysique == Jump)
				{
					CompPhysique = Attaque;
					t_Attack = JumpAttack;
				}
				if (CompPhysique == Iddle || CompPhysique == Walking)
				{
					CompPhysique = Attaque;
					t_Attack = Jab1;
				}
			}
			/*LES COLIS*/

			if (inputControler->getType(gp::Gamepad::RB) == PRESSED)
			{
				
				if (auto player = getParents().lock())
				{
					if (auto parent = player->getObjects("SCORE_ID"))
					{
						if (auto score = parent->getComponents<Score>())
						{
							score->checkScoreLargage();
							if (score->getScoreTotal() >= 8000) {
								score->setRouletteActif(true);
								/*if (random == 1) {
									std::shared_ptr<GameObject> colis = Colis::createDrop(BLEU, sf::Vector2f(test.x, testZBuffer - 1000.f), sf::Vector2f(test.x, testZBuffer));
									player->addGameObject(colis);
									score->setTypeColisUI(colis);
									score->scoreAdd(-8,0);
									score->setTextWhite();
								}
								else if (random == 2) {
									std::shared_ptr<GameObject> colis = Colis::createDrop(JAUNE, sf::Vector2f(test.x, testZBuffer - 1000.f), sf::Vector2f(test.x, testZBuffer));
									player->addGameObject(colis);
									score->setTypeColisUI(colis);
									score->scoreAdd(-8,0);
								}
								else if (random == 3) {
									std::shared_ptr<GameObject> colis = Colis::createDrop(ROUGE, sf::Vector2f(test.x, testZBuffer - 1000.f), sf::Vector2f(test.x, testZBuffer));
									player->addGameObject(colis);
									score->setTypeColisUI(colis);

									score->scoreAdd(-8,0);
								}
								else if (random == 4) {
									std::shared_ptr<GameObject> colis = Colis::createDrop(VERT, sf::Vector2f(test.x, testZBuffer - 1000.f), sf::Vector2f(test.x, testZBuffer));
									player->addGameObject(colis);
									score->setTypeColisUI(colis);

									score->scoreAdd(-8,0);
								}*/
							}
						}
					}
				}
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || inputControler->getType(gp::Gamepad::A) == PRESSED) && !getCanMooved())
			{
				if (auto Parent = getParents().lock())
				{
					if (Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("Jump").getStatus() == sf::Sound::Stopped)
						Parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("Jump").play();
				}
				launchEntity(-800, Jump, false);
			}

			if (inputControler->moveDirection(gpDirection::RIGHT) || inputControler->moveDirection(gpDirection::LEFT))
			{
				if (!HoldStick)
				{
					DoubleCheckStick++;
				}
				HoldStick = true;

			}
			else
			{
				HoldStick = false;
			}
			if (DoubleCheckStick != 0)
			{
				TimerStick += tools::GetTimeDelta();

				if (TimerStick > 0.2)
				{
					TimerStick = 0;
					DoubleCheckStick = 0;
				}
			}
			if (DoubleCheckStick > 1)
			{
				b_Sprint = true;
				DoubleCheckStick = 1;
			}
			/*if (inputControler->getType(gp::Gamepad::Y) == PRESSED && !getCanMooved())
			{

			}*/

		}

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !getCanMooved())
		{
			setDamageEntity2v(true, 0);
		}*/
		if (auto tmp_Sprite = getParents().lock()->getComponents<Sprite>())
		{
			if (e_look == LookRight)
			{
				tmp_Sprite->getSprite().setScale({ 1,1 });
			}
			else
			{
				tmp_Sprite->getSprite().setScale({ -1,1 });
			}
		}

		if (auto ForPlayer = getParents().lock()->getParent()->getObjects(PLAYER)) {
			if (auto Animator = getParents().lock()->getComponents<Animation>()) {
				if (auto ForPlayer = getParents().lock()) {

					if (CompPhysique == Jump)
					{

						int JumpFrame = 5;
						if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
							JumpFrame = 6;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
							JumpFrame = 4;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player3") {
							JumpFrame = 3;
						}
						ForPlayer->getComponents<Animation>()->playAnim("JUMP", false);
						if (ForPlayer->getComponents<Animation>()->getCurrentFrame() == JumpFrame)
						{
							ForPlayer->getComponents<Animation>()->pause();
						}
					}
					if (CompPhysique == HitStun)
					{
						ForPlayer->getComponents<Animation>()->playAnim("Hit", false);
						ForPlayer->getComponents<Animation>()->pause();
					}

					if (CompPhysique == Died)
					{
						ForPlayer->getComponents<Animation>()->playAnim("Dying", false);

						if (ForPlayer->getComponents<Animation>()->getCurrentFrame()> 4)
						{

							B_Dead = true;

						}

					}


					if (CompPhysique == Ejection || CompPhysique == KnockDown)
					{

						int ReleverFrame = 5;
						int ejectionFrame = 5;
						int TomberFrame = 5;
						if (ForPlayer->getComponents<Identity>()->getName() == "Player") {
							ReleverFrame = 5;
							TomberFrame = 6;
							ejectionFrame = 5;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player2") {
							ReleverFrame = 6;
							ejectionFrame = 5;
							TomberFrame = 5;
						}
						if (ForPlayer->getComponents<Identity>()->getName() == "Player3") {
							ReleverFrame = 6;
							ejectionFrame = 5;
							TomberFrame = 6;
						}

						if (CompPhysique == Ejection)
						{
							ForPlayer->getComponents<Animation>()->playAnim("Ejection", false);
							if (ForPlayer->getComponents<Animation>()->getCurrentFrame() == ejectionFrame)
							{
								ForPlayer->getComponents<Animation>()->pause();
							}

						}

						if (CompPhysique == KnockDown)
						{
							if (!b_ReleverAnimation)
							{
								ForPlayer->getComponents<Animation>()->play();

							}
							if (ForPlayer->getComponents<Animation>()->getCurrentFrame() == TomberFrame && !b_ReleverAnimation)
							{
								ForPlayer->getComponents<Animation>()->pause();
								//b_ReleverAnimation = true;

							}
							if (b_ReleverAnimation)
							{
								if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("getup").getStatus() == sf::Sound::Stopped)
									ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("getup").play();
								ForPlayer->getComponents<Animation>()->playAnim("Relever", false);
								if (ForPlayer->getComponents<Animation>()->getCurrentFrame() == ReleverFrame)
								{
									ForPlayer->getComponents<Animation>()->pause();

								}
							}
						}

					}
					else
					{
						b_ReleverAnimation = false;
					}
					if (CompPhysique == Grab && e_GrabType == GrabNeutre)
					{
						ForPlayer->getComponents<Animation>()->playAnim("GrabIdle", true);
					}
					if (CompPhysique == Iddle)
					{
						if (ForPlayer->getComponents<Identity>()->getName() == "Player" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bb_charging").getStatus() == sf::Sound::Playing)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bb_charging").stop();

						if (ForPlayer->getComponents<Identity>()->getName() == "Player2" && ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_charging").getStatus() == sf::Sound::Playing)
							ForPlayer->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_charging").stop();

						ForPlayer->getComponents<Animation>()->playAnim("IDLE", true);
					}
					if (CompPhysique == Walking)
					{
						if (!b_Sprint)
						{
							ForPlayer->getComponents<Animation>()->playAnim("MOVE", true);
						}
						else
						{
							ForPlayer->getComponents<Animation>()->playAnim("SPRINT", true);
						}
					}

				}
			}
		}

		checkMask();

	}
	else
	{
		//if (auto AutoEnnemis = getParents().lock()->getParent()->getObjects(ENNEMY)) {


		//	//AutoEnnemis->getObjects("OmbreObj")->getComponents<ObjectTransform>()->setZBuffer(AutoEnnemis->getComponents<ObjectTransform>()->getZBuffer() - 1000);

		//}
	}
}

void Physique::draw()
{

	//window.draw(*m_spriteMask1);
	//window.draw(*m_spriteMask2);
	//window.draw(*m_spriteMask3);
	//window.draw(*m_spriteMask4);
	//window.draw(*m_spriteMask5);
	//window.draw(*m_spriteMask6);
	//window.draw(*m_spriteMask7);

}

bool Physique::getCanMooved() {

	if (CompPhysique == Grabed || CompPhysique == Grab || CompPhysique == Attaque || CompPhysique == Jump || CompPhysique == Ejection || CompPhysique == KnockDown || CompPhysique == HitStun || CompPhysique == Died)
	{
		return true;

	}
	else
	{
		return false;
	}
}

void Physique::checkMask()

{
	if (auto parent = getParents().lock())
	{
		auto root = parent->getParent();

		if (auto mapCollision = root->getObjects("MapCollision"))//récupération de la map de collision qui est link au root

		{
			auto collisionMask = mapCollision->getComponents<CollisionMask>(); //récupération de son mask de collsision
			bool checkX = collisionMask->checkCollisionMap(X, getParents().lock());//vérfication des collisions sur l'axe X
			bool checkY = collisionMask->checkCollisionMap(Y, getParents().lock());//vérification des collisions sur l'axe Z avec  la speed Y

			auto body = parent->getComponents<RigidBody>();

			if (checkX)
			{
				body->setSpeed(sf::Vector2f(0, body->getSpeed().y));
			}

			if (checkY && CompPhysique != Jump && CompPhysique != Ejection && CompPhysique != Attaque && t_Attack != JumpAttack)
			{
				body->setSpeed(sf::Vector2f(body->getSpeed().x, 0));
			}
		}
	}

}

void Physique::AddParticule(int type) {
	if (type == 1) {
		if (auto Parent = getParents().lock())
		{
			auto direction = Parent->getParent()->getObjects(PLAYER)->getComponents<Physique>()->getLook();
			auto position = Parent->getComponents<ObjectTransform>()->getPosition();
			auto hit = Parent->getParent()->getObjects("Hit");
			if (auto Bigdirection = Parent->getParent()->getObjects(PLAYER)->getComponents<Physique>()->getLook() == 0) {
				hit->getComponents<Hit>()->add(sf::Vector2f(position.x + tools::frand(20.f, 30.f),
					position.y - tools::frand(380.f, 420.f)),
					sf::Vector2f(0.8f, 0.8f));
			}
			if (auto Bigdirection = Parent->getParent()->getObjects(PLAYER)->getComponents<Physique>()->getLook() == 1) {
				hit->getComponents<Hit>()->add(sf::Vector2f(position.x + tools::frand(20.f, 30.f),
					position.y - tools::frand(380.f, 420.f)),
					sf::Vector2f(-0.8f, 0.8f));
			}

		}
	}
	if (type == 2) {
		if (auto Parent = getParents().lock())
		{
			auto Bigposition = Parent->getComponents<ObjectTransform>()->getPosition();
			auto Bighit = Parent->getParent()->getObjects("BigHit");
			if (auto Bigdirection = Parent->getParent()->getObjects(PLAYER)->getComponents<Physique>()->getLook() == 0) {
				Bighit->getComponents<BigHit>()->add(sf::Vector2f(Bigposition.x + tools::frand(20.f, 30.f),
					Bigposition.y - tools::frand(350.f, 380.f)),
					sf::Vector2f(0.8f, 0.8f));
			}
			if (auto Bigdirection = Parent->getParent()->getObjects(PLAYER)->getComponents<Physique>()->getLook() == 1) {
				Bighit->getComponents<BigHit>()->add(sf::Vector2f(Bigposition.x + tools::frand(20.f, 30.f),
					Bigposition.y - tools::frand(350.f, 380.f)),
					sf::Vector2f(-0.8f, 0.8f));
			}
		}
	}

	if (type == 3) {
		if (auto Parent = getParents().lock())
		{
			auto bossPos = Parent->getComponents<ObjectTransform>()->getPosition();
			auto smoke = Parent->getParent()->getObjects("Boss_Smoke");
			if (auto BossDirection = Parent->getParent()->getObjects(PLAYER)->getComponents<Physique>()->getLook() == 0) {
				smoke->getComponents<Boss_Smoke>()->add(sf::Vector2f(bossPos.x + 220,
					bossPos.y - 330.f),
					100.f,
					tools::frand(45.f, 315.f),
					sf::Vector2f(0.6f, 0.6f));
			}
			if (auto BossDirection = Parent->getParent()->getObjects(PLAYER)->getComponents<Physique>()->getLook() == 1) {
				smoke->getComponents<Boss_Smoke>()->add(sf::Vector2f(bossPos.x - 220,
					bossPos.y - 330.f),
					-100.f,
					tools::frand(135.f, 225.f),
					sf::Vector2f(0.6f, 0.6f));
			}
		}
	}

	if (type == 4)
	{
		timerSpawn += tools::GetTimeDelta();
		if (auto Parent = getParents().lock())
		{
			auto position = Parent->getParent()->getObjects(PLAYER)->getComponents<ObjectTransform>()->getPosition();
			//auto position = Parent->getComponents<ObjectTransform>()->getPosition();
			auto boost = Parent->getParent()->getObjects("BoostEffect");
			if (timerSpawn >= 0.05)
			{
				boost->getComponents<Particules>()->addParticules(sf::Vector2f(position.x + tools::frand(-111.f, 111.f),
					position.y - tools::frand(0.f, 465.f)),//Position
					"bleu.png",
					HAUT,//Direction
					255,//opacite
					100 + tools::frand(10, 20),//speed
					200.f);//EraseSpeed
				timerSpawn = 0.f;
			}
		}
	}
	if (type == 5)
	{
		timerSpawn += tools::GetTimeDelta();
		if (auto Parent = getParents().lock())
		{
			auto position = Parent->getParent()->getObjects(PLAYER)->getComponents<ObjectTransform>()->getPosition();
			auto boost = Parent->getParent()->getObjects("BoostEffect");
			if (timerSpawn >= 0.05)
			{
				boost->getComponents<Particules>()->addParticules(sf::Vector2f(position.x + tools::frand(-111.f, 111.f),
					position.y - tools::frand(0.f, 465.f)),//Position
					"jaune.png",
					HAUT,//Direction
					255,//opacite
					100 + tools::frand(10, 20),//speed
					200.f);//EraseSpeed
				timerSpawn = 0.f;
			}
		}
	}
	if (type == 6)
	{
		timerSpawn += tools::GetTimeDelta();
		if (auto Parent = getParents().lock())
		{
			auto position = Parent->getParent()->getObjects("Camera")->getComponents<Camera>()->getView().getCenter();
			auto CameraSize = Parent->getParent()->getObjects("Camera")->getComponents<Camera>()->getView().getSize();
			auto randomX = CameraSize.x / 2;
			auto randomY = (CameraSize.y / 2) + 200;
			auto ulti = Parent->getParent()->getObjects("BoostEffect");
			if (timerSpawn >= 0.001)
			{
				for (int i = 0; i <= 5; i++) {
					ulti->getComponents<Particules>()->addParticules(sf::Vector2f(position.x + tools::frand(-randomX, randomX),
						position.y - randomY),//Position
						"sang.png",
						BAS,//Direction
						255,//opacite
						6400 + tools::frand(500, 800),//speed
						200.f);//EraseSpeed
				}
				timerSpawn = 0.f;
			}
		}
	}
	if (type == 7)
	{
		if (auto Parent = getParents().lock())
		{
			auto position = Parent->getParent()->getObjects("Camera")->getComponents<Camera>()->getView().getCenter();
			auto CameraSize = Parent->getParent()->getObjects("Camera")->getComponents<Camera>()->getView().getSize();
			auto randomX = CameraSize.x / 2;
			auto randomY = (CameraSize.y / 2) + 200;
			auto ulti = Parent->getParent()->getObjects("BoostEffect");

			ulti->getComponents<Particules>()->addParticules(sf::Vector2f(position.x + 600.f,
				position.y - 320.f),//Position
				"splash2.png",
				STATIQUE,//Direction
				255,//opacite
				0,//speed
				10.f);//EraseSpeed

			ulti->getComponents<Particules>()->addParticules(sf::Vector2f(position.x - 600.f,
				position.y + 320.f),//Position
				"splash1.png",
				STATIQUE,//Direction
				255,//opacite
				0,//speed
				10.f);//EraseSpeed

		}
	}
	if (type == 8)
	{
		timerSpawn += tools::GetTimeDelta();
		if (auto Parent = getParents().lock())
		{
			auto position = Parent->getParent()->getObjects(PLAYER)->getComponents<ObjectTransform>()->getPosition();
			//auto position = Parent->getComponents<ObjectTransform>()->getPosition();
			auto boost = Parent->getParent()->getObjects("BoostEffect");
			if (timerSpawn >= 0.3)
			{
				boost->getComponents<Particules>()->addParticules(sf::Vector2f(position.x + tools::frand(-111.f, 90.f),
					position.y - tools::frand(0.f, 465.f)),//Position
					"fleche2.png",
					HAUT,//Direction
					255,//opacite
					100 + tools::frand(10, 20),//speed
					200.f);//EraseSpeed
				timerSpawn = 0.f;
			}
		}
	}
}
