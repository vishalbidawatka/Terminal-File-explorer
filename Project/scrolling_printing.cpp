//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
int print_content(std::vector<std::vector<string>> &filesinfo)
{
	if (filesinfo.size() <= rows - 1)
	{
		for (int i = 0; i < filesinfo.size(); i++)
		{
			for (int j = 0; j < filesinfo[i].size(); j++)
			{
				cout << filesinfo[i][j] << " ";
			}
			cout << i << endl;
		}
	}
	else
	{ //cout<<"ROWS"<<rows;
		for (int i = 0; i < rows - 1; i++)
		{
			for (int j = 0; j < filesinfo[i].size(); j++)
			{
				cout << filesinfo[i][j] << " ";
			}
			cout << i << endl;
		}
	}
}
void print_scrolling_content(std::vector<std::vector<string>> &filesinfo, int cursor_pos)
{
	for (int i = cursor_pos; i < rows + cursor_pos - 1; i++)
	{
		for (int j = 0; j < filesinfo[i].size(); j++)
		{
			cout << filesinfo[i][j] << " ";
		}
		cout << i << endl;
	}
}
int scrollingflag(vector<vector<string>> &a)
{
	if (a.size() <= rows)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
void printing_whole_page(string path)
{
	clear();
	vector<vector<string>> new_d = contentofpwd(path);
	current_d = new_d;
	print_content(current_d);
	home();
	relative_count = 0;
	cursor = 0;
	scrollcount = 0;
}
void print_search_page(string cwd, vector<vector<string>> answers)
{
	clear();
	for (int i = 0; i < answers.size(); i++)
	{
		cout << answers[i][0] << " " << answers[i][1] << " " << answers[i][3] << " " << endl;
	}
	home();
	relative_count = 0;
	cursor = 0;
	scrollcount = 0;
}
