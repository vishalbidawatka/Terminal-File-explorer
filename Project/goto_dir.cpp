//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
int goto_dir(vector<string> command, string cwd)
{
	if (command[1] == "/")
	{
		chdir(HOME.c_str());
		printing_whole_page(HOME.c_str());
		left_one.push(HOME);
		forcecursor(0, 0);
		global_status_bar_flag = 0;
	}
	else
	{
		string_processing(command[1]);
		char buff[4096];
		realpath(command[1].c_str(), buff);
		left_one.push(string(buff));
		chdir(buff);
		printing_whole_page(string(buff));
		forcecursor(0, 0);
		global_status_bar_flag = 0;
	}
	return 0;
}