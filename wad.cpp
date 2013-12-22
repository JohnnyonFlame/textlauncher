#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#include <string>
#include <vector>

/* yes, really. */
#define PATH_MAX 4096

#include "wad.h"

using namespace std;

vector<string> wadpath_list;

vector<wad_t> iwad_list; /* internal wads */
vector<wad_t> pwad_list; /* patch wads */

vector<map_t> map_list;

//TODO:: Move these out of here.
int wad_iwad_c = 0;
int wad_iwad_v = 0;
char **wad_iwad_s = NULL;

static void WAD_ClearList(vector<wad_t> wad_vec)
{
	while (!wad_vec.empty())
	{
		if (wad_vec.back().fname)
			free(wad_vec.back().fname);

		wad_vec.pop_back();
	}
}

static void WAD_MapClearList(vector<map_t> map_vec)
{
	while (!map_vec.empty())
	{
		if (map_vec.back().wad)
			free(map_vec.back().wad);

		map_vec.pop_back();
	}
}

void WAD_ProcessWAD(char *fmt, ...)
{
        char buffer[PATH_MAX];

        /* build filename */
        va_list args;
        va_start(args, fmt);
        vsnprintf(buffer, PATH_MAX-1, fmt, args);
        va_end(args);

        /* open file */
    	FILE *file = fopen(buffer, "r");

    	if (file)
    	{
    		wad_t wad_, *wad;

    		if (fread(&wad_.header, sizeof(wad_.header), 1, file)) {
				/* check if internal wad, add it to the right list */
				if (!memcmp(&wad_.header.id, "IWAD", 4))
				{
					iwad_list.push_back(wad_);
					wad = &iwad_list.back();
				}
				else
				{
					pwad_list.push_back(wad_);
					wad = &pwad_list.back();
				}

				wad->active = 0;
				/* we gotta know the name/path of the wad amirite */
				wad->fname = strdup(buffer);
    		}

    		/* close file. */
    		fclose(file);
    	}
}

static void WAD_ParseWadlist(vector<wad_t> wad_list)
{
	int i;
	for (i=0; i<wad_list.size(); i++)
	{
		FILE *f = fopen(wad_list.at(i).fname, "r");
		fseek(f, wad_list.at(i).header.dir_location, SEEK_SET);

		wad_lump_t *lumps = (wad_lump_t*)malloc(sizeof(*lumps) * wad_list.at(i).header.lump_count);
		if (fread(lumps, sizeof(*lumps), wad_list.at(i).header.lump_count, f))
		{
			int j;
			for (j=0; j<wad_list.at(i).header.lump_count; j++)
			{
				if (j < wad_list.at(i).header.lump_count) {
					if (!memcmp(lumps[j+1].name, "THINGS\0\0", 8))
					{
						map_t map;
						memcpy(map.name, lumps[j].name, 8); map.name[8] = '\0';
						map.wad = strdup(basename(wad_list.at(i).fname));
						map.active = 0;

						map_list.push_back(map);
					}
				}
			}
		}

		free(lumps);
		fclose(f);
	}
}

static int WAD_IsValidWAD(char *wad)
{
	char *INVALID_WADS[] =
	{
			"hacx.wad",
			"heretic.wad",
			"hexdd.wad",
			"hexen.wad",
			"strife1.wad",
			"voices.wad",
			"odamex.wad",

			NULL
	};

	int i;
	for (i=0; INVALID_WADS[i] != NULL; i++)
	{
		if (!strcasecmp(wad, INVALID_WADS[i]))
			return 0;
	}

	return 1;
}

void WAD_BuildWadList()
{
	int i;
	for (i=0; i<wadpath_list.size(); i++)
	{
		const char *path = wadpath_list.at(i).c_str();

		DIR *dir = opendir(path);
		struct dirent *ent;

		if (dir) {
			while ((ent = readdir(dir))) {
				char *ext = strrchr(ent->d_name, '.');
				if (ext) {
					if (!strcasecmp(ext, ".WAD"))
					{
						if (WAD_IsValidWAD(basename(ent->d_name)))
							WAD_ProcessWAD("%s/%s", path, ent->d_name);
					}
				}
			}
			closedir(dir);
		}
	}

	WAD_ParseWadlist(iwad_list);
	WAD_ParseWadlist(pwad_list);
}

void WAD_RebuildPath()
{
	//Should only be ran once, so no need to actually clean it.
	/*WAD_ClearList(iwad_list);
	WAD_ClearList(pwad_list);
	WAD_MapClearList(map_list);
	wadpath_list.clear();*/

	WAD_AddPathFmt(".");
	WAD_AddPathFmt("/usr/share/games/doom");
	WAD_AddPathFmt("/usr/local/share/games/doom");
	WAD_AddPathFmt("/usr/local/share/doom");

	if (getenv("HOME")) {
		WAD_AddPathFmt("%s/.odamex", getenv("HOME"));
		WAD_AddPathFmt(getenv("HOME"));
	}

	if (getenv("DOOMWADDIR"))
		WAD_AddPathFmt(getenv("DOOMWADDIR"));

	if (getenv("DOOMWADPATH"))
		WAD_AddPathFmt(getenv("DOOMWADPATH"));

	WAD_BuildWadList();

	int i;
	if (!wad_iwad_s) {
		wad_iwad_s = (char**)malloc(sizeof(*wad_iwad_s) * iwad_list.size());

		for (i=0; i<iwad_list.size(); i++)
		{
			wad_iwad_s[i] = strdup(basename(iwad_list.at(i).fname));
		}
	}

	wad_iwad_c = iwad_list.size();
}

void WAD_AddPathFmt(char *fmt, ...)
{
        char buffer[PATH_MAX];

        va_list args;
        va_start(args, fmt);

        vsnprintf(buffer, PATH_MAX-1, fmt, args);

        if (strlen(buffer) > 0)
                wadpath_list.push_back(buffer);

        va_end(args);
}

void WAD_AddPathSeparator(char *waddirs, int separator)
{
	char *head, *tail;
	char buffer[PATH_MAX];

	tail = waddirs;
	head = strchr(tail, separator);

	while(head)
	{
		memcpy(buffer, tail, head-tail);
		buffer[head-tail] = '\0';

		wadpath_list.push_back(buffer);

		tail = head+1;
		head = strchr(tail, separator);
	}

	wadpath_list.push_back(tail);
}

void MAP_MarkMapActive(char *map, char *wad)
{
	int i;
	for (i=0; i<map_list.size(); i++)
	{
		if (!strcasecmp(map, map_list.at(i).name))
		{
			if (!strcasecmp(wad, map_list.at(i).wad))
			{
				map_list.at(i).active = 1;
				break;
			}
		}
	}
}

char **MAP_PopulateList(char *wad, int &map_count)
{
	map_count = 0;

	//pass 1- count maps
	for (int i=0; i<map_list.size(); i++)
	{
		if (!strcasecmp(map_list.at(i).wad, wad))
			map_count++;
	}


	/*
	 * <off> 0
	 * map01 1
	 * map02 2
	 */

	//intermission: allocate list
	char **list = (char**)malloc(sizeof(char*) * (map_count+2));

	//pass 2- populate list
	list[0] = strdup("<off>");
	list[map_count+1] = NULL;

	for (int i=0, l=1; i<map_list.size(); i++)
	{
		if (!strcasecmp(map_list.at(i).wad, wad)) {
			list[l++] = strdup(map_list.at(i).name);
			if (l > map_count)
				break; //stop on last
		}
	}

	return list;
}
