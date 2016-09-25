#ifndef TIME_CLASS_HPP
#define TIME_CLASS_HPP

class Time {

public:
	Time(void);
	Time(Time const &);
	~Time(void);

	Time &					operator=(Time const &);

	void					reset(void);
	unsigned long			getStartTime(void) const;
	unsigned long			getEllapsedTime(void) const;
	unsigned long			getEllapsedTimeInMs(void) const;

	static unsigned long	getMonoliticTime(void);

private:
	unsigned long			_startTime;

};

#endif // TIME_CLASS_HPP
