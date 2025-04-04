#include "CheckCollision.h"
#include "Physique.h"
#include "Destructible.h"
#include "Package.h"
#include "Shake.h"
#include "Collectible.h"
#include "Particules.h"
#include "Ui_Player.h"
#include "Sounds3D.h"




CheckCollision::CheckCollision()
{
	//Button.setTexture(RessourceManager::get()->getSceneTexture("touche_b.png"));
	timerSpawn = 0;
	timerParticules = 0;
}

CheckCollision::~CheckCollision()
{
}

void CheckCollision::update()
{
	if (auto parent = getParents().lock())
	{
		if (!parent->getComponents<Collider>()->getRectAttack().empty())
		{
			if (parent->getComponents<Identity>()->getType() == PLAYER)
			{
				auto attack = parent->getComponents<Collider>()->getRectAttack();

				for (auto& o : GameObject::l_Ennemy)
				{
					auto _o = o->getComponents<Collider>();
					for (int i = 0; i < attack.size(); i++)
					{
						for (auto j : _o->getRectBody())
						{
							if (attack[i].rect.intersects(j.rect) && o->getComponents<Physique>()->getLife() >= 0 && o->getComponents<Identity>()->getName() != "Boss" && o->isActive())
							{
								if (attack[i].name == "UltimateBloodDamage")
								{
									o->getComponents<Physique>()->setDamageEntity2v(true, 1000);
								}
								if (attack[i].name == "GrandZoneAspiration")
								{
									if (!o->getComponents<Physique>()->Aspired)
									{
										if (parent->getComponents<Physique>()->getLook() == LookRight)
										{
											o->getComponents<Physique>()->SetAspired(sf::Vector2f(parent->getComponents<ObjectTransform>()->getPosition().x + 350, parent->getComponents<ObjectTransform>()->getPosition().y - 300));
										}
										else
										{
											o->getComponents<Physique>()->SetAspired(sf::Vector2f(parent->getComponents<ObjectTransform>()->getPosition().x - 350, parent->getComponents<ObjectTransform>()->getPosition().y - 300));
										}

									}
								}

								if (attack[i].name == "ZoneDisparition")
								{
									o->getComponents<Physique>()->setLife(0);
									o->setActive(false);
								}
							}


							if (attack[i].rect.intersects(j.rect) && !o->getComponents<Physique>()->getInKnockDown()
								&& parent->getComponents<ObjectTransform>()->getZBuffer() - 80 < o->getComponents<ObjectTransform>()->getZBuffer() &&
								parent->getComponents<ObjectTransform>()->getZBuffer() + 80 > o->getComponents<ObjectTransform>()->getZBuffer() && o->isActive()) // rajouter le check Zbuffer
							{

								if (parent->getComponents<ObjectTransform>()->getZBuffer() - 10 < o->getComponents<ObjectTransform>()->getZBuffer() &&
									parent->getComponents<ObjectTransform>()->getZBuffer() + 10 > o->getComponents<ObjectTransform>()->getZBuffer() && !o->getComponents<Physique>()->Aspired
									&& parent->getComponents<Physique>()->getComportement() != Grab && o->getComponents<Physique>()->getComportement() != Grabed && o->isActive() && o->getComponents<Identity>()->getName() != "Boss")
								{

									if (attack[i].name == "MoveBigBoyGrab")
									{

										o->getComponents<Physique>()->setGrabEntity(parent->getComponents<Identity>()->getName(), o->getComponents<Identity>()->getName(), parent->getComponents<Physique>()->getLook());
										parent->getComponents<Physique>()->setComportement(Grab);
										parent->getComponents<Physique>()->e_GrabType = GrabNeutre;

										//o->getComponents<Physique>()->setDamageEntity2v(false, 0);
									}

									if (attack[i].name == "MoveBloodLustGrab")
									{

										o->getComponents<Physique>()->setGrabEntity(parent->getComponents<Identity>()->getName(), o->getComponents<Identity>()->getName(), parent->getComponents<Physique>()->getLook());
										parent->getComponents<Physique>()->setComportement(Grab);
										parent->getComponents<Physique>()->e_GrabType = GrabNeutre;


									}
								}
								int BonusAttack;

								if (parent->getComponents<Physique>()->Starter == DamageDoubleTranchant)
								{
									BonusAttack = 10;
								}
								else if (parent->getComponents<Physique>()->Starter == ScoreBonusMalusDegat)
								{
									BonusAttack = -5;
								}
								else
								{
									BonusAttack = 0;
								}

								if (attack[i].name == "Jab1BigBoy")
								{
									o->getComponents<Physique>()->setDamageEntity2v(false, 12 + BonusAttack);
									
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;

									}
								
								}
								if (attack[i].name == "Jab2BigBoy")
								{
									o->getComponents<Physique>()->setDamageEntity2v(false, 12 + BonusAttack);
								
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}
								if (attack[i].name == "Jab3BigBoy")
								{
									o->getComponents<Physique>()->setDamageEntity2v(false, 12 + BonusAttack);
									
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}
								if (attack[i].name == "Jab4BigBoy")
								{
									if (parent->getComponents<Physique>()->BoostVitesseAttack)
									{
										o->getComponents<Physique>()->setDamageEntity2v(false, 10 + BonusAttack);
										if (o->getComponents<Physique>()->m_typeMob != H)
										{
											parent->getComponents<Physique>()->setCoupTouched();
											o->getComponents<Shake>()->m_activeET = true;
										}
									}
									else
									{
										if (o->getComponents<Physique>()->m_typeMob != H)
										{
											parent->getComponents<Physique>()->setCoupTouched();
											o->getComponents<Shake>()->m_activeET = true;
										}
										o->getComponents<Physique>()->setDamageEntity2v(true, 20 + BonusAttack);
									
									}

								}
								if (attack[i].name == "ATTACKJumpBigBoy")
								{
									o->getComponents<Physique>()->setDamageEntity2v(true, 15 + BonusAttack);
								
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}
								if (attack[i].name == "chargeAttackBigBoy")
								{
									o->getComponents<Physique>()->setDamageEntity2v(false, 7 + BonusAttack);
									
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}
								if (attack[i].name == "finalchargeAttackBigBoy")
								{
									o->getComponents<Physique>()->setDamageEntity2v(true, 20 + BonusAttack);
									
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}
								if (attack[i].name == "sprintATTACKBigBoy")
								{
									o->getComponents<Physique>()->setDamageEntity2v(true, 15 + BonusAttack);
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}


								if (attack[i].name == "Jab1BloodLust")
								{
									o->getComponents<Physique>()->setDamageEntity2v(false, 10 + BonusAttack);
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}
								if (attack[i].name == "Jab2BloodLust")
								{
									o->getComponents<Physique>()->setDamageEntity2v(false, 10 + BonusAttack);
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}
								if (attack[i].name == "Jab3BloodLust")
								{
									o->getComponents<Physique>()->setDamageEntity2v(false, 10 + BonusAttack);
									if (o->getComponents<Physique>()->m_typeMob != H) 
									{
										o->getComponents<Shake>()->m_activeET = true;
									}
								

								}
								if (attack[i].name == "Jab4BloodLust")
								{
									if (parent->getComponents<Physique>()->BoostVitesseAttack)
									{
										o->getComponents<Physique>()->setDamageEntity2v(false, 10 + BonusAttack);
										if (o->getComponents<Physique>()->m_typeMob != H)
										{
											parent->getComponents<Physique>()->setCoupTouched();
											o->getComponents<Shake>()->m_activeET = true;
										}
									}
									else
									{
										o->getComponents<Physique>()->setDamageEntity2v(true, 15 + BonusAttack);
										if (o->getComponents<Physique>()->m_typeMob != H)
										{
											parent->getComponents<Physique>()->setCoupTouched();
											o->getComponents<Shake>()->m_activeET = true;
										}
									}

								}
								if (attack[i].name == "ATTACKJumpBloodLust")
								{
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
									o->getComponents<Physique>()->setDamageEntity2v(true, 12 + BonusAttack);
								}
								if (attack[i].name == "chargeAttackBloodLust")
								{
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
									o->getComponents<Physique>()->setDamageEntity2v(true, 20 + BonusAttack);
								}
								if (attack[i].name == "sprintATTACKBloodLust")
								{
									o->getComponents<Physique>()->setDamageEntity2v(true, 15 + BonusAttack);
									if (o->getComponents<Physique>()->m_typeMob != H)
									{
										parent->getComponents<Physique>()->setCoupTouched();
										o->getComponents<Shake>()->m_activeET = true;
									}
								}


								if (attack[i].name == "Jab1KimpahPlayer")
									o->getComponents<Physique>()->setDamageEntity2v(false, 0);
								if (attack[i].name == "Jab2KimpahPlayer")
									o->getComponents<Physique>()->setDamageEntity2v(false, 0);
								if (attack[i].name == "Jab3KimpahPlayer")
									o->getComponents<Physique>()->setDamageEntity2v(false, 0);
								if (attack[i].name == "Jab4KimpahPlayer")
									o->getComponents<Physique>()->setDamageEntity2v(true, 0);
								if (attack[i].name == "ATTACKJumpKimpahPlayer")
									o->getComponents<Physique>()->setDamageEntity2v(true, 0);
								if (attack[i].name == "chargeAttackKimpahPlayer")
									o->getComponents<Physique>()->setDamageEntity2v(true, 0);
								if (attack[i].name == "sprintATTACKKimpahPlayer")
									o->getComponents<Physique>()->setDamageEntity2v(true, 0);


								if (parent->getComponents<Physique>()->getComportement() != Grab && o->getComponents<Physique>()->getComportement() != Grabed)
								{
									if (parent->getComponents<ObjectTransform>()->getPosition().x > o->getComponents<ObjectTransform>()->getPosition().x)
									{
										o->getComponents<Physique>()->setLook(LookRight);
									}
									else
									{
										o->getComponents<Physique>()->setLook(LookLeft);
									}
								}
							}
						}
					}
				}

				for (auto& destruct : GameObject::l_Collectible)
				{
					if (auto testDestruct = destruct->getComponents<Destructible>())
					{
						auto rectBox = testDestruct->getRectDestruct();
						for (int i = 0; i < attack.size(); i++)
						{
							if (attack[i].rect.intersects(rectBox) && destruct->getComponents<ObjectTransform>()->getZBuffer() - 100 < parent->getComponents<ObjectTransform>()->getZBuffer() &&
								parent->getComponents<ObjectTransform>()->getZBuffer() + 100 > parent->getComponents<ObjectTransform>()->getZBuffer())
							{
								auto destructObj = destruct->getComponents<Destructible>();
								if (attack[i].name != "MoveBigBoyGrab" && attack[i].name != "SprintBigBoyGrab" && !destructObj->getIsHit() && !destructObj->getHasDestroyed())
								{
									if (destructObj->getPVDestructible() > 1)
									{
										if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
										{
											BigBoy->getComponents<Audio3D_Manager>()->getSound3D("destruction").play();
										}
										destructObj->setPVDestructible(destructObj->getPVDestructible() - 1);
										destructObj->setHit(true);
										destruct->getComponents<Shake>()->m_activeET = true;
									}
									else
									{
										if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
										{
											BigBoy->getComponents<Audio3D_Manager>()->getSound3D("breakdestructable").play();
										}
										destructObj->setDestroyed();

										if (parent->getComponents<RigidBody>()->getDirection().first == DirectionX::LEFT)
											destructObj->getParents().lock()->getComponents<RigidBody>()->setSpeed({ -500.f, -200.f });
										else
											destructObj->getParents().lock()->getComponents<RigidBody>()->setSpeed({ 500.f, -200.f });

										destructObj->m_yBoing = destruct->getComponents<ObjectTransform>()->getPosition().y;
										destruct->getParent()->addGameObject(Collectible::createCollectible(static_cast<TypeCollectible>(tools::iRand(1, 3)), { destruct->getComponents<ObjectTransform>()->getPosition().x + destruct->getComponents<Sprite>()->getSprite().getGlobalBounds().width / 2.0f, destruct->getComponents<ObjectTransform>()->getPosition().y + destruct->getComponents<Sprite>()->getSprite().getGlobalBounds().height - 100.0f }));
									}
								}
							}
						}
					}
					else if (auto testCollect = destruct->getComponents<Collectible>())
					{
						auto rectBox = testCollect->getRectCollectible();
						auto rectBoxPlayer = parent->getComponents<Collider>()->getRectBody();
						for (auto& r : rectBoxPlayer)
						{
							if (r.rect.intersects(rectBox) && testCollect->isActive())
							{
								testCollect->setIsLootable(true);
								if (auto input = parent->getComponents<Input>())
								{
									if (input->getType(gp::Gamepad::B) == PRESSED && parent->getComponents<ObjectTransform>()->getZBuffer() - 140 < destruct->getComponents<ObjectTransform>()->getZBuffer() &&
										parent->getComponents<ObjectTransform>()->getZBuffer() + 140 > destruct->getComponents<ObjectTransform>()->getZBuffer())
									{
										if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
										{
											BigBoy->getComponents<Audio3D_Manager>()->getSound3D("pickupitem").play();
										}
										if (testCollect->getTypeCollectible() == PUCE)
										{
											addfx(2);
											parent->getObjects("SCORE_ID")->getComponents<Score>()->justAddScore(0, 500);
										}
										else if (testCollect->getTypeCollectible() == SOIN)
										{
											addfx(2);
											if (parent->getComponents<Physique>()->getLife() > 60)
												parent->getComponents<Physique>()->setLife(100);
											else
												parent->getComponents<Physique>()->setLife(parent->getComponents<Physique>()->getLife() + 40);
										}
										else if (testCollect->getTypeCollectible() == ULTI)
										{
											addfx(2);
											if (parent->getComponents<Physique>()->ChargeUltimate > 60)
												parent->getComponents<Physique>()->ChargeUltimate = 100;
											else
												parent->getComponents<Physique>()->ChargeUltimate += 40;
										}

										testCollect->getParents().lock()->setActive(false);
										break;
									}
								}
							}
							else
								testCollect->setIsLootable(false);
						}
					}
					else if (auto testDestruct = destruct->getComponents<Package>()) {
						sf::IntRect rectBox = testDestruct->getRect();
						auto ColliderNoAttack = parent->getComponents<Collider>()->getRectBody();
						for (int i = 0; i < ColliderNoAttack.size(); i++) {
							if (ColliderNoAttack[i].rect.intersects(rectBox) && parent->getComponents<ObjectTransform>()->getZBuffer() - 140 < destruct->getComponents<ObjectTransform>()->getZBuffer() &&
								parent->getComponents<ObjectTransform>()->getZBuffer() + 140 > destruct->getComponents<ObjectTransform>()->getZBuffer()) {
								auto destructObj = destruct->getComponents<Package>();
								if (auto inputControler = parent->getComponents<Input>()) {
									if (inputControler->getType(gp::Gamepad::B) == PRESSED && !destructObj->getIs_PickedUp()) {
										if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
										{
											BigBoy->getComponents<Audio3D_Manager>()->getSound3D("pickuppackage").play();
										}
										if (destructObj->getType() == BLEU) {
											parent->getComponents<Physique>()->BoostVitesseAttack = true;
											destruct->setActive(false);
										}
										if (destructObj->getType() == JAUNE) {
											parent->getComponents<Physique>()->BoostImortalite = true;
											destruct->setActive(false);
										}
										if (destructObj->getType() == ROUGE) {
											addfx(1);
											parent->getComponents<Physique>()->ChargeUltimate = 100;
											destruct->setActive(false);
										}
										if (destructObj->getType() == VERT) {
											parent->getComponents<Physique>()->BoostScore = true;
											destruct->setActive(false);
										}
									}
								}
							}
						}
					}
				}
			}
			if (parent->getComponents<Identity>()->getType() == ENNEMY)
			{
				auto attack = parent->getComponents<Collider>()->getRectAttack();
				for (auto& o : GameObject::l_Player)
				{
					auto _o = o->getComponents<Collider>();
					for (int i = 0; i < attack.size(); i++)
					{
						for (auto j : _o->getRectBody())
						{
							if (attack[i].rect.intersects(j.rect) && !_o->getIsHit()) // rajouter le check Zbuffer
							{
								if (attack[i].rect.intersects(j.rect) && !o->getComponents<Physique>()->getInKnockDown()
									&& parent->getComponents<ObjectTransform>()->getZBuffer() - 70 < o->getComponents<ObjectTransform>()->getZBuffer() &&
									parent->getComponents<ObjectTransform>()->getZBuffer() + 60 > o->getComponents<ObjectTransform>()->getZBuffer())// rajouter le check Zbuffer
								{
									if (attack[i].name == "jabb") {
										o->getComponents<Physique>()->setDamageEntity2v(false, 8);
										//o->getComponents<Shake>()->m_activeET = true;
									}
									if (attack[i].name == "DOUBLEHIIT") {
										o->getComponents<Physique>()->setDamageEntity2v(false, 4);
										//o->getComponents<Shake>()->m_activeET = true;
									}
									if (attack[i].name == "DOUBLEHIIT2") {
										o->getComponents<Physique>()->setDamageEntity2v(true, 11);
										//o->getComponents<Shake>()->m_activeET = true;
									}
									if (attack[i].name == "GRAB") {
										o->getComponents<Physique>()->setDamageEntity2v(false, 14);
										//o->getComponents<Shake>()->m_activeET = true;
									}
									if (attack[i].name == "LONGHIT") {
										o->getComponents<Physique>()->setDamageEntity2v(true, 14);
										//o->getComponents<Shake>()->m_activeET = true;
									}
									if (attack[i].name == "UPPERCUT") {
										o->getComponents<Physique>()->setDamageEntity2v(true, 14);
										//o->getComponents<Shake>()->m_activeET = true;
									}
									if (attack[i].name == "JAB") {
										o->getComponents<Physique>()->setDamageEntity2v(false, 10);
										o->getComponents<Shake>()->m_activeET = true;
									}


									if (parent->getComponents<ObjectTransform>()->getPosition().x > o->getComponents<ObjectTransform>()->getPosition().x)
									{
										o->getComponents<Physique>()->setLook(LookRight);
									}
									else
									{
										o->getComponents<Physique>()->setLook(LookLeft);
									}
								}
							}
						}
					}
				}
			}
		}
		if (parent->getComponents<Identity>()->getType() == ENNEMY)
		{
			auto attack = parent->getComponents<Collider>()->getRectAttack();
			for (auto& o : GameObject::l_Player)
			{
				auto _o = o->getComponents<Collider>();
				for (int i = 0; i < attack.size(); i++)
				{
					for (auto j : _o->getRectBody())
					{
						if (attack[i].rect.intersects(j.rect) && !_o->getIsHit()) // rajouter le check Zbuffer
						{
							if (attack[i].name == "Jab1KimpahPlayer") {
								o->getComponents<Physique>()->setDamageEntity2v(false, 5);
								o->getComponents<Shake>()->m_activeET = true;
							}
							if (attack[i].name == "Jab2KimpahPlayer") {
								o->getComponents<Physique>()->setDamageEntity2v(false, 5);
								o->getComponents<Shake>()->m_activeET = true;
							}
							if (attack[i].name == "Jab3KimpahPlayer") {
								o->getComponents<Physique>()->setDamageEntity2v(false, 5);
								o->getComponents<Shake>()->m_activeET = true;
							}
							if (attack[i].name == "Jab4KimpahPlayer") {
								o->getComponents<Physique>()->setDamageEntity2v(false, 5);
								o->getComponents<Shake>()->m_activeET = true;
							}

							/*	if (attack[i].name == "jabb")
									o->getComponents<Physique>()->setDamageEntity2v(false, 10);
								if (attack[i].name == "DOUBLEHIIT")
									o->getComponents<Physique>()->setDamageEntity2v(false, 10);
								if (attack[i].name == "DOUBLEHIIT2")
									o->getComponents<Physique>()->setDamageEntity2v(true, 10);
								if (attack[i].name == "GRAB")
									o->getComponents<Physique>()->setDamageEntity2v(false, 0);
								if (attack[i].name == "LONGHIT")
									o->getComponents<Physique>()->setDamageEntity2v(true, 0);
								if (attack[i].name == "UPPERCUT")
									o->getComponents<Physique>()->setDamageEntity2v(true, 0);
								if (attack[i].name == "JAB ")
									o->getComponents<Physique>()->setDamageEntity2v(false, 0);*/
						}
					}
				}
				/*if (parent->getComponents<Collider>()->checkSelfColisionBox(o->getComponents<Collider>()->getRect())) {
					if (o->getComponents<ObjectTransform>()->getZBuffer() >= parent->getComponents<ObjectTransform>()->getZBuffer() - 70.0f
						&& o->getComponents<ObjectTransform>()->getZBuffer() <= parent->getComponents<ObjectTransform>()->getZBuffer() + 70.0f)
						parent->getComponents<Collider>()->isHit();
				}*/
			}
		}
	}

}
//checkCollisionMask();


void CheckCollision::draw()
{
	/*if (attack[i].name == "Jab1BigBoy")
	{
		parent->getComponents<Physique>()->setDamageEntity(true, false, 10);
	}*/

	//window.draw(m_spriteMask);
}

void CheckCollision::check()
{
}

void CheckCollision::addfx(int type)
{
	if (type == 1) {
		timerParticules += tools::GetTimeDelta();
		if (auto Parent = getParents().lock())
		{
			auto position = Parent->getParent()->getObjects(PLAYER)->getComponents<ObjectTransform>()->getPosition();
			//auto position = Parent->getComponents<ObjectTransform>()->getPosition();
			auto boost = Parent->getParent()->getObjects("BoostEffect");

			for (int i = 0; i < 15; i++)
			{
				boost->getComponents<Particules>()->addParticules(sf::Vector2f(position.x + tools::frand(-111.f, 111.f),
					position.y - tools::frand(200.f, 465.f)),//Position
					"rouge.png",
					HAUT,//Direction
					255,//opacite
					350 + tools::frand(80, 100),//speed
					300);//EraseSpeed
			}
		}
	}
	if (type == 2) {
		timerParticules += tools::GetTimeDelta();
		if (auto Parent = getParents().lock())
		{
			auto position = Parent->getParent()->getObjects(PLAYER)->getComponents<ObjectTransform>()->getPosition();
			//auto position = Parent->getComponents<ObjectTransform>()->getPosition();
			auto boost = Parent->getParent()->getObjects("BoostEffect");
			for (int i = 0; i < 8; i++)
			{

				boost->getComponents<Particules>()->addParticules(sf::Vector2f(position.x + tools::frand(-111.f, 111.f),
					position.y - tools::frand(0.f, 100.f)),//Position
					"pixel.png",
					HAUT,//Direction
					255,//opacite
					150 + tools::frand(80, 100),//speed
					230);//EraseSpeed
			}
		}
	}
}

