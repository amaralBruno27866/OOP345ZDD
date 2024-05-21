#ifndef SENECA_TIMED_TASK_H
#define SENECA_TIMED_TASK_H

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

#endif // !SENECA_TIMED_TASK_H
