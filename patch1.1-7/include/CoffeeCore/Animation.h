#pragma once
#include "GameComponent.h"
#include "RessourceManager.h"



struct COFFEECORE_API AnimInfo
{
	std::string m_nameAnimation;
	std::weak_ptr<Texture> p_texture;
	int m_maxAnimFrame;
	float m_timePerFrame;
	float m_pauseTime;
	int m_sizeWidthFrame;
	int m_sizeHeightFrame;
	bool m_loop;
	bool m_playing;
	bool m_pause;
	AnimInfo(std::string _nameAnimation, std::string _nameTexture, int _maxAnimFrame, float _timePerFrame, bool _loop);
	~AnimInfo();
};

class COFFEECORE_API Animation : public GameComponent
{
private:
	int m_currentFrame;
	sf::IntRect m_intRect;
	float m_elapsedAnimTime, m_elapsedPauseTime;
	std::vector<AnimInfo> m_vectorAnim;
	std::unique_ptr<AnimInfo> m_currentAnim;
public:
	Animation();
	~Animation();

	void update();
	void draw();

	void addAnimation(std::string _nameAnimation, std::string _nameTexture, int _maxAnimFrame, float _timePerFrame, bool _loop);
	void playAnim(std::string _nameAnimation, bool _loop);
	void resetCurrentAnim();
	void play();
	void pause();
	void pauseFor(float _timer);
	sf::Vector2i getSizeFrame();
	int getCurrentFrame();
	void setCurrentFrame(int _frame);
	AnimInfo* getCurrentAnimInfo();
};
