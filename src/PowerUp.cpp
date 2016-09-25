#include "PowerUp.hpp"
#include <cstdlib>

// Ctors
PowerUp::PowerUp() : AGameEntity(0, 0, 1, 1)
{
}

PowerUp::PowerUp(int x, int y) : AGameEntity(x, y, 1, 1)
{
}

PowerUp::PowerUp(const PowerUp& rhs) : AGameEntity(0, 0)
{
	*this = rhs;
}

// Functions
void
PowerUp::render(Interface& interface) const
{
	interface.printText(_x, _y, "P", Interface::C_BLUE);
}

void
PowerUp::unrender(Interface& interface) const {
	interface.printText(_x, _y, " ");
}

void
PowerUp::moveY(Interface& interface, bool direction)
{
	unrender(interface);
	if (direction)
		_y++;
	else
		_y--;
}

void
PowerUp::moveX(Interface& interface, bool direction)
{
	unrender(interface);
	if (direction)
		_x++;
	else
		_x--;
}

bool
PowerUp::move(Interface & interface, unsigned long time, unsigned int delay) {
	if (time - _lastMove > delay) {
		_lastMove = time;
		unrender(interface);
		_x--;
		return (true);
	}
	return (false);
}

// Otors
PowerUp&
PowerUp::operator=(const PowerUp& rhs)
{
	(void)rhs;
	return *this;
}

// Dtor
PowerUp::~PowerUp()
{
}
