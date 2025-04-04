#pragma once
#include "Tools.h"

class COFFEECORE_API Movie
{
public:
	Movie(const std::string& _MovieName);
	~Movie();

	sfe::Movie& getMovie();

	sfe::Movie m_movie;
	bool m_isPlaying;
};

typedef std::vector<std::pair<std::string, std::shared_ptr<Movie>>> Vector_Movies;

class COFFEECORE_API MovieManager
{
public:
	MovieManager();
	~MovieManager();

	/// \How to add line under
	void addMovie(std::string _MovieName);

	void playMovie(std::string _MovieName);

	void stopMovie(std::string _MovieName);

	void UpdateMovie(std::string _MovieName);

	void PauseMovie(std::string _MovieName);

	void UpdateAndDrawMovie(std::string _MovieName, sf::RenderWindow& _window);

	void resetSceneMovie();

	const sfe::Movie& getGlobalMovie(std::string _MovieName);

	void setSize(sf::FloatRect _newSize, std::string _MovieName);

	bool getReadiness();

private:
	Vector_Movies vec_GlobalMovies;
	bool m_isReady;
};
