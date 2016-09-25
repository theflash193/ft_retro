#ifndef INTERFACE_CLASS_HPP
#define INTERFACE_CLASS_HPP

#include <string>
#include <ncurses.h>
#include <Time.hpp>

class Interface {

public:
	enum e_color {
		C_NONE = 1,
		C_RED,
		C_GREEN,
		C_BLUE,
		C_YELLOW,
		C_WHITE
	};

	Interface(void);
	Interface(Interface const &);
	~Interface(void);

	Interface &	operator=(Interface const &);

	unsigned int	getWidth(void) const;
	unsigned int	getHeight(void) const;
	WINDOW *		getWindow(void) const;
	WINDOW *		getHud(void) const;
	void			clearLine(int) const;
	void			clearWindow(void) const;
	void			refreshWindow(void) const;
	void			setCursor(int, int) const;
	void			printText(std::string) const;
	void			printText(std::string, e_color) const;
	void			printText(int, int, std::string) const;
	void			printText(int, int, std::string, e_color) const;
	int				getPressedKey(void);
	void			clearHud(void) const;
	void			refreshHud(void) const;
	void			printHudText(std::string) const;
	void			printHudText(std::string, e_color) const;
	void			printHudText(int, int, std::string) const;
	void			printHudText(int, int, std::string, e_color) const;
	void			printEndView(void) const;

private:
	unsigned int	_width;
	unsigned int	_height;
	WINDOW *		_window;
	WINDOW *		_hud;

};

#endif // INTERFACE_CLASS_HPP
