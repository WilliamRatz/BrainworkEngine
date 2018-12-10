#include "Tests.h"

void Tests::SpeedTest(void(*function), int iterations)
{
	std::chrono::duration<double, std::milli> time_span;
	std::chrono::high_resolution_clock::time_point t2;
	std::cout << "the time is calculated by your own os time" << std::endl;

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < iterations; ++i)
	{
		function;
	}

	t2 = std::chrono::high_resolution_clock::now();
	time_span = t2 - t1;

	std::cout << "To use the function " << iterations << " iterations took me:" << std::endl;
	std::cout << time_span.count() << std::endl;
}
