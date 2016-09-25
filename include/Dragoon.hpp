#ifndef DRAGOON_HPP
#define DRAGOON_HPP
#include "AEnemy.hpp"
#include "Player.hpp"

class Dragoon : public AEnemy {
private:

	virtual void	render(Interface &) const;
	void			unrender(Interface &) const;
	Dragoon &		operator=(Dragoon const &);
public:
	Dragoon (void);
	virtual ~Dragoon ();
	Dragoon(int, int);
	Dragoon(Dragoon const &);
	void	move(Interface &, Player & player, unsigned long, unsigned int);
};
#endif
