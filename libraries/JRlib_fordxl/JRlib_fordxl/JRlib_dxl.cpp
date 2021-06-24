#include "JRlib_dxl.h"
#define onboard_ser 1
#define cm485exp 3


Dynamixel servo_xl (onboard_ser);
Dynamixel servo_mx (cm485exp);

void ceckingServo(int jumlah_servo){
  int suhu[jumlah_servo],model[jumlah_servo];
  float tegangan[jumlah_servo];
  SerialUSB.println("==============================================================");
    SerialUSB.println("                        CECK ON CM904                           ");
	 SerialUSB.println("===============================================================");
   SerialUSB.println("Untuk DXL yang terhubung pada port onboard OPNCM9.04");
   for (int i=1; i<jumlah_servo+1; i++){
    suhu[i]=servo_xl.readByte(i,43);
    tegangan[i]=((float)(servo_xl.readByte(i,42)))/10;
    model[i]=servo_xl.getModelNumber(i);
   
	if(model[i] != 12 && model[i] != 300 &&  model[i] != 18 &&  model[i] != 29 &&  model[i] != 1 &&  model[i] != 54 &&  model[i] != 64 &&  model[i] != 350)continue;
    SerialUSB.print("ID : "); 
    SerialUSB.print(i); 
    SerialUSB.print(" | MODEL ");
    if(model[i] == 12)
      SerialUSB.print(": AX-12A");

    else if(model[i] == 300)
      SerialUSB.print(": AX-12W");

    else if(model[i] == 18)
      SerialUSB.print(": AX-18A");

    else if(model[i] == 29)
      SerialUSB.print(": MX-28");     

    else if(model[i] == 54 || model[i]== 1 )
      SerialUSB.print(": MX-64");

    else if(model[i] == 64)
      SerialUSB.print(": MX-106");

    else if(model[i] == 350)
      SerialUSB.print(": XL-320"); 
    else {  SerialUSB.print(": Not Connect"); }
      
      SerialUSB.print(" | Suhu : "); SerialUSB.print(suhu[i]);
      SerialUSB.print(" C "); SerialUSB.print(" | Tegangan : ");
      SerialUSB.print(tegangan[i]); SerialUSB.println(" DONE!");
      //SerialUSB.println("___________________________________________");
  }
   SerialUSB.println("==============================================================");
    SerialUSB.println("                        CECK EXP485                           ");
	 SerialUSB.println("===============================================================");
   SerialUSB.println("Untuk DXL yang terhubung pada port CM845 EXP");
  
  for (int i=1; i<jumlah_servo+1; i++){
    suhu[i]=servo_mx.readByte(i,43);
    tegangan[i]=((float)(servo_mx.readByte(i,42)))/10;
    model[i]=servo_mx.getModelNumber(i);
   
	if(model[i] != 12 && model[i] != 300 &&  model[i] != 18 &&  model[i] != 29 &&  model[i] != 1 &&  model[i] != 54 &&  model[i] != 64 &&  model[i] != 350)continue;
    SerialUSB.print("ID : "); 
    SerialUSB.print(i); 
    SerialUSB.print(" | MODEL ");
    if(model[i] == 12)
      SerialUSB.print(": AX-12A");

    else if(model[i] == 300)
      SerialUSB.print(": AX-12W");

    else if(model[i] == 18)
      SerialUSB.print(": AX-18A");

    else if(model[i] == 29)
      SerialUSB.print(": MX-28");     

    else if(model[i] == 54)
      SerialUSB.print(": MX-64");

    else if(model[i] == 64)
      SerialUSB.print(": MX-106");

    else if(model[i] == 350)
      SerialUSB.print(": XL-320"); 
    else {  SerialUSB.print(": Not Connect"); }
      SerialUSB.print(" | Suhu : "); SerialUSB.print(suhu[i]);
      SerialUSB.print(" C "); SerialUSB.print(" | Tegangan : ");
      SerialUSB.print(tegangan[i]); SerialUSB.println(" DONE!");
     // SerialUSB.println("___________________________________________");
  }
  
  
}

void startingServo(){
	
  servo_xl.begin(3);
  servo_mx.begin(3);
  SerialUSB.println("Inisialisasi selesai");
  delay(1000);
  
}

void servoOn(int id){
	servo_xl.writeByte(id,24,1);
	servo_mx.writeByte(id,24,1);
}

void servoOff(int id){
	servo_xl.writeByte(id,24,0);
	servo_mx.writeByte(id,24,0);
}

void servoxlWrite (int id, int pos, int kec){
	
	servo_xl.setPosition(id,pos,kec);
	//servo_mx.setPosition(id,pos,kec);
	
}

void servomxWrite (int id, int pos, int kec){
	
	servo_mx.setPosition(id,pos,kec);
	//servo_mx.setPosition(id,pos,kec);
	
}

int servoxlRead(int id){
	return servo_xl.getPosition(id);
}

int servomxRead(int id){
	return servo_mx.getPosition(id);
}
	
void centerposXl(int id){
		servo_xl.goalPosition(id,512);

}

void centerposMx(int id){
	servo_mx.goalPosition(id,2027);
}

