#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <memory.h>

int main(int argc, char* argv[])
{
    int c_socket;
    struct sockaddr_in c_addr;

    FILE* fp;
    char buffer[BUFSIZ] = {'\0'};
    int bufferStat = 0;
    
// file open

    if(argc != 4)
    {
        printf("%s [server ip address] [port number] [file name]\n", argv[0]);
        return -1;
    }

    if((fp = fopen(argv[3], "rb")) == NULL)
    {
        printf("file error\n");
        return -1;
    }

// socket connecting

    c_socket = socket(PF_INET, SOCK_STREAM, 0);

    memset(&c_addr, 0, sizeof(c_addr));
    c_addr.sin_addr.s_addr = inet_addr(argv[1]);
    c_addr.sin_family = AF_INET;
    c_addr.sin_port = htons(atoi(argv[2]));

    if(connect(c_socket, (struct sockaddr*)&c_addr, sizeof(c_addr)) == -1)
    {
        printf("can not connect\n");
        close(c_socket);
        return -1;
    }

// file upload

    do
    {
        bufferStat = fread(buffer, 1, BUFSIZ, fp);
        write(c_socket, buffer, BUFSIZ);
        printf("#");
    } while(bufferStat == BUFSIZ);

    printf("\nupload complete\n");

// end

    close(c_socket);

    return 0;
}
