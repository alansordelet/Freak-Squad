#include "Physique.h"
#include "Score.h"
#include "FeedBackScore.h"
#include"IA_Pattern.h"
#include "Ui_Player.h"
#include "Blood.h"
#include "CheckCollision.h"
#include"Hit.h"
#include"Sounds3D.h"
#include"Boss_Smoke.h"
#include"IA_PatternT.h"
#include"IA_PatternS.h"
#include"IA_PatternC.h"


void Physique::updateUltimate()
{
	if (auto AutoPlayer = getParents().lock()->getParent()->getObjects("Player"))
	{
		if (CompPhysique == Attaque)
		{
			if (t_Attack == UltimeAttack)
			{
				if (!TornadoActive)
				{
					if (auto parent = getParents().lock())
					{
						if (parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("vaccum").getStatus() == sf::Sound::Stopped)
							parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("vaccum").play();
					}
					AutoPlayer->getComponents<Animation>()->playAnim("UltimateAttackDebut", false);
					if (AutoPlayer->getComponents<Animation>()->getCurrentFrame() == 5)
					{
						if (auto parent = getParents().lock())
						{
							if (parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bb_ulti").getStatus() == sf::Sound::Stopped)
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bb_ulti").play();
						}
						TornadoActive = true;
						AutoPlayer->getObjects("PlayerUltimeBB")->getComponents<Animation>()->playAnim("Tornado", true);
						AutoPlayer->getComponents<Animation>()->playAnim("UltimateAttackBoucle", true);
					}
				}
				else
				{
					timerTornado += tools::GetTimeDelta();

					timerParticules += tools::GetTimeDelta();
					////std::cout << "je fais des particules de sang" << std::endl;
					if (timerTornado > 3)
					{
						if (auto parent = getParents().lock())
						{
							if (parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("chainsaw").getStatus() == sf::Sound::Stopped)
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("chainsaw").play();

							if (parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("flesh").getStatus() == sf::Sound::Stopped)
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("flesh").play();
						}
						AutoPlayer->getComponents<Animation>()->playAnim("UltimateAttackEnd", true);
						if (AutoPlayer->getComponents<Animation>()->getCurrentFrame() == 15)
						{
							
							if (auto parent = getParents().lock())
							{
								if (parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("gush").getStatus() == sf::Sound::Stopped)
									parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("gush").play();
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bb_ulti").stop();
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("chainsaw").stop();
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("flesh").stop();
							}
							timerTornado = 0;
							TornadoActive = false;
							t_Attack = NUllattack;
							CompPhysique = Iddle;
							AddParticule(7);
						}

						if (AutoPlayer->getComponents<Animation>()->getCurrentFrame() == 12)
						{
							AutoPlayer->getObjects("PlayerUltimeBB")->getComponents<Animation>()->playAnim("TornadoEnd", false);

						}
						if (timerParticules >= 3.80f) {
							AddParticule(6);
							
						}
						
						
						/*EndTornado = true;*/
					}
					else if (timerParticules > 4.05f)
						timerParticules = 0.f;
					////std::cout << timerParticules << std::endl;


					auto TransformPlayer = AutoPlayer->getComponents<ObjectTransform>();
					if (e_look == LookRight)
					{
						AutoPlayer->getObjects("PlayerUltimeBB")->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(TransformPlayer->getPosition().x + 1300, TransformPlayer->getPosition().y + 100));
						AutoPlayer->getObjects("PlayerUltimeBB")->getComponents<Sprite>()->getSprite().setScale(1, 1);
					}
					else
					{
						AutoPlayer->getObjects("PlayerUltimeBB")->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(TransformPlayer->getPosition().x - 1300, TransformPlayer->getPosition().y + 100));
						AutoPlayer->getObjects("PlayerUltimeBB")->getComponents<Sprite>()->getSprite().setScale(-1, 1);
					}
				}


			}

		}


	}


	if (auto AutoPlayer2 = getParents().lock()->getParent()->getObjects("Player2"))
	{
		if (CompPhysique == Attaque)
		{
			if (t_Attack == UltimeAttack)
			{
				if (!UltimateBlood)
				{
					if (!EndUltimateBlood)
					{
						if (auto parent = getParents().lock())
						{
							if (parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_ulti").getStatus() == sf::Sound::Stopped)
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_ulti").play();
						}

						AutoPlayer2->getComponents<Animation>()->playAnim("UltimateAttackDebut", false);
						if (AutoPlayer2->getComponents<Animation>()->getCurrentFrame() == 3)
						{	
							AutoPlayer2->getObjects("PlayerUltimeBL")->getComponents<Animation>()->playAnim("YeuxAnnim", false);
							UltimateBlood = true;
						}

						if (colorSetFondu < 250)
						{
							colorSetFondu += 1000 * tools::GetTimeDelta();
						}
					}

					if (EndUltimateBlood)
					{
						
						if (AutoPlayer2->getComponents<Animation>()->getCurrentFrame() == 3)
						{
							
							AutoPlayer2->getComponents<ObjectTransform>()->setState(NON_STATIC);
							CompPhysique = Iddle;
							t_Attack = NUllattack;
							EndUltimateBlood = false;

						}

						if (colorSetFondu > 2)
						{
							colorSetFondu -= 1000 * tools::GetTimeDelta();
						}
					}


				}
				if (UltimateBlood)
				{




					if (AutoPlayer2->getObjects("PlayerUltimeBL")->getComponents<Animation>()->getCurrentFrame() > 8 && !EndUltimateBlood)

					{
						if (auto parent = getParents().lock())
						{
							parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("attack_bl_ulti2").play();
						}
						AutoPlayer2->getObjects("PlayerUltimeBL")->getComponents<Animation>()->playAnim("EnchainementAnim", false);
						EndUltimateBlood = true;

					}

					if (AutoPlayer2->getObjects("PlayerUltimeBL")->getComponents<Animation>()->getCurrentFrame() > 7 && EndUltimateBlood)
					{
						UltimateBlood = false;
						AutoPlayer2->getComponents<Animation>()->playAnim("UltimateAttackEnd", false);


					}
				}
				AutoPlayer2->getObjects("PlayerUltimeBLFond")->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 255, colorSetFondu));
			}
		}
	}
	if (auto AutoEnnemis = getParents().lock())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !Aspired)
		{

		}

		if (Aspired)
		{
			CompPhysique = HitStun;
			AutoEnnemis->getComponents<RigidBody>()->setSpeed(sf::Vector2f(tools2::direction(AutoEnnemis->getComponents<ObjectTransform>()->getPosition(), PosDirectionApired).x * 1200, tools2::direction(AutoEnnemis->getComponents<ObjectTransform>()->getPosition(), PosDirectionApired).y * 1200));
		}


	}

}

void Physique::SetAspired(sf::Vector2f _pos)
{
	PosDirectionApired = _pos;
	Aspired = true;
}



