
#include "VK_Window.h"

int main() {

	//ranspose Matrix check
	//Matrix<float, 2, 3> mat1;
	//Matrix<float, 3, 2> mat2;
	//mat1[0][0] = 1;
	//mat1[0][1] = 2;
	//mat1[1][0] = 3;
	//mat1[1][1] = 4;
	//mat1[2][0] = 5;
	//mat1[2][1] = 6;
	//mat2 = mat1.transpose();
	//std::cout << mat2;
	
	VK_Window vk_Window;

	try {
		vk_Window.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}