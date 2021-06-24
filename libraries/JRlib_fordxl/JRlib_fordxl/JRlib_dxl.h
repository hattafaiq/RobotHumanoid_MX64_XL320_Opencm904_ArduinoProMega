#include "wirish.h"
#include "dxl_devices.h"
//#include "wirish.h"
#include <Dynamixel.h>

void ceckingServo(int jumlah_servo);
void startingServo(void);
void servoOn(int id);
void servoOff(int id);
void servoxlWrite (int id, int pos, int sudut);
void servomxWrite (int id, int pos, int sudut);
int servoxlRead(int id);
int servomxRead(int id);
void centerposMx(int id);
void centerposXl(int id);
//void writeAllServo (int jumlah_servo, int sudut, int speed);
