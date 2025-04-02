/* socksd.c */
#include "socksd.h"

#define LISTERNADDR "0.0.0.0"

/*global*/
char *error;

/*Return 0 on error or return socket fd*/
int srv_init(int port){
    int s;
    struct sockaddr_in srv;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0){
        error = "socket() error";
        return 0;
    }

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = inet_addr(LISTERNADDR);
    srv.sin_port = htons(port);

    if(bind(s, (struct sockaddr *)&srv, sizeof(srv))){
	error = "bind() error";
        close(s);
        return 0;
    }

    if(listen(s, 5)){
	close(s);
	error = "listen() error";
    }
    return s;
}

/*return 0 on error return client fd on success*/
int cli_acccept(int sockfd){
    int client;
    socklen_t addrlen;
    struct sockaddr_in cli_addr;

    memset(&cli_addr, 0, sizeof(cli_addr));
    addrlen = 0;
    if(0 > (client = accept(sockfd, (struct sockaddr *)&cli_addr, &addrlen))){
        error = "accept() error";
        return 0;
    }
    return client;
}

/**/
int cli_conn(int serverfd, int clientfd)
{
    return 0;
}

int main(int argc, char *argv[]) {
    int sockfd, client;
    char *port;

    if(argc < 2){
        fprintf(stderr, "Usage: %s <lisening port>\n", argv[0]);
    }

    port = argv[1];
    sockfd = srv_init(atoi(port));
    if(!sockfd){
        fprintf(stderr, "%s\n",error);
        return -1;
    }

    printf("Listerning on %s:%s\n", LISTERNADDR, port);
    while(1){
        client = cli_acccept(sockfd);
        if(!client){
            fprintf(stderr, "%s\n", error);
            continue;
        }
        printf("incoming connection\n");
        if (!fork()) /*create a copy of the program*/
        {
            cli_conn(sockfd, client);
        }
    }

    return -1;
}
