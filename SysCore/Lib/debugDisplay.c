
#include<stdarg.h>
#include<string.h>
#include<debugDisplay.h>

#define VID_MEMORY 0xB8000
#define COLS 80
#define ROWS 25

// this tells us about the current postion on the screen
static unsigned int xPos=0,yPos=0;

// this is used to set the bounding box so that after debugGoToXY box will start at x,y instead of corner of screen(0,0) 
// the actual box will not change but the all the next text will start from x,y
static unsigned int startX=0,startY=0;

static unsigned color=0;


void debugPutC(unsigned char c){
    if(c==0){
        return;
    }
    if(c=='\n' || c=='\r' || xPos>79){
        yPos+=1;
        xPos=startX;
        return;
    }
    unsigned char*p =(unsigned char *)(VID_MEMORY) + (xPos)*2+ yPos*COLS*2;
    *p++=c;
    *p=color;
    xPos++;
}
//temporary buffer used by the itoa func
char tbuf[32]; 
char hexchars[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void itoa(unsigned i,int base,char*buf){
    int pos=0;
    int idx=0;
    

    if(i==0 || base>16){
        buf[0]='0';
        buf[1]='\0';
        return;
    }

    while(i!=0){
        tbuf[pos++]=hexchars[i%base];
        i=i/base;

    }
    
    for(idx=0;idx<pos;idx++){
        buf[idx]=tbuf[pos-idx-1];
    }
    buf[pos]=0;


}

void itoa_s(signed i,int base,char*buf){
    if(base>16) return;
    if(i<0){
        *buf='-';
        buf++;
        i*=-1;
    }
    itoa(i,base,buf);

}

unsigned debugSetColor(const unsigned c){
    unsigned t=color;
    color=c;
    return t;
}

void debugGoToXY(unsigned x,unsigned y){
    xPos=x;
    yPos=y;
    startX=xPos;
    startY=yPos;
    
}

void debugClrScr(const unsigned short c){
    unsigned char *p=(unsigned char*)VID_MEMORY;
    for(int i=0;i<4000;i+=2){
        p[i]=' ';
        p[i+1]=c;
    }
    xPos=startX;
    yPos=startY;
    
}

void debugPutS(char *str ){
    if(!str) return;

    for (size_t i = 0; i < strlen(str); i++)
    {
        debugPutC(str[i]);
    }
    
}

int debugPrintf(const char* str,...){
    if(!str){
        return 0;
    }
    va_list args;
    va_start(args,str);
    for(size_t i=0;i<strlen(str);i++){
        switch(str[i]){
            case '%':

                switch(str[i+1]){
                    // chars
                    case 'c':{
                        char c=va_arg(args,char);
                        debugPutC(c);
                        i++;
                        break;
                    }

                    case 'd':
                    case 'i':{
                        int c=va_arg(args,int);
                        char str[32]={0};
                        itoa_s(c,10,str);
                        debugPutS(str);
                        i++;
                        break;
                    }

                    case 'x':
                    case 'X':{
                        int c=va_arg(args,int);
                        char str[32]={0};
                        itoa_s(c,16,str);
                        debugPutS(str);
                        i++;break;
                    }
                    default:
                        va_end(args)
                        return 1;
                    
                }
                break;

            default:
                debugPutC(str[i]);
                break;
        }   
    }
    va_end(args)
}

