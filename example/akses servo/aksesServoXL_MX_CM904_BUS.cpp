/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define ID_NUM 3
#define ID_NUMA 2
Dynamixel Dxl(DXL_BUS_SERIAL3);
Dynamixel DxlA(DXL_BUS_SERIAL1);

void setup() {
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  DxlA.begin(3);
  Dxl.jointMode(ID_NUM);
 DxlA.jointMode(ID_NUMA); //jointMode() is to use position mode
  //Dxl.begin(3);
  //Dxl.jointMode(ID_NUM);
}

void loop() {
  /*ID 1 dynamixel moves to position 0 with velocity 100 */
  Dxl.setPosition(ID_NUM,0,100);
  DxlA.setPosition(ID_NUMA,0,100);
  delay(1000);// it has more delay time for slow movement
  /*ID 1 dynamixel moves to position 500 with velocity 300 */
  Dxl.setPosition(ID_NUM,500,300);
  DxlA.setPosition(ID_NUMA,500,300);
  delay(500);
}
