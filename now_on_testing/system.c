#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

struct termios new_settings,initial_settings;

void set_nodelay_mode(){
    int termflags;
    termflags=fcntl(0,F_GETFL);
    termflags |=O_NDELAY;
    fcntl(0, F_SETFL,termflags);
}

int get_ok_char(){
    int c;
    while((c=getchar())!=EOF&&strchr("ikjla",c)==NULL);
    return c;
}

void init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}
