#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

#define BASE_LIVES		3

#include <AGameEntity.hpp>
#include <Interface.hpp>
#include "PowerUp.hpp"

class Player : public AGameEntity {

public:
	Player(int, int);
	Player(Player const &);
	virtual ~Player(void);

	Player &		operator=(Player const &);

	unsigned int	getScore(void) const;
	unsigned int	getLives(void) const;

	PowerUp::MissileType getMissileType() {return _missileType;}

	void			setLives(unsigned int);
	void			score(void);

	virtual void	render(Interface &) const;
	void			moveY(Interface &, bool);
	void			moveX(Interface &, bool);

	void			setMissile(PowerUp::MissileType missile);

private:
	Player(void);

	unsigned int			_score;
	unsigned int			_lives;
	PowerUp::MissileType	_missileType;

	void			_unrender(Interface &) const;

};

#endif // PLAYER_CLASS_HPP
