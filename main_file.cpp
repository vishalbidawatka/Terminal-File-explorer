//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
struct termios initialrsettings, newrsettings, initial_command_settings, new_commandM_settings;
stack<string> left_one, right_one;
int global_status_bar_flag = 0;
int cursor = 0;
int rows;
int columns;
int relative_count = 0;
int command_mode_flag = 0;
int scrollcount = 0;
string HOME = presentworkingdir();
vector<vector<string>> current_d = contentofpwd(HOME);
vector<string> seprated_command;
void windowsize(int &a, int &b)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	a = w.ws_row;
	b = w.ws_col;
}
int main(int argc, char const *argv[])
{
	char c;
	int down_scroll_flag = 0;
	setting_terminal_attributes();
	windowsize(rows, columns);
	struct stat filestatus_2;
	clear();
	print_content(current_d);
	left_one.push(HOME);
	home();
	while (1)
	{
		display_status_bar(cursor, global_status_bar_flag);
		windowsize(rows, columns);
		c = (int)getchar();
		if (c == '\n')
		{
			if (current_d[relative_count][3][0] == 'd')
			{
				if (!(presentworkingdir() == HOME && current_d[relative_count][4] == ".."))
				{
					char buf[4096];
					realpath(current_d[relative_count][4].c_str(), buf);
					stat(buf, &filestatus_2);
					chdir(buf);
					left_one.push(string(buf));
					make_stack_empty(right_one);
					printing_whole_page(string(buf));
				}
			}
			else
			{
				//int storing_i = i;
				char buf2[4096];
				realpath(current_d[relative_count][4].c_str(), buf2);
				strcat(buf2, "\0");
				int pid = fork();
				if (pid == 0)
				{
					execl("/usr/bin/xdg-open", "xdg-open", buf2, (char *)0);
					exit(1);
				}
			}
			//forcecursor(i,0);
		}
		if (c == 'B')
		{
			if (relative_count < current_d.size() - 1)
			{
				downwards();
				relative_count++;
				if (cursor == rows - 2)
				{
					if (scrollingflag(current_d) && relative_count < current_d.size())
					{
						scrollcount++;
						clear();
						print_scrolling_content(current_d, scrollcount);
						down_scroll_flag = 1;
						forcecursor(rows - 1, 0);
					}
				}
				else
				{
					cursor++;
				}
			}
		}
		if (c == 'A')
		{
			if (relative_count > 0)
			{
				upwards();
				relative_count--;
				if (cursor == 0)
				{
					if (scrollingflag(current_d) && scrollcount > 0 && down_scroll_flag)
					{
						scrollcount--;
						clear();
						print_scrolling_content(current_d, scrollcount);
						home();
					}
				}
				else
				{
					cursor--;
				}
			}
		}
		if (c == 'h' || c == 'H')
		{
			clear();
			left_one.push(HOME);
			make_stack_empty(right_one);
			chdir(HOME.c_str());
			printing_whole_page(HOME);
		}
		if (c == 127 || c == 8)
		{
			if (!(presentworkingdir() == HOME))
			{
				clear();
				string s = presentworkingdir();
				s = s + "/..";
				left_one.push(s);
				make_stack_empty(right_one);
				chdir(s.c_str());
				printing_whole_page(presentworkingdir());
			}
		}
		if (c == 'D')
		{
			string temp = left_one.top();
			if (temp != HOME || (left_one.size() != 1))
			{
				clear();
				left_one.pop();
				right_one.push(temp);
				chdir((left_one.top()).c_str());
				printing_whole_page(presentworkingdir());
			}
		}
		if (c == 'p')
		{
			clear();
			break;
		}
		if (c == 'C')
		{
			if (!(right_one.empty()))
			{
				clear();
				string temp = right_one.top();
				right_one.pop();
				left_one.push(temp);
				chdir(temp.c_str());
				printing_whole_page(presentworkingdir());
			}
		}
		if (c == ':')
		{
			command_mode_flag = 1;
			enter_command_mode(presentworkingdir());
		}
		display_status_bar(cursor, global_status_bar_flag);
	}
	tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
	return 0;
}
void setting_terminal_attributes()
{
	tcgetattr(fileno(stdin), &initialrsettings);
	newrsettings = initialrsettings;
	newrsettings.c_lflag &= ~ICANON;
	newrsettings.c_lflag &= ~ECHO;
	newrsettings.c_cc[VMIN] = 1;
	newrsettings.c_cc[VTIME] = 0;
	tcsetattr(fileno(stdin), TCSANOW, &newrsettings);
}
void display_status_bar(int cursor_pos, int flag)
{
	if (flag == 0)
	{
		char normal_mode[columns] = "NORMAL MODE\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
		save_cursor();
		forcecursor(rows, 0);
		printf("%c[%d;%d;%dm%s%c[%dm", 27, 1, 30, 47, normal_mode, 27, 0);
		restore_cursor_back();
	}
}
void make_stack_empty(stack<string> &s)
{
	while (!(s.empty()))
	{
		s.pop();
	}
}
