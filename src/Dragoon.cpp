#include "Dragoon.hpp"

Dragoon::Dragoon(void) : AEnemy(0, 0, 43, 11, 100) {
}

Dragoon::Dragoon(int x, int y) : AEnemy(x, y, 43, 11, 100) {
}

Dragoon::Dragoon(Dragoon const & src) : AEnemy(0, 0) {
	*this = src;
}

Dragoon::~Dragoon(void) {
}

Dragoon &	Dragoon::operator=(Dragoon const & rhs) {
	if (this != &rhs) {
		_x = rhs.getX();
		_y = rhs.getY();
		_width = rhs.getWidth();
		_height = rhs.getHeight();
	}
	return (*this);
}

void	Dragoon::render(Interface & interface) const {
	interface.printText(_x, _y,      ",===:\'.,`-._                             ", Interface::C_RED);
	interface.printText(_x, _y + 1,  "          `:.`---.__         `-._         ", Interface::C_RED);
	interface.printText(_x, _y + 2,  "            `:.     `--.         `.       ", Interface::C_RED);
	interface.printText(_x, _y + 3,  "              \\.        `.         `.    ", Interface::C_RED);
	interface.printText(_x, _y + 4,  "      (,,(,    \\.         `.   ____,-`., ", Interface::C_RED);
	interface.printText(_x, _y + 5,  "   (,\'     `/   \\.   ,--.___`.\'        ", Interface::C_RED);
	interface.printText(_x, _y + 6,  "`{D, {    \\  :    \\;                    ", Interface::C_RED);
	interface.printText(_x, _y + 7,  "  V,,\'    /  /    //                     ", Interface::C_RED);
	interface.printText(_x, _y + 8,  "  j;;    /  ,\' ,-//.    ,---.      ,     ", Interface::C_RED);
	interface.printText(_x, _y + 9,  "  \\;\'   /  ,\' /  _  \\  /  _  \\   ,\'/", Interface::C_RED);
	interface.printText(_x, _y + 10, "        \\   `\'  / \\  `\'  / \\  `.\' / ", Interface::C_RED);
	interface.printText(_x, _y + 11, "         `.___,\'   `.__,\'   `.__,\'     ", Interface::C_RED);
}

void	Dragoon::unrender(Interface & interface) const {
	interface.printText(_x, _y,     "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 1, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 2, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 3, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 4, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 5, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 6, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 7, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 8, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 9, "                                        ", Interface::C_RED);
	interface.printText(_x, _y + 10,"                                        ", Interface::C_RED);
	interface.printText(_x, _y + 11,"                                        ", Interface::C_RED);

}

void	Dragoon::move(Interface & interface, Player & player, unsigned long time, unsigned int delay) {
	if (time - this->getLastMove() > delay) {
		this->setLastMove(time);
		unrender(interface);
		if (player.getX() != this->getX())
			_x = ((int)player.getX() - (int)this->getX() < 0) ? _x - 1 : _x + 1;
		if (player.getY() != this->getY())
			_y = ((int)player.getY() - (int)this->_y < 0) ? _y - 1 : _y + 1;
	}
}
