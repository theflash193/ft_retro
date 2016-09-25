#include <mach/mach.h>
#include <mach/clock.h>
#include <Time.hpp>

Time::Time(void) : _startTime(getMonoliticTime()) {
}

Time::Time(Time const & src) {
	*this = src;
}

Time::~Time(void) {
}

Time &					Time::operator=(Time const & rhs) {
	if (this != &rhs) {
		_startTime = rhs._startTime;
	}
	return (*this);
}

void					Time::reset(void) {
	_startTime = getMonoliticTime();
}

unsigned long			Time::getStartTime(void) const {
	return (_startTime);
}

unsigned long			Time::getEllapsedTime(void) const {
	return ((getMonoliticTime() - _startTime) / 1000);
}

unsigned long			Time::getEllapsedTimeInMs(void) const {
	return (getMonoliticTime() - _startTime);
}

unsigned long			Time::getMonoliticTime(void) {
	clock_serv_t	cclock;
	mach_timespec_t	mts;

	host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	return (mts.tv_nsec / 1000000 + mts.tv_sec * 1000);
}
