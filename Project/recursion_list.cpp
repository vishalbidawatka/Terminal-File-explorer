#include "global.h"

void recursive_struct_gen(string source,string actual_source ,vector<vector <string> >& global_dir_info)
{
	DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(source.c_str())))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {   string path = "";
        string path_to_be_pushed = "";
        vector<string> current_info;
        if (entry->d_type == DT_DIR) 
        {
			
			if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
		        continue;
           
            path=source+"/"+string(entry->d_name);
            path_to_be_pushed = actual_source+"/"+string(entry->d_name);
            current_info.push_back(string(entry->d_name));
            current_info.push_back("d");
            current_info.push_back(path);
            current_info.push_back(path_to_be_pushed);
            global_dir_info.push_back(current_info);
            recursive_struct_gen(path,path_to_be_pushed,global_dir_info);
               
      } 
        else 
        {
            current_info.push_back(string(entry->d_name));
            current_info.push_back("r");
            current_info.push_back(path+source+"/"+entry->d_name);
            current_info.push_back(path_to_be_pushed+actual_source+"/"+entry->d_name);
             global_dir_info.push_back(current_info);
        }
    }
    closedir(dir);
}
string get_base_name(string source)
{
    char buf[source.size() + 1];
    char *buf2 ;
    strcpy(buf,source.c_str());
    buf2 = basename(buf);
    return string(buf2);


}
string ger_real_path(string fn)
{
    char buf[4096];
    realpath(fn.c_str(),buf);
    return string(buf);
}
