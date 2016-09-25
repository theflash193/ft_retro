#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "AGameEntity.hpp"
#include "Interface.hpp"

class PowerUp : public AGameEntity
{
public:
	enum MissileType
	{
		BASIC = 0,
		MULTI,
		PENETRATIVE
	};

	PowerUp();
	PowerUp(int x, int y);
	PowerUp(const PowerUp& rhs);

	void		render(Interface& interface) const;
	void		unrender(Interface& interface) const;
	void		moveX(Interface& interface, bool direction);
	void		moveY(Interface& interface, bool direction);
	bool		move(Interface &, unsigned long, unsigned int);

	PowerUp&	operator=(const PowerUp& rhs);

	~PowerUp();

private:
	unsigned long	_lastMove;
};

#endif
