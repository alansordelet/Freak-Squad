#pragma once
#include"CoffeeCore.hpp"


struct Sound3D
{
	Sound3D(std::string _ressourceName, float _volume);
	std::weak_ptr<ObjectTransform> p_ObjectTransform;
	sf::Sound sound3D;
	std::string name;
	float volume = 100;
};

struct Musics
{
	Musics(std::string _ressourceName, float _volume);
	sf::Sound music;
	std::string name;
    float volume = 100;
};

typedef std::vector<std::pair< std::unique_ptr<Sound3D>, std::string>> VectorSound3D;
typedef std::vector<std::pair< std::unique_ptr<Musics>, std::string>> VectorMusics;

class Audio3D_Manager : public GameComponent
{
public:
	Audio3D_Manager() = default;
	~Audio3D_Manager();


	void update();

	void draw();

	/// \brief Set the 3D Sound to the object
	/// \brief Use the name you assigned to the 3D Sound
	void setSoundToObjectPosition(std::string _soundName, std::shared_ptr<ObjectTransform> _objectTransform);

	sf::Vector3f getListenerPosition() { return sf::Listener::getPosition(); }

	sf::Vector3f getListenerDirection() { return sf::Listener::getDirection(); }

	void setListenerPosition(sf::Vector3f pos);

	/// \brief relative to the direction of the Player (Y = Z in 2D games)
	void setListenerDirection(sf::Vector3f dir);//

	/// \brief relative to the direction of the player (Y = Z in 2D games)
	void setListenerVolume(float _volume);

	/// \brief if Attenuation is 0, The sound will always have the same Volume
	/// \brief More attenuation means more volume distortion
	void setAttenuation(const std::string& name, float _attenuation);

	/// \brief set the Loop -> true/false  music/sound  name
	void setLoop(bool _loop, const std::string& category, const std::string& name);

	/// \brief set music to gradually fade
	void graduallyStopMusic(const std::string& name, float fadeDuration);

	/// \brief set music to gradually start
	void graduallyStartMusic(const std::string& name, float fadeDuration);

	/// \brief Default value is 1, Which is in the head of the Listener  
	/// \brief it is the Minimum distance where the 3D Sound will start being heard
	void setMinimumDistance(const std::string& name, float _Distance);

	/// \brief Set the Volume of the 3D Sound
	void setGlobalVolume(const std::string& name, float _volume);

	// \brief Set the Volume of all the 3D Sound
	void setAllGlobalVolume(float _volume);

	// \brief Set the Volume of all the 3D Sound
	void setAllMusicVolume(float _volume);

	/// \brief Set the Position of the 3D Sound
	void setSoundPosition(const std::string& name, sf::Vector3f _posSound);

	/// \brief Add a 3D Sound to the Scene you are in  
	/// \brief First the Name of the Song then the Ressource Name 
	void addSceneSound(std::string _soundName, std::string _ressourceName, float _volume);

	/// \brief Get the 3D Sound through its Name
	sf::Sound& getSound3D(const std::string& name);

	/// \brief Add a Music to the Scene you are in  
	/// \brief First the Name of the Song then the Ressource Name 
	void addSceneMusic(std::string _soundName, std::string _ressourceName, float _volume);

	/// \brief Get the Music through its Name
	sf::Sound& getMusic(const std::string& name);

	/// \brief Get the volume for the sounds
	float getVolumeSound();

	/// \brief Get the volume for the music
	float getVolumeMusic();

	VectorSound3D vector_sounds3D;
	VectorMusics vector_music;
};

