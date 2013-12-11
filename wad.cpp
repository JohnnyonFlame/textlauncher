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

int max_iwad = 0;
int iwad_value = 0;
char **iwad_dropdown = NULL;

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
					char *ext_buf = strdup(ext);

					char *n;
					for (n = ext_buf; *n != '\0'; n++)
					{
						*n = toupper(*n);
					}

					if (!strcmp(ext_buf, ".WAD"))
					{
						WAD_ProcessWAD("%s/%s", path, ent->d_name);
					}

					free(ext_buf);
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

	WAD_AddPathFmt("%s/.odamex", getenv("HOME"));

	WAD_AddPathFmt(getenv("DOOMWADDIR"));
	WAD_AddPathFmt(getenv("DOOMWADPATH"));
	WAD_AddPathFmt(getenv("HOME"));

	WAD_BuildWadList();

	if (!iwad_dropdown) {
		iwad_dropdown = (char**)malloc(sizeof(*iwad_dropdown) * iwad_list.size());

		int i;
		for (i=0; i<iwad_list.size(); i++)
		{
			iwad_dropdown[i] = strdup(basename(iwad_list.at(i).fname));
		}
	}

	max_iwad = iwad_list.size();
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
