#include "CoffeeCore.hpp"

enum e_WHAT_IS_SELECTED
{
	STORY,
	/*STATS,
	ACHIEVEMENTS,*/
	OPTIONS,
	CREDITS,
	//MEDIA,
	EXIT,
	GA
};

class MainMenu : public GameComponent
{
private:
	//position constante	
	//position en % d'ecran
	const sf::Vector2f posBloodLeftPlaced{ 0.5f,1.f };
	const sf::Vector2f posBloodLeftOut{ 0.f,1.f };
	const sf::Vector2f posBloodRightPlaced{ 0.5f,1.f };
	const sf::Vector2f posBloodRightOut{ 1.f,1.f };

	//pos des splash art
	//coordonnee de kevin a ajuster
	const sf::Vector2f posFireFistPlaced{ 0.29f,0.37f };
	const sf::Vector2f posBloodLustFistPlaced{0.7f,0.37};

	//pos des textes
	//coordonnee de kevin a ajuster
	const sf::Vector2f posStory{0.05f,0.18f};
	const sf::Vector2f posStats{0.05f,0.25f};
	const sf::Vector2f posAchievement{0.05f,0.32f};
	const sf::Vector2f posOptions{0.05f,0.50f};
	const sf::Vector2f posCredits{0.05f,0.55f};
	const sf::Vector2f posMedia{0.05f,0.60f};
	const sf::Vector2f posExit{0.05f,0.65f};
	const sf::Vector2f posGA{ 0.95f,0.88f };//l'origine de ce sprite est au centre

	//character Size premiere partie
	const float characterSizeFirstPart = 70.f;

	//character Size deuxieme partie
	const float characterSizeSecPart = 35.f;

	//string des text de l'ui
	const std::string stringStory = "STORY";
	const std::string stringStats = "STATS";
	const std::string stringAchievement = "ACHIEVEMENTS";//success sur les trucs des graphs a voir ce qui est le mieux
	const std::string stringOptions = "OPTIONS";//Options sur les trucs des graphs a voir ce qui est le mieux
	const std::string stringCredits = "CREDITS";
	const std::string stringMedia = "MEDIA";
	const std::string stringExit = "EXIT";


	//position des elements à deplacer
	sf::Vector2f m_posBloodLeft;
	sf::Vector2f m_posBloodRight;
	sf::Vector2f m_posKimpah;

	const float bloodSpeed = 500.f;

	bool m_isBloodLeftPlaced;
	bool m_isBloodRightPlaced;
	bool m_startCredits;
	
	//le curseur
	e_WHAT_IS_SELECTED m_cursorSelect;
	sf::Vector2f m_posCursor;//20,30 coordonnee de kevin à ajuster

	

	
	void updateBloodLeft();
	void updateBloodRight();
	void updateCursor();
	void changeMenu();

	void drawBackGround();
	void drawCharacters();
	
	void drawTextFirstPart();
	void drawTextSecondePart();
	
	//ce qui doit se draw par dessus tout
	void drawText();
	void drawCursor();
	void drawLock();
	void drawLogoGa();
	
	float m_keyTimer;
	//ajouter le select avec le logo du bouton A a cote + le logo GA en bas a droite qui renvoie vers le site de GA
	//plusieurs niveau de gras à checker si faisable

public:
	MainMenu();
	~MainMenu();

	void update();
	void draw();


	void drawUpside();//a mettre dans la scene menu pou afficher par dessus les anims de sang
	bool getStartCredits();
	void setStartCredits(bool _start);
};
