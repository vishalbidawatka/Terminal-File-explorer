#include "global.h"
void enter_command_mode_old()
{

	// tcgetattr(fileno(stdin), &initial_command_settings);
	// new_commandM_settings = initial_command_settings;
	// new_commandM_settings.c_lflag = ICANON;
	// new_commandM_settings.c_lflag = ECHO;
	// tcsetattr(fileno(stdin), TCSANOW, &new_commandM_settings);
	forcecursor(rows,0);
	clear_line();
	cout<<":";
	string s;
	//forcecursor(rows,1);
	string command = get_command(s);

}
void enter_command_mode(string current_working_directory)
{
	chdir(HOME.c_str());
	forcecursor(rows,0);
	clear_line();   
	//command_cursor = 0;  
	cout<<":";
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
{	//cout<<"IN GET COMMAND";
	char c;
	string command;
	int command_cursor = 0;
	while(1)
	{
		c = getchar();
		if(c == '\n')
		{	
			seprated_command = split_command(command);
			execute_command(seprated_command,current_working_directory);
			chdir(HOME.c_str());
			forcecursor(rows,0);
			// clear_line();   
			// command_cursor = 0;  
			// cout<<":";
			//return command;

		}
		else if(c == 27)
		{
			exit_command_mode(current_working_directory);
			return "0";

		}
		else if(c == 'A')
		{


		}
		else if(c == 'B')
		{


		}
		else if(c== 127)
		{


		}
		else
		{
		command.append(1,c);
		cout<<c;
		command_cursor++;
		}

	}
	
}
vector<string> split_command(string command)
{

	size_t a,b = 0;
	vector<string> splited_string;
	a = command.find(' ');
	while(a != string::npos)
	{
		splited_string.push_back(command.substr(b,a-b));
		b = a+1;
		a = command.find(' ',b);

	}

	splited_string.push_back(command.substr(b,a-b));
	return splited_string;

}
void execute_command(vector<string> s , string current_working_directory )
{	
	cout<<s[0]<<" command";
	if(s[1] == "copy")
	{
		//copy_files(s,current_working_directory);
	}
	else if(s[1] == "create_file")
	{
		//copy_files(s,current_working_directory);
	}
	else if(s[1] == "create_dir")
	{
		//copy_files(s,current_working_directory);
	}
	else if(s[0] == "delete_file")
	{
		delv(s,current_working_directory);
	}
	else if(s[0] == "delete_dir")
	{
		deldir(s,current_working_directory);
		//copy_files(s,current_working_directory);
	}
	else if(s[1] == "goto")
	{
		//copy_files(s,current_working_directory);
	}
	else if(s[1] == "search")
	{
		//copy_files(s,current_working_directory);
	}
	else if(s[1] == "snapshot")
	{
		//copy_files(s,current_working_directory);
	}




}