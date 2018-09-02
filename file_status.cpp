//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
string presentworkingdir()
{
	char currentdirecory[4096];
	getcwd(currentdirecory, sizeof(currentdirecory));
	string s(currentdirecory);
	return s;
}
vector<vector<string>> contentofpwd(string s)
{
	struct dirent **dirent_structure;
	DIR *dir;
	vector<vector<string>> files_info;
	char *file_name;
	char *username;
	unsigned int filesize;
	struct stat filestatus;
	register uid_t userid;
	register gid_t groupid;
	register struct passwd *forusername;
	register time_t modified_time;
	struct group *gro;
	struct tm *date_time;
	char date_time_buffer[40];
	int no_of_files = scandir(s.c_str(), &dirent_structure, NULL, alphasort);
	char filenamebuff[4096];

	for (int i = 0; i < no_of_files; i++)
	{
		vector<string> file_info;
		file_name = dirent_structure[i]->d_name;
		realpath(file_name, filenamebuff);
		if (stat(filenamebuff, &filestatus) == -1)
		{
			cout << "Error in stat of file name: " << filenamebuff << endl;
		}
		userid = filestatus.st_uid;
		groupid = filestatus.st_gid;
		modified_time = filestatus.st_mtime;
		date_time = localtime(&modified_time);
		strftime(date_time_buffer, sizeof(date_time_buffer), " %H:%M:%S %d/%m/%Y", date_time);
		forusername = getpwuid(userid);
		gro = getgrgid(groupid);
		filesize = (int)filestatus.st_size;
		file_info.push_back(forusername->pw_name);
		file_info.push_back(gro->gr_name);
		file_info.push_back(string(date_time_buffer));
		file_info.push_back(permission_of_file(filestatus));
		file_info.push_back(file_name);
		files_info.push_back(file_info);
	}
	return files_info;
}
string permission_of_file(struct stat fstatus)
{
	string s;
	mode_t mode = fstatus.st_mode;
	if (S_ISDIR(mode))
	{
		s.insert(s.end(), 'd');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IRUSR)
	{
		s.insert(s.end(), 'r');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IWUSR)
	{
		s.insert(s.end(), 'w');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IXUSR)
	{
		s.insert(s.end(), 'x');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IRGRP)
	{
		s.insert(s.end(), 'r');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IWGRP)
	{
		s.insert(s.end(), 'w');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IXGRP)
	{
		s.insert(s.end(), 'x');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IROTH)
	{
		s.insert(s.end(), 'r');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IWOTH)
	{
		s.insert(s.end(), 'w');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	if (mode & S_IXOTH)
	{
		s.insert(s.end(), 'x');
	}
	else
	{
		s.insert(s.end(), '-');
	}
	return s;
}