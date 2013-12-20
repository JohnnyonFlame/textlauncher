#include <cstdio>
#include <SDL.h>
#include "textscreen.h"

#include "common.h"
#include "c_cvars.h"
#include "network.h"
#include "panel.h"
#include "wad.h"

static txt_window_t *window, *joinwindow;
char *launchgame_cmdline_addr = NULL;

static void joingame(TXT_UNCAST_ARG(widget), void *user_data)
{
	joinwindow = TXT_NewWindow("Join Game");

    TXT_AddWidgets(joinwindow,
    		TXT_NewButton2("Join Local Servers", NET_LanDiscoveryMenu, NULL),
    		TXT_NewButton2("Join Internet Servers", NET_NetDiscoveryMenu, NULL),
    		TXT_NewButton2("Join Manually", NET_ManualMenu, NULL),
    		NULL);
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
    CVAR_LoadSettings();

    //NET_LanDiscoveryMenu();

    //NET_NetDiscoveryMenu();

    window = TXT_NewWindow("Multi Player");
    TXT_AddWidgets(window,
    		TXT_NewButton2("Configure Player Settings", CVAR_MenuFromList, cl_mp_cvars),
    		TXT_NewButton2("Configure Player Macros", CVAR_MenuFromList, cl_macro_cvars),
    		TXT_NewButton2("Configure Player Misc", CVAR_MenuFromList, cl_misc_cvars),
    		TXT_NewStrut(0,1),
    		TXT_NewButton2("Configure Server", config_server, NULL),
    		TXT_NewButton2("Configure Server Details", CVAR_MenuFromList, sv_misc_cvars),
    		TXT_NewButton2("Configure Server Gameplay", CVAR_MenuFromList, sv_gameplay_cvars),
    		TXT_NewStrut(0,1),
    		TXT_NewButton2("Server Panel", serverpanel, NULL),
    		TXT_NewButton2("Join Game", joingame, NULL),
    		NULL);

    TXT_GUIMainLoop();
    TXT_Shutdown();

    CVAR_SaveSettings();

    if (launchgame_cmdline_addr)
    {
    	systemf("./odamex -config %s/.odamex/l_odamex.cfg -connect %s", getenv("HOME"), launchgame_cmdline_addr);
    }

	return 0;
}
