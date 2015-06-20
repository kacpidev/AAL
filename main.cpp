/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#include <iostream>
#include "Program.h"
#include "Collection.h"

int main(int argc, char *argv[])
{
	srand(((unsigned) time(NULL)));

	Program::program = new Program(argc, argv);
	Program::program->run();

	std::cout << "\nProgram terminated, press Enter to continue..." << std::endl;

	int temp = 0;

	glutInit(&temp, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(1000, 50);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("AAL_Kacper_Domanski");

	glutDisplayFunc(&Program::draw);

	glutMainLoop();

	std::cin.get();

	delete(Program::program);

	return 0;
}