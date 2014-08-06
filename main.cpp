#include "task.h"

int main()
{
	try
	{
		RLOG("--- started");
		Emulator().start();
		RLOG("--- completed successfully");
		return 0;
	}
	catch (std::exception& e)
	{
		RLOG("Error: " << e.what());
	}
	catch (...)
	{
		RLOG("Unknown error");
	}
	return 1;
}
