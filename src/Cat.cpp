#include "Cat.hpp"

Cat::Cat(void) : AEnemy(0, 0, 6, 3, 15) {
}

Cat::Cat(int x, int y) : AEnemy(x, y, 6, 3, 15) {
}

Cat::Cat(Cat const & src) : AEnemy(0, 0) {
	*this = src;
}

Cat::~Cat(void) {
}

Cat &	Cat::operator=(Cat const & rhs) {
	if (this != &rhs) {
		_x = rhs.getX();
		_y = rhs.getY();
		_width = rhs.getWidth();
		_height = rhs.getHeight();
	}
	return (*this);
}

void	Cat::render(Interface & interface) const {
	interface.printText(_x, _y, " /\\_/\\", Interface::C_RED);
	interface.printText(_x, _y + 1 , "( o.o )", Interface::C_RED);
	interface.printText(_x, _y + 2, " > ^ <", Interface::C_RED);
}

void	Cat::unrender(Interface & interface) const {
	interface.printText(_x, _y, "        ", Interface::C_RED);
	interface.printText(_x, _y + 1, "       ", Interface::C_RED);
	interface.printText(_x, _y + 2, "      ", Interface::C_RED);
}

void	Cat::move(Interface & interface, Player & player, unsigned long time, unsigned int delay) {
	(void)player;
	if (time - this->getLastMove() > delay) {
		this->setLastMove(time);
		// _lastMove = time;
		unrender(interface);
		_x--;
	}
}
