#include "global.h"

int create_files(string file_name,string destination ,vector<string> s,string current_working_directory)
{

	char buf[4096];
	if(destination == ".")
	{
		
		chdir(current_working_directory.c_str());
		int a = creat(file_name.c_str(),S_IRWXG);
		// if(a == 0)
		// {
		// 	perror(file_name.c_str());
		// }
		// else
		// {
		// 	cout<<"File created succesfully";
		// }
		chdir(HOME.c_str());

	}
	else if(destination[0] == '~')
	{	cout<<destination<<"destination"<<endl;
		destination.erase(0,2);
		cout<<destination<<endl;

		realpath(destination.c_str(),buf);
		strcat(buf,"/\0");
		int b = chdir(buf);
		//cout<<buf<<endl;

		int a = creat(file_name.c_str(),S_IRWXG);
		//cout<<b<<" "<<a;
		// if(a==0)
		// {
		// 	perror(file_name.c_str());
		// }
		// else
		// {
		// 	cout<<"File created succesfully";
		// }
		chdir(HOME.c_str());

	}
	else if(destination[0] == '/')
	{	
		destination.erase(0,1);
		realpath(destination.c_str(),buf);
		chdir(buf);
		int a = creat(file_name.c_str(),S_IRWXG);
		// if(a == 0)
		// {
		// 	perror(file_name.c_str());
		// }
		// else
		// {
		// 	cout<<"File created succesfully";
		// }
		chdir(HOME.c_str());
	}
	else
	{
		realpath(destination.c_str(),buf);
		chdir(buf);
		int a = creat(file_name.c_str(),S_IRWXG);
		// if(a == 0)
		// {
		// 	perror(file_name.c_str());
		// }
		// else
		// {
		// 	cout<<"File created succesfully";
		// }
		chdir(HOME.c_str());




	}

	return 0;

}

int create_multiple_files(vector<string> s,string current_working_directory)
{
	string destination = s[s.size()-1];
	for(int i = 1; i<s.size()-1;i++)
	{
		create_files(s[i],destination,s,current_working_directory);
	}

}

