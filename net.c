#include "net.h"

void net_setup(bool is_server){
	if (is_server){
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
            perror("Socket creation failed");
            exit(1);
        }

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

	}
}

void send_position(int pos){
    sendto(sockfd, &pos, sizeof(pos), MSG_CONFIRM,
        (const struct sockaddr*) &servaddr, sizeof(servaddr));
}

int recv_position(){
    printf("i got called");
    int len = sizeof(cliaddr);
    int opp_pos;
    recvfrom(sockfd, &opp_pos, sizeof(opp_pos), MSG_WAITALL, 
        (struct sockaddr *) &servaddr, &len);
    return opp_pos;
}