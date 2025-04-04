#pragma once

#ifdef COFFEECORE_EXPORTS
#define COFFEECORE_API __declspec(dllexport)
#else
#define COFFEECORE_API __declspec(dllimport)
#endif

#ifdef NDEBUG
#else
#define DEBUG_TOOLS
#endif;

#define CONVERT_TO_MEGA_OCTET 1048576.f

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <typeindex>
#include <sstream>
#include <thread>
#include <any>
#include <mutex>
#include <memory>
#include <filesystem>
#include "sfeMovie/Movie.hpp"

namespace fs = std::filesystem;

namespace tools
{
	COFFEECORE_API int iRand(int _min, int _max);

	COFFEECORE_API double frand(float _min, float _max);

	COFFEECORE_API void restartClock();

	COFFEECORE_API float GetTimeDelta();

	COFFEECORE_API float lerp(float v0, float v1, float t);

	COFFEECORE_API sf::Vector2f vec2f_lerp(sf::Vector2f v0, sf::Vector2f v1, float t);

	COFFEECORE_API sf::Vector3f vec3f_lerp(sf::Vector3f v0, sf::Vector3f v1, float t);

	COFFEECORE_API sf::Color color_lerp(sf::Color v0, sf::Color v1, float t);

	COFFEECORE_API bool Circle_Collision(sf::Vector2f _pos1, sf::Vector2f _pos2, float _rayon1, float _rayon2);

	COFFEECORE_API bool Rectangle_Collision(sf::FloatRect _box1, sf::FloatRect _box2);

};
