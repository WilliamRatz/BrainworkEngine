
#include "VK_Window.h"


int main() {

	VK_Window vk_Window;

	try {
		vk_Window.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	/*
	int r = 0;
	int f = 0;

	bool go = false;

	for (float i = 0; i < 900; i += 0.1)
	{
		////std::cout << std::cos(i *MathLib::toDeg)  << " value: " << i << std::endl;
		//if (MathLib::sign(std::cos(i) > 0)) {

		//	std::cout << "+";
		//	if (go)
		//	{
		//		std::cout << std::cos(i) << std::endl;

		//		go = false;
		//	}
		//}
		//else {

		//	std::cout << "-";
		//	if (!go)
		//	{
		//		std::cout << std::cos(i) << std::endl;
		//		go = true;

		//	}
		//}

		if (MathLib::Cos(i) + 0.02 > std::cos(i) && MathLib::Cos(i*MathLib::toDeg) - 0.02 < std::cos(i))
		{
			++r;
		}
		else
		{
			++f;
			std::cout << "failed at:" << i << " , BW: " << MathLib::Cos(i) << " right: " << std::cos(i) << std::endl;
		}

	}
	std::cout << "right:" << r << std::endl;
	std::cout << "false:" << f << std::endl;
	*/
	return EXIT_SUCCESS;
}