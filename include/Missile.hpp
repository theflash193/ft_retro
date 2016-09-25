#ifndef MISSILE_CLASS_HPP
#define MISSILE_CLASS_HPP

#include <AGameEntity.hpp>
#include <Interface.hpp>

class Missile : public AGameEntity {

public:
	Missile(int, int);
	Missile(Missile const &);
	virtual ~Missile(void);

	Missile &		operator=(Missile const &);

	virtual void	render(Interface &) const;
	void			unrender(Interface &) const;
	bool			move(Interface &, unsigned long, unsigned int);

private:
	Missile(void);

	unsigned long	_lastMove;

};

#endif // MISSILE_CLASS_HPP
