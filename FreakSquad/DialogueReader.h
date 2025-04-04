#pragma once
#include "CoffeeCore.hpp"
#include <fstream>
#define DIALOGUE_PATH "../Ressources/Game/DIALOGUE/"

struct BackgroundIntroEnding
{
	sf::Sprite sprite;
	sf::Vector2f position;
	float speed;
};

class DialogueReader : public GameComponent
{
private:
	BackgroundIntroEnding background;
	std::ifstream dialogueFile;
	std::vector<sf::Text> m_text;
	std::shared_ptr<GameObject> sptr_dialogue;
	
	bool m_isReading; /// indicateur de lecture
	bool m_intro;
	bool m_ending;
	float m_timerDialogue;
public:
	DialogueReader();
	DialogueReader(const std::string& _filename);
	~DialogueReader();
	void initRead(std::shared_ptr<GameObject> _object);
	void resetReading();
	void read(const std::string& _start, int _line, const sf::Vector2f& _position, sf::RenderWindow& _window);
	void setEnding(bool _start);
	void updateDialogueIntro();
	void updateDialogueEnding();
	void updateIntro();
	void updateEnding();
	void update();
	bool getEndIntro();
	bool getEnding();
	std::shared_ptr<GameObject> getObject();
	void draw();
	void display();
};
