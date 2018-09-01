#include "global.h"

int copy_file(string source, string destination, vector<string> command, string cwd)
{	
    char ch;
	FILE *from, *to;
    int end_of_file;
	struct stat filestatus;
	stat(source.c_str(),&filestatus);
	mode_t mode = filestatus.st_mode;
	from = fopen(source.c_str(),"r");
	if(from == NULL)
	{
		return 0;
	}
	to = fopen(destination.c_str(),"w");
	if(to == NULL)
	{

		return 0;
	}
    fseek(from,0L,SEEK_END);
    end_of_file = ftell(from);
    fseek(from,0L,SEEK_SET);
	while(end_of_file-- )
	{   
        ch = fgetc(from);
		fputc(ch,to);
       
	}
	fclose(from);
	fclose(to);
    chmod(destination.c_str(),mode);
	return 1;

}

int copy_multiple_files(vector<string> s,string current_working_directory)
{	

	string destination = s[s.size()-1];
	string sources = s[1];
	char filenamebuff[1024];
	string_processing(sources);
	struct stat filestatus;
	realpath(sources.c_str(),filenamebuff);
	if (stat(filenamebuff,&filestatus) == -1)
	{	cout<<"Error in stat of file name: "<<filenamebuff<<endl;
		
	}
	if(S_ISDIR(filestatus.st_mode))
	{
		copy_directory(s[1],s[2],s,current_working_directory);
	}
	else
	{
	for(int i = 1; i<s.size()-1;i++)
	{
		create_files(s[i],destination,s,current_working_directory);
	}
	}
	return 1;
}

int copy_directory(string source,string destination, vector<string> command, string current_working_directory)

{
	vector< vector < string > > global_dir_info;
	string_processing(source);
	string real_path_of_source = ger_real_path(source);
	recursive_struct_gen(source,get_base_name(source),global_dir_info);
	string_processing(destination);
	char buf[source.size() + 1];
	char *buf2 ;
	strcpy(buf,source.c_str());
	buf2 = basename(buf);
	//cout<<string(buf2)<<endl;
	mkdir((destination+"/"+string(buf2)).c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//cout<<destination+"/"+string(buf2)<<endl;
	//chdir(destination.c_str());
	//cout<<presentworkingdir()<<end;

	//cout<<get_base_name(source)<<source<<endl;
	for(int i = 0 ; i < global_dir_info.size() ; i++)
	{	

		//cout<<global_dir_info[i][2]<<" "<<global_dir_info[i][3]<<endl;
	if(get_base_name(source) == source)
	{
		if(global_dir_info[i][1] == "r")
		{
			copy_file(global_dir_info[i][2],destination+"/"+global_dir_info[i][2],command,current_working_directory);
		}
		else
		{
			mkdir((destination+"/"+global_dir_info[i][2]).c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}
	}
	else
	{

		if(global_dir_info[i][1] == "r")
		{
			copy_file(global_dir_info[i][2],destination+"/"+global_dir_info[i][3],command,current_working_directory);
		}
		else
		{
			mkdir((destination+"/"+global_dir_info[i][3]).c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}

	}


	}

}