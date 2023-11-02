#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 6969

// Global variables
int sockfd;
struct sockaddr_in servaddr, cliaddr;

// Prototypes
void net_setup(bool is_server, char* host);
void send_position(int pos);
int recv_position();