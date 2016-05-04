#pragma once
#include <cassert>
#include <string>
#include <Windows.h>
#include "globalFunctions.h"
#include "injector.h"

namespace retool
{
	class injectorTest
	{
	public:
		//@pre Process named "injectorTest.exe" running, file with path C:\exampleInjectedDLL.dll exists.
		//@post Test successfully completes.
		injectorTest()
		{
			std::string processName = "injectorTestExe.exe";
			std::string dllPath = "C:\\exampleInjectedDLL.dll";
			assert (getPid(processName) != 0);

			injector exampleInjector(processName, dllPath);
			assert (exampleInjector.isInjected() == true);
		}
	};
}