//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
int delv(vector<string> s, string cwd)
{	
	//removes single file.
	
	char buf[4096];
	realpath(s[1].c_str(), buf);
	remove(buf);
	return 0;
}
int deldir(vector<string> s, string cwd)
{	
	//nftw will traverse the whole directory tree and will call the unlinkv function for each call.

	char buf[4096];
	realpath(s[1].c_str(), buf);
	nftw(buf, unlinkv, 64, FTW_DEPTH | FTW_PHYS);
}
int unlinkv(const char *path, const struct stat *sb, int dn, struct FTW *buf)
{
	int return_value = remove(path);
	if (return_value)
		perror(path);
	return return_value;
}
int deldir_v2(string s, string cwd)
{
	char buf[4096];
	realpath(s.c_str(), buf);
	nftw(buf, unlinkv, 64, FTW_DEPTH | FTW_PHYS);
}