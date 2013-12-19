#include <cstdio>
#include <SDL.h>
#include "textscreen.h"

#include "wad.h"

char *launchgame_cmdline_addr;
static txt_window_t *window;
static int systemf(const char *fmt, ...)
{
        char __sys[1024];
        int ret_code;
        va_list args;
        va_start(args, fmt);
        //TODO: CODE
                vsnprintf(__sys, 1023, fmt, args);
                ret_code = system(__sys);
        va_end(args);

        return ret_code;
}

int main(int argc, char *argv[])
{
    if (!TXT_Init())
    {
        fprintf(stderr, "Failed to initialise GUI\n");
        return -1;
    }

    SDL_ShowCursor(0);

    WAD_RebuildPath();

    window = TXT_NewWindow("Single Player");
    TXT_AddWidgets(window,

    		NULL);

    TXT_GUIMainLoop();
    TXT_Shutdown();

    if (launchgame_cmdline_addr)
    {
    	systemf("./odamex -config %s/.odamex/l_odamex.cfg -connect %s", getenv("HOME"), launchgame_cmdline_addr);
    }

	return 0;
}
