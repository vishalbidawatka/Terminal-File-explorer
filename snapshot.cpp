//ROll No: 2018201004
//Name: VISHAL BIDAWATKA
#include "global.h"
string maintext = "";
vector<pair<int, string>> sorteddump;
int snapshot(string source, vector<string> command, string current_working_dir)
{	
	/* nftw travese the whole tree but in an unordered fashion with respect to current directory, 
		also nftw returns the depth at which file is present , so i collected first the list of files
		and folders and the sorted them with respect to their depth and then dumped them in the dump
		file with the space indent = depth of file */
		
	string destination = command[2];
	string_processing(destination);
	string_processing(source);
	FILE *dump = fopen(destination.c_str(), "w");
	if (nftw(source.c_str(), puttingDump, FOPEN_MAX, 0) < 0)
	{
		cout << "error in snapshot";
	}
	else
	{
		sort(sorteddump.begin(), sorteddump.end());
		for (int i = 0; i < sorteddump.size(); i++)
		{
			for (int j = 0; j < sorteddump[i].first; j++)
			{
				fprintf(dump, "\t");
			}
			fprintf(dump, "%s\n", sorteddump[i].second.c_str());
		}
		fclose(dump);
	}
	return 1;
}
int puttingDump(const char *textpath, const struct stat *s, int flag, struct FTW *f)
{
	maintext = maintext + textpath + " " + to_string(f->level) + "\n";
	sorteddump.push_back(make_pair(f->level, textpath));
	return 0;
}