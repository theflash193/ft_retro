#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#define DEADZONE_RIGHT		20
#define DEADZONE_LEFT		5

#define ENEMIES_PER_SEC		3
#define MAX_ENEMIES			120
#define ENEMIES_MOVE_DELAY	35

#define MISSILES_PER_SEC	25
#define MISSILES_MOVE_DELAY	10

#define POWERUPS_SEC		10
#define POWERUPS_MOVE_DELAY	40


#include <Interface.hpp>
#include <Time.hpp>
#include <Player.hpp>
#include <Missile.hpp>
#include "PowerUp.hpp"
#include "AEnemy.hpp"
#include "Duck.hpp"
#include "Cat.hpp"
#include "Dragoon.hpp"

typedef struct			s_enemy {
	AEnemy *			enemy;
	struct s_enemy *	prev;
	struct s_enemy *	next;
}						t_enemy;

typedef struct			s_missile {
	Missile *			missile;
	struct s_missile *	prev;
	struct s_missile *	next;
}						t_missile;

typedef struct			s_powerup {
	PowerUp*			powerup;
	struct s_powerup*	prev;
	struct s_powerup*	next;
}						t_powerup;

class Game {

public:
	Game(void);
	Game(int, int);
	Game(Game const &);
	~Game(void);

	Game &				operator=(Game const &);

	Interface &			getInterface(void) const;
	Time &				getTime(void) const;
	Player &			getPlayer(void) const;
	t_enemy &			getEnemies(void) const;
	t_missile &			getMissiles(void) const;
	t_powerup &			getPowerups(void) const;
	int					getNukes(void) const;
	bool				isPaused(void) const;
	bool				isEnded(void) const;
	void				setPaused(bool);
	void				updateHUD(void);
	bool				update(void);
	void				shoot(void);
	void				nuke(void);
	AEnemy				*type_enemy_popup(int x, int y);

private:
	unsigned int const	_enemiesPerSec;
	unsigned int const	_enemiesMoveDelay;

	Interface *			_interface;
	Time *				_time;
	Player *			_player;
	t_enemy *			_enemies;
	t_missile *			_missiles;
	t_powerup *			_powerups;

	unsigned long		_lastEnemy;
	unsigned long		_lastMissile;
	unsigned long		_lastPowerup;
	int					_nukes;
	bool				_paused;
	bool				_ended;
	bool				_dragoon;
	void				_addEnemy(void);
	t_enemy *			_deleteEnemy(t_enemy *);

	void				_addMissile(int);
	t_missile *			_deleteMissile(t_missile *);

	void				_addPowerup(void);
	t_powerup *			_deletePowerup(t_powerup *);

	bool				_valueInRange(int, int, int) const;
	bool				_checkCollision(AGameEntity &, AGameEntity &) const;

};

#endif // GAME_CLASS_HPP
