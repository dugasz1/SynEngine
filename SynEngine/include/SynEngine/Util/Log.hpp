#pragma once
#include <string>
#include <iostream>

namespace SynEngine {

	typedef std::ostream LogStream;

	class Log
	{
	public:
		Log();
		~Log();

		void Error(std::string msg);
		void Warn(std::string msg);
		void Info(std::string msg);
		LogStream& Stream() {
			return std::cout;
		}

	private:

	};
}

