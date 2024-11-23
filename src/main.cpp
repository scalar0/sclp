#include "logparser.h"

int main()
{
	if (const LogParser parser(R"(C:\Users\main\source\repos\sclp\sample.log)",
								R"(C:\Users\main\source\repos\sclp\output.jsonl)"); !parser.parse())
	{
		return 1;
	}
	return 0;
}
