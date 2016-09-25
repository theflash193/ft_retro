#ifndef AENEMY_CLASS_HPP
#define AENEMY_CLASS_HPP

#include <AGameEntity.hpp>
#include <Interface.hpp>
#include "Player.hpp"
class AEnemy : public AGameEntity {

public:
	AEnemy(int, int);
	AEnemy(int, int, int, int);
	AEnemy(int, int, int, int, int hp);
	AEnemy(AEnemy const &);
	virtual ~AEnemy(void);

	AEnemy &			operator=(AEnemy const &);

	virtual void	render(Interface &) const = 0;
	virtual void	unrender(Interface &) const = 0;
	virtual void	move(Interface &, unsigned long, unsigned int);
	virtual void	move(Interface &, Player & player, unsigned long, unsigned int);
	void			setLastMove(const unsigned long lastMove);
	unsigned long	getLastMove(void) const;
private:
	AEnemy(void);

	unsigned long	_lastMove;


};

#endif // ENEMY_CLASS_HPP
