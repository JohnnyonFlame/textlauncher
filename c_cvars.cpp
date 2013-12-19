#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include <string>

#include "textscreen.h"
#include "panel.h"
#include "c_cvars.h"
#include "wad.h"

using namespace std;

static txt_window_t* window;

void CVAR_NewDialog(TXT_UNCAST_ARG(widget), void *user_data)
{
	TXT_CAST_ARG(txt_button_t, widget);
	txt_window_t* dialog = TXT_NewWindow(widget->label);

	if (strlen((char*)user_data) > 0)
	{
		/*
		 * forces the text to fit inside the limit of sizeof(buffer),
		 * wrapping text around where needed.
		 */
		char buffer[70];
		int n = 0;
		char *head;

		for (head = (char*)user_data;; head++)
		{
			char c = *head;

			if ((c == '\n') || (n == sizeof(buffer) - 1) || (c == '\0'))
			{
				char keep[3];

				buffer[n] = '\0';

				if (strlen(buffer) < 1)
					continue;

				/*
				 * not a new line, so buffer too big, wrap around string.
				 * 1- copy content 'to be lost' into keep
				 * 2- lose the 'to be lost' content by setting it to ...
				 */

				if ((c != '\n') && (c!='\0'))
				{
					int i;
					for (i=0; i<3; i++)
					{
						keep[i] = buffer[n-3+i];
						buffer[n-3+i] = '.';
					}
				}

				TXT_AddWidget(dialog, TXT_NewLabel(buffer));

				/*
				 * not a new line part 2, recover lost content edition.
				 * if not the case, then just set index to 0
				 */
				if ((c != '\n') && (c!='\0'))
				{
					int i;
					for (i=0; i<3; i++)
					{
						buffer[i] = keep[i];
					}

					buffer[3] = c;

					n = 4;
				}
				else
					n = 0;

				if (c=='\0')
				{
					return;
				}
			}
			else
			{
				buffer[n++] = c; // store char, since not fully loaded or newline
			}
		}
	}
	else
	{
		TXT_AddWidget(dialog, TXT_NewLabel("No description available"));
	}
}

void CVAR_MenuFromList(TXT_UNCAST_ARG(widget), void *user_data)
{
	cvar_t *cvar_list = (cvar_t*)user_data;

	TXT_CAST_ARG(txt_button_t, widget);
	txt_table_t *table;

	window = TXT_NewWindow(widget->label);
	table  = TXT_NewTable(2);

	int i;
	for (i=0; cvar_list[i].name != 0x0; i++)
	{
		char buffer[32];
		snprintf(buffer, 32, "%s: ", cvar_list[i].name);

		TXT_AddWidgets(table, TXT_NewButton2(buffer, CVAR_NewDialog, cvar_list[i].descript), TXT_NewInputBox(&cvar_list[i].def_val, 32), NULL);
	}

	TXT_AddWidget(window, TXT_NewScrollPane(0, (i < 10) ? i : 10,table));
}

static void CVAR_SaveCvars(char *file, ...)
{
    va_list args;
    FILE *f;

    f = fopen(file, "w");
    if (!f)
    {
    	printf("L%i: Error opening file %s.\n", __LINE__, file);
    	return;
    }

	va_start(args, file);

	// Keep adding widgets until a NULL is reached.

	for (;;)
	{
		cvar_t *cvar_list = va_arg(args, cvar_t *);
		if (!cvar_list)
			break;

		int i;
		for (i=0; cvar_list[i].name != 0x0; i++)
		{
			char buffer[256];
			snprintf(buffer, 256, "set %s \"%s\"\n", cvar_list[i].name, cvar_list[i].def_val);

			fputs(buffer, f);
		}
	}

	va_end(args);
	fclose(f);
}

static cvar_t* CVAR_FindByName(char *cvar, cvar_t* list)
{
	cvar_t *iterator;
	for (iterator = list; iterator->name; iterator++)
	{
		if (!strcmp(iterator->name, cvar))
			return iterator;
	}

	return NULL;
}

static void UTIL_Tokenize(char *s, vector<string> &token)
{
	string str;

	int quoted=0;

	for (char *head = s;; head++ )
	{
		if ((((*head != ' ') && (*head != '\t')) || quoted) && (*head != '\0') && (*head != '\n') && (*head != '"'))
				str += *head;
		else
		{
			int wasquoted = quoted;

			if (*head == '"')
				quoted = !quoted;

			if ((str.size() > 0) || wasquoted)
			{
				token.push_back(str);

				str.clear();

				if ((*head == '\0') || (*head == '\n'))
					break;
			}
		}
	}
}

static void CVAR_LoadCvars(char *file, ...)
{
    va_list args;
    FILE *f;

    f = fopen(file, "r");
    if (!f)
    {
    	printf("L%i: Error opening file %s.\n", __LINE__, file);
    	return;
    }

    char buffer[128];
    char *head;

    while (fgets(buffer, 128, f))
    {
    	vector<string> token;
    	UTIL_Tokenize(buffer, token);

    	if ((token.size() >= 3) && (token.at(0) == "set"))
    	{
    		va_start(args, file);

    		// Keep adding widgets until a NULL is reached.

    		for (;;)
    		{
    			cvar_t *cvar_list = va_arg(args, cvar_t *);
    			if (!cvar_list)
    				break;

    			cvar_t* cvar = CVAR_FindByName((char*)token.at(1).c_str(), cvar_list);
    			if (cvar)
    			{
    				free(cvar->def_val);
    				cvar->def_val = strdup(token.at(2).c_str());
    			}
    			else
    				continue;
    		}

    		va_end(args);
    	}
    }

	fclose(f);
}

void CVAR_SaveSettings()
{
	char f_name[4096];

	snprintf(f_name, 4096, "%s%s", getenv("HOME"), "/.odamex/l_odasrv.cfg");
	CVAR_SaveCvars(f_name, sv_gameplay_cvars, sv_misc_cvars, NULL);

	snprintf(f_name, 4096, "%s%s", getenv("HOME"), "/.odamex/l_odamex.cfg");
	CVAR_SaveCvars(f_name, cl_mp_cvars, cl_macro_cvars, cl_misc_cvars, NULL);

	snprintf(f_name, 4096, "%s%s", getenv("HOME"), "/.odamex/l_mapcycle.cfg");
	FILE *f = fopen(f_name, "w");
	if (f)
	{
		extern vector<map_t> map_list;
		int i;
		for (i=0; i<map_list.size(); i++)
		{
			if (map_list.at(i).active)
			{
				char buffer[128];

				/*
				 * Ugly hack to make .wad file name lowercase to circumvent issues in
				 * the odamex server code.
				 */
				char *fname = strdup(basename(map_list.at(i).wad));
				char *itr = fname;

				while (*itr != '\0')
				{
					*itr = tolower(*itr);
					itr ++;
				}

				snprintf(buffer, 127, "addmap \"%s\" \"%s\"\n", map_list.at(i).name, fname);

				fwrite(buffer, sizeof(char), strlen(buffer), f);

				free(fname);
			}
		}

		fclose(f);
	}

	snprintf(f_name, 4096, "%s%s", getenv("HOME"), "/.odamex/l_settings.cfg");
	f = fopen(f_name, "w");
	if (f)
	{
		char buffer[256];
		snprintf(buffer, 256, "%s = %s\n", "port", server_port);
		fputs(buffer, f);

		snprintf(buffer, 256, "%s = %s\n", "iwad", iwad_dropdown[iwad_value]);
		fputs(buffer, f);

		fclose(f);
	}

}

void CVAR_LoadSettings()
{
	FILE *f;
	char f_name[4096];

	snprintf(f_name, 4096, "%s%s", getenv("HOME"), "/.odamex/l_odasrv.cfg");
	CVAR_LoadCvars(f_name, sv_gameplay_cvars, sv_misc_cvars, NULL);

	snprintf(f_name, 4096, "%s%s", getenv("HOME"), "/.odamex/l_odamex.cfg");
	CVAR_LoadCvars(f_name, cl_mp_cvars, cl_macro_cvars, cl_misc_cvars, NULL);

	snprintf(f_name, 4096, "%s%s", getenv("HOME"), "/.odamex/l_mapcycle.cfg");
	f = fopen(f_name, "r");
	if (f) {
		char buffer[512];
		while (fgets(buffer, 512, f))
		{
			vector<string> token;
			UTIL_Tokenize(buffer, token);

			if (token.size() > 2) { //three or more tokens
				if (!strcasecmp(token.at(0).c_str(), "addmap")) {
					for (int i = 2; i<token.size(); i++) {
						MAP_MarkMapActive((char*)token.at(1).c_str(), basename(token.at(2).c_str()));
					}
				}
			}
		}
		fclose(f);
	}

	snprintf(f_name, 4096, "%s%s", getenv("HOME"), "/.odamex/l_settings.cfg");
	f = fopen(f_name, "r");
	if (f) {
		char buffer[512];
		while (fgets(buffer, 512, f))
		{
			vector<string> token;
			UTIL_Tokenize(buffer, token);

			if (token.size() > 2) { //three or more tokens
				if (!strcmp(token.at(0).c_str(), "port")) {
					if (server_port)
						free(server_port);

					server_port = strdup(token.at(2).c_str());
				} else if (!strcmp(token.at(0).c_str(), "iwad")) {
					if (iwad_dropdown)
					{
						for (int i=0; i<max_iwad; i++)
						{
							if (!strcasecmp(token.at(2).c_str(), iwad_dropdown[i]))
							{
								iwad_value = i;
								break;
							}
						}
					}
				}
			}
		}
		fclose(f);
	}
}
