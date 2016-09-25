#include "AEnemy.hpp"

#ifndef DUCK_HPP
#define DUCK_HPP
class Duck : public AEnemy {
private:

	virtual void	render(Interface &) const;
	void			unrender(Interface &) const;
	Duck &			operator=(Duck const &);
public:
	Duck (void);
	virtual ~Duck ();
	void	move(Interface &, Player & player, unsigned long, unsigned int);
	Duck(int, int);
	Duck(Duck const &);
};
#endif
