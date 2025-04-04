#include "DialogueReader.h"
#include"Sounds3D.h"
DialogueReader::DialogueReader()
{

}

DialogueReader::DialogueReader(const std::string& _filename)
{
	dialogueFile.open(_filename);
	m_isReading = false;
	m_intro = true;
	m_ending = false;
	m_timerDialogue = 0.0f;
}

DialogueReader::~DialogueReader()
{
}

void DialogueReader::initRead(std::shared_ptr<GameObject> _object)
{
	sptr_dialogue = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> id_dialogue = std::shared_ptr<Identity>(new Identity("Dialogue", OBJECT));
	std::shared_ptr<Input> sptr_inputDialogue = std::shared_ptr<Input>(new Input());

	std::shared_ptr<DialogueReader> background_parallax = std::shared_ptr<DialogueReader>(new DialogueReader(DIALOGUE_PATH"IntroEnding.txt"));
	sptr_dialogue->addComponents<Identity>(id_dialogue);
	sptr_dialogue->addComponents<DialogueReader>(background_parallax);
	sptr_dialogue->addComponents<Input>(sptr_inputDialogue);
	_object->addGameObject(sptr_dialogue);
}


void DialogueReader::resetReading()
{
	m_isReading = false;
	m_text.clear();
}

void DialogueReader::read(const std::string& _start, int _line, const sf::Vector2f& _position, sf::RenderWindow& _window)
{
	if (m_isReading)
		return;

	std::string line;
	bool found = false;
	int currentLine = 0;
	std::string dialogue;
	bool isDialogueFound = false;

	while (std::getline(dialogueFile, line))
	{
		currentLine++;
		if (line.find(_start) != std::string::npos) // Recherche du mot indiqu� comme startert dans la ligne
		{
			if (currentLine == _line)
			{
				found = true;
				dialogue += line.substr(line.find(_start) + _start.length());
				isDialogueFound = true;
			}
			else if (isDialogueFound)
			{
				break;
			}
		}
		else if (isDialogueFound)
		{
			dialogue += line;
		}
	}

	if (found)
	{
		// Ajout d'un saut de ligne ('\n') si un point-virgule est d�tect�
		std::size_t upLine = dialogue.find(';');
		while (upLine != std::string::npos)
		{
			dialogue.insert(upLine + 1, "\n");
			dialogue.erase(upLine, 1);
			upLine = dialogue.find(';', upLine + 1);
		}
		std::size_t end = dialogue.find('*');
		if (end != std::string::npos)
		{
			dialogue = dialogue.substr(0, end);
		}
		sf::Text text;
		text.setFont(RessourceManager::get()->getFont("steelfishNormal.otf"));
		text.setPosition(_position);
		m_text.push_back(text);


		for (std::size_t i = 0; i < dialogue.size(); i++)
		{
			m_text.back().setString(dialogue.substr(0, i + 1));

			_window.clear();
			display();
			_window.display();

			sf::sleep(sf::milliseconds(2)); // Delai entre chaque lettre
		}
		m_isReading = true;
	}
	else
	{
		std::cerr << "dialogue no found" << std::endl;
	}

	// Remettre le curseur du fichier au d�but pour les appels ult�rieurs
	dialogueFile.clear(); // Effacer les �ventuels indicateurs d'erreur
	dialogueFile.seekg(0, std::ios::beg); // D�placer le curseur au d�but du fichier
}

void DialogueReader::setEnding(bool _start)
{
	m_ending = _start;
}

void DialogueReader::updateDialogueIntro()
{
	for (auto Parent : GameObject::l_Player)
	{
		auto input = Parent->getComponents<Input>();
		input->update();
		m_timerDialogue += tools::GetTimeDelta();
		if (m_intro)
		{
			if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
			{
				BigBoy->getComponents<Audio3D_Manager>()->getSound3D("text").play();
			}
			read("Intro : ", 1, { 270,200 }, window.getWindow());
		}
			

		if (input->getType(gp::Gamepad::A) == PRESSED && m_timerDialogue > 0.2f)
		{
			m_intro = false;
			resetReading(); // Reinitialiser la lecture du dialogue
			m_timerDialogue = 0.0f;
		}
	}
}

void DialogueReader::updateDialogueEnding()
{
	sf::View tmpview = window.getWindow().getView();
	window.getWindow().setView(window.getWindow().getDefaultView());
	for (auto Parent : GameObject::l_Player)
	{
		auto input = Parent->getComponents<Input>();
		input->update();
		m_timerDialogue += tools::GetTimeDelta();
		
		if (m_ending)
		{
			if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
			{
				BigBoy->getComponents<Audio3D_Manager>()->getSound3D("text").play();
			}
			read("Ending : ", 13, { 350,200 }, window.getWindow());
		}
			

		if (input->getType(gp::Gamepad::A) == PRESSED && m_timerDialogue > 0.2f)
		{
			m_ending = false;
			resetReading(); // Reinitialiser la lecture du dialogue
			m_timerDialogue = 0.0f;
		}
	}
	window.getWindow().setView(tmpview);
}

void DialogueReader::updateIntro()
{
	if (auto parent = getParents().lock()) {
		if (auto InputComp = parent->getComponents<DialogueReader>())
		{
			InputComp->updateDialogueIntro();
		}
	}
}

void DialogueReader::updateEnding()
{
	if (auto parent = getParents().lock()) {
		if (auto InputComp = parent->getComponents<DialogueReader>())
		{
			InputComp->updateDialogueEnding();
		}
	}
}


void DialogueReader::update()
{
	
}


bool DialogueReader::getEndIntro()
{
	return m_intro;
}

bool DialogueReader::getEnding()
{
	return m_ending;
}



std::shared_ptr<GameObject> DialogueReader::getObject()
{
	return sptr_dialogue;
}

void DialogueReader::draw()
{
}

void DialogueReader::display()
{
	sf::View tmpview = window.getWindow().getView();
	window.getWindow().setView(window.getWindow().getDefaultView());
	for (const auto& text : m_text)
	{
		window.draw(text);
	}
	window.getWindow().setView(tmpview);
}

