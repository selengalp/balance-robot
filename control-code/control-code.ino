#include <PID_v1.h>
#include <L3G.h>
#include <LSM303.h>
#include <Wire.h>


//------------------------------------------------------------
//     DEĞİŞKEN VE SABİTLER BURADA TANIMLANACAK
//------------------------------------------------------------

// pid katsayıları
const double kp=0.0;        // oransal katsayısı
const double ki=0.0;        // integral katsayısı
const double kd=0.0;        // türev kaysayısı

// pid değişkenleri
double error=0,referance=0,output=0;

// pid objesi
// error     -> sensörlerden elde edilen hata 
// output    -> pid algoritmasının verdiği çıktı
// referance -> ulaşılması hedeflenen nokta, hatanın sıfır olduğu yer
PID pid1(&error,&output,&referance , kp, ki, kd, DIRECT);

// motor pinleri
const int motorRightForward = 8;
const int motorRightBack = 4;
const int motorRightEnable = 3;
const int motorLeftForward = 11;
const int motorLeftBack = A3;
const int motorLeftEnable = 9;

// Sensörler --> 
// LSM303DLM 3D Compass and Accelerometer-Product 1273
// L3G4200D 3-Axis Gyro-Product 1272
// Sensör nesneleri oluşturuluyor 
L3G gyro;  
LSM303 compass;

// Sensör değişkenleri oluşturuluyor
int gyroValue[3];
int accelerometerValue[3];
int compassValue[3];

 
//-------------------------------------------------------------
//          AYARLAR BU BÖLÜMDE YAPILACAK
//-------------------------------------------------------------

void setup()
{
  // pin modu ayarları
  DDRB = B000000;   // tüm B portu çıkış
  DDRD = B00000000; // tüm D portu çıkış
  pinMode(A3,OUTPUT); // A3 pini çıkış
  
  // pid ayarları
  pid1.SetMode(AUTOMATIC);
  pid1.SetOutputLimits(-255, 255);
  
}

//-------------------------------------------------------------
//      LOOP BÖLÜMÜ
//-------------------------------------------------------------

void loop()
{
}




//------------------------------------------------------------
//        FONKSİYONLAR BURADA TANIMLANACAK
//------------------------------------------------------------        

// Sensörler için ayar fonksiyonu
void adjustSensors(){
  gyro.init();
  gyro.enableDefault();
  compass.init();
  compass.enableDefault();
}


// Sensör okuma fonksiyonu
void readSensors(){  
  gyro.read();
  compass.read();
  
  gyroValue[0] = gyro.g.x;
  gyroValue[1] = gyro.g.y;
  gyroValue[2] = gyro.g.z;
  accelerometerValue[0] = compass.a.x;
  accelerometerValue[1] = compass.a.y;
  accelerometerValue[2] = compass.a.z;
  compassValue[0] = compass.m.x;
  compassValue[1] = compass.m.y;
  compassValue[2] = compass.m.z; 
}

