#include <Game.hpp>
#include <Player.hpp>

Player::Player(void) : AGameEntity(0, 0, 1, 1) {
	_score = 0;
	_lives = BASE_LIVES;
	_missileType = PowerUp::BASIC;
}

Player::Player(int x, int y) : AGameEntity(x, y, 1, 1) {
	_score = 0;
	_lives = BASE_LIVES;
	_missileType = PowerUp::BASIC;
}

Player::Player(Player const & src) : AGameEntity(0, 0) {
	*this = src;
}

Player::~Player(void) {
}

Player &		Player::operator=(Player const & rhs) {
	if (this != &rhs) {
		_x = rhs.getX();
		_y = rhs.getY();
		_width = rhs.getWidth();
		_height = rhs.getHeight();
		_score = rhs.getScore();
		_lives = rhs.getLives();
		_missileType = rhs._missileType;
	}
	return (*this);
}

unsigned int	Player::getScore(void) const {
	return (_score);
}

unsigned int	Player::getLives(void) const {
	return (_lives);
}

void			Player::setLives(unsigned int lives) {
	_lives = lives;
}

void			Player::score(void) {
	_score++;
}

void			Player::render(Interface & interface) const {
	interface.printText(_x, _y, ">", Interface::C_GREEN);
}

void			Player::_unrender(Interface & interface) const {
	interface.printText(_x, _y, " ");
}

void			Player::moveY(Interface & interface, bool increment) {
	if (_lives > 0) {
		if (increment) {
			if (_y + _height < interface.getHeight()) {
				_unrender(interface);
				_y++;
			}
		} else if (_y > 0) {
			_unrender(interface);
			_y--;
		}
	}
}

void			Player::moveX(Interface & interface, bool increment) {
	if (_lives > 0) {
		if (increment) {
			if (_x + _width + DEADZONE_RIGHT < interface.getWidth()) {
				_unrender(interface);
				_x++;
			}
		} else if (_x > DEADZONE_LEFT) {
			_unrender(interface);
			_x--;
		}
	}
}

void
Player::setMissile(PowerUp::MissileType missile)
{
	_missileType = missile;
}
