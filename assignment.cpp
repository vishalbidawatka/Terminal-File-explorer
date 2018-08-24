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


using namespace std;
void windowsize(int& a, int& b);
void printvector(vector<vector< string > >& filesinfo,int start, int end);
int print_content(std::vector<std::vector< string > >& filesinfo);
void print_scrolling_content(std::vector<std::vector< string > >& filesinfo, int cursor_pos); 
int scrollingflag(vector<vector<string> >& a);
int rows,columns;
string HOME;

struct termios initialrsettings,newrsettings;
#define clear() printf("\033[H\033[J")
#define home() printf("\033[1;0H")
#define downwards() printf("\033[B")
#define upwards() printf("\033[A")
#define scrollup() printf("\033[M")
#define forcecursor(x,y) printf("\033[%d;%df",x,y)


#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108


string permission_of_file(struct stat fstatus);
string presentworkingdir()
{
    char currentdirecory[4096];
	getcwd(currentdirecory,sizeof(currentdirecory));
	string s(currentdirecory);
	return s;

}


vector<vector<string > > contentofpwd(string s)
{
	// char char_array[direcname.size() + 1]; 
	// strcpy(char_array, direcname.c_str()); 
	struct dirent **dirent_structure;
	DIR *dir;
	vector<vector <string> > files_info; 
	//struct dirent **dirent_structure;
	char * file_name;
	char *username;
	
	//dir = opendir(s.c_str());
	unsigned int filesize;
	struct stat filestatus;
	register uid_t userid;
	register  gid_t groupid;
	register struct passwd *forusername;
	register time_t modified_time;
	struct group *gro;
	struct tm *date_time;
	char date_time_buffer[40];
	int no_of_files = scandir(s.c_str(),&dirent_structure,NULL,alphasort);
	//cout<<"no_of_files"<<no_of_files;
	char filenamebuff[4096];
	for(int i =0 ; i<no_of_files ; i++)
	{
	// {	cout<<"before1";
		vector<string> file_info ;
	// 	cout<<"before";
		file_name = dirent_structure[i]->d_name;
		realpath(file_name,filenamebuff);
	// 	cout<<"before";
	// 	char char_array[s.length()+1]; 
	// 	strcpy(char_array,s.c_str());
	// 	strcat(char_array,"/");
	// 	strcat(char_array,file_name);

		if (stat(filenamebuff,&filestatus) == -1)
		{	cout<<"file name"<<filenamebuff<<endl;
			cout<<"lag gaye"<<endl;
		}
		userid = filestatus.st_uid;
		groupid = filestatus.st_gid;
		modified_time = filestatus.st_mtime;
		date_time = localtime(&modified_time);
		strftime(date_time_buffer,sizeof(date_time_buffer),   " %H:%M:%S %d/%m/%Y" , date_time);
		
		forusername = getpwuid(userid);
		gro = getgrgid(groupid);
		//cout<<forusername->pw_name<<" "<<gro->gr_name<<" "<<string(date_time_buffer)<<" "<<permission_of_file(filestatus)<<" ";
		filesize = (int)filestatus.st_size;


		file_info.push_back(forusername->pw_name);
		file_info.push_back(gro->gr_name);
		file_info.push_back(string(date_time_buffer));
		file_info.push_back(permission_of_file(filestatus));
		//std::string size = std::to_string(filesize);
		//file_info.push_back(filesize);
		file_info.push_back(file_name);



		

		//cout<<filesize<<" "<<file_name<<" "<<endl;

		files_info.push_back(file_info);
		//cout<<i<<endl;
	}
	return files_info;

}
string permission_of_file(struct stat fstatus)
{	
	string s;
	mode_t mode = fstatus.st_mode;
	if(S_ISDIR(mode))
	{
		s.insert(s.end(),'d');

	}
	//cout<<mode<<"mode"<<endl;
	if(mode & S_IRUSR)
	{
		s.insert(s.end(),'r');
		
	}
	else
	{
		s.insert(s.end(),'-');
	}
	if(mode & S_IWUSR)
	{
		s.insert(s.end(),'w');
	}
	else
	{
		s.insert(s.end(),'-');
	
	}
	if(mode & S_IXUSR)
	{
		s.insert(s.end(),'x');
	}
	else
	{
		s.insert(s.end(),'-');
	}
	if(mode & S_IRGRP)
	{
		s.insert(s.end(),'r');
	}
	else
	{
		s.insert(s.end(),'-');
	}
	if(mode & S_IWGRP)
	{
		s.insert(s.end(),'w');
	}
	else
	{
		s.insert(s.end(),'-');
	}
	if(mode & S_IXGRP)
	{
		s.insert(s.end(),'x');
	}
	else
	{
		s.insert(s.end(),'-');
	}
	if(mode & S_IROTH)
	{
		s.insert(s.end(),'r');
	}
	else
	{
		s.insert(s.end(),'-');
	}
	if(mode & S_IWOTH)
	{
		s.insert(s.end(),'w');
	}
	else
	{
		s.insert(s.end(),'-');
	}
	if(mode & S_IXOTH)
	{
		s.insert(s.end(),'x');
	}
	else
	{
		s.insert(s.end(),'-');
	}
	return s;
}
void windowsize(int& a, int& b)
{

	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    a = w.ws_row;
    b = w.ws_col;
}

int main(int argc, char const *argv[])
{	char c;
	//contentofpwd();
	
	tcgetattr(fileno(stdin), &initialrsettings);
	newrsettings = initialrsettings;
	newrsettings.c_lflag &= ~ICANON;
	newrsettings.c_lflag &= ~ECHO;
	newrsettings.c_cc[VMIN] = 1;
	newrsettings.c_cc[VTIME] = 0;
	tcsetattr(fileno(stdin), TCSANOW, &newrsettings);
	
	windowsize(rows,columns);
	HOME = presentworkingdir();
	vector<vector< string> > current_d = contentofpwd(HOME);
	
	struct stat filestatus_2;
	

	//forcecursor(rows,columns);
	//scroll();
	int i = 0;
	clear();
	print_content(current_d);
	int count = 0;
	home();
	while(1)
	{	
		
		windowsize(rows,columns);
		c = (int)getchar();
		if(c == '\n')

		{	int retrieval_int = i+count;
			if(current_d[i][3][0] == 'd')
			{
				if(!(presentworkingdir() == HOME && current_d[retrieval_int][4] == ".."))
				{
				clear();
				char buf[4096];
				realpath(current_d[retrieval_int][4].c_str(),buf);
				//cout<<buf<<endl;
				stat(buf,&filestatus_2);
				chdir(buf);
				count = 0; 
				vector<vector< string> > new_d = contentofpwd(string(buf));
				current_d = new_d;
				print_content(current_d);

				}
				home();
				i = 0 ;
				count = 0;
			}
			else
			{	

				//int storing_i = i;
				char buf2[4096];
				realpath(current_d[retrieval_int][4].c_str(),buf2);
				strcat(buf2,"\0");
				int pid = fork();
				if (pid == 0) {
				execl("/usr/bin/xdg-open", "xdg-open", buf2, (char *)0);
				exit(1);
				}
				
			}
			//forcecursor(i,0);
		}
		if(c == 'B')
		{	

			downwards();
			
			if(i==rows)
			{
				if(scrollingflag(current_d) && rows+count<current_d.size())
				{
					count++;
					clear();
					print_scrolling_content(current_d,count);
					continue;

				}
				continue;
			}
			i++;
			//cout<<i+count<<" "<<i;
			//forcecursor(i,0);
		}
		if(c == 'A')
		{	
			upwards();
			if(i == 1)
			{
				if(scrollingflag(current_d) && count>-1)
				{
					count--;
					clear();
					print_scrolling_content(current_d,count);
					home();
					continue;
				}
				continue;
			}
			if(i != 0)
			i--;
			//cout<<i+count<<" "<<i;
			//forcecursor(i,0);
		}
	
		if(c == 'p')
		{
			clear();
			break;

		}
		if(c== 'h' || c== 'H')
		{		
				clear();
				chdir(HOME.c_str());
				count = 0; 
				vector<vector< string> > new_d = contentofpwd(HOME);
				current_d = new_d;
				print_content(current_d);
				home();
				i = 0 ;
		}
		if(c== 127 || c== 8)
		{		if(!(presentworkingdir() == HOME)){
				clear();
				string s = presentworkingdir();
				s = s+"/..";
				chdir(s.c_str());
				count = 0; 
				vector<vector< string> > new_d = contentofpwd(presentworkingdir());
				current_d = new_d;
				print_content(current_d);
				home();
				i = 0 ;
			}
		}

	}
	tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
	

	return 0;
}
int print_content(std::vector<std::vector< string > >& filesinfo)
{
	if(filesinfo.size()<=rows)
	{
		for(int i = 0 ; i<filesinfo.size(); i++)
		{

		for(int j =0; j<filesinfo[i].size(); j++)
		{

			cout<<filesinfo[i][j]<<" ";


		}

		cout<<i<<endl;

		}
	}
	else
	{	//cout<<"ROWS"<<rows;
		for(int i = 0 ; i<rows-1; i++)
		{

		for(int j =0; j<filesinfo[i].size(); j++)
		{

			cout<<filesinfo[i][j]<<" ";


		}

		cout<<i<<endl;

		}

	}

}
void print_scrolling_content(std::vector<std::vector< string > >& filesinfo, int cursor_pos)
{


	for(int i = cursor_pos ; i<rows+cursor_pos; i++)
		{

		for(int j =0; j<filesinfo[i].size(); j++)
		{

			cout<<filesinfo[i][j]<<" ";


		}

		cout<<i<<endl;

		}
	}
	

int scrollingflag(vector<vector<string> >& a)
{
	if(a.size()<=rows)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}




// void printvector(std::vector<std::vector< string > >& filesinfo,int start, int end)
// {
// 	for(int i = start ; i<=end ; i++)
// 	{

// 		for(int j =0; j<filesinfo[i].size(); j++)
// 		{

// 			cout<<filesinfo[i][j]<<" ";


// 		}

// 		cout<<endl;

// 	}






