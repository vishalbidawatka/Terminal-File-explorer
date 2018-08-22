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





struct termios initialrsettings,newrsettings;
#define clear() printf("\033[H\033[J")
#define home() printf("\033[1;0H")
#define downwards() printf("\033[B")
#define upwards() printf("\033[A")
#define scroll() printf("\033[r")

#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108
using namespace std;

// cout<<a;
// newrsettings = initialrsettings;
// newrsettings.c_1flag = ~ICANON;
// newrsettings.MIN  = 1;
// newrsettings.TIME = 0;
string permission_of_file(struct stat fstatus);
string presentworkingdir()
{
    char currentdirecory[4096];
	getcwd(currentdirecory,sizeof(currentdirecory));
	string s(currentdirecory);
	return s;

}

struct dirent **dirent_structure;
void contentofpwd(string s)
{
	// char char_array[direcname.size() + 1]; 
	// strcpy(char_array, direcname.c_str()); 
	DIR *dir;
	vector<string> files;
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
	for(int i =0;i<no_of_files;i++)
	{
		file_name = dirent_structure[i]->d_name;
		stat(file_name,&filestatus);
		userid = filestatus.st_uid;
		groupid = filestatus.st_gid;
		modified_time = filestatus.st_mtime;
		date_time = localtime(&modified_time);
		strftime(date_time_buffer,sizeof(date_time_buffer),   " %H:%M:%S %d/%m/%Y" , date_time);
		
		forusername = getpwuid(userid);
		gro = getgrgid(groupid);
		cout<<forusername->pw_name<<" "<<gro->gr_name<<" "<<string(date_time_buffer)<<" "<<permission_of_file(filestatus)<<" ";


		filesize = (unsigned int)filestatus.st_size;

		cout<<filesize<<" "<<file_name<<" "<<endl;



	}
	// while ((dirent_structure=scandir(dir,alphasort)) != NULL) 
	// {
	// 	file_name =  dirent_structure->d_name;
	// 	stat(file_name,&filestatus);
	// 	userid = filestatus.st_uid;
	// 	groupid = filestatus.st_gid;
	// 	modified_time = filestatus.st_mtime;
	// 	date_time = localtime(&modified_time);
	// 	strftime(date_time_buffer,sizeof(date_time_buffer),   " %H:%M:%S %d/%m/%Y" , date_time);
		
	// 	forusername = getpwuid(userid);
	// 	gro = getgrgid(groupid);
	// 	cout<<forusername->pw_name<<" "<<gro->gr_name<<" "<<string(date_time_buffer)<<" "<<permission_of_file(filestatus)<<" ";


	// 	filesize = (unsigned int)filestatus.st_size;

	// 	cout<<filesize<<" "<<file_name<<" "<<endl;
		       
	// }
	//return files;
}
string permission_of_file(struct stat fstatus)
{	
	string s;
	mode_t mode = fstatus.st_mode;
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
static int kbget(void)
{
    int c;

    c = getchar();
    return c;
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
	clear();
	contentofpwd(presentworkingdir());
	home();
	int i =0;
	while(1)
	{	
		c = (int)getchar();
		if(c == '\n')

		{
			char buf[4096];
			realpath(dirent_structure[i]->d_name,buf);
			
			clear();
			cout<<string(buf)<<endl;
			contentofpwd(string(buf));
			home();
			i = -1 ;
			
		}
		
		
		if(c == 'B')
		{	
			downwards();
			scroll();
			i++;
		}
		if(c == 'A')
		{	
			upwards();
			i--;
		}
	
		if(c == 'p')
		{

			break;

		}

	}
	tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
	

	return 0;
}