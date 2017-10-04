//talk_server_pthread.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define NUM 5
#define NAMELEN 20

void *do_keyboard(void *);
void *do_socket(void *);
void* do_thread(void*);
void* do_socket_thread(void*);
void* do_chat(void*);

char quit[ ] = "exit";
char	rbuf[BUFSIZ];

pthread_t pid[NUM];
int saveSock[NUM];
char nameList[NUM][NAMELEN];

int
main(int argc, char *argv[ ]) {

	int	thr_id;
	int	status;

	int	listenSock, connSock;
	struct sockaddr_in client_addr, server_addr;

	int	len;
	int	i = 0;

	if(argc < 2) {
		printf("Usage:  talk_server port_num ");
		return -1;
	}

	if((listenSock=socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Server: Can't open socket\n");
		return -1;
	}

	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	if(bind(listenSock, (struct sockaddr *) &server_addr, sizeof(server_addr))<0){
		printf("talk Server Can't bind \n");
		return -1;
	}

	listen(listenSock, 5);

	len = sizeof(client_addr);
	while(1)
	{
		if((connSock = accept(listenSock,(struct sockaddr *) &client_addr, &len))<0){
			printf("Talk Server failed in accepting\n");
			return -1;
		}
		printf("Talk Server accept new request\n");

		read(connSock, nameList[i], NAMELEN);

		pthread_create(&pid[i], NULL, do_thread, (void*)connSock);	
		saveSock[i] = connSock;
		i++;
	}

	close(listenSock);
	close(connSock);
}

void* do_thread(void* connSock)
{
	pthread_t pid[2];
	int status;

	pthread_create(&pid[0], NULL, do_keyboard, (void *)connSock);
	pthread_create(&pid[1], NULL, do_socket, (void *)connSock);

	pthread_join(pid[0], (void **) &status);
	pthread_join(pid[1], (void **) &status);
}

void *
do_keyboard(void *data)
{
	int	n;
	char	sbuf[BUFSIZ];
	int	connSock = (int) data;

	while((n = read(0, sbuf, BUFSIZ)) > 0) {
		if(write(connSock, sbuf, n) != n) {
			printf("Talk Server fail in sending\n");
		}
		if(strncmp(sbuf, quit, 4) == 0) {
			pthread_kill(pid[1], SIGINT);
			break;
		}
	}
}

void *
do_socket(void *data)
{
	pthread_t pid[NUM];
	int status;
	int i;
	
	for(i = 0; i < NUM; i++)
	{
		pthread_create(&pid[i], NULL, do_socket_thread, (void*)saveSock[i]);
	}
}

void* do_socket_thread(void* data)
{
	int	n;
	int	connSock = (int) data;
	int	i, j, k;
	int	saveIdx;

	pthread_t chat[1];

	j = 0;
	while(connSock != saveSock[j]) j++;

	while(1) {
		if((n = read(connSock, rbuf, BUFSIZ)) > 0) {
			rbuf[n] = '\0';
			if(strncmp(rbuf, "quit", 4) == 0) {
				pthread_kill(chat[0], SIGINT);
				break;
			}
			if(rbuf[0] == '[')
			{
				pthread_create(&pid[0], NULL, do_chat, (void*) connSock);
			}
			else
			{
				for(i = 0; i < NUM; i++)
				{
					write(saveSock[i], nameList[j], NAMELEN);
					if(write(saveSock[i], rbuf, n) != n) {
						printf("Talk Server fail in sending\n");
					}
				}
			}
		}
	}
}

void* do_chat(void* data)
{
	int i = 1;
	int j;
	int k = 0;
	int saveIdx = 0;
	int	connSock = (int) data;

	j = 0;
	while(connSock != saveSock[j]) j++;

	while(strlen(nameList[saveIdx]) >= 1 && saveIdx < NUM)
	{
		saveIdx++;
	}
	while(k < saveIdx)
	{
		i = 1;
		while(rbuf[i] == nameList[k][i-1] && i <= strlen(nameList[k]))
		{
			i++;
		}

		if(rbuf[i] == ']')
		{
			break;
		}
		
		k++;
	}
	if(k < saveIdx)
	{
		write(saveSock[k], nameList[j], NAMELEN);
		if(write(saveSock[k], rbuf, BUFSIZ) != BUFSIZ) {
			printf("Talk Server fail in sending\n");
		}
	}
}
