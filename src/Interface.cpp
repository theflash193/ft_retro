#include <cstdlib>
#include <signal.h>
#include <Interface.hpp>
#include <curses.h>

Interface::Interface(void) {
	initscr();
	cbreak();
	noecho();
	nonl();
	start_color();

	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_GREEN, 0, 1000, 0);
	init_color(COLOR_BLUE, 0, 0, 1000);
	init_color(COLOR_YELLOW, 1000, 1000, 0);

	curs_set(FALSE);
	init_pair(C_NONE, COLOR_WHITE, COLOR_BLACK);
	init_pair(C_RED, COLOR_RED, COLOR_BLACK);
	init_pair(C_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(C_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(C_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(C_WHITE, COLOR_BLACK, COLOR_WHITE);
	getmaxyx(stdscr, _height, _width);
	--_height;
	_hud = newwin(1, _width, 0, 0);
	wclear(_hud);
	wrefresh(_hud);
	_window = newwin(_height, _width, 1, 0);
	keypad(_window, TRUE);
	wclear(_window);
	wrefresh(_window);
}

Interface::Interface(Interface const & src) {
	*this = src;
}

Interface &		Interface::operator=(Interface const & rhs) {
	if (this != &rhs) {
		_width = rhs._width;
		_height = rhs._height;
		_window = rhs._window;
	}
	return (*this);
}

unsigned int	Interface::getWidth(void) const {
	return (_width);
}

unsigned int	Interface::getHeight(void) const {
	return (_height);
}

WINDOW *		Interface::getWindow(void) const {
	return (_window);
}

void			Interface::clearLine(int y) const {
	wmove(_window, y, 0);
	wclrtoeol(_window);
	wrefresh(_window);
}

void			Interface::clearWindow(void) const {
	wclear(_window);
}

void			Interface::refreshWindow(void) const {
	wrefresh(_window);
}

void			Interface::setCursor(int x, int y) const {
	wmove(_window, y, x);
}

void			Interface::printText(std::string str) const {
	wattrset(_window, COLOR_PAIR(C_NONE));
	wprintw(_window, str.data());
	wrefresh(_window);
}

void			Interface::printText(std::string str, e_color color) const {
	wattrset(_window, COLOR_PAIR(color));
	wprintw(_window, str.data());
	wrefresh(_window);
}

void			Interface::printText(int x, int y, std::string str) const {
	wattrset(_window, COLOR_PAIR(C_NONE));
	mvwprintw(_window, y, x, str.data());
	wrefresh(_window);
}

void			Interface::printText(int x, int y, std::string str, e_color color) const {
	wattrset(_window, COLOR_PAIR(color));
	mvwprintw(_window, y, x, str.data());
	wrefresh(_window);
}

int				Interface::getPressedKey(void) {
	return (wgetch(_window));
}

void			Interface::clearHud(void) const {
	wclear(_hud);
}

void			Interface::refreshHud(void) const {
	wrefresh(_hud);
}

void			Interface::printHudText(std::string str) const {
	wattrset(_hud, COLOR_PAIR(C_NONE));
	wprintw(_hud, str.data());
	wrefresh(_hud);
}

void			Interface::printHudText(std::string str, e_color color) const {
	wattrset(_hud, COLOR_PAIR(color));
	wprintw(_hud, str.data());
	wrefresh(_hud);
}

void			Interface::printHudText(int x, int y, std::string str) const {
	wattrset(_hud, COLOR_PAIR(C_NONE));
	mvwprintw(_hud, y, x, str.data());
	wrefresh(_hud);
}

void			Interface::printHudText(int x, int y, std::string str, e_color color) const {
	wattrset(_hud, COLOR_PAIR(color));
	mvwprintw(_hud, y, x, str.data());
	wrefresh(_hud);
}

void			Interface::printEndView(void) const {
	printText(10, 5, " _____________________________", C_YELLOW);
	printText(10, 6, "|       __     __             |", C_YELLOW);
	printText(10, 7, "|       \\ \\   / /             |", C_YELLOW);
	printText(10, 8, "|        \\ \\_/ /__  _   _     |", C_YELLOW);
	printText(10, 9, "|         \\   / _ \\| | | |    |", C_YELLOW);
	printText(10, 10, "|          | | (_) | |_| |    |", C_YELLOW);
	printText(10, 11, "|        _ |_|\\___/ \\__,_|    |", C_YELLOW);
	printText(10, 12, "|       | |         | |       |", C_YELLOW);
	printText(10, 13, "|       | | ___  ___| |_      |", C_YELLOW);
	printText(10, 14, "|       | |/ _ \\/ __| __|     |", C_YELLOW);
	printText(10, 15, "|       | | (_) \\__ \\ |_      |", C_YELLOW);
	printText(10, 16, "|       |_|\\___/|___/\\__|     |", C_YELLOW);
	printText(10, 17, "|_____________________________|", C_YELLOW);
}

Interface::~Interface(void) {
	delwin(_window);
	endwin();
}
