#pragma once
#include"CoffeeCore.hpp"
#include"Map.h"

class Camera : public GameComponent {
private:
	sf::View m_View;
	sf::View m_viewHUD;
	std::weak_ptr<ObjectTransform> m_viewPosition;
	bool m_lockCamera = false;
	sf::Vector2f m_PositionMax;
	sf::Vector2f m_PositionMin;
	sf::Vector2f m_positionLine;
	sf::VertexArray rail;
	sf::VertexArray railLimitsTop;
	sf::VertexArray railLimitsBot;
	CoffeeWindow window;
	float m_MinDistance = 1000;
	float m_MaxDistance = 5000;
public:
	Camera();
	Camera(int _different);
	~Camera();

	void resetView();

	void setPositiontoObjectTransform(std::weak_ptr<ObjectTransform> _posView);

	void setPositionLine(int railStart, int railEnd, int raillimit_nb, sf::View view, sf::VertexArray railLimitsTop, sf::VertexArray railLimitsBot, sf::Vector2f& positionLine);

	void setPosition(sf::Vector2f _posView);

	void setFixedLine(sf::Vector2f _newposLine);

	void setSize(sf::Vector2f _size);

	void lockCamera(bool _cameraLock);

	void setlockCameraMinMax(float MinDistance,float MaxDistance);

	void update();

	void draw();

	void clampPlayerToView(std::shared_ptr<GameObject> player, float frontLimitOffset, float backLimitOffset, float playerSizeY);

    bool isInRailSegment(float playerX, int startIndex, int endIndex); 

    void updateCameraXFollow(std::shared_ptr<ObjectTransform> objectTransform);

    void followSlope_6_7_Behavior(const sf::Vector2f& playerPos, const sf::Vector2f& previousPosition);

    void followSlope_10_11_Behavior(const sf::Vector2f& playerPos, const sf::Vector2f& previousPosition);

    void followSlope(int startIdx, int endIdx, const sf::Vector2f& playerPos, float offsetX, float offsetY, bool xPositiveCheck, bool requireXGreaterThanY);

	void followSlope_2_3_Behavior(const sf::Vector2f& playerPos, const sf::Vector2f& previousPosition);

	void setandDrawViewHUD();

	void shakeCamera();

	sf::View getView();

	sf::Vector2f getViewPos();

	sf::Vector2f getViewTransformPosition();
};

