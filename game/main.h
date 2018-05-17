#define PI 3.1415926535
#define Gravity 9.8

struct coeffient{
    float angle;
    float power;
    float a;
    float b;
    int direction;
};

typedef struct coeffient element;

void set_nodelay_mode();
int get_ok_char();
void init_keyboard();
void get_screen(int posX,int posY);
void move_screen(int command,int *posX,int *posY);
void equation(element *store);
void parabola(element store,int pos_X,int pos_Y,char bomb);

int map[1000][1000];

