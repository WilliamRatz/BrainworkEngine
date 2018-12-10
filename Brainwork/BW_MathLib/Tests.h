#ifndef TESTS_H
#define TESTS_H

#include <chrono>
#include <ratio>
#include <ctime>
#include <iostream>

class Tests
{
public:
	static void SpeedTest(void(*function), int iterations);
};
#endif // !TESTS_H

