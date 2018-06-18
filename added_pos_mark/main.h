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

struct bomb_option{
    int range;
    int power;
};
typedef struct bomb_option boption;

struct charact{
    int posX;
    int posY;
    int hp;
    int gas;
    int range;
    int power;
    int colorType;
    char color;
    boption btype[4];
};

typedef struct coeffient element;
typedef struct charact character;

void chooses_character(character *char0);
void set_nodelay_mode();
int get_ok_char();
void init_keyboard();
void get_screen(int posX,int posY,int msizeX, int msizeY);
void move_screen(int command,int *posX,int *posY, int msizeX, int msizeY);
void equation(element *store);
void parabola(element store,int pos_X,int pos_Y,char bomb,character *char0,character *char1);
void startmenu();
int map[1000][500];

int temp; //
int first; //


void set_mpos(int,int);
void move_char(int *posX, int *posY,int *direct,character* char0);
void set_angle_power(int posX,int posY,element *store);
void make_edge(/*character *char0,character *char1*/);
void if_descent(int Xlength,int Ylength,int *posX,int *posY,character char0);
void add_rectangle(int Xlength,int Ylength,int posX,int posY,int input);
void make_char_option(character char0);
void chooses_option(character *char0);
void moving_map(character char0);
void print_character();
void chooses_map(int *mapNum);
void how_to_play();

extern int mposX,mposY,msizeX,msizeY;
extern int turn;
extern int charColor1, charColor2;
