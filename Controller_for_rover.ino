#include <FilterTwoPole.h>
#include <FilterDerivative.h>
#include <FloatDefine.h>
#include <FilterOnePole.h>
#include <RunningStatistics.h>
#include <Filter.h>
#include <SharpIR.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <SharpIR.h>
#include <I2C.h>

ExponentialFilter<float> Filtereddis1(50, 0);
ExponentialFilter<float> Filtereddis2(50, 0);
ExponentialFilter<float> Filtereddis3(50, 0);
ExponentialFilter<float> Filtereddis4(50, 0);
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo myservoX;
Servo myservoY;

int x = 30;
int y = 15;
int a = 50 ;
int b = 15 ;
String inString="";
int j;
long Changedirection;

#define IR1 A15
#define IR2 A14
#define IR3 A13
#define IR4 A12
#define model1 1080
#define model2 430
#define SCL_PORT PORTC
#define SDA_PORT PORTC
#define SCL_PIN 5        
#define SDA_PIN 4        

SharpIR SharpIR1(IR1, model1);
SharpIR SharpIR3(IR3, model1);
SharpIR SharpIR2(IR2, model2);
SharpIR SharpIR4(IR4, model2);

// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;

// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

void setup() {
  Serial.begin(115200);
  I2c.begin();
  servo1.attach (53);
  servo2.attach (52);
  servo3.attach (50);
  servo4.attach (47);
  servo5.attach (51);
  
  servo1.write (x);
  servo2.write (x);
  servo3.write (x);
  servo4.write (x);
  servo5.write (x);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myservoX.attach(40);
  myservoY.attach(41);
  Serial.begin(115200);
  myservoX.write(a);
  myservoY.write(b);
}

void demo1()
  {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
        for (int j = 150; j < 250; j++)
          {
            analogWrite(enA, j);
            analogWrite(enB, j);
            delay(2);
          }
   }  
   
void demo2()
   {  
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);  
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH); 
        for (int j = 150; j < 250; j++)
          {
           analogWrite(enA, j);
           analogWrite(enB, j);
           delay(2); 
          }
    }  
    
void demo3()
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);  
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW); 
        for (int j = 150; j < 250; j++)
          {
           analogWrite(enA, j);
           analogWrite(enB, j);
           delay(2);
           }
    }

void demo4()
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

        for (int j = 150; j < 250; j++)
           {
           analogWrite(enA, j);
           analogWrite(enB, j);
           delay(2);
           }
    }  

void demo5()
    {  
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);  
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enB, 200);
      analogWrite(enA, 200);
    }

void loop() { 
  
  while (Serial.available()>0){
    int inChar = Serial.read();
    if (isDigit(inChar)){
      inString += (char)inChar;
    }
       if (inString.toInt() == 5)
        {a = a - 1; 
        myservoX.write(a);
        demo2();
        delay(10);
        demo1();
        delay(50);
        }
        
       if (inString.toInt() == 6)
        {a = a + 1; 
        myservoX.write(a);
        demo3();
        delay(10);
        demo1();
        delay(50);
        }
        
       if (inString.toInt() == 8)
        {b = b + 1; 
        myservoY.write(b);
        Serial.flush();
        }
        
       if (inString.toInt() == 7)
        {b = b - 1; 
        myservoY.write(b);
        //delay(50);
        }
        
        inString="";
  
  }
  
  while (Serial.available()<=0) {
  
      uint16_t i;
      if (x <= 30)
        {while (servo1.read() < 90) 
          { x = x + 2;
          servo1.write(x);
          servo2.write(140-x);
          servo3.write(90-x);
          servo4.write(30+x);
          servo5.write(x-20);
  
            float Rawdis1=SharpIR1.distance();
            Filtereddis1.Filter(Rawdis1);
            float dis1 = Filtereddis1.Current();
            
            if (dis1 > 60){
            dis1 = 60;
            }
             
            float Rawdis2=SharpIR2.distance();  
            Filtereddis2.Filter(Rawdis2);
            float dis2 = Filtereddis2.Current();
            
            if (dis2 > 30){
            dis2 = 30;
            }
       
            float Rawdis3=SharpIR3.distance(); 
            Filtereddis3.Filter(Rawdis3);
            float dis3 = Filtereddis3.Current();
            
            if (dis3 > 60){
            dis3 = 60;
            }
  
            float Rawdis4=SharpIR4.distance();  
            Filtereddis4.Filter(Rawdis4);
            float dis4 = Filtereddis4.Current();
            
            if (dis4 > 30){
            dis4 = 30;
            }
  
            I2c.write(0x10,'D');  
            I2c.read(0x10,2);     
            i = I2c.receive();        
            i = i<<8 | I2c.receive();       
            delay(50);
          
            if (i/10 > 40 || i< 0){
            demo1();
            delay(500);
            } 
           
            else if(dis1 <= 20 || dis2 <= 15){
            demo3();
            delay((90-x)*10);         
            }
          
            else if(dis3 <= 20 || dis4 <= 15){
            demo2();
            delay((90-x)*10);
            }
           
            else if(i/10 <40 && i> 1){
            demo5();
            demo4();
            delay(500);
            demo2();
            delay(100);
           
            if (Serial.available()>0){break;}   
            }
            
          if (Serial.available()>0){break;}
  
          
          }
        }
      if (x >= 90)
        { while (servo1.read() > 30) 
          {x = x - 2;
            servo1.write(x);
            servo2.write(140-x);
            servo3.write(90-x);
            servo4.write((x+30));
            servo5.write(x);
            servo5.write(x-20);
   
            float Rawdis1=SharpIR1.distance(); // this returns the distance to the object you're measuring
            Filtereddis1.Filter(Rawdis1);
            float dis1 = Filtereddis1.Current();
            if (dis1 > 60){
            dis1 = 60;}
  
            float Rawdis2=SharpIR2.distance();  
            Filtereddis2.Filter(Rawdis2);
            float dis2 = Filtereddis2.Current();
            if (dis2 > 30){
            dis2 = 30;}
  
            float Rawdis3=SharpIR3.distance();  
            Filtereddis3.Filter(Rawdis3);
            float dis3 = Filtereddis3.Current();
            if (dis3 > 60){
            dis3 = 60;}
  
            float Rawdis4=SharpIR4.distance();  
            Filtereddis4.Filter(Rawdis4);
            float dis4 = Filtereddis4.Current();
            if (dis4 > 30){
            dis4 = 30;}
  
            I2c.write(0x10,'D');  
            I2c.read(0x10,2);     
            i = I2c.receive();        
            i = i<<8 | I2c.receive(); 
          
            delay(50);
      
          if (i/10 > 40 || i< 1){
            demo1();
            delay(50);
           } 
               
          else if(dis1 <= 20 || dis2 <= 15){
            demo3();
            delay((90-x)*10);
           }
          
          
          else if(dis3 <= 20 || dis4 <= 15){
            demo2();
            delay((90-x)*10);
           }
  
          else if(i/10 <40 && i> 1){
            demo5();
            demo4();
            delay(500);
            demo2();
            delay(100);
          }
  
          if (Serial.available()>0){break;}
       
          }
        }            
   }
 }




    
 
