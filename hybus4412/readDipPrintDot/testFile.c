#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>
#include <asm/ioctls.h>
#include <pthread.h>

#define DotDev	"/dev/dot"
#define DipswDev "/dev/dipsw"

void* dotPrint(void*);
void* dipGet(void*);

unsigned char row[8][63] ={
    {0,1,1,1,0,0,1,0,0, 0,0,0,0,1,0,0,0,1, 0,0,1,1,1,0,0,1,0,0, 0,1,0,0,0,0,1,0,0, 0,0,1,0,0,0,1,0,0, 0,1,1,1,1,1,1,1,0, 0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,1,0,0, 0,0,0,0,1,0,0,0,1, 0,1,0,0,0,1,0,1,0,0, 0,1,0,0,0,0,1,0,0, 1,1,1,1,1,1,1,0,0, 0,0,0,0,0,0,0,1,0, 0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,1,0,0, 0,0,0,0,1,0,0,0,1, 0,1,0,0,0,1,0,1,0,0, 0,1,0,0,0,0,1,0,0, 0,0,1,1,0,0,1,1,1, 0,0,0,0,1,0,0,1,0, 0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,1,0,0, 0,0,0,1,0,0,0,0,1, 0,1,0,0,0,1,0,1,0,0, 0,1,0,0,0,0,1,0,0, 0,1,0,0,1,0,1,0,0, 0,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,1,1,1, 0,0,1,0,1,0,0,0,1, 0,1,0,0,0,1,0,1,1,1, 0,1,0,0,0,0,1,1,1, 0,0,1,1,0,0,1,0,0, 1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,1,0,0, 0,1,0,0,0,1,0,0,1, 0,1,0,0,0,1,0,1,0,0, 0,1,0,0,0,0,1,0,0, 0,0,0,1,1,1,0,0,0, 0,0,0,1,1,1,0,0,0, 0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,1,0,0, 1,0,0,0,0,0,1,0,1, 0,1,0,0,0,1,0,1,0,0, 0,1,0,0,0,0,1,0,0, 0,0,1,0,0,0,1,0,0, 0,0,1,0,0,0,1,0,0, 0,0,0,0,0,0,0,0},
    {0,1,1,1,0,0,1,0,0, 1,0,0,0,0,0,1,0,1, 0,0,1,1,1,0,0,1,0,0, 0,1,1,1,1,0,1,0,0, 0,0,0,1,1,1,0,0,0, 0,0,0,1,1,1,0,0,0, 0,0,0,0,0,0,0,0}
};

static unsigned char c;

int main(void)
{
    int value;
    pthread_t pid[2];

    pthread_create(&pid[1], NULL, dotPrint, (void*)&value);
    pthread_create(&pid[0], NULL, dipGet, (void*)&value);
    pthread_join(pid[0], (void**)&value);
    pthread_join(pid[1], (void**)&value);
    
    return 0;
}

void* dotPrint(void* value)
{
    unsigned char dotData[8] = {'\0'};
    int dotFd = 0;
    int dipswFd = 0;
    int i, j;
    
    dotFd = open(DotDev, O_RDWR);
    if(dotFd <0){
        printf("Can't Open %s\n", DotDev);
        return;
    }

    write(dotFd, dotData, sizeof(dotData));
    
    while(1)
    {
        if(c == 97)
        {
            for(i = 0; i < 63; i++)
            {
                for(j = 0; j < 8; j++)
                {
                    dotData[j] <<= 1;
                    dotData[j] += row[j][i];
                }
                if(c != 97)
                {
                    memset(dotData, 0, 8);
                    write(dotFd, dotData, sizeof(dotData));
                    break;
                }
                write(dotFd, dotData, sizeof(dotData));
                usleep(100000);
            }
        }
    }
}

void* dipGet(void* value)
{
    int dipswFd = 0;

    if((dipswFd = open(DipswDev, O_RDONLY)) < 0)
    {
        printf("Can't open %s\n", DipswDev);
        return;
    }

    while(1)
    {
        read(dipswFd, &c, sizeof(c));
        printf("DIP => %d\n", c);
        usleep(300000);
    }
}
