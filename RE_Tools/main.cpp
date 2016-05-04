/*
 * main.cpp by Erik Lanning 2016
 *	Used to call the various tests for the project.
 */

#include "scannerTest.h"
#include "injectorTest.h"
#include "globalFunctionsTest.h"

int main()
{
	using namespace retool;

	testAllGlobalFunctions();
	injectorTest testInjector;
	scannerTest testScanner;

	std::cout << "Tests successfully run." << std::endl;
	getchar();
	return 0;
}