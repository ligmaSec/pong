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
void send_position_server(int player1_pos_y, float *ball_pos_x, float *ball_pos_y);
void send_position_client(int player1_pos_y);
int recv_position_server();
void recv_position_client(char** data);