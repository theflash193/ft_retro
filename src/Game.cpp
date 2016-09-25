#include <sstream>
#include <cstdlib>
#include <signal.h>
#include <Game.hpp>

#include <iostream>

Game::Game(void) : _enemiesPerSec(ENEMIES_PER_SEC), _enemiesMoveDelay(ENEMIES_MOVE_DELAY) {
	_interface = new Interface;
	_time = new Time;
	_player = new Player(10, _interface->getHeight() / 2);
	_enemies = NULL;
	_missiles = NULL;
	_powerups = NULL;
	_lastEnemy = 0;
	_lastMissile = 0;
	_lastPowerup = 0;
	_nukes = 1;
	_paused = false;
	_ended = false;
	_dragoon = false;
}

Game::Game(int eps, int emd) : _enemiesPerSec(eps), _enemiesMoveDelay(emd) {
	_interface = new Interface;
	_time = new Time;
	_player = new Player(10, _interface->getHeight() / 2);
	_enemies = NULL;
	_missiles = NULL;
	_powerups= NULL;
	_lastEnemy = 0;
	_lastMissile = 0;
	_lastPowerup = 0;
	_nukes = 1;
	_paused = false;
	_ended = false;
	_dragoon = false;
}

Game::Game(Game const & src) : _enemiesPerSec(ENEMIES_PER_SEC), _enemiesMoveDelay(ENEMIES_MOVE_DELAY) {
	*this = src;
}

Game::~Game(void) {
	delete _interface;
	delete _time;
	delete _player;
	t_enemy *	nextEnemy;
	while (_enemies != NULL) {
		delete _enemies->enemy;
		nextEnemy = _enemies->next;
		delete _enemies;
		_enemies = nextEnemy;
	}
	t_missile *	nextMissile;
	while (_missiles != NULL) {
		delete _missiles->missile;
		nextMissile = _missiles->next;
		delete _missiles;
		_missiles = nextMissile;
	}
	t_powerup *	nextPowerUp;
	while (_powerups != NULL) {
		delete _powerups->powerup;
		nextPowerUp = _powerups->next;
		delete _powerups;
		_powerups = nextPowerUp;
	}
}

Game &		Game::operator=(Game const & rhs) {
	if (this != &rhs) {
		_interface = new Interface(rhs.getInterface());
		_time = new Time(rhs.getTime());
		_player = new Player(rhs.getPlayer());
		_enemies = NULL;
		_missiles = NULL;
		_powerups = NULL;
		_lastEnemy = 0;
		_lastMissile = 0;
		_lastPowerup = 0;
		_nukes = 1;
		_paused = rhs.isPaused();
		_ended = false;
		_dragoon = false;
	}
	return (*this);
}

Interface &	Game::getInterface(void) const {
	return (*(_interface));
}

Time &		Game::getTime(void) const {
	return (*(_time));
}

Player &	Game::getPlayer(void) const {
	return (*(_player));
}

t_enemy &	Game::getEnemies(void) const {
	return (*(_enemies));
}

t_missile &	Game::getMissiles(void) const {
	return (*(_missiles));
}

t_powerup & Game::getPowerups(void) const {
	return (*(_powerups));
}

int			Game::getNukes(void) const {
	return _nukes;
}

bool		Game::isPaused(void) const {
	return (_paused);
}

bool		Game::isEnded(void) const {
	return (_ended);
}

void		Game::setPaused(bool state) {
	_paused = state;
}

void		Game::shoot(void) {
	unsigned int	lives = _player->getLives();

	if (_paused || lives == 0) {
		return;
	}
	unsigned long time = _time->getEllapsedTimeInMs();
	if (time - _lastMissile > 1000 / (MISSILES_PER_SEC + _player->getScore())) {
		_lastMissile = time;
		if (_player->getMissileType() == PowerUp::MULTI)
			_addMissile(3);
		else
			_addMissile(1);
	}
}

void		Game::nuke(void) {
	if (_paused || _player->getLives() == 0 || _nukes == 0)
		return;

	_nukes--;
	updateHUD();
	_interface->refreshHud();

	// Nuke effect
	wbkgd(_interface->getWindow(), Interface::C_WHITE);

	t_enemy * current = _enemies;
	while (current != NULL) {
		current->enemy->beDamaged(20);
		if (current->enemy->beDestroyed() == true)
			current = _deleteEnemy(current);
	}
}

void		Game::updateHUD(void) {
	std::ostringstream	s;

	_interface->clearHud();
	_interface->printHudText(10, 0, "LIVES: ", Interface::C_GREEN);
	s << _player->getLives() << "         ";
	_interface->printHudText(s.str());
	s.str("");
	s.clear();
	_interface->printHudText("SCORE: ", Interface::C_GREEN);
	s << _player->getScore() << "         ";
	_interface->printHudText(s.str());
	s.str("");
	s.clear();
	if (_paused) {
		_interface->printHudText("PAUSED", Interface::C_GREEN);
	}
}

bool		Game::update(void) {
	unsigned int	lives = _player->getLives();

	if (lives == 0) {
		_interface->printEndView();
		_ended = true;
		return (false);
	}
	unsigned long time = _time->getEllapsedTimeInMs();
	if (time - _lastEnemy > 1000 / _enemiesPerSec) {
		_lastEnemy = time;
		_addEnemy();
	}
	if (time - _lastPowerup > POWERUPS_SEC * 1000)
	{
		_lastPowerup = time;
		_addPowerup();
	}

	_player->render(*(_interface));
	t_missile *	currentMissile;
	currentMissile = _missiles;
	while (currentMissile != NULL) {
		currentMissile->missile->move(*(_interface), time, MISSILES_MOVE_DELAY);
		currentMissile->missile->render(*(_interface));
		currentMissile = currentMissile->next;
	}

	t_powerup * currentPowerup;
	currentPowerup = _powerups;
	while (currentPowerup != NULL)
	{
		currentPowerup->powerup->move(*(_interface), time, POWERUPS_MOVE_DELAY);
		if (currentPowerup->powerup->getX() == 0)
			currentPowerup = _deletePowerup(currentPowerup);
		else if (_checkCollision(*(_player), *(currentPowerup->powerup)))
		{
			currentPowerup = _deletePowerup(currentPowerup);
			_player->setMissile(static_cast<PowerUp::MissileType>((rand() % 2) + 1));
		}
		else
		{
			currentPowerup->powerup->render(*_interface);
			currentPowerup = currentPowerup->next;
		}
	}

	t_enemy *	currentEnemy;
	currentEnemy = _enemies;
	while (currentEnemy != NULL) {
		if (_dragoon == false)
			currentEnemy->enemy->move(*(_interface), time, _enemiesMoveDelay);
		else
			currentEnemy->enemy->move(*(_interface), *(_player), time, _enemiesMoveDelay);
		if (_checkCollision(*(_player), *(currentEnemy->enemy))) {
			if (_dragoon == true)
				_dragoon = false;
			_player->setLives(--lives);
			updateHUD();
			if (lives > 0) {
				currentEnemy = _deleteEnemy(currentEnemy);
			} else {
				return (true);
			}
		} else {
			if (currentEnemy->enemy->getX() == 0) {
				currentEnemy = _deleteEnemy(currentEnemy);
			} else {
				currentMissile = _missiles;
				bool hit = false;
				while (currentMissile != NULL) {
					if (_checkCollision(*(currentMissile->missile), *(currentEnemy->enemy))) {
						currentEnemy->enemy->beDamaged(1);
						if (currentEnemy->enemy->beDestroyed() == true) {
							if (_dragoon == true)
								_dragoon = false;
							hit = true;
							_player->score();
							updateHUD();
							currentEnemy = _deleteEnemy(currentEnemy);
							if (_player->getMissileType() != PowerUp::PENETRATIVE)
								currentMissile = _deleteMissile(currentMissile);
							break;
						}
						else {
							currentEnemy->enemy->setHp(currentEnemy->enemy->getHp() - 1);
							if (_player->getMissileType() != PowerUp::PENETRATIVE)
								currentMissile = _deleteMissile(currentMissile);
						}
					} else if (currentMissile->missile->getX() >= _interface->getWidth() - 1) {
						currentMissile = _deleteMissile(currentMissile);
					} else {
						currentMissile = currentMissile->next;
					}
				}
				if (!hit) {
					currentEnemy->enemy->render(*(_interface));
					currentEnemy = currentEnemy->next;
				}
			}
		}
	}
	return (true);
}

void		Game::_addEnemy(void) {
	static int	count = 0;
	t_enemy *	enemy = new t_enemy;
	t_enemy *	prev;

	if (_dragoon == true)
		return ;
	if (++count == 8 && _dragoon == true) {
		if (rand() % 2 == 0) {
			enemy->enemy = type_enemy_popup(_interface->getWidth() - 10, _player->getY());
		} else {
			enemy->enemy = type_enemy_popup(_interface->getWidth() - 10, rand() % (_interface->getHeight() - 3));
		}
		count = 0;
	} else {
		enemy->enemy = type_enemy_popup(_interface->getWidth() -10, rand() % (_interface->getHeight() - 3));
	}
	enemy->next = NULL;
	if (_enemies == NULL) {
		enemy->prev = NULL;
		_enemies = enemy;
	} else {
		int	i = 1;
		prev = _enemies;
		while (prev != NULL && prev->next != NULL) {
			prev = prev->next;
			i++;
		}
		if (i < MAX_ENEMIES) {
			prev->next = enemy;
			enemy->prev = prev;
		} else {
			delete enemy;
		}
	}
}

t_enemy *	Game::_deleteEnemy(t_enemy * enemy) {
	t_enemy *	next = enemy->next;

	enemy->enemy->unrender(*(_interface));
	if (enemy->prev != NULL) {
		enemy->prev->next = enemy->next;
	} else {
		_enemies = enemy->next;
	}
	if (enemy->next != NULL) {
		enemy->next->prev = enemy->prev;
	}
	delete enemy;
	return (next);
}

void		Game::_addMissile(int n) {
	t_missile *	missile;
	t_missile *	prev;

	for (int k = 0; k < n; k++)
	{
		missile = new t_missile;
		missile->missile = new Missile(_player->getX() + _player->getWidth(), (_player->getY() + (_player->getHeight() / 2)) - n / 2 + k);
		missile->next = NULL;
		if (_missiles == NULL) {
			missile->prev = NULL;
			_missiles = missile;
		} else {
			int	i = 1;
			prev = _missiles;
			while (prev != NULL && prev->next != NULL) {
				prev = prev->next;
				i++;
			}
			prev->next = missile;
			missile->prev = prev;
		}
	}
}

t_missile *	Game::_deleteMissile(t_missile * missile) {
	t_missile *	next = missile->next;

	missile->missile->unrender(*(_interface));
	if (missile->prev != NULL) {
		missile->prev->next = missile->next;
	} else {
		_missiles = missile->next;
	}
	if (missile->next != NULL) {
		missile->next->prev = missile->prev;
	}
	delete missile;
	return (next);
}

void		Game::_addPowerup(void) {
	t_powerup *	powerup = new t_powerup;
	t_powerup *	prev;

	powerup->powerup = new PowerUp(_interface->getWidth() - 10, rand() % (_interface->getHeight() - 1));
	powerup->next = NULL;
	if (_powerups == NULL) {
		powerup->prev = NULL;
		_powerups = powerup;
	} else {
		int	i = 1;
		prev = _powerups;
		while (prev != NULL && prev->next != NULL) {
			prev = prev->next;
			i++;
		}
		prev->next = powerup;
		powerup->prev = prev;

	}
}

t_powerup *	Game::_deletePowerup(t_powerup * powerup) {
	t_powerup *	next = powerup->next;

	powerup->powerup->unrender(*(_interface));
	if (powerup->prev != NULL) {
		powerup->prev->next = powerup->next;
	} else {
		_powerups = powerup->next;
	}
	if (powerup->next != NULL) {
		powerup->next->prev = powerup->prev;
	}
	delete powerup;
	return (next);
}

bool		Game::_valueInRange(int value, int min, int max) const {
	return (value >= min) && (value < max);
}

bool		Game::_checkCollision(AGameEntity & ent1, AGameEntity & ent2) const {
	bool xOverlap = _valueInRange(ent1.getX(), ent2.getX(), ent2.getX() + ent2.getWidth())
		|| _valueInRange(ent2.getX(), ent1.getX(), ent1.getX() + ent1.getWidth());
	bool yOverlap = _valueInRange(ent1.getY(), ent2.getY(), ent2.getY() + ent2.getHeight())
		|| _valueInRange(ent2.getY(), ent1.getY(), ent1.getY() + ent1.getHeight());
	return (xOverlap && yOverlap);
}

AEnemy	*Game::type_enemy_popup(int x, int y) {
	if (this->_player->getScore() < 5)
		return (new Duck(x, y));
	else if (this->_player->getScore() % 8 == 0)
	{
		_dragoon = true;
		return (new Dragoon(x - 33, y - 33));
	}
	else if (rand() % 2)
	{
		_dragoon = true;
		return (new Dragoon(x - 33, y - 33));
	}
	else
		return (new Cat(x, y));
}
