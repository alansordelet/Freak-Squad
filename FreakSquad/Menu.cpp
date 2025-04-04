#include "Menu.h"
#include "Game.h"
#include "Selection.h"
#include "MainMenu.h"
#include "MenuFactory.h"
#include "Selection.h"
#include "Ui.h"
#include "Sounds3D.h"
#include "Transition.h"

Menu::Menu()
{
	timer = 0.f;
}

Menu::~Menu()
{
}

void Menu::init()
{
	m_isReady = true; // Pret a faire l'update
	m_firstPass = true; // Ne fait plus de cinematique

	m_object = std::shared_ptr<GameObject>(new GameObject);
	std::shared_ptr<Identity> id = std::shared_ptr<Identity>(new Identity("Menu", ROOT));
	std::shared_ptr<Ui> ui = std::shared_ptr<Ui>(new Ui());

	std::shared_ptr<GameObject> soundObject = std::shared_ptr<GameObject>(new GameObject);
	std::shared_ptr<Identity> idsoundObject = std::shared_ptr<Identity>(new Identity("sounds", OBJECT));
	std::shared_ptr<Audio3D_Manager> soundPlayer = std::shared_ptr<Audio3D_Manager>(new Audio3D_Manager());

	soundPlayer->addSceneSound("menuswitch", "menu_switch2.wav", 75);
	soundPlayer->addSceneSound("menuselect", "menu_select.wav", 75);
	soundPlayer->addSceneSound("characterselect", "character_selected.wav", 75);
	soundPlayer->addSceneSound("characterswitch", "switch_character.wav", 75);
	soundPlayer->addSceneSound("cancel", "cancel.wav", 75);
	soundPlayer->addSceneSound("startgame", "start_game.wav", 75);
	soundPlayer->addSceneSound("back", "back.wav", 75);
	soundPlayer->addSceneMusic("menumusic", "Magasin_Jouet_44Hz_16bits.wav", 75);
	soundPlayer->addSceneMusic("CreditMusic", "NightOfRage_Single_44Hz_16bit.wav", 75);
	soundPlayer->setLoop(true, "music", "menumusic");
	soundPlayer->setAllMusicVolume(75);
	soundPlayer->setAllGlobalVolume(75);
	soundObject->addComponents<Identity>(idsoundObject);
	soundObject->addComponents<Audio3D_Manager>(soundPlayer);

	std::shared_ptr<GameObject> inputJ1Obj = std::shared_ptr<GameObject>(new GameObject);
	std::shared_ptr<Identity> idInputJ1 = std::shared_ptr<Identity>(new Identity("INPUT_J1", OBJECT));
	std::shared_ptr<Input> inputJ1Comp = std::shared_ptr<Input>(new Input());
	inputJ1Obj->addComponents<Identity>(idInputJ1);
	inputJ1Obj->addComponents<Input>(inputJ1Comp);

	std::shared_ptr<GameObject> inputJ2Obj = std::shared_ptr<GameObject>(new GameObject);
	std::shared_ptr<Identity> idInputJ2 = std::shared_ptr<Identity>(new Identity("INPUT_J2", OBJECT));
	std::shared_ptr<Input> inputJ2Comp = std::shared_ptr<Input>(new Input());
	inputJ2Obj->addComponents<Identity>(idInputJ2);
	inputJ2Obj->addComponents<Input>(inputJ2Comp);

	m_object->addComponents<Identity>(id);
	m_object->addComponents<Ui>(ui);
	m_objectMainMenu = MenuFactory::factory(MAIN_MENU_FACTO);
	m_object->addGameObject(m_objectMainMenu);
	m_object->addGameObject(MenuFactory::factory(SELECTION_MENU_FACTO));
	m_object->addGameObject(MenuFactory::factory(OPTION_MENU_FACTO));
	m_object->addGameObject(MenuFactory::factory(START_MENU_FACTO));
	m_object->addGameObject(inputJ1Obj);
	m_object->addGameObject(inputJ2Obj);
	m_object->addGameObject(soundObject);

	m_objectTransition = std::shared_ptr<GameObject>(new GameObject);
	std::shared_ptr<Identity> idRootTransition = std::shared_ptr<Identity>(new Identity("RootTransition", ROOT));
	std::shared_ptr<Transition> compoTransition = std::shared_ptr<Transition>(new Transition);
	//std::shared_ptr<Input>InputTransition = std::shared_ptr<Input>(new Input);
	m_objectTransition->addComponents<Identity>(idRootTransition);
	m_objectTransition->addComponents<Transition>(compoTransition);
	m_objectTransition->addComponents<Input>(inputJ1Comp);

	//m_object->addGameObject(m_objectTransition);
}

void Menu::update()
{
	m_object->updateAllObject();


	auto tmp_selectionObj = m_object->getObjects("SELECTION_MENU");
	auto tmp_selectionComp = tmp_selectionObj->getComponents<Selection>();
	if (tmp_selectionComp->getTransitToGame())
	{
		auto tmp_ui = tmp_selectionObj->getComponents<Ui>();
		auto tmp_inputJ1 = tmp_selectionComp->getInputJ1();
		auto tmp_inputJ2 = tmp_selectionComp->getInputJ2();
		auto volumMusic = m_object->getObjects("sounds")->getComponents<Audio3D_Manager>()->getVolumeMusic();
		auto volumSound = m_object->getObjects("sounds")->getComponents<Audio3D_Manager>()->getVolumeSound();
		m_object->deleteAllObjects();
		
		GameObject::l_Player.clear();
		GameObject::l_Ennemy.clear();
		GameObject::l_Object.clear();
		GameObject::l_Ui.clear();
		GameObject::l_Collectible.clear();

		if (tmp_ui->getPlayerNumber() == 1)
			this->p_SceneManager->transitionTo(new Game(tmp_ui, tmp_inputJ1, nullptr, volumMusic, volumSound));
		else if (tmp_ui->getPlayerNumber() == 2)
			this->p_SceneManager->transitionTo(new Game(tmp_ui, tmp_inputJ1, tmp_inputJ2, volumMusic, volumSound));


		return;
	}

	if (m_object->getObjects("MAIN_MENU")->isActive())
	{
		m_object->getObjects("MAIN_MENU")->getObjects("BLOOD_LEFT")->updateAllComponents();
		m_object->getObjects("MAIN_MENU")->getObjects("BLOOD_RIGHT")->updateAllComponents();
		m_object->getObjects("MAIN_MENU")->getObjects("FIRE_FIST")->updateAllComponents();
		m_object->getObjects("MAIN_MENU")->getObjects("BLOODLUST_FIST")->updateAllComponents();
	}

	if (auto mainMenuComp = m_objectMainMenu->getComponents<MainMenu>())
	{
		if (mainMenuComp->getStartCredits())
		{
			m_objectMainMenu->setActive(false);
			m_object->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("menumusic").stop();
			if (m_object->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("CreditMusic").getStatus() == sf::Sound::Stopped)
				m_object->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("CreditMusic").play();

			m_objectTransition->getComponents<Transition>()->setStartCredit(true);
			m_objectTransition->getComponents<Transition>()->update();
			if (m_objectTransition->getComponents<Transition>()->getRetourMenu())
			{
				m_objectMainMenu->setActive(true);
				mainMenuComp->setStartCredits(false);
				m_objectTransition->getComponents<Transition>()->setStartCredit(false);
				if(m_object->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("menumusic").getStatus()==sf::Sound::Stopped)
				m_object->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("menumusic").play();
				m_object->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("CreditMusic").stop();
				m_objectTransition->getComponents<Transition>()->setPosition(window.getSize().y);
				m_objectTransition->getComponents<Transition>()->setTransitionMenu(false);
			}
		}
	}
}

void Menu::display()
{
	m_object->drawAllObject();
	if (auto mainMenu = m_object->getObjects("MAIN_MENU"))
	{
		auto isActive = mainMenu->isActive();
		if (isActive)
		{
			m_object->getObjects("MAIN_MENU")->getComponents<MainMenu>()->drawUpside();

		}
		if (auto mainMenuComp = m_objectMainMenu->getComponents<MainMenu>())
		{
			if (mainMenuComp->getStartCredits())
			{
				m_objectTransition->getComponents<Transition>()->draw();
			}
		}
	}
}

void Menu::deInit()
{
	m_isReady = false;
	m_isLoading = false;
	m_object.reset();
}
