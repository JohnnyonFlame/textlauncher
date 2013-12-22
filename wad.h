#ifndef WAD_H_
#define WAD_H_

/*
 * You can find the doom WAD specs at:
 * http://doom.wikia.com/wiki/WAD (14:47, 09/12/2013)
 *
 * Assuming every map must have a name[8] = "THINGS\0\0" lump following it,
 * we can use that to determine map lumps and list them.
 */
typedef struct {
	__int32_t id;
	__int32_t lump_count;
	__int32_t dir_location;
} wad_header_t;

typedef struct {
	int active;
	char *fname;
	wad_header_t header;
} wad_t;

typedef struct {
	__int32_t file_location;
	__int32_t file_size;
	__int8_t  name[8];
} wad_lump_t;

typedef struct {
	int active;

	char *wad;
	char name[9];
} map_t;

extern int wad_iwad_c;
extern int wad_iwad_v;
extern char **wad_iwad_s;

void WAD_RebuildPath();
void WAD_AddPathFmt(char *fmt, ...);
void WAD_AddPathSeparator(char *waddirs, int separator);

void MAP_MarkMapActive(char *map, char *wad);
char **MAP_PopulateList(char *wad, int &map_count);

#endif /* WAD_H_ */
