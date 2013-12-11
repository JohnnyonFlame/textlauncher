#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#include <pthread.h>

#include <vector>

#include "textscreen.h"
#include "network.h"

#define BROADCAST_IP "255.255.255.255"
#define CHALLENGE 777123
#define PORT 10666

static txt_window_t* window;
static pthread_t thread;

//Allows us to know when the thread has to die.
static volatile int t_status;

class server_t{
public:
	char addr[32];
	uint16_t port;
	char name[61];
	char cur, max; //current/max players

	server_t(char *_addr, int _port, char *response);
};

std::vector<server_t> serverlist;

static void clearServerList()
{
	while (!serverlist.empty())
	{
		serverlist.pop_back();
	}
}

server_t::server_t(char *_addr, int _port, char *response)
{
	strncpy(addr, _addr, 32);
	strncpy(name, &response[8], 60);

	//truncate name to 60 chars
	if (strlen(name) > 59)
	{
		name[57] = '.';
		name[58] = '.';
		name[59] = '.';
		name[60] = '\0';
	}

	port = _port;
	cur = response[8 + strlen(&response[8]) + 1];
	max = response[8 + strlen(&response[8]) + 2];
}

static void sendChallenge(int *sockfd, sockaddr_in* sockaddr, int broadcast, int challenge, char *ip_addr, int port) {
	hostent* server;
	int timeout = 5;

	*sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	server = gethostbyname(ip_addr);

	sockaddr->sin_family = AF_INET;
	memcpy((char *) &sockaddr->sin_addr.s_addr, (char *) server->h_addr,
			server->h_length);
	sockaddr->sin_port = htons(port);

	if (setsockopt(*sockfd, SOL_SOCKET, SO_BROADCAST, (void *) &broadcast, sizeof(broadcast)) < 0) {
		fprintf(stderr, "setsockopt error");
		exit(1);
	}

	struct timeval tv;
	tv.tv_sec = 5;	tv.tv_usec = 0;

	setsockopt(*sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
	setsockopt(*sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(struct timeval));

	//Sets non-blocking.
	if (broadcast)
		fcntl(*sockfd, F_SETFL, fcntl(*sockfd, F_GETFL) | O_NONBLOCK);

	sendto(*sockfd, &challenge, 4, 0, (struct sockaddr*) sockaddr,
			sizeof(*sockaddr));
}

static void join_joinmenu(TXT_UNCAST_ARG(widget), void *user_data)
{
	TXT_ExitMainLoop();
}

static void cancel_joinmenu(TXT_UNCAST_ARG(widget), void *user_data)
{
	TXT_CAST_ARG(txt_window_t, widget);

	if (launchgame_cmdline_addr)
	{
		free(launchgame_cmdline_addr);
		launchgame_cmdline_addr = NULL;
	}
}

static void make_joinmenu(char *addr, int port)
{
	int sockfd;
	sockaddr_in sockaddr;
	txt_window_t* dialog;

	sendChallenge(&sockfd, &sockaddr, 0, CHALLENGE, addr, port);

	char buffer[8192];
	unsigned int buffer_head = 8;

	unsigned int slen = sizeof(sockaddr);
	int size = recvfrom(sockfd, &buffer, 8192, 0,(struct sockaddr*) &sockaddr, &slen);


#define _READ8()   *((uint8_t*)(&buffer[buffer_head]));  buffer_head += 1;
#define _READ16()  *((uint16_t*)(&buffer[buffer_head])); buffer_head += 2;
#define _READ32()  *((uint32_t*)(&buffer[buffer_head])); buffer_head += 4;
#define _READSTR() strdup(&buffer[buffer_head]); 	     buffer_head += strlen(&buffer[buffer_head])+1;

	if (size>0) {
		//TXT_CloseWindow(window);
		dialog = TXT_NewWindow("Join Game");
		txt_table_t *table = TXT_NewTable(3);

		char *servername = _READSTR();

		if (strlen(servername) > 50)
		{
			servername[46] = '.';
			servername[47] = '.';
			servername[48] = '.';
			servername[49] = '\0';
		}

		uint8_t players = _READ8();
		uint8_t maxplayers = _READ8();
		char *curmap = _READSTR();
		uint8_t wadcount = _READ8();
		char **wadlist = (char**)malloc(sizeof(*wadlist) * wadcount);

		int i;
		for (i=0;i<wadcount;i++)
		{
			wadlist[i] = _READSTR();
		}

		uint8_t gametype = _READ8();
		uint8_t skilllevel = _READ8();
		uint8_t teamplay = _READ8();
		uint8_t ctfmode = _READ8();

		char sv_addr_tmp[32];
		snprintf(sv_addr_tmp, 32, "%s:%i", addr, port);

		char sv_players_tmp[16];
		snprintf(sv_players_tmp, 16, "%i/%i", players, maxplayers);

		launchgame_cmdline_addr = strdup(sv_addr_tmp);

		TXT_AddWidgets(table,
				TXT_NewLabel("Name:"), TXT_NewStrut(3,0), TXT_NewLabel(servername),
				TXT_NewLabel("Address:"), TXT_NewStrut(3,0), TXT_NewLabel(sv_addr_tmp),
				TXT_NewLabel("Players:"), TXT_NewStrut(3,0), TXT_NewLabel(sv_players_tmp),
				NULL);

		if (ctfmode)
		{
			TXT_AddWidgets(table,
					TXT_NewLabel("Gametype:"), TXT_NewStrut(3,0), TXT_NewLabel("Capture the Flag"),
					NULL);
		}
		else
		{
			if (gametype == 0)
			{
				TXT_AddWidgets(table,
						TXT_NewLabel("Gametype:"), TXT_NewStrut(3,0), TXT_NewLabel("CO-OP"),
						NULL);
			}
			else
			{
				if (teamplay)
				{
					TXT_AddWidgets(table,
							TXT_NewLabel("Gametype:"), TXT_NewStrut(3,0), TXT_NewLabel("Team Deathmatch"),
							NULL);
				}
				else
				{
					TXT_AddWidgets(table,
							TXT_NewLabel("Gametype:"), TXT_NewStrut(3,0), TXT_NewLabel("Deathmatch"),
							NULL);
				}
			}
		}

		TXT_AddWidgets(table,
				TXT_NewLabel("Map:"), TXT_NewStrut(3,0), TXT_NewLabel(curmap),
				TXT_NewLabel("IWad:"), TXT_NewStrut(3,0), TXT_NewLabel(wadlist[0]),
				NULL);

		for (i=1;i<((wadcount<3) ? wadcount : 3);i++)
		{
			if (i==1)
				TXT_AddWidgets(table, TXT_NewLabel("PWad(s):"), TXT_NewStrut(3,0), TXT_NewLabel(wadlist[i]),	NULL);
			else
				TXT_AddWidgets(table, TXT_NewStrut(0,0), TXT_NewStrut(3,0), TXT_NewLabel(wadlist[i]),	NULL);
		}

		if (wadcount >= 3)
		{
			TXT_AddWidgets(table, TXT_NewStrut(0,0), TXT_NewStrut(3,0), TXT_NewLabel("..."),	NULL);
		}

		TXT_AddWidget(dialog, table);
		for (i=0;i<wadcount;i++)
		{
			free(wadlist[i]);
		}

		free(wadlist);
		free(curmap);
		free(servername);
	}
	else
	{
		dialog = TXT_NewWindow("Timeout");
		TXT_AddWidget(dialog, TXT_NewLabel("Challenge to server timed out."));
	}

	txt_window_action_t* act;
	TXT_SignalConnect(act = TXT_NewWindowAction(KEY_ENTER, "Join"), "pressed", join_joinmenu, NULL);
	TXT_SetWindowAction(dialog, TXT_HORIZ_RIGHT, act);

	TXT_SignalConnect(dialog, "closed", cancel_joinmenu, NULL);

#undef _READ8
#undef _READ16
#undef _READ32
#undef _READSTR
}

static void joinmenu_fromServer(TXT_UNCAST_ARG(widget), void *user_data)
{
	server_t* server = &serverlist.at((int) user_data);

	make_joinmenu(server->addr, server->port);
}

static void query_server(char *addr, int port, txt_table_t *table)
{
	int sockfd;
	sockaddr_in sockaddr;

	sendChallenge(&sockfd, &sockaddr, 0, CHALLENGE, addr, port);

	char buffer[8192];

	unsigned int slen = sizeof(sockaddr);
	int size = recvfrom(sockfd, &buffer, 8192, 0,(struct sockaddr*) &sockaddr, &slen);

	if (size>0)
	{
		server_t server (inet_ntoa(sockaddr.sin_addr), port, buffer);
		char clients[8];

		snprintf(clients, 8, "%i/%i", server.cur, server.max);

		TXT_AddWidgets(table, TXT_NewButton2(server.name, joinmenu_fromServer, (void*)serverlist.size()),TXT_NewStrut(3, 0),TXT_NewLabel(clients),NULL);
		serverlist.push_back(server);
	}
}

static void *thread_landiscovery(void* user_data) {
	txt_table_t* table = (txt_table_t*) user_data;
	int sockfd;
	sockaddr_in sockaddr;

	sendChallenge(&sockfd, &sockaddr, 1, CHALLENGE, BROADCAST_IP, 10666);

	time_t starttime, curtime;
	double TIMEOUT = 5;

	time(&starttime);

	do {
		char buffer[8192];

		unsigned int slen = sizeof(sockaddr);
		int size = recvfrom(sockfd, &buffer, 8192, 0,(struct sockaddr*) &sockaddr, &slen);

		if (size > 0) {
			server_t server (inet_ntoa(sockaddr.sin_addr), 10666, buffer);
			char clients[8];

			snprintf(clients, 8, "%i/%i", server.cur, server.max);

			TXT_AddWidgets(table, TXT_NewButton2(server.name, joinmenu_fromServer, (void*)serverlist.size()),TXT_NewStrut(3, 0),TXT_NewLabel(clients),NULL);
			serverlist.push_back(server);
		}

		time(&curtime);
	} while ((difftime(curtime, starttime) < TIMEOUT) && t_status);

	return NULL;
}

static void *thread_netdiscovery(void* user_data) {
	txt_table_t* table = (txt_table_t*) user_data;
	int sockfd;
	sockaddr_in sockaddr;
	unsigned char buffer[8192];
	unsigned int  buffer_head=0;

	sendChallenge(&sockfd, &sockaddr, 0, CHALLENGE, "76.74.252.88", 15000);

	unsigned int slen = sizeof(sockaddr);
	int size = recvfrom(sockfd, &buffer, 8192, 0,(struct sockaddr*) &sockaddr, &slen);

	if (size <= 0)
		return NULL;

	uint16_t server_count = *((uint16_t*)&buffer[4]);

	int i;
	for (i=0;(i<server_count) && t_status;i++)
	{
		char server_ip[20];
		int  server_port = *((uint16_t*)&buffer[10+ (i*6)]);

		snprintf(server_ip, 20, "%u.%u.%u.%u",
				buffer[6+ (i*6)],
				buffer[7+ (i*6)],
				buffer[8+ (i*6)],
				buffer[9+ (i*6)]);

		query_server(server_ip, server_port, table);
	}

	return NULL;
}

static void signal_closed(TXT_UNCAST_ARG(widget), void *user_data) {
	t_status = 0;
	pthread_join(thread, NULL);
}

static void NET_ThreadedMenu(char *title, void *(*__start_routine) (void *))
{
	clearServerList();

	txt_table_t *table_sv = TXT_NewTable(3);

	window = TXT_NewWindow(title);
	TXT_SignalConnect(window, "closed", signal_closed, NULL);

	TXT_AddWidgets(table_sv, TXT_NewLabel("Server"),TXT_NewStrut(3, 0),TXT_NewLabel("Players"),NULL);
	TXT_AddWidgets(window, TXT_NewScrollPane(0, 10, table_sv), NULL);

	t_status = 1;
	pthread_create(&thread, NULL, __start_routine, (void*) table_sv);
}

char *customaddr = strdup("127.0.0.1:10666");

static void action_manualdiscovery(TXT_UNCAST_ARG(widget), void *user_data) {
	if (strlen(customaddr) == 0) {
		txt_window_t *dialog = TXT_NewWindow("Error");
		TXT_AddWidget(dialog, TXT_NewLabel("Please specify address"));

		return;
	}

	TXT_CloseWindow(window);

	char *portstart = strrchr(customaddr, ':');
	int pos = portstart - customaddr;

	if (!portstart)
	{
		make_joinmenu(customaddr, 10666);
	}
	else
	{
		char address[32];
		int port = 0;

		memcpy(address, customaddr, pos);
		address[pos] = '\0';

		sscanf(&customaddr[pos], ":%i", &port);

		printf("%i %i\n", strlen(customaddr), pos);

		if (pos == strlen(customaddr)-1)
		{
			txt_window_t *dialog = TXT_NewWindow("Error");
			TXT_AddWidget(dialog, TXT_NewLabel("Malformed address syntax"));

			return;
		}

		make_joinmenu(address, port);
	}

}

void NET_ManualMenu(TXT_UNCAST_ARG(widget), void *user_data) {
	window = TXT_NewWindow("Specify Server");
	txt_table_t *table = TXT_NewTable(2);

	TXT_AddWidgets(table, TXT_NewLabel("Address: "), TXT_NewInputBox(&customaddr, 32), NULL);
	TXT_AddWidget(window, table);

	txt_window_action_t* act;
	TXT_SignalConnect(act = TXT_NewWindowAction(KEY_SPACE, "Join"), "pressed", action_manualdiscovery, NULL);
	TXT_SetWindowAction(window, TXT_HORIZ_CENTER, act);
}

void NET_LanDiscoveryMenu(TXT_UNCAST_ARG(widget), void *user_data) {
	NET_ThreadedMenu("Local Servers", thread_landiscovery);
}

void NET_NetDiscoveryMenu(TXT_UNCAST_ARG(widget), void *user_data) {
	NET_ThreadedMenu("Internet Servers", thread_netdiscovery);
}
