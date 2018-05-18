#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <sys/time.h>

void set_nodelay_mode(){
        int termflags;
        termflags=fcntl(0,F_GETFL);
        termflags |=O_NDELAY;
        fcntl(0, F_SETFL,termflags);
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

int get_ok_char(){
        int c;
        while((c=getchar())!=EOF&&strchr("jkliasqp",c)==NULL);
        return c;
}

int main(void)
{
    initscr();
    init_keyboard();
    set_nodelay_mode();
    
    while(1)
    {
        while(1)
        {
            if((command=get_ok_char())!=EOF)
            {
                if(command=='q')
                    break;
                command_function();
            }
            process_function1();
        }
    }
    
    return 0;
}
