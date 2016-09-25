#include "Duck.hpp"

Duck::Duck(void) : AEnemy(0, 0, 6, 2) {
}

Duck::Duck(int x, int y) : AEnemy(x, y, 6, 2) {
}

Duck::Duck(Duck const & src) : AEnemy(0, 0) {
	*this = src;
}

Duck::~Duck(void) {
}

Duck &	Duck::operator=(Duck const & rhs) {
	if (this != &rhs) {
		_x = rhs.getX();
		_y = rhs.getY();
		_width = rhs.getWidth();
		_height = rhs.getHeight();
	}
	return (*this);
}

void	Duck::render(Interface & interface) const {
	interface.printText(_x, _y, ">(.)__", Interface::C_RED);
	interface.printText(_x, _y + 1, " (___/", Interface::C_RED);
}

void	Duck::unrender(Interface & interface) const {
	interface.printText(_x, _y, "      ");
	interface.printText(_x, _y + 1, "      ");
}

void	Duck::move(Interface & interface, Player & player, unsigned long time, unsigned int delay) {
	(void)player;
	if (time - this->getLastMove() > delay) {
		this->setLastMove(time);
		unrender(interface);
		_x--;
	}
}
