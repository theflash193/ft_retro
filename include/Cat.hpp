#ifndef CAT_HPP
#define CAT_HPP
#include "AEnemy.hpp"

class Cat : public AEnemy {
private:

	virtual void	render(Interface &) const;
	void			unrender(Interface &) const;
	Cat &			operator=(Cat const &);
public:
	Cat (void);
	virtual ~Cat ();
	Cat(int, int);
	Cat(Cat const &);
	void	move(Interface &, Player & player, unsigned long, unsigned int);
};
#endif
