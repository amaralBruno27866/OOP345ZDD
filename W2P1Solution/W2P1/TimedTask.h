#ifndef TIMED_TASK_SENECA
#define TIMED_TASK_SENECA

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

namespace seneca {
	typedef std::chrono::steady_clock::duration clockDuration;
	typedef std::chrono::steady_clock::time_point clockTime;
	typedef std::chrono::steady_clock clock;

	extern const int MAX_NUM_OF_TASK = 10;

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
		Task m_tasks[MAX_NUM_OF_TASK];
	public:
		TimedTask();
		TimedTask(int numOfRecord, clockTime startTime, clockTime endTime, Task tasks[MAX_NUM_OF_TASK]);
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

#endif // !TIMED_TASK_SENECA
