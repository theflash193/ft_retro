#include <Game.hpp>
#include <Missile.hpp>

Missile::Missile(void) : AGameEntity(0, 0, 1, 1) {
}

Missile::Missile(int x, int y) : AGameEntity(x, y, 1, 1) {
}

Missile::Missile(Missile const & src) : AGameEntity(0, 0) {
	*this = src;
}

Missile::~Missile(void) {
}

Missile &	Missile::operator=(Missile const & rhs) {
	if (this != &rhs) {
		_x = rhs.getX();
		_y = rhs.getY();
		_width = rhs.getWidth();
		_height = rhs.getHeight();
	}
	return (*this);
}

void	Missile::render(Interface & interface) const {
	interface.printText(_x, _y, "o", Interface::C_YELLOW);
}

void	Missile::unrender(Interface & interface) const {
	interface.printText(_x, _y, " ");
}

bool	Missile::move(Interface & interface, unsigned long time, unsigned int delay) {
	if (time - _lastMove > delay) {
		_lastMove = time;
		unrender(interface);
		_x++;
		return (true);
	}
	return (false);
}
