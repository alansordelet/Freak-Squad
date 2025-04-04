#pragma once
#include "CoffeeCore.hpp"

class Game;
class CoffeeCore;
class IAMOTHER;
namespace IAFonction
{
	void mooveToPlay(Game* _game,const std::shared_ptr<RigidBody>& _body, const std::shared_ptr<IAMOTHER>& _ia);
	void back(Game* _game, const std::shared_ptr<RigidBody>& _body, const std::shared_ptr<IAMOTHER>& _ia);
	void monte(Game* _game, const std::shared_ptr<RigidBody>& _body, const std::shared_ptr<IAMOTHER>& _ia);

	bool cMooveToPlayTrash(Game* _game, const std::shared_ptr<IAMOTHER>& _ia);
	bool cMonteTrash(Game* _game, const std::shared_ptr<IAMOTHER>& _ia);
}