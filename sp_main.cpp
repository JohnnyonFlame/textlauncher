#include <cstdio>
#include <SDL.h>
#include "textscreen.h"

#include "common.h"
#include "wad.h"
#include "iwad_selector.h"

int main(int argc, char *argv[])
{
    if (!TXT_Init())
    {
        fprintf(stderr, "Failed to initialise GUI\n");
        return -1;
    }

    SDL_ShowCursor(0);

    WAD_RebuildPath();

    IWAD_CreateMenu();

    TXT_GUIMainLoop();
    TXT_Shutdown();

    if (iwad_launch_params)
    {
    	systemf("./odamex %s", iwad_launch_params);
    }

	return 0;
}
