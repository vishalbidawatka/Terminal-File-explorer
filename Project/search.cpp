#include "global.h"
int search_file(string source , vector<string> command , string current_working_directory )
{
	vector<vector < string > > whole_directory_struct;
	vector<vector < string > > answers;
	chdir(current_working_directory.c_str());
	recursive_struct_gen(current_working_directory,get_base_name(current_working_directory),whole_directory_struct);
	for(int i = 0 ; i < whole_directory_struct.size() ; i++)
	{
		if(whole_directory_struct[i][0] == source)
		{
			answers.push_back(whole_directory_struct[i]);
		}

	}
	print_search_page(current_working_directory,answers);
	return 1;

}

