#include <cstdio>
#include <SDL.h>
#include "textscreen.h"

#include "common.h"
#include "wad.h"

int main(int argc, char *argv[])
{
    if (!TXT_Init())
    {
        fprintf(stderr, "Failed to initialise GUI\n");
        return -1;
    }

    SDL_ShowCursor(0);

    WAD_RebuildPath();

    TXT_GUIMainLoop();
    TXT_Shutdown();

    /*if (launchgame_cmdline_addr)
    {
    	systemf("./odamex -config %s/.odamex/l_odamex.cfg -connect %s", getenv("HOME"), launchgame_cmdline_addr);
    }*/

	return 0;
}
