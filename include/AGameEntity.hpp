#ifndef AGAME_ENTITY_CLASS_HPP
#define AGAME_ENTITY_CLASS_HPP

#include <string>
#include <Interface.hpp>

class AGameEntity {

public:
	AGameEntity(int, int);
	AGameEntity(int, int, int, int);
	AGameEntity(int, int, int, int, int hp);
	AGameEntity(AGameEntity const &);
	virtual ~AGameEntity(void);

	AGameEntity &			operator=(AGameEntity const &);

	unsigned int			getX(void) const;
	unsigned int			getY(void) const;
	unsigned int			getWidth(void) const;
	unsigned int			getHeight(void) const;
	int						getHp(void) const;
	void					setHp(int hp);
	virtual void			render(Interface &) const = 0;
	void					beDamaged(const unsigned int amount);
	bool					beDestroyed(void) const;

protected:
	unsigned int			_x;
	unsigned int			_y;
	unsigned int			_width;
	unsigned int			_height;
	int						_hp;

private:
	AGameEntity(void);

};

#endif // AGAME_ENTITY_CLASS_HPP
