#include "Camera.h"
#include"Physique.h"

#define topLimitY 580
#define bottomLimitY 680
#define PlayerBigBoySizeY 497.f
#define PlayerBloodlustSizeY 406.f

Camera::Camera()
{
	m_View.setCenter(1040.f, 540.f);
	m_positionLine.x = 1040.f;
	m_positionLine.y = 540.f;
	rail.setPrimitiveType(sf::Lines);
	rail.resize(20.f);
	railLimitsTop.setPrimitiveType(sf::Lines);
	railLimitsTop.resize(20.f);
	railLimitsBot.setPrimitiveType(sf::Lines);
	railLimitsBot.resize(20.f);

	//1st Horizontal rail 
	rail[0].position = sf::Vector2f(0, 1900);
	rail[1].position = sf::Vector2f(3000, 1900);
	rail[0].color = sf::Color::Blue;
	rail[1].color = sf::Color::Blue;
	//1st Diagonal rail 
	rail[2].position = sf::Vector2f(3050, 1630);
	rail[3].position = sf::Vector2f(7100, 4100);
	rail[2].color = sf::Color::Blue;
	rail[3].color = sf::Color::Blue;
	//2nd Horizontal rail 
	rail[4].position = sf::Vector2f(7100, 4100);
	rail[5].position = sf::Vector2f(12000, 4100);
	rail[4].color = sf::Color::Blue;
	rail[5].color = sf::Color::Blue;
	//2nd Diagonal rail 
	rail[6].position = sf::Vector2f(12200, 4100);
	rail[7].position = sf::Vector2f(14500, 2730);
	rail[6].color = sf::Color::Blue;
	rail[7].color = sf::Color::Blue;
	//3rd Horizontal rail
	rail[8].position = sf::Vector2f(14550, 3000);
	rail[9].position = sf::Vector2f(18000, 3000);
	rail[8].color = sf::Color::Blue;
	rail[9].color = sf::Color::Blue;
	//3rd Diagonal rail
	rail[10].position = sf::Vector2f(18050, 2630);
	rail[11].position = sf::Vector2f(21750, 4950);
	rail[10].color = sf::Color::Blue;
	rail[11].color = sf::Color::Blue;
	//4th Horizontal rail
	rail[12].position = sf::Vector2f(21750, 5100);
	rail[13].position = sf::Vector2f(26500, 5100);
	rail[12].color = sf::Color::Blue;
	rail[13].color = sf::Color::Blue;

	//5th Horizontal rail BOSS
	rail[16].position = sf::Vector2f(26800, 5100);
	rail[17].position = sf::Vector2f(29200, 5100);
	rail[16].color = sf::Color::Blue;
	rail[17].color = sf::Color::Blue;

	//Beginning Zone
	rail[14].position = sf::Vector2f(0, 750);
	rail[15].position = sf::Vector2f(3838, 750);
	rail[14].color = sf::Color::Blue;
	rail[15].color = sf::Color::Blue;


	railLimitsTop[0].position = sf::Vector2f(rail[0].position.x, rail[0].position.y - (topLimitY - 15));
	railLimitsTop[1].position = sf::Vector2f(rail[1].position.x, rail[1].position.y - (topLimitY - 15));
	railLimitsTop[0].color = sf::Color::Red;
	railLimitsTop[1].color = sf::Color::Red;
	railLimitsTop[4].position = sf::Vector2f(rail[4].position.x, rail[4].position.y - (topLimitY + 25));
	railLimitsTop[5].position = sf::Vector2f(rail[5].position.x, rail[5].position.y - (topLimitY + 25));
	railLimitsTop[4].color = sf::Color::Red;
	railLimitsTop[5].color = sf::Color::Red;
	railLimitsTop[6].position = sf::Vector2f(rail[8].position.x, rail[8].position.y - topLimitY);
	railLimitsTop[7].position = sf::Vector2f(rail[9].position.x, rail[9].position.y - topLimitY);
	railLimitsTop[6].color = sf::Color::Red;
	railLimitsTop[7].color = sf::Color::Red;
	railLimitsTop[8].position = sf::Vector2f(rail[12].position.x, rail[12].position.y - (topLimitY - 50));
	railLimitsTop[9].position = sf::Vector2f(rail[13].position.x, rail[13].position.y - (topLimitY - 50));
	railLimitsTop[8].color = sf::Color::Red;
	railLimitsTop[9].color = sf::Color::Red;

	//Beginning Zone
	railLimitsTop[10].position = sf::Vector2f(rail[14].position.x, rail[14].position.y - 600);
	railLimitsTop[11].position = sf::Vector2f(rail[15].position.x, rail[15].position.y - 600);
	railLimitsTop[10].color = sf::Color::Red;
	railLimitsTop[11].color = sf::Color::Red;

	//Boss Zone
	railLimitsTop[12].position = sf::Vector2f(rail[16].position.x, rail[16].position.y - 505);
	railLimitsTop[13].position = sf::Vector2f(rail[17].position.x, rail[17].position.y - 505);
	railLimitsTop[12].color = sf::Color::Red;
	railLimitsTop[13].color = sf::Color::Red;

	railLimitsBot[0].position = sf::Vector2f(rail[0].position.x, rail[0].position.y + bottomLimitY);
	railLimitsBot[1].position = sf::Vector2f(rail[1].position.x, rail[1].position.y + bottomLimitY);
	railLimitsBot[0].color = sf::Color::Red;
	railLimitsBot[1].color = sf::Color::Red;
	railLimitsBot[4].position = sf::Vector2f(rail[4].position.x, rail[4].position.y + (bottomLimitY - 100));
	railLimitsBot[5].position = sf::Vector2f(rail[5].position.x, rail[5].position.y + (bottomLimitY - 100));
	railLimitsBot[4].color = sf::Color::Red;
	railLimitsBot[5].color = sf::Color::Red;
	railLimitsBot[6].position = sf::Vector2f(rail[8].position.x, rail[8].position.y + bottomLimitY);
	railLimitsBot[7].position = sf::Vector2f(rail[9].position.x, rail[9].position.y + bottomLimitY);
	railLimitsBot[6].color = sf::Color::Red;
	railLimitsBot[7].color = sf::Color::Red;
	railLimitsBot[8].position = sf::Vector2f(rail[12].position.x, rail[12].position.y + (bottomLimitY - 50));
	railLimitsBot[9].position = sf::Vector2f(rail[13].position.x, rail[13].position.y + (bottomLimitY - 50));
	railLimitsBot[8].color = sf::Color::Red;
	railLimitsBot[9].color = sf::Color::Red;

	//Beginning Zone
	railLimitsBot[10].position = sf::Vector2f(rail[14].position.x, rail[14].position.y);
	railLimitsBot[11].position = sf::Vector2f(rail[15].position.x, rail[15].position.y);
	railLimitsBot[10].color = sf::Color::Red;
	railLimitsBot[11].color = sf::Color::Red;

	//Boss Zone
	railLimitsBot[12].position = sf::Vector2f(rail[16].position.x, rail[16].position.y + 1670);
	railLimitsBot[13].position = sf::Vector2f(rail[17].position.x, rail[17].position.y + 1670);
	railLimitsBot[12].color = sf::Color::Red;
	railLimitsBot[13].color = sf::Color::Red;
}

Camera::Camera(int _different)
{
	m_viewHUD.setCenter(1000, 1200);
}

Camera::~Camera()
{
}

void Camera::resetView()
{
	m_View.reset(sf::FloatRect(0, 0, 1920, 1080));
}

void Camera::setPositiontoObjectTransform(std::weak_ptr<ObjectTransform> _posView)
{
	m_viewPosition = _posView;
}

void Camera::setPosition(sf::Vector2f _posView)
{
	m_View.setCenter(_posView);
}

void Camera::setFixedLine(sf::Vector2f _newposLine)
{
	m_positionLine = _newposLine;
}

void Camera::setSize(sf::Vector2f _size)
{
	m_View.setSize(_size);
}

void Camera::lockCamera(bool _cameraLock)
{
	m_lockCamera = _cameraLock;
}

void Camera::setlockCameraMinMax(float MinDistance, float MaxDistance)
{
	m_MinDistance = MinDistance;
	m_MaxDistance = MaxDistance;
}

void Camera::setPositionLine(int railStart, int railEnd, int raillimit_nb, sf::View view, sf::VertexArray railLimitsTop, sf::VertexArray railLimitsBot, sf::Vector2f& positionLine)
{
	if (auto objectTransform = m_viewPosition.lock())
	{
		if (objectTransform->getPosition().x > rail[railStart].position.x && objectTransform->getPosition().x < rail[railEnd].position.x)
		{
			if ((objectTransform->getPosition().y - view.getSize().y / 2.f) > railLimitsTop[raillimit_nb].position.y && (objectTransform->getPosition().y + view.getSize().y / 2.f) < railLimitsBot[raillimit_nb].position.y)
			{
				positionLine.y = objectTransform->getPosition().y - (PlayerBigBoySizeY / 2.f);
			}
		}
	}
}

std::vector<float> getYcoordinatesforLines(sf::Vector2f _arrivalPoint, sf::Vector2f _startingPoint)
{
	std::vector<float> y;
	float slope = (_arrivalPoint.y - _startingPoint.y) / (_arrivalPoint.x - _startingPoint.x);// calculate slope
	float intercept_y = _startingPoint.y - slope * _startingPoint.x;//calculate y intercept
	for (float coordinate_x = _startingPoint.x; coordinate_x <= _arrivalPoint.x; coordinate_x++)
	{
		float coordinate_y = slope * coordinate_x + intercept_y;// coordinate_y = all the corresponding y coordinates to the x between the two lines
		y.push_back(coordinate_y);
	}
	return y;
}

void Camera::update()
{

	if (auto player1 = getParents().lock()->getParent()->getObjects("Player"))
	{
		clampPlayerToView(player1, 110.f, 100.f, PlayerBigBoySizeY);
	}

	if (auto player2 = getParents().lock()->getParent()->getObjects("Player2"))
	{
		clampPlayerToView(player2, 65.f, 0.f, PlayerBloodlustSizeY); 
	}
	if (auto objectTransform = m_viewPosition.lock())
	{
		sf::Vector2f currentPos = m_View.getCenter();
		sf::Vector2f targetPos = sf::Vector2f(m_positionLine.x, m_positionLine.y);
		sf::Vector2f distance = targetPos - currentPos;
		float smoothingFactor = tools::GetTimeDelta() * 3.f;

		if (!m_lockCamera)
			updateCameraXFollow(objectTransform);




		//Horizontal rails
		if (auto parent = getParents().lock()->getParent()->getObjects(PLAYER))
		{
			if (parent->getComponents<Physique>()->getCanMooved() == false)
			{
				setPositionLine(0, 1, 0, getView(), railLimitsTop, railLimitsBot, m_positionLine);
				setPositionLine(4, 5, 4, getView(), railLimitsTop, railLimitsBot, m_positionLine);
				setPositionLine(8, 9, 6, getView(), railLimitsTop, railLimitsBot, m_positionLine);
				setPositionLine(12, 13, 8, getView(), railLimitsTop, railLimitsBot, m_positionLine);


				//Beginning Zone
				if (objectTransform->getPosition().x > rail[14].position.x && objectTransform->getPosition().x < rail[15].position.x && objectTransform->getPosition().y < railLimitsTop[0].position.y)
				{
					if ((objectTransform->getPosition().y - getView().getSize().y / 2.f) > railLimitsTop[10].position.y && (objectTransform->getPosition().y + getView().getSize().y / 2) < railLimitsBot[10].position.y)
					{
						m_positionLine.y = objectTransform->getPosition().y - (PlayerBigBoySizeY / 2.f);
					}
				}

				//Boss Zone
				if (objectTransform->getPosition().x > rail[16].position.x && objectTransform->getPosition().x < rail[17].position.x && objectTransform->getPosition().x > rail[13].position.x)
				{
					if ((objectTransform->getPosition().y - getView().getSize().y / 2.f) > railLimitsTop[12].position.y && (objectTransform->getPosition().y + getView().getSize().y / 2) < railLimitsBot[12].position.y)
					{
						m_positionLine.y = objectTransform->getPosition().y - (PlayerBigBoySizeY / 2.f);
					}
				}

				followSlope_6_7_Behavior(objectTransform->getPosition(), m_positionLine);
			}
		}

		sf::Vector2f previousPosition = m_positionLine;

		followSlope_2_3_Behavior(objectTransform->getPosition(), previousPosition);




		followSlope_10_11_Behavior(objectTransform->getPosition(), previousPosition);

		if (objectTransform->getPosition().x - getView().getSize().x / 2.f < 105 && objectTransform->getPosition().x < 26527)
		{
			m_positionLine.x = 1000;
		}

		if ((objectTransform->getPosition().x + getView().getSize().x / 2.f > 26400) && objectTransform->getPosition().x < 26980)
		{
			m_positionLine.x = 25900;
		}


		if (m_lockCamera == false)
			m_View.setCenter(currentPos + smoothingFactor * distance);
		else
			m_View.setCenter(sf::Vector2f(m_View.getCenter().x, currentPos.y + smoothingFactor * distance.y));
	}
}

void Camera::followSlope(int startIdx, int endIdx, const sf::Vector2f& playerPos, float offsetX, float offsetY, bool xPositiveCheck, bool requireXGreaterThanY)
{
	
	const sf::Vector2f& start = rail[startIdx].position;
	const sf::Vector2f& end = rail[endIdx].position;

	float slope = (end.y - start.y) / (end.x - start.x);
	float interceptY = start.y - slope * start.x;

	sf::Vector2f previousPos = m_positionLine;

	for (float x = start.x; x <= end.x; x += 1.0f)
	{
		float y = slope * x + interceptY;

	
		if (requireXGreaterThanY && x <= playerPos.y)
			continue;

		bool validY = y + offsetY < playerPos.y;
		bool validX = xPositiveCheck ? (x < playerPos.x + offsetX) : (x < playerPos.x - offsetX);

		if (validY || validX)
		{
			m_positionLine.x = x;
			m_positionLine.y = y;

			if ((xPositiveCheck && m_positionLine.x < previousPos.x) ||
				(!xPositiveCheck && m_positionLine.x > previousPos.x) ||
				(m_positionLine.y < previousPos.y))
			{
				m_positionLine = previousPos;
				return;
			}
		}
	}
}


bool Camera::isInRailSegment(float playerX, int startIndex, int endIndex)
{
	return playerX > rail[startIndex].position.x && playerX < rail[endIndex].position.x;
}

void Camera::updateCameraXFollow(std::shared_ptr<ObjectTransform> objectTransform)
{
	sf::Vector2f pos = objectTransform->getPosition();
	sf::Vector2f viewSize = getView().getSize();

	// skip if player is in special zones
	bool inSpecialZone =
		isInRailSegment(pos.x, 2, 3) ||
		isInRailSegment(pos.x, 6, 7) ||
		isInRailSegment(pos.x, 10, 11) ||
		isInRailSegment(pos.x, 16, 17);

	if (inSpecialZone) return;

	if (m_positionLine.x < pos.x + 50.f && pos.y > railLimitsTop[0].position.y)
	{
		m_positionLine.x = pos.x + 50.f;
	}
	else if (
		pos.y < railLimitsTop[0].position.y &&
		(pos.x - viewSize.x / 2.f > 70.f) &&
		(pos.x + viewSize.x / 2.f < 3838.f)
		)
	{
		m_positionLine.x = pos.x - 75.f;
	}
}

void Camera::draw()
{
	window.getWindow().setView(m_View);
	/*window.draw(rail);
	window.draw(railLimitsTop);
	window.draw(railLimitsBot);*/
}

void Camera::clampPlayerToView(std::shared_ptr<GameObject> player, float frontLimitOffset, float backLimitOffset, float playerSizeY)
{
	if (!player || player->getComponents<Physique>()->B_Dead) return;

	auto transform = player->getComponents<ObjectTransform>();
	sf::Vector2f pos = transform->getPosition();
	sf::Vector2f viewCenter = getView().getCenter();
	sf::Vector2f viewSize = getView().getSize();

	// X front limit (locked camera)
	if (m_lockCamera && pos.x > (viewCenter.x + viewSize.x / 2.f) - frontLimitOffset)
	{
		pos.x = (viewCenter.x + viewSize.x / 2.f) - frontLimitOffset;
	}

	// X back limit
	if (pos.x < (viewCenter.x - viewSize.x / 2.f) + backLimitOffset)
	{
		pos.x = (viewCenter.x - viewSize.x / 2.f) + backLimitOffset;
	}

	// Y top limit
	if (pos.y - playerSizeY < viewCenter.y - viewSize.y / 2.f)
	{
		pos.y = viewCenter.y - viewSize.y / 2.f + playerSizeY;
	}

	// Y bottom limit
	if (pos.y > viewCenter.y + viewSize.y / 2.f)
	{
		pos.y = viewCenter.y + viewSize.y / 2.f;
	}

	transform->setPosition(pos);
}


void Camera::setandDrawViewHUD()
{
	window.getWindow().setView(m_viewHUD);
}

sf::View Camera::getView()
{
	return m_View;
}

sf::Vector2f Camera::getViewPos()
{
	return sf::Vector2f(m_View.getCenter().x - 960, m_View.getCenter().y - 540);
}

sf::Vector2f Camera::getViewTransformPosition()
{
	if (auto objectTransform = m_viewPosition.lock())
	{
		return sf::Vector2f(objectTransform->getPosition().x - 960, objectTransform->getPosition().y - 600);
	}
}

void Camera::followSlope_2_3_Behavior(const sf::Vector2f& playerPos, const sf::Vector2f& previousPosition)
{
	if (playerPos.x > rail[2].position.x && playerPos.x < rail[3].position.x && playerPos.y > railLimitsTop[0].position.y)
	{
		float slope = (rail[3].position.y - rail[2].position.y) / (rail[3].position.x - rail[2].position.x); // calculate slope
		float intercept_y = rail[2].position.y - slope * rail[2].position.x; // calculate y intercept

		for (float coordinate_x = rail[2].position.x; coordinate_x <= rail[3].position.x; coordinate_x++)
		{
			if (coordinate_x > playerPos.y) // 👈 yes, x > y as in original
			{
				float coordinate_y = slope * coordinate_x + intercept_y;

				if (coordinate_y + 475 < playerPos.y || coordinate_x < playerPos.x - 350)
				{
					m_positionLine.y = coordinate_y;
					m_positionLine.x = coordinate_x;

					if (m_positionLine.x < previousPosition.x)
					{
						m_positionLine = previousPosition;
					}
					if (m_positionLine.y < previousPosition.y)
					{
						m_positionLine = previousPosition;
					}
				}
			}
		}
	}
}

void Camera::followSlope_6_7_Behavior(const sf::Vector2f& playerPos, const sf::Vector2f& previousPosition)
{
	if (playerPos.x > rail[6].position.x && playerPos.x < rail[7].position.x)
	{
		float slope = (rail[7].position.y - rail[6].position.y) / (rail[7].position.x - rail[6].position.x); // calculate slope
		float intercept_y = rail[6].position.y - slope * rail[6].position.x; // calculate y intercept

		for (float coordinate_x = rail[6].position.x; coordinate_x <= rail[7].position.x; coordinate_x++)
		{
			float coordinate_y = slope * coordinate_x + intercept_y;

			if (coordinate_y - 500 > playerPos.y - PlayerBigBoySizeY || coordinate_x < playerPos.x - 350)
			{
				m_positionLine.y = coordinate_y;
				m_positionLine.x = coordinate_x;

				if (m_positionLine.y > previousPosition.y)
				{
					m_positionLine = previousPosition;
				}
			}
		}
	}
}

void Camera::followSlope_10_11_Behavior(const sf::Vector2f& playerPos, const sf::Vector2f& previousPosition)
{
	if (playerPos.x > rail[10].position.x && playerPos.x < rail[11].position.x)
	{
		float slope = (rail[11].position.y - rail[10].position.y) / (rail[11].position.x - rail[10].position.x); // calculate slope
		float intercept_y = rail[10].position.y - slope * rail[10].position.x; // calculate y intercept

		for (float coordinate_x = rail[10].position.x; coordinate_x <= rail[11].position.x; coordinate_x++)
		{
			float coordinate_y = slope * coordinate_x + intercept_y;

			if (coordinate_y + 475 < playerPos.y || coordinate_x < playerPos.x + 50)
			{
				m_positionLine.y = coordinate_y;
				m_positionLine.x = coordinate_x;

				if (m_positionLine.x < previousPosition.x)
				{
					m_positionLine = previousPosition;
				}
				if (m_positionLine.y < previousPosition.y)
				{
					m_positionLine = previousPosition;
				}
			}
		}
	}
}
