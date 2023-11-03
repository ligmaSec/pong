#include "net.h"

void net_setup(bool is_server, char* host){
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket creation failed");
        exit(1);
    }

	if (is_server){
        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        // Filling server information
        servaddr.sin_family = AF_INET; // IPv4
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(PORT);

        // Bind the socket with the server address
        if (bind(sockfd, (const struct sockaddr *) &servaddr,
                sizeof(servaddr)) < 0){
            perror("Bind failed");
            exit(1);
        }
	} else {
        memset(&servaddr, 0, sizeof(servaddr));
        // Filling server information
        servaddr.sin_family = AF_INET; // IPv4
        servaddr.sin_port = htons(PORT);
        printf("%s\n", host);
        servaddr.sin_addr.s_addr = inet_addr(host);
	}
}

void send_position_server(int player1_pos_y, float *ball_pos_x, float *ball_pos_y){
    char data[100];
    sprintf(data, "%d$%.2f$%.2f", player1_pos_y, *ball_pos_x, *ball_pos_y);
    sendto(sockfd, &data, strlen(data), MSG_CONFIRM,
        (const struct sockaddr*) &servaddr, sizeof(servaddr));
}

void send_position_client(int player1_pos_y){
    sendto(sockfd, &player1_pos_y, sizeof(player1_pos_y), MSG_CONFIRM,
        (const struct sockaddr*) &servaddr, sizeof(servaddr));
}

int recv_position_server(){
    int len = sizeof(cliaddr);
    int opp_pos;
    recvfrom(sockfd, &opp_pos, sizeof(opp_pos), MSG_WAITALL, 
        (struct sockaddr *) &servaddr, &len);
    return opp_pos;
}

void recv_position_client(char** data){
    int len = sizeof(cliaddr);
    char buffer[100];
    memset(&buffer, 0, sizeof(buffer));
    recvfrom(sockfd, &buffer, sizeof(buffer), MSG_WAITALL, 
        (struct sockaddr *) &servaddr, &len);

    // printf("From recv_client: %s\n", buffer);
    *data = malloc(100*sizeof(char));
    strcpy(*data, buffer);
}