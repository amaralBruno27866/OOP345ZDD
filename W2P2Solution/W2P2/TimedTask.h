/*/////////////////////////////////////////////////////////////////////////
						  Workshop - #2 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

namespace seneca {
	const int MAX_TASKS = 10;

	typedef std::chrono::steady_clock::duration clockDuration;
	typedef std::chrono::steady_clock::time_point clockTime;
	typedef std::chrono::steady_clock clock;

	struct Task {
		std::string task_name;
		std::string unit_of_time;
		clockDuration duration;

		Task();
	};

	class TimedTask {
	private:
		int m_numOfRecord;
		clockTime m_startTime;
		clockTime m_endTime;
		Task m_tasks[MAX_TASKS];
	public:
		TimedTask();
		TimedTask(int numOfRecord, clockTime startTime, clockTime endTime, Task tasks[MAX_TASKS]);
		TimedTask(const TimedTask& tt);
		TimedTask& operator=(const TimedTask& tt);
		~TimedTask();
		void init(const TimedTask& tt);

		void startClock();
		void stopClock();
		void addTask(const char* taskName);
		friend std::ostream& operator<< (std::ostream & os, const TimedTask & tt);
	};
}

#endif // !SENECA_TIMEDTASK_H
