#include "Sounds3D.h"

Audio3D_Manager::~Audio3D_Manager()
{
}

void Audio3D_Manager::update()
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
	{
		if (auto objectTransform = it->first.get()->p_ObjectTransform.lock())
		{
			(it)->first.get()->sound3D.setPosition(sf::Vector3f(objectTransform->getPosition().x, objectTransform->getPosition().y, 0));
		}
	}
}

void Audio3D_Manager::draw()
{

}

void Audio3D_Manager::setListenerPosition(sf::Vector3f pos)
{
	sf::Listener::setPosition(pos);
}

void Audio3D_Manager::setListenerDirection(sf::Vector3f dir)
{
	sf::Listener::setDirection(dir);
}

void Audio3D_Manager::setListenerVolume(float _volume)
{
	sf::Listener::setGlobalVolume(_volume);
}

void Audio3D_Manager::setAttenuation(const std::string& name, float _attenuation)
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
	{
		if ((*it).second == name)
			(*it).first.get()->sound3D.setAttenuation(_attenuation);
		else
			std::cout << "\n\n3Dsound :" << name << " NOT FOUND!\n\n";
	}
}

void Audio3D_Manager::setLoop(bool _loop, const std::string& category, const std::string& name)
{
	if (category == "sound")
	{
		for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
		{
			if ((*it).second == name)
				(*it).first.get()->sound3D.setLoop(_loop);
			else
				std::cout << "\n\n3Dsound :" << name << " NOT FOUND!\n\n";
		}
	}
	else if (category == "music")
	{
		for (VectorMusics::iterator it = vector_music.begin(); it != vector_music.end(); ++it)
		{
			if ((*it).second == name)
				(*it).first.get()->music.setLoop(_loop);
			else
				std::cout << "\n\music :" << name << " NOT FOUND!\n\n";
		}
	}
	else
	{
		std::cout << "***********Music/Sound not found! or wrong category**********" << std::endl;
	}
}

void Audio3D_Manager::setMinimumDistance(const std::string& name, float _Distance)
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
	{
		if ((*it).second == name)
			(*it).first.get()->sound3D.setMinDistance(_Distance);
		else
			std::cout << "\n\n3Dsound :" << name << " NOT FOUND!\n\n";
	}
}

void Audio3D_Manager::setGlobalVolume(const std::string& name, float _volume)
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
	{
		if ((*it).second == name)
			(*it).first.get()->sound3D.setVolume(_volume);
	}
}

void Audio3D_Manager::setSoundPosition(const std::string& name, sf::Vector3f _posSound)
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
	{
		if ((*it).second == name)
			(*it).first.get()->sound3D.setPosition(_posSound);
		else
			std::cout << "\n\n3Dsound :" << name << " NOT FOUND!\n\n";
	}
}

void Audio3D_Manager::addSceneSound(std::string _soundName, std::string _ressourceName, float _volume)
{
	vector_sounds3D.emplace_back(std::make_unique<Sound3D>(_ressourceName, _volume), _soundName);
}

sf::Sound& Audio3D_Manager::getSound3D(const std::string& name)
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
	{
		if ((it)->second == name)
			return (it)->first.get()->sound3D;
		//else
			////std::cout << "\n\n3Dsound :" << name << " NOT FOUND!\n\n";
	}

}

void Audio3D_Manager::addSceneMusic(std::string _soundName, std::string _ressourceName, float _volume)
{
	vector_music.emplace_back(std::make_unique<Musics>(_ressourceName, _volume), _soundName);
}

sf::Sound& Audio3D_Manager::getMusic(const std::string& name)
{
	for (VectorMusics::iterator it = vector_music.begin(); it != vector_music.end(); ++it)
	{
		if ((it)->second == name)
			return (it)->first.get()->music;
		//else
			////std::cout << "\n\nmusic :" << name << " NOT FOUND!\n\n";
	}

}

float Audio3D_Manager::getVolumeSound()
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
		return (*it).first.get()->volume;

}

float Audio3D_Manager::getVolumeMusic()
{
	for (VectorMusics::iterator it = vector_music.begin(); it != vector_music.end(); ++it)
		return (*it).first.get()->volume;

}

void Audio3D_Manager::setAllGlobalVolume(float _volume)
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
	{
		(*it).first.get()->volume = _volume;
		(*it).first.get()->sound3D.setVolume((*it).first.get()->volume);
	}
}

void Audio3D_Manager::setAllMusicVolume(float _volume)
{
	for (VectorMusics::iterator it = vector_music.begin(); it != vector_music.end(); ++it)
	{
		(*it).first.get()->volume = _volume;
		(*it).first.get()->music.setVolume((*it).first.get()->volume);
	}
}

void Audio3D_Manager::graduallyStopMusic(const std::string& name, float fadeDuration)
{
	const float fadeStep = 1.0f / fadeDuration;

	for (VectorMusics::iterator it = vector_music.begin(); it != vector_music.end(); ++it)
	{
		if ((it)->second == name)
		{
			while ((*it).first.get()->volume > 0.0f)
			{
				(*it).first.get()->volume -= fadeStep;
				if ((*it).first.get()->volume < 0.0f)
					(*it).first.get()->volume = 0.0f;

				(*it).first.get()->music.setVolume((*it).first.get()->volume);
				sf::sleep(sf::milliseconds(10));
			}
			(*it).first.get()->music.stop();
		}
		else
			std::cout << "\n\nmusic :" << name << " NOT FOUND!\n\n";
	}
}

void Audio3D_Manager::graduallyStartMusic(const std::string& name, float fadeDuration)
{
	const float fadeStep = 1.f / fadeDuration;

	for (VectorMusics::iterator it = vector_music.begin(); it != vector_music.end(); ++it)
	{
		if ((*it).second == name)
		{
			if ((*it).first.get()->music.getStatus() != sf::Music::Playing)
			{
				(*it).first.get()->music.play();

				while ((*it).first.get()->volume < 100.0f)
				{
					(*it).first.get()->volume += fadeStep;
					if ((*it).first.get()->volume > 100.f)
						(*it).first.get()->volume = 100.f;

					(*it).first.get()->music.setVolume((*it).first.get()->volume);

					sf::sleep(sf::milliseconds(10));
				}

				(*it).first.get()->volume = 100.f;
				(*it).first.get()->music.setVolume((*it).first.get()->volume);
			}
		}
		else
		{
			std::cout << "\n\nmusic :" << name << " NOT FOUND!\n\n";
		}
	}
}

Sound3D::Sound3D(std::string _ressourceName, float _volume)
{
	sound3D.setBuffer(RessourceManager::get()->getGlobalSoundBuffer(_ressourceName));
	//volume = _volume;
	sound3D.setVolume(_volume);
}

Musics::Musics(std::string _ressourceName, float _volume)
{
	music.setBuffer(RessourceManager::get()->getGlobalSoundBuffer(_ressourceName));
	//volume = _volume;
	music.setVolume(_volume);
}

void Audio3D_Manager::setSoundToObjectPosition(std::string _soundName, std::shared_ptr<ObjectTransform> _objectTransform)
{
	for (VectorSound3D::iterator it = vector_sounds3D.begin(); it != vector_sounds3D.end(); ++it)
	{
		(it)->first.get()->p_ObjectTransform = _objectTransform;
	}
}