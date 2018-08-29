#include "global.h"
int delv(vector<string> s, string cwd)

{
	char buf[4096];
	realpath(s[1].c_str(),buf);
	//cout<<buf;
	if(remove(s[1].c_str()) != 0)
	{
		perror("File deletion failed");
	}
	else
	{
		cout<< "File deleted successfully";
	}
	return 0;

}
int deldir(vector<string> s, string cwd)
{


	char buf[4096];
	realpath(s[1].c_str(),buf);
	nftw(buf,unlinkv,64,FTW_DEPTH | FTW_PHYS);
}
int unlinkv(const char *path, const struct stat *sb, int dn, struct FTW *buf)
{
    int return_value = remove(path);

    if (return_value)
        perror(path);

    return return_value;
}