#include "global.h"
int move_multiple_files(vector<string> s,string current_working_directory)
{	

	string destination = s[s.size()-1];
	string sources = s[1];
	char filenamebuff[1024];
	string_processing(sources);
	string_processing(destination);
	struct stat filestatus;
	realpath(sources.c_str(),filenamebuff);
	if (stat(filenamebuff,&filestatus) == -1)
	{	cout<<"Error in stat of file name: "<<filenamebuff<<endl;
		
	}
	if(S_ISDIR(filestatus.st_mode))
	{
		move_directory(s[1],s[2],s,current_working_directory);
	}
	else
	{
	for(int i = 1; i<s.size()-1;i++)
	{
		move_file(s[i],destination,s,current_working_directory);
	}
	}
	return 1;
}
int move_file(string source, string destination, vector<string> command, string cwd)
{
	rename(source.c_str(),(destination+"/"+source).c_str());

}
int move_directory(string source,string destination, vector<string> command, string current_working_directory)
{

	string_processing(source);
	string_processing(destination);
	copy_directory(source,destination,command,current_working_directory);
	deldir_v2(source,current_working_directory);
}

