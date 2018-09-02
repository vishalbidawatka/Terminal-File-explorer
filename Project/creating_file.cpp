//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
int create_files(string file_name, string destination, vector<string> s, string current_working_directory, int flag)
{
	char buf[4096];
	if (destination == ".")
	{
		chdir(current_working_directory.c_str());
		if (flag == 0)
			int a = creat(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (flag == 1)
			int a = mkdir(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		chdir(current_working_directory.c_str());
	}
	else if (destination[0] == '~')
	{ //cout<<destination<<"destination"<<endl;
		destination.erase(0, 2);
		//cout<<destination<<endl;
		realpath(destination.c_str(), buf);
		strcat(buf, "/\0");
		int b = chdir(buf);
		if (flag == 0)
			int a = creat(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (flag == 1)
			int a = mkdir(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		chdir(current_working_directory.c_str());
	}
	else if (destination[0] == '/')
	{
		destination.erase(0, 1);
		realpath(destination.c_str(), buf);
		chdir(buf);
		if (flag == 0)
			int a = creat(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		else
			int a = mkdir(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		chdir(current_working_directory.c_str());
	}
	else
	{
		realpath(destination.c_str(), buf);
		chdir(buf);
		if (flag == 0)
			int a = creat(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		else
			int a = mkdir(file_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		chdir(current_working_directory.c_str());
	}
	return 0;
}
int create_multiple_files(vector<string> s, string current_working_directory)
{
	string destination = s[s.size() - 1];
	for (int i = 1; i < s.size() - 1; i++)
	{
		create_files(s[i], destination, s, current_working_directory);
	}
}
int creating_directory(vector<string> s, string current_working_directory)
{
	string destination = s[s.size() - 1];
	for (int i = 1; i < s.size() - 1; i++)
	{
		create_files(s[i], destination, s, current_working_directory, 1);
	}
}
void string_processing(string &s)
{
	if (s[0] == '~')
	{
		s.erase(0, 2);
	}
	if (s[0] == '/')
	{
		s.erase(0, 1);
	}
}
