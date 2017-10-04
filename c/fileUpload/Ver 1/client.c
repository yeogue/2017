#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <memory.h>

#define PORT 2000

int main(void)//int argc, char* argv)
{
    int c_socket;
    struct sockaddr_in c_addr;

    FILE* fp;
    char buffer[BUFSIZ] = {'\0'};
    int bufferStat = 0;
    

    if((fp = fopen("test.jpg", "rb")) == NULL)
    {
        printf("file error\n");
        return -1;
    }

//    if(argc < 2)
//    {
//        printf("%s [input ip address]\n", argv[0]);
//        return -1;
//    }

    c_socket = socket(PF_INET, SOCK_STREAM, 0);

    memset(&c_addr, 0, sizeof(c_addr));
    c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    c_addr.sin_family = AF_INET;
    c_addr.sin_port = htons(PORT);

    if(connect(c_socket, (struct sockaddr*)&c_addr, sizeof(c_addr)) == -1)
    {
        printf("can not connect\n");
        close(c_socket);
        return -1;
    }

    do
    {
        bufferStat = fread(buffer, 1, BUFSIZ, fp);
        write(c_socket, buffer, BUFSIZ);
    } while(bufferStat == BUFSIZ);

    printf("upload complete\n");

    close(c_socket);

    return 0;
}
