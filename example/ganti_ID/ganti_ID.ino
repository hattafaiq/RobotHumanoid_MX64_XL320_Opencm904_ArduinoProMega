#define DXL_BUS_SERIAL1 1
#define NEW_ID 2
Dynamixel Dxl(DXL_BUS_SERIAL1);
void setup(){
  Dxl.begin(3);
  Dxl.jointMode(NEW_ID);
}
void loop(){
  Dxl.setID(BROADCAST_ID, NEW_ID);
}
