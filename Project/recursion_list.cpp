#include "global.h"

void recursive_struct_gen(string source,vector<vector <string> >& global_dir_info)
{
	DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(source.c_str())))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {   string path = "";
        vector<string> current_info;
        if (entry->d_type == DT_DIR) 
        {
			
			if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
		        continue;
           
            path=source+"/"+string(entry->d_name);
            current_info.push_back(string(entry->d_name));
            current_info.push_back("d");
            current_info.push_back(path);
            global_dir_info.push_back(current_info);
            recursive_struct_gen(path,global_dir_info);
               
      } 
        else 
        {
            current_info.push_back(string(entry->d_name));
            current_info.push_back("r");
            current_info.push_back(path+source+"/"+entry->d_name);
             global_dir_info.push_back(current_info);
        }
    }
    closedir(dir);
}
 
