#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>
#include <asm/ioctls.h>
#include <pthread.h>

#define DotLen 46
#define PASSWORD 795 // 135
#define DIPSW 97

#define DotDev	"/dev/dot"
#define DipswDev "/dev/dipsw"
#define LedDev "/dev/led"
#define tactswDev "/dev/tactsw"
#define fndDev "/dev/fnd"

void* dotPrint(void*);
void* dipGet(void*);
void* ledPrint(void*);
void* tactGet(void*);
void* fndPrint(void*);

int row[8][DotLen] ={//      //        //        //          //          //
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,1,0,1,1,1,0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,1,0,1,0,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,1,0,0,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

static unsigned char c;
static unsigned int saveKeyPad;
static unsigned int enterKeyPad;

int main(void)
{
    int value;
    pthread_t pid[5];

    pthread_create(&pid[4], NULL, fndPrint, (void*)&value);
    pthread_create(&pid[3], NULL, tactGet, (void*)&value);
    pthread_create(&pid[2], NULL, ledPrint, (void*)&value);
    pthread_create(&pid[1], NULL, dotPrint, (void*)&value);
    pthread_create(&pid[0], NULL, dipGet, (void*)&value);
    pthread_join(pid[0], (void**)&value);
    pthread_join(pid[1], (void**)&value);
    pthread_join(pid[2], (void**)&value);
    pthread_join(pid[3], (void**)&value);
    pthread_join(pid[4], (void**)&value);
    
    return 0;
}

void* dotPrint(void* value)
{
    unsigned char dotData[8];
    int dotFd = 0;
    int i, j;
    
    dotFd = open(DotDev, O_RDWR);
    if(dotFd <0){
        printf("Can't Open %s\n", DotDev);
        return;
    }

    while(1)
    {
        if(c == DIPSW && enterKeyPad == PASSWORD)
        {
            memset(dotData, 0, 8);
            for(i = 0; i < DotLen; i++)
            {
                for(j = 0; j < 8; j++)
                {
                    dotData[j] <<= 1;
                    dotData[j] += row[j][i];
                }
                if(c != DIPSW)
                {
                    memset(dotData, 0, 8);
                    write(dotFd, dotData, sizeof(dotData));
                    break;
                }
                if(enterKeyPad != PASSWORD)
                {
                    memset(dotData, 0, 8);
                    write(dotFd, dotData, sizeof(dotData));
                    break;
                }
                write(dotFd, dotData, sizeof(dotData));
                usleep(80000);
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
        usleep(1000000);
    }
}

void* ledPrint(void* value)
{
    unsigned char ledData;
    int ledFd = 0;

    if((ledFd = open(LedDev, O_RDWR)) < 0)
    {
        printf("Can't open %s\n", LedDev);
        return;
    }

    while(1)
    {
        ledData = 0xff - c;
        
        write(ledFd, &ledData, sizeof(unsigned char));
        usleep(1000000);
    }
}

void* tactGet(void* value)
{
    int tactswFd = 0;
    unsigned char keyPad;

    if((tactswFd = open(tactswDev, O_RDONLY)) < 0)
    {
        printf("Can't open %s\n", tactswDev);
        return;
    }

    while(1)
    {
        read(tactswFd, &keyPad, sizeof(keyPad));
        if(keyPad != 0)
        {
            if(keyPad == 10)
            {
                saveKeyPad = 0; // 鍮꾨?踰덊샇 ?섎せ ?낅젰?덉쓣 ?? 蹂??珥덇린???⑸룄
                printf("KEYPAD => RETRY\n");
            }
            if(keyPad == 12)
            {
                enterKeyPad = saveKeyPad; // 鍮꾨?踰덊샇 ?낅젰??留덉낀???? ???댁젣
                printf("KEYPAD => TRY ENTER\n");
            }
            if(keyPad != 10 && keyPad != 12)
            {
                if(keyPad == 11)
                {
                    keyPad = 0;
                }
                saveKeyPad *= 10;
                saveKeyPad += keyPad;
                printf("KEYPAD => %d\n", keyPad);
            }
        }
        usleep(1500000);
    }
}

void* fndPrint(void* value)
{
    unsigned char FND_DATA_TBL[11]={
        0xc0,
        0xF8,0x80,0x90,
        0x99,0x92,0x82,
        0xF9,0xA4,0xB0,
        0xFF
    };
    int fndFd = 0;
    int getSKP;
    unsigned char fndNum[4];
    char a=0, b=0, c=0, d=0;

    while(1)
    {
        if(getSKP != saveKeyPad)
        {
            getSKP = saveKeyPad;
            a = 10;
            fndNum[0] = FND_DATA_TBL[a];
            b = c;
            fndNum[1] = FND_DATA_TBL[b];
            c = d;
            fndNum[2] = FND_DATA_TBL[c];
            d = saveKeyPad % 10;
            fndNum[3] = FND_DATA_TBL[d];

            if((fndFd = open(fndDev, O_RDWR)) < 0)
            {
                printf("Can't open %s\n", fndDev);
                return;
            }
            write(fndFd, &fndNum, sizeof(fndNum));
        }
        usleep(1000000);
        close(fndFd);
    }
}
