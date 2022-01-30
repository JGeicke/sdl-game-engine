#pragma once
#include <chrono>
#include <iostream>

class Timer {
public:
	Timer() {
		startTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
	}

	void stop() {
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start;

		double ms = duration * 0.001;

		std::cout << duration << "us (" << ms << "ms)\n";
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
};