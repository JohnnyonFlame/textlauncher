#ifndef NETWORK_H_
#define NETWORK_H_

extern char *launchgame_cmdline_addr;

void NET_LanDiscoveryMenu(TXT_UNCAST_ARG(widget), void *user_data);
void NET_NetDiscoveryMenu(TXT_UNCAST_ARG(widget), void *user_data);
void NET_ManualMenu(TXT_UNCAST_ARG(widget), void *user_data);

#endif /* NETWORK_H_ */
