#define PI 3.1415926535
#define Gravity 9.8
#define MAP_X 120
#define MAP_Y 40

struct coeffient{
    float angle;
    float power;
    float a;
    float b;
    int direction;
};

struct charact{
    int posX;
    int posY;
    int hp;
    int gas;
    int range;
};

typedef struct coeffient element;
typedef struct charact character;

void set_nodelay_mode();
int get_ok_char();
void init_keyboard();
void get_screen(int posX,int posY,int msizeX, int msizeY);
void move_screen(int command,int *posX,int *posY, int msizeX, int msizeY);
void equation(element *store);
void parabola(element store,int pos_X,int pos_Y,char bomb);
void startmenu();
int map[1000][1000];
void set_mpos(int,int);
void move_char(int *posX, int *posY,int *direct,character char0);
void set_angle_power(int posX,int posY,element *store);
void make_edge();
void if_descent(int Xlength,int Ylength,int *posX,int *posY);


extern int mposX,mposY,msizeX,msizeY;
