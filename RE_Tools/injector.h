/*
* injector.h by Erik Lanning, 2016
*	Declares a class dealing with injecting, hooking, modifying various processes or objects.
*/
#pragma once
#include <string>

namespace retool
{
	class injector
	{
		friend class injectorTest;
	public:
		injector(std::string processName,std::string dllLocation);
		virtual ~injector() = default;
		void injectDll(std::string processName,std::string dllLocation);
		
		bool isInjected()
		{
			return isInjected_; 
		}

	private:
		bool isInjected_;
	};
}