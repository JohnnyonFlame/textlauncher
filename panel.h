#ifndef PANEL_H_
#define PANEL_H_

extern char *server_port;

void serverpanel(void *widget, void *user_data);
void config_server(TXT_UNCAST_ARG(widget), void *user_data);

#endif /* PANEL_H_ */
