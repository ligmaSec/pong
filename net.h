#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	6969


// Prototypes
void net_setup(bool is_server);

void send_position(int pos);
int recv_position();
