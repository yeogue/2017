#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <memory.h>

#define PORT 2000

int main(void)
{
    int c_socket, s_socket;
    int len;
    struct sockaddr_in c_addr, s_addr;

    int result;
    int a;
    int b;
    char op;
    
    s_socket = socket(PF_INET, SOCK_STREAM, 0);
    
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);

    if(bind(s_socket, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1)
    {
        printf("can not bind\n");
        return -1;
    }

    if(listen(s_socket, 5) == -1)
    {
        printf("listen fail\n");
        return -1;
    }

    len = sizeof(c_addr);
    c_socket = accept(s_socket, (struct sockaddr*)&c_addr, &len);

    while(1)
    {
        read(c_socket, &a, sizeof(int));
        read(c_socket, &op, 1);
        read(c_socket, &b, sizeof(int));
    
        switch(op)
        {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        }
    
        write(c_socket, &result, sizeof(int));
    }
    close(c_socket);
    close(s_socket);

    return 0;
}
