#include <Game.hpp>
#include <AEnemy.hpp>

AEnemy::AEnemy(void) : AGameEntity(0, 0, 6, 2) {
}

AEnemy::AEnemy(int x, int y) : AGameEntity(x, y, 6, 2) {
}

AEnemy::AEnemy(int x, int y, int width, int height)
		: AGameEntity(x, y, width, height, 4) {
}

AEnemy::AEnemy(int x, int y, int width, int height, int hp)
		: AGameEntity(x, y, width, height, hp) {
}

AEnemy::AEnemy(AEnemy const & src) : AGameEntity(0, 0) {
	*this = src;
}

AEnemy::~AEnemy(void) {
}

AEnemy &	AEnemy::operator=(AEnemy const & rhs) {
	if (this != &rhs) {
		_x = rhs.getX();
		_y = rhs.getY();
		_width = rhs.getWidth();
		_height = rhs.getHeight();
	}
	return (*this);
}

void	AEnemy::move(Interface & interface, unsigned long time, unsigned int delay) {
	if (time - _lastMove > delay) {
		_lastMove = time;
		unrender(interface);
		_x--;
	}
}

void	AEnemy::move(Interface & interface, Player & player, unsigned long time, unsigned int delay) {
	(void)player;
	if (time - _lastMove > delay) {
		_lastMove = time;
		unrender(interface);
		_x--;
	}
}

unsigned long AEnemy::getLastMove(void) const {
	return (this->_lastMove);
}

void AEnemy::setLastMove(const unsigned long lastMove) {
	this->_lastMove = lastMove;
}
