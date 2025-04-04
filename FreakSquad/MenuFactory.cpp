#include "MenuFactory.h"
#include "MainMenu.h"
#include "Selection.h"
#include "Ui.h"
#include "MenuSettings.h"
#include "MenuStart.h"

MenuFactory::MenuFactory()
{
}

MenuFactory::~MenuFactory()
{
}

std::shared_ptr<GameObject> MenuFactory::factory(e_MENUTYPE_FACTORY _type)
{
	switch (_type)
	{
	case MAIN_MENU_FACTO:
		return createMainMenu();
		break;
	case SELECTION_MENU_FACTO:
		return createSelectionMenu();		
	case OPTION_MENU_FACTO:
		return createSettingsMenu();
		break;		
	case START_MENU_FACTO:
		return createStartMenu();
		break;
	}
	return nullptr;
}

std::shared_ptr<GameObject> MenuFactory::createMainMenu()
{
	std::shared_ptr<GameObject> menu = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<MainMenu> core = std::shared_ptr<MainMenu>(new MainMenu());
	std::shared_ptr<Identity> identityMenu = std::shared_ptr<Identity>(new Identity("MAIN_MENU", UI));
	

	menu->addComponents<Identity>(identityMenu);
	//menu->addComponents<Input>(InputMenu);
	menu->addComponents<MainMenu>(core);

	//bloodLeft
	std::shared_ptr<GameObject> bloodLeft = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> identityBloodLeft = std::shared_ptr<Identity>(new Identity("BLOOD_LEFT", UI));
	std::shared_ptr<ObjectTransform> transformBloodLeft = std::shared_ptr<ObjectTransform>(new ObjectTransform({0, 1080.0f}, STATIC));
	std::shared_ptr<Sprite> spriteBloodLeft = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animationBloodLeft = std::shared_ptr<Animation>(new Animation());
	
	
	animationBloodLeft->addAnimation("bloodLeft", "menu_gauche_f14.png", 14, 0.08f, true);
	
	bloodLeft->addComponents<Identity>(identityBloodLeft);
	bloodLeft->addComponents<ObjectTransform>(transformBloodLeft);
	bloodLeft->addComponents<Sprite>(spriteBloodLeft);
	bloodLeft->addComponents<Animation>(animationBloodLeft);

	animationBloodLeft->playAnim("bloodLeft", true);


	//bloodRight
	std::shared_ptr<GameObject> bloodRight = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> identityBloodRight = std::shared_ptr<Identity>(new Identity("BLOOD_RIGHT", UI));
	std::shared_ptr<ObjectTransform> transformBloodRight = std::shared_ptr<ObjectTransform>(new ObjectTransform({1920.f, 1080.f }, STATIC));
	std::shared_ptr<Sprite> spriteBloodRight = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animationBloodRight = std::shared_ptr<Animation>(new Animation());

	animationBloodRight->addAnimation("bloodRight", "menu_droite_f14.png", 14, 0.08f, true);
	
	bloodRight->addComponents<Identity>(identityBloodRight);
	bloodRight->addComponents<ObjectTransform>(transformBloodRight);
	bloodRight->addComponents<Sprite>(spriteBloodRight);
	bloodRight->addComponents<Animation>(animationBloodRight);

	animationBloodRight->playAnim("bloodRight", true);


	//FireFist
	std::shared_ptr<GameObject> fireFist = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> identityFireFist = std::shared_ptr<Identity>(new Identity("FIRE_FIST", UI));
	std::shared_ptr<ObjectTransform> transformFireFist = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 550.f,715.f }, STATIC));//ce que kevin a mis à ajuster
	std::shared_ptr<Sprite> spriteFireFist = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animationFireFist = std::shared_ptr<Animation>(new Animation());

	animationFireFist->addAnimation("fireFist", "bigboy_f7.png", 7, 0.08f, true);

	fireFist->addComponents<Identity>(identityFireFist);
	fireFist->addComponents<ObjectTransform>(transformFireFist);
	fireFist->addComponents<Sprite>(spriteFireFist);
	fireFist->addComponents<Animation>(animationFireFist);
	animationFireFist->playAnim("fireFist", true);

	//bloodLustPunch
	std::shared_ptr<GameObject> bloodLustFist = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> identityBloodLustFist = std::shared_ptr<Identity>(new Identity("BLOODLUST_FIST", UI));
	std::shared_ptr<ObjectTransform> transformBloodLustFist = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 1353.f,715.f }, STATIC));//ce que kevin a mis à ajuster
	std::shared_ptr<Sprite> spriteBloodLustFist = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<Animation> animationBloodLustFist = std::shared_ptr<Animation>(new Animation());

	animationBloodLustFist->addAnimation("bloodLust", "bloodlust_f7.png", 7, 0.08f, true);

	bloodLustFist->addComponents<Identity>(identityBloodLustFist);
	bloodLustFist->addComponents<ObjectTransform>(transformBloodLustFist);
	bloodLustFist->addComponents<Sprite>(spriteBloodLustFist);
	bloodLustFist->addComponents<Animation>(animationBloodLustFist);
	animationBloodLustFist->playAnim("bloodLust", true);

	//ajout des components et des GameObject à l'objet parent

	menu->addGameObject(bloodLeft);
	menu->addGameObject(bloodRight);
	menu->addGameObject(fireFist);
	menu->addGameObject(bloodLustFist);
	
	return menu;
}

std::shared_ptr<GameObject> MenuFactory::createSelectionMenu()
{
	std::shared_ptr<GameObject> menu = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> identityMenu = std::shared_ptr<Identity>(new Identity("SELECTION_MENU", UI));
	std::shared_ptr<Selection> core = std::shared_ptr<Selection>(new Selection());
	std::shared_ptr<Ui> ui = std::shared_ptr<Ui>(new Ui());

	menu->addComponents<Identity>(identityMenu);
	menu->addComponents<Selection>(core);
	menu->addComponents<Ui>(ui);

	return menu;
}

std::shared_ptr<GameObject> MenuFactory::createSettingsMenu()
{
	std::shared_ptr<GameObject> menu = std::shared_ptr<GameObject>(new GameObject(false));
	std::shared_ptr<Identity> identityMenu = std::shared_ptr<Identity>(new Identity("OPTION_MENU", UI));
	std::shared_ptr<MenuSettings> core = std::shared_ptr<MenuSettings>(new MenuSettings());
	std::shared_ptr<Ui> ui = std::shared_ptr<Ui>(new Ui());

	menu->addComponents<Identity>(identityMenu);
	menu->addComponents<MenuSettings>(core);
	menu->addComponents<Ui>(ui);

	return menu;
}

std::shared_ptr<GameObject> MenuFactory::createStartMenu()
{
	std::shared_ptr<GameObject> menu = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> identityMenu = std::shared_ptr<Identity>(new Identity("START_MENU", UI));
	std::shared_ptr<MenuStart> core = std::shared_ptr<MenuStart>(new MenuStart());
	std::shared_ptr<Ui> ui = std::shared_ptr<Ui>(new Ui());
	std::shared_ptr<ObjectTransform> transform = std::shared_ptr<ObjectTransform>(new ObjectTransform({0,0}));

	menu->addComponents<Identity>(identityMenu);
	menu->addComponents<MenuStart>(core);
	menu->addComponents<Ui>(ui);
	menu->addComponents<ObjectTransform>(transform);

	return menu;
}
