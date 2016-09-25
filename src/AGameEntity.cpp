#include <AGameEntity.hpp>

AGameEntity::AGameEntity(void) : _x(0), _y(0), _width(1), _height(1) , _hp(1) {
}

AGameEntity::AGameEntity(int x, int y) : _x(x), _y(y), _width(1), _height(1), _hp(1) {
}

AGameEntity::AGameEntity(int x, int y, int width, int height)
		: _x(x), _y(y), _width(width), _height(height) , _hp(1){
}

AGameEntity::AGameEntity(int x, int y, int width, int height, int hp)
		: _x(x), _y(y), _width(width), _height(height), _hp(hp) {
}

AGameEntity::AGameEntity(AGameEntity const & src) {
	*this = src;
}

AGameEntity::~AGameEntity(void) {
}

AGameEntity &	AGameEntity::operator=(AGameEntity const & rhs) {
	if (this != &rhs) {
		_x = rhs._x;
		_y = rhs._y;
		_width = rhs._width;
		_height = rhs._height;
	}
	return (*this);
}

unsigned int	AGameEntity::getX(void) const {
	return (_x);
}

unsigned int	AGameEntity::getY(void) const {
	return (_y);
}

unsigned int	AGameEntity::getWidth(void) const {
	return (_width);
}

unsigned int	AGameEntity::getHeight(void) const {
	return (_height);
}

int	AGameEntity::getHp(void) const {
	return (_hp);
}

void	AGameEntity::setHp(const int hp) {
	_hp = hp;
}

void	AGameEntity::beDamaged(const unsigned int amount) {
	int result;

	result = _hp - amount;
	_hp = (result < 0) ? 0 : result;
}

bool	AGameEntity::beDestroyed(void) const {
	if (_hp == 0)
		return true;
	return false;
}
