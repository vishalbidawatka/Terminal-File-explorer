//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
void enter_command_mode(string current_working_directory)
{
	chdir(HOME.c_str());
	forcecursor(rows, 0);
	clear_line();
	//command_cursor = 0;
	cout << ":";
	string command = get_command(current_working_directory);
	//cout<<seprated_command.size()<<seprated_command[0];
}
void exit_command_mode(string current_working_directory)
{
	//tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
	chdir(current_working_directory.c_str());
	printing_whole_page(current_working_directory);
	global_status_bar_flag = 0;
}
string get_command(string current_working_directory)
{ //cout<<"IN GET COMMAND";
again:
	char c;
	string command;
	int command_cursor = 0;
	int command_return_code;
	while (1)
	{
		c = getchar();
		if (c == '\n')
		{
			seprated_command = split_command(command);
			command_return_code = execute_command(seprated_command, current_working_directory);
			//chdir(HOME.c_str());
			if (command_return_code == 5)
			{
				return "0";
			}
			forcecursor(rows, 0);
			clear_line();
			command_cursor = 0;
			cout << ":";
			command = "";
			goto again;
			//return command;
		}
		else if (c == 27)
		{
			exit_command_mode(current_working_directory);
			return "0";
		}
		else if (c == 'A')
		{
		}
		else if (c == 'B')
		{
		}
		else if (c == 127)
		{
			if (command.size() != 0)
			{
				command.pop_back();
				moveleft();
				cout << " ";
				moveleft();
			}
		}
		else
		{
			command.append(1, c);
			cout << c;
			command_cursor++;
		}
	}
}
vector<string> split_command(string command)
{
	size_t a, b = 0;
	vector<string> splited_string;
	a = command.find(' ');
	while (a != string::npos)
	{
		splited_string.push_back(command.substr(b, a - b));
		b = a + 1;
		a = command.find(' ', b);
	}
	splited_string.push_back(command.substr(b, a - b));
	return splited_string;
}
int execute_command(vector<string> s, string current_working_directory)
{
	//cout<<s[0]<<" command";
	if (s[0] == "copy")
	{
		copy_multiple_files(s, current_working_directory);
		return 0;
	}
	else if (s[0] == "create_file")
	{
		create_multiple_files(s, current_working_directory);
		return 1;
		//copy_files(s,current_working_directory);
	}
	else if (s[0] == "create_dir")
	{
		creating_directory(s, current_working_directory);
		return 2;
		//copy_files(s,current_working_directory);
	}
	else if (s[0] == "delete_file")
	{
		delv(s, current_working_directory);
		return 3;
	}
	else if (s[0] == "delete_dir")
	{
		deldir(s, current_working_directory);
		return 4;
		//copy_files(s,current_working_directory);
	}
	else if (s[0] == "goto")
	{
		goto_dir(s, current_working_directory);
		return 5; //copy_files(s,current_working_directory);
	}
	else if (s[0] == "search")
	{
		search_file(s[1], s, current_working_directory);
		return 6;
		//copy_files(s,current_working_directory);
	}
	else if (s[0] == "snapshot")
	{
		snapshot(s[1], s, current_working_directory);
		return 7;
		//copy_files(s,current_working_directory);
	}
	else if (s[0] == "rename")
	{
		chdir(current_working_directory.c_str());
		rename(s[1].c_str(), s[2].c_str());
	}
	else if (s[0] == "move")
	{
		move_multiple_files(s, current_working_directory);
		return 0;
	}
}
