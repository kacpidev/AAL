#include <iostream>
#include "Program.h"
#include "Collection.h"

int main(int argc, char *argv[])
{
	srand(((unsigned) time(NULL)));

	Program program(argc, argv);
	program.run();

	std::cout << "\nProgram terminated, press Enter to continue..." << std::endl;

	int temp = 0;

	glutInit(&temp, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("AAL_Kacper_Domanski");


	std::cin.get();

	return 0;
}