#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include <string>

#include "textscreen.h"
#include "wad.h"

//ugly hack!
extern std::vector<wad_t> pwad_list;

char *iwad_launch_params = NULL;

static int  iwad_skill_v = 2;
static char *iwad_skill_s[] = {
		"I'm too young to die",
		"Hey, not too rough",
		"Hurt me plenty",
		"Ultra-Violence",
		"Nightmare!"
};

static int  iwad_warp_v = 0, iwad_warp_c = 0;
static char **iwad_warp_s = NULL;

static int iwad_nomonsters_v = 0;
static int iwad_fastmonsters_v = 0; //-s
static int iwad_respmonsters_v = 0; //-s

static char *iwad_cmdline_s[] = {
		strdup(""),
		strdup(""),
		strdup("")
};

static char *iwad_lastiwad;

txt_window_t *window;

#define strconcat(buf, size, fmt, args...) snprintf(buf+strlen(buf), size-strlen(buf), fmt, args)

void IWAD_FinishAdvMenu(TXT_UNCAST_ARG(widget), void *user_data)
{
	char buffer[1024] = {'\0'};
	strconcat(buffer, 1024, "./odamex -iwad %s", iwad_lastiwad);

	if (iwad_warp_v)
		strconcat(buffer, 1024, " -warp %i", iwad_warp_v);

	strconcat(buffer, 1024, " -skill %i", iwad_skill_v+1);
	if (iwad_nomonsters_v)
		strconcat(buffer, 1024, " -nomonsters", 0);
	if (iwad_fastmonsters_v)
		strconcat(buffer, 1024, " -fast", 0);
	if (iwad_respmonsters_v)
		strconcat(buffer, 1024, " -respawn", 0);

	int active = 0;

	for (int i=0; i<pwad_list.size(); i++)
	{
		if (pwad_list.at(i).active)
		{
			if (!active) {
				strconcat(buffer, 1024, " -file", 0);
				active = 1;
			}
			strconcat(buffer, 1024, " %s", basename(pwad_list.at(i).fname));
		}
	}

	if (strlen(iwad_cmdline_s[0]) > 0)
		strconcat(buffer, 1024, " %s", iwad_cmdline_s[0]);
	if (strlen(iwad_cmdline_s[1]) > 0)
		strconcat(buffer, 1024, " %s", iwad_cmdline_s[1]);
	if (strlen(iwad_cmdline_s[2]) > 0)
		strconcat(buffer, 1024, " %s", iwad_cmdline_s[2]);

	iwad_launch_params = strdup(buffer);

	printf("launching: %s\n", buffer);

	TXT_ExitMainLoop();
}

#undef strconcat

static void IWAD_AdvMenu(TXT_UNCAST_ARG(widget), void *user_data)
{
	TXT_CAST_ARG(txt_window_t, widget);
	txt_window_t         *dialog;
	txt_table_t          *table;
	txt_window_action_t  *act;

	iwad_lastiwad = strdup(((txt_button_t*)TXT_GetSelectedWidget(&window->table))->label);
	char title_buf[64];
	snprintf(title_buf, 64, "Adv. Options (%s)", iwad_lastiwad);


	dialog = TXT_NewWindow(title_buf);

	//de-populate iwad_maplist and delete it.
	if (iwad_warp_s)
	{
		for (int i=0; iwad_warp_s[i] != NULL; i++) {
			free(iwad_warp_s[i]);
		}
		free(iwad_warp_s);
	}

	iwad_warp_s = MAP_PopulateList(iwad_lastiwad, iwad_warp_c);

	table =  TXT_NewTable(2);
	TXT_AddWidget(dialog, TXT_NewSeparator("Warp"));
	TXT_AddWidget(dialog, table);
	TXT_AddWidgets(table, TXT_NewLabel("Warp: "), TXT_NewDropdownList(&iwad_warp_v, iwad_warp_s, iwad_warp_c+1), NULL);
	TXT_AddWidgets(table, TXT_NewLabel("Skill: "), TXT_NewDropdownList(&iwad_skill_v, iwad_skill_s, 5), NULL);

	TXT_AddWidget(dialog, TXT_NewSeparator("Monsters"));

	TXT_AddWidgets(dialog, TXT_NewCheckBox("No Monsters", &iwad_nomonsters_v), NULL);
	TXT_AddWidgets(dialog, TXT_NewCheckBox("Fast Monsters", &iwad_fastmonsters_v), NULL);
	TXT_AddWidgets(dialog, TXT_NewCheckBox("Respawning Monsters", &iwad_respmonsters_v), NULL);

	if (pwad_list.size() > 0) {
		TXT_AddWidget(dialog, TXT_NewSeparator("Active PWADs"));

		table =  TXT_NewTable(1);
		TXT_AddWidget(dialog, TXT_NewScrollPane(0, (pwad_list.size() > 3) ? 3 : pwad_list.size(), table));

		for(int i=0; i<pwad_list.size(); i++)
		{
			TXT_AddWidget(table, TXT_NewCheckBox(pwad_list.at(i).fname, &pwad_list.at(i).active));
		}
	}

	TXT_AddWidget(dialog, TXT_NewSeparator("Extra Command Lines"));
	TXT_AddWidget(dialog, TXT_NewInputBox(&iwad_cmdline_s[0], 50));
	TXT_AddWidget(dialog, TXT_NewInputBox(&iwad_cmdline_s[1], 50));
	TXT_AddWidget(dialog, TXT_NewInputBox(&iwad_cmdline_s[2], 50));

	TXT_SignalConnect(act = TXT_NewWindowAction(KEY_ENTER, "Launch"), "pressed", IWAD_FinishAdvMenu, NULL);
	TXT_SetWindowAction(dialog, TXT_HORIZ_CENTER, act);
}

void IWAD_SelectIWAD(TXT_UNCAST_ARG(widget), void *user_data)
{
	if (iwad_launch_params)
		return;

	char buffer[1024];
	snprintf(buffer, 1024, "./odamex -iwad %s", (((txt_button_t*)TXT_GetSelectedWidget(&window->table))->label));

	iwad_launch_params = strdup(buffer);
	TXT_ExitMainLoop();
	//TODO:: ALL
}

void IWAD_CreateMenu()
{
	txt_table_t *table;
	txt_window_action_t* act;

	window = TXT_NewWindow("Choose IWAD");


	table = TXT_NewTable(2);
	TXT_SignalConnect(act = TXT_NewWindowAction(KEY_SPACE, "Adv."), "pressed", IWAD_AdvMenu, NULL);
	TXT_SetWindowAction(window, TXT_HORIZ_CENTER, act);

	for (int i=0; i< wad_iwad_c; i++)
	{
		txt_button_t *btn;
		TXT_AddWidget(window, btn = TXT_NewButton2(wad_iwad_s[i], IWAD_SelectIWAD, NULL));
		TXT_SetWidgetAlign(btn, TXT_HORIZ_CENTER);
	}
}
