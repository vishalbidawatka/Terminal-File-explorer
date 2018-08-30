#include <unistd.h>
#include <stdio.h>
#include <string>
#include<iostream>
#include<dirent.h>
#include<vector>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <termios.h>
#include <bits/stdc++.h>
#include <sys/ioctl.h>
#include <stack>
#include<fcntl.h>
#include <ftw.h>

using namespace std;




#define clear_line() printf("%c[2K",27);
#define clear() printf("\033[H\033[J")
#define home() printf("\033[1;0H")
#define downwards() printf("\033[B")
#define upwards() printf("\033[A")
#define scrollup() printf("\033[M")
#define forcecursor(x,y) printf("\033[%d;%df",x,y)
#define save_cursor() printf("\033[s")
#define restore_cursor_back() printf( "\0338");





string presentworkingdir();
vector<vector<string > > contentofpwd(string s);
void windowsize(int& a, int& b);
void printvector(vector<vector< string > >& filesinfo,int start, int end);
int print_content(std::vector<std::vector< string > >& filesinfo);
void print_scrolling_content(std::vector<std::vector< string > >& filesinfo, int cursor_pos); 
int scrollingflag(vector<vector<string> >& a);
void display_status_bar(int cursor_pos, int flag=0);
void setting_terminal_attributes();
void make_stack_empty(stack<string>& s);
string get_command(string current_working_directory);
void enter_command_mode(string current_working_directory);
void exit_command_mode(string current_working_directory);
string permission_of_file(struct stat fstatus);
vector<string> split_command(string command);
void printing_whole_page(string path);
int delv(vector<string> s, string cwd);
void execute_command(vector<string> s , string current_working_directory );
int unlinkv(const char *path, const struct stat *sb, int dn, struct FTW *buf);
int deldir(vector<string> s, string cwd);
int create_files(string file_name,string destination ,vector<string> s,string current_working_directory);
int create_multiple_files(vector<string> s,string current_working_directory);

extern struct termios initialrsettings,newrsettings,initial_command_settings,new_commandM_settings;
extern stack<string> left_one, right_one;
extern int global_status_bar_flag ;
extern int rows,columns;
extern int cursor;
extern int relative_count;
extern int command_mode_flag ;
extern int scrollcount ;
extern vector<string> seprated_command;

extern string HOME ;
extern vector<vector< string> > current_d;
