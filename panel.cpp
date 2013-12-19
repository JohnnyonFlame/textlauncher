#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <vector>

#include "c_cvars.h"
#include "textscreen.h"
#include "pthread.h"
#include "wad.h"

#define ODASRV_PIPE "/tmp/odasrv.pipe"
#define ODASRV_LOG "/tmp/odasrv.log"
#define ODASRV_PID "/tmp/odasrv.pid"

char *server_port = strdup("10666");
char *cmdline = strdup("");

static txt_window_t* window;

/*
 * t_id[0] = server spawn thread
 * t_id[1] = log reading thread
 *
 * t_status = thread status (1 - keep on, 2 - should die)
 */
static pthread_t t_id[2];
static volatile int t_status;

using namespace std;

/*
 * O_NONBLOCK write pipes will return an error in case nobody is reading them.
 */
static int is_pipe_open(char *file)
{
	int pipe = open(file, O_WRONLY | O_NONBLOCK);

	if (pipe > 0)
	{
		close(pipe);
		return 1;
	}
	else
	{
		return 0;
	}
}

static void *thread_spawnserver(void *user_data)
{
	char buffer[512];
	snprintf(buffer, 511, "./odasrv -config %s/.odamex/l_odasrv.cfg -iwad %s +exec %s/.odamex/l_mapcycle.cfg +logfile %s -fork %s -port %s %s < %s",
			getenv("HOME"), /*-config*/
			iwad_dropdown[iwad_value], /*-iwad*/
			getenv("HOME"), /*-exec*/
			ODASRV_LOG, /*+logfile*/
			ODASRV_PID, /*-fork*/
			server_port, /*-port*/
			cmdline, /* ... */
			ODASRV_PIPE);

	printf("Launching server:\n%s\n\n", buffer);

	txt_table_t *table = (txt_table_t*) user_data;
	//int ret = system("./odasrv +logfile "ODASRV_LOG" -fork "ODASRV_PID" < "ODASRV_PIPE);
	int ret = system(buffer);

	return NULL;
}

static void *thread_readlogs(void *user_data)
{
	txt_table_t *table = (txt_table_t*) user_data;
	char buffer[60];
	int n = 0;

	FILE *pipe = fopen(ODASRV_PIPE, "w");
	if (pipe)
	{
		fwrite("\n", 1, 1, pipe);
		fclose(pipe);
	}

	FILE *log = fopen(ODASRV_LOG, "r");

	while (!log && t_status)
	{
		log = fopen(ODASRV_LOG, "r");
	}

	if (!log || !t_status)
	{
		return NULL;
	}

	//flag | O_NONBLOCK && seek to end of file
	fcntl(fileno(log), F_SETFD, fcntl(fileno(log), F_GETFD, 0) | O_NONBLOCK);
	fseek(log, 0, SEEK_END);

	int fd = fileno(log);

	//While thread is alive
	while (t_status)
	{
		char c;
		int size = read(fd, &c, 1);

		if (size>0)
		{
			if ((c == '\n') || (n == sizeof(buffer) - 1))
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

				if (c != '\n')
				{
					int i;
					for (i=0; i<3; i++)
					{
						keep[i] = buffer[n-3+i];
						buffer[n-3+i] = '.';
					}
				}

				TXT_AddWidget(table, TXT_NewLabel(buffer));

				/*
				 * not a new line part 2, recover lost content edition.
				 * if not the case, then just set index to 0
				 */
				if (c != '\n')
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

				txt_scrollpane_t* pane = (txt_scrollpane_t*)table->widget.parent;
				pane->y++;
			}
			else
				buffer[n++] = c; // store char, since not fully loaded or newline
		}
	}

	fclose(log);

	return NULL;
}

static char *cmd_input = strdup("");
static void server_inputcmd_done(TXT_UNCAST_ARG(widget), void *user_data)
{
	txt_window_t *window = (txt_window_t*)user_data;
	if (cmd_input && (strlen(cmd_input) > 0)) {
		int pipe = open(ODASRV_PIPE, O_WRONLY | O_NONBLOCK);

		if (pipe > 0)
		{
			write(pipe, cmd_input, strlen(cmd_input));
			write(pipe, "\n", 1);
			close(pipe);
		}
	}

	TXT_CloseWindow(window);
}

static void server_inputcmd(TXT_UNCAST_ARG(widget), void *user_data)
{
	txt_window_t *dialog;
	txt_table_t *table;

	dialog = TXT_NewWindow("Input Command");
	table =  TXT_NewTable(2);

	TXT_AddWidgets(table, TXT_NewLabel("] "), TXT_NewInputBox(&cmd_input, 60), NULL);
	TXT_AddWidget(dialog, table);

	txt_window_action_t* act;
	TXT_SignalConnect(act = TXT_NewWindowAction(KEY_SPACE, "Done"), "pressed", server_inputcmd_done, dialog);
	TXT_SetWindowAction(dialog, TXT_HORIZ_RIGHT, act);
}

void config_server(TXT_UNCAST_ARG(widget), void *user_data)
{
	extern vector<map_t> map_list; /* internal wads */

	txt_window_t *dialog;
	txt_table_t *table, *mapcycle;

	dialog = TXT_NewWindow("Configure Server");
	table =  TXT_NewTable(2);
	mapcycle = TXT_NewTable(1);

	TXT_AddWidgets(table, TXT_NewLabel("IWad:      "), TXT_NewDropdownList(&iwad_value, iwad_dropdown, max_iwad), NULL);
	TXT_AddWidgets(table, TXT_NewLabel("UDP Port:  "), TXT_NewInputBox(&server_port, 6), NULL);
	TXT_AddWidgets(table, TXT_NewLabel("CMD Line:  "), TXT_NewInputBox(&cmdline, 32), NULL);

	TXT_AddWidgets(dialog, table, TXT_NewSeparator("Map Cycle"), TXT_NewScrollPane(0,5,mapcycle), NULL);

	int i;
	for (i=0; i<map_list.size(); i++)
	{
		char buffer[128];
		snprintf(buffer, 127, "%s @ %s", map_list.at(i).name, basename(map_list.at(i).wad));

		TXT_AddWidgets(mapcycle, TXT_NewCheckBox(buffer, &map_list.at(i).active), NULL);
	}
}

static void signal_closed(TXT_UNCAST_ARG(widget), void *user_data)
{
	t_status = 0;

	pthread_join(t_id[0], NULL);
	pthread_join(t_id[1], NULL);
}

void serverpanel(TXT_UNCAST_ARG(widget), void *user_data)
{
	txt_window_t *dialog;
	txt_table_t *table;

	dialog = TXT_NewWindow("Server Console");
	table = TXT_NewTable(1);

	txt_window_action_t* act;
	TXT_SignalConnect(act = TXT_NewWindowAction(KEY_SPACE, "Input Command"), "pressed", server_inputcmd, NULL);
	TXT_SetWindowAction(dialog, TXT_HORIZ_CENTER, act);

	TXT_SignalConnect(dialog, "closed", signal_closed, NULL);

	TXT_AddWidget(dialog, TXT_NewScrollPane(0, 10, table));

	t_status = 1;

	//make sure we have a pipe!
	mkfifo(ODASRV_PIPE, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

	if (!is_pipe_open(ODASRV_PIPE))
	{
		CVAR_SaveSettings();
		pthread_create(&t_id[0], NULL, thread_spawnserver, (void*)table);
	}
	else
		TXT_AddWidget(table, TXT_NewLabel("Continuing..."));

	pthread_create(&t_id[1], NULL, thread_readlogs, (void*)table);
}
