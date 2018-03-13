

void MotorsInit();
  
#define STOP 0

/*
 * 
 * GLOBAL VARIABLES
 * 
 */

 /****Motor Variables****/
unsigned int _offsetM1;
unsigned int _offsetM2;
unsigned int _offsetM3;
unsigned int _offsetM4;

static const unsigned char _M1PWM = 3;
static const unsigned char _M2PWM = 4;
static const unsigned char _M3PWM = 29;
static const unsigned char _M4PWM = 30;

unsigned char _M1DIR = 2;
unsigned char _M2DIR = 5;
unsigned char _M3DIR = 6;
unsigned char _M4DIR = 7;

unsigned char _M1CS = A15;
unsigned char _M2CS = A17;
unsigned char _M3CS = A18;
unsigned char _M4CS = A19;

int max_speed = 255;
int pause = 10;

//******CAMERA********//
double ballAngle;
