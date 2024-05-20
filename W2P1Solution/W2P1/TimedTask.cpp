#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

#include "TimedTask.h"

using namespace std;
namespace seneca {
	Task::Task() {
		task_name = "";
		unit_of_time = "";
		duration = clockDuration::zero();
	}

	TimedTask::TimedTask() {
		m_numOfRecord = 0;
	}

	TimedTask::TimedTask(int numOfRecord, clockTime startTime, clockTime endTime, Task tasks[MAX_NUM_OF_TASK]) {
		m_numOfRecord = numOfRecord;
		m_startTime = startTime;
		m_endTime = endTime;
		for (int i = 0; i < MAX_NUM_OF_TASK; i++) {
			m_tasks[i] = tasks[i];
		}
	}

	TimedTask::TimedTask(const TimedTask& tt) {
		init(tt);
	}

	TimedTask& TimedTask::operator=(const TimedTask& tt) {
		if (this != &tt) {
			init(tt);
		}

		return *this;
	}

	TimedTask::~TimedTask() {
	}

	void TimedTask::init(const TimedTask& tt) {
		m_numOfRecord = tt.m_numOfRecord;
		m_startTime = tt.m_startTime;
		m_endTime = tt.m_endTime;
		for (int i = 0; i < MAX_NUM_OF_TASK; i++) {
			m_tasks[i] = tt.m_tasks[i];
		}
	}

	void TimedTask::startClock() {
		m_startTime = clock::now();
	}

	void TimedTask::stopClock() {
		m_endTime = clock::now();
	}

	void TimedTask::addTask(const char* taskName) {
		m_tasks[m_numOfRecord].task_name = taskName;
		m_tasks[m_numOfRecord].unit_of_time = "nanoseconds";
		m_tasks[m_numOfRecord].duration = m_endTime - m_startTime;
		m_numOfRecord++;
	}

	ostream& operator<<(ostream& os, const TimedTask& tt) {
		os << "Execution Times:" << endl;
		os << "--------------------------" << endl;

		for (int i = 0; i < MAX_NUM_OF_TASK; i++) {
			// Print the task name
			os << left << setw(21) << tt.m_tasks[i].task_name << " ";

			// Print the task duration
			os << right << setw(13) << tt.m_tasks[i].duration.count() << " ";

			// Print the task unit time
			os << tt.m_tasks[i].unit_of_time << endl;
		}

		os << "--------------------------" << endl;
	}
}
