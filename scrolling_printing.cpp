//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
int print_content(std::vector<std::vector<string>> &filesinfo)
{
	//this prints the content of 2d vector to screen and manages overflow of the screen.
	if (filesinfo.size() <= rows - 1)
	{
		for (int i = 0; i < filesinfo.size(); i++)
		{
			cout << setw(3) << i + 1 << "."
				 << " ";
			for (int j = 0; j < filesinfo[i].size(); j++)
			{
				cout << filesinfo[i][j] << " ";
			}
			cout << endl;
		}
	}
	else
	{ 
		for (int i = 0; i < rows - 1; i++)
		{
			cout << setw(3) << i + 1 << "."
				 << " ";
			for (int j = 0; j < filesinfo[i].size(); j++)
			{
				cout << filesinfo[i][j] << " ";
			}
			cout << endl;
		}
	}
}
void print_scrolling_content(std::vector<std::vector<string>> &filesinfo, int cursor_pos)
{	
	//this actually slices the vector according to buffer and cursor position.

	for (int i = cursor_pos; i < rows + cursor_pos - 1; i++)
	{
		cout << setw(3) << i + 1 << "."
			 << " ";
		for (int j = 0; j < filesinfo[i].size(); j++)
		{
			cout << filesinfo[i][j] << " ";
		}
		cout << endl;
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
	//Printing search results.

	clear();
	for (int i = 0; i < answers.size(); i++)
	{
		cout << answers[i][0] << " " << answers[i][1] << " " << answers[i][3] << " " << endl;
	}
	cout << endl<< endl;
	cout << "PRESS ESC TO GO BACK";
	home();
	relative_count = 0;
	cursor = 0;
	scrollcount = 0;
}
