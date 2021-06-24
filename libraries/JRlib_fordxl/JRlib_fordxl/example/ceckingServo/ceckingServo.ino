#include <dxl_devices.h>
#include <JRlib_dxl.h>
/*================================================
Library for dynamixel 
by : jihad rahmawan, indonesia | jihadrahmawan20@gmail.com
=================================================== 
Isi konten lirary
Librari ini bekerja pada serial 1 opencm 9.04 untuk servo seri XL,AX
dan serial 3 opencm 9.04 (cm 485EXP ) untuk servo MX
1. ceckingServo (jumlah servo anda); -> untuk cecking kondisi semua servo dg pencarian ID scr otomatis
2. startingServo (); ->inisialisasi servo dg serial 1 dan serial 3 dg Baudrate 1MBps
3. servoxlWrite (id, goalpos, kecepatan) ->menulis sudut ke servo XL atau AX
4. servomxWrite (id, goalpos, kecepatan) ->menulis sudut ke servo MX
5. servoxlRead (id) -> membaca sudut servo XL atau AX pada id
   contoh: int sudut = servoxlRead(5); -> membaca sudut pada servo id 5 dan memberikan nilai ke 
                                          variable "sudut"
6. servomxRead (id) -> membaca sudut servo MX pada id
7. servoOn (id) -> Enable torsi servo pada id
8. servoOff (id) -> Disable torsi servo pada id
9. centerposXl (id) -> menulis servo XL atau AX pada center posisinya
10. centerposMx (id) -> menulis servo MX pada center posisinya

Teruslah berkarya, sesuai bidang, Demi kemajuan Indonesia
===================================================================
*/


void setup() {
  startingServo();  //inisialisasi servo
  

}

void loop() {
  delay(2000);
  ceckingServo(12); //cecking servo pada sistem dengan jumlah total servo 12
  
}

