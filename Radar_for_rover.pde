  import processing.serial.*;
  String inString;
  Serial myPort;        
  int xPos = 1;         
  float inByte = 0;
  ChildApplet child;
  int value1 = 0;
  int value2 = 0;
  int value3 = 0;
  int value4 = 0;
  int value5 = 0;

void settings (){
    size(1000, 1000);
    smooth();
}

   void setup () {
    surface.setTitle("Main sketch");
    child = new ChildApplet();
    myPort = new Serial(this, Serial.list()[2], 9600);
    myPort.bufferUntil('\n');   
  }
 
int n =1;
float speed = (PI/180);
float a = 30 * (PI/180) + PI;
 
  void draw () {
  
      fill(0,10);
      noStroke();
      rect(0,0,width,height);
 
       float px1 = width/2 + cos( a - (PI/2)  )* value1;
       float py1 = height/2 + sin( a - (PI/2) )*value1;
 
       float px2 = width/2 + cos( a+ (PI/2) )*value2;
       float py2 = height/2 + sin( a+ (PI/2)  )*value2;
 
       float px3 = width/2 + cos( a - (PI/2) )*value3;
       float py3 = height/2 + sin( a - (PI/2) )*value3;
 
       float px4 = width/2 + cos( a + (PI/2) )*value4;
       float py4 = height/2 + sin( a +(PI/2)  )*value4;
 
       float px5 = width/2 + cos( a  )*value5;
       float py5 = height/2 + sin( a  )*value5;
 
       stroke(0,255,0,120);
       strokeWeight(3);
       line(width/2-65,height/2-65, px1 - 65, py1 - 65);
 
       stroke(255,0,0,120);
       strokeWeight(3);
       line(width/2+65,height/2+65,px2+65,py2+65);

       stroke(0,0,255,120);
       strokeWeight(3);
       line(width/2-65,height/2+65,px3-65,py3+65);
 
       stroke(255,255,255,120);
       strokeWeight(3);
       line(width/2+65,height/2-65,px4+65,py4-65);

       stroke(255,255,0,120);
       strokeWeight(3);
       line(width/2,height/2,px5,py5);
 
       stroke(204, 250, 250);
       strokeWeight(3);
       rect(400, 340, 200, 390,7);
 
    if (a >= 150 * (PI/180) + PI) {
      n=-1;
    } 
    
    if (a <= 30 * (PI/180) + PI) {
      n=1;
    }
      
    
      a+=speed*n;
  }
  
  void serialEvent (Serial myPort) {
      String inString = myPort.readStringUntil('\n');
      if (inString != null) {
      inString = trim(inString);
      String sensors[] = split(inString, ',');
      if(sensors.length>1) {
      value1 = int(sensors[0]); 
      value2 = int(sensors[1]); 
      value3 = int(sensors[2]); 
      value4 = int(sensors[3]);
      value5 = int(sensors[4]);
      //println(inString);
      //print(',');
      //println(value2);
      //print(',');
      //println(value3);
      //print(',');
      //println(value4);
      //print(',');
      //println(value5);
    }
    }
  }
  

int i = 120;
class ChildApplet extends PApplet {
 
  
float[] X1;
float[] Y1;
float[] X2;
float[] Y2;
float[] X3;
float[] Y3;
float[] X4;
float[] Y4;
float[] X5;
float[] Y5;

  public ChildApplet() {
    super();
    PApplet.runSketch(new String[]{this.getClass().getName()}, this);
  }

  public void settings() {
    size(1000, 1000, P2D);
    smooth();
  }
  public void setup() { 
    surface.setTitle("Enviroment_radar_2s");
    frameRate(40);
    X1 = new float[i];
    Y1 = new float[i];
    X2 = new float[i];
    Y2 = new float[i];
    X3 = new float[i];
    Y3 = new float[i];
    X4 = new float[i];
    Y4 = new float[i];
    X5 = new float[i];
    Y5 = new float[i];
  }

  public void draw() {
    
      fill(0,10);
      noStroke();
      rect(0,0,width,height); 
     //px1[i] = px1[i-1];
     //py1[i] = py1[i-1]; 
   
      float px1 = width/2 + cos( a - (PI/2)  )* value1;
      float py1 = height/2 + sin( a - (PI/2) )*value1;
 
      float px2 = width/2 + cos( a+ (PI/2) )*value2;
      float py2= height/2 + sin( a+ (PI/2)  )*value2;
 
      float px3= width/2 + cos( a - (PI/2) )*value3;
      float py3= height/2 + sin( a - (PI/2) )*value3;
 
      float px4= width/2 + cos( a + (PI/2) )*value4;
      float py4= height/2 + sin( a +(PI/2)  )*value4;
 
      float px5= width/2 + cos( a  )*value5;
      float py5= height/2 + sin( a  )*value5;
 
       X1[i-1]=px1;
       Y1[i-1]=py1;
       X2[i-1]=px2;
       Y2[i-1]=py2;
       X3[i-1]=px3;
       Y3[i-1]=py3;
       X4[i-1]=px4;
       Y4[i-1]=py4;
       X5[i-1]=px5;
       Y5[i-1]=py5;

       if (i == 120){
         stroke(0,255,0,5000);
         strokeWeight(3);
         println(X1);
             for (int i = 0; i < 120; i++) {
                 point(X1[i]-65,Y1[i]-65);
                  point(X2[i]+65,Y2[i]+65);
                   point(X3[i]-65,Y3[i]+65);
                    point(X4[i]+65,Y4[i]-65);
                      point(X5[i],Y5[i]);
       }
     i = 0;
   }
   
    stroke(204, 250, 250);
    strokeWeight(3);
    rect(400, 340, 200, 390,7);
 
    if (a >= 150 * (PI/180) + PI) {
      n=-1;
    } 
    
    if (a <= 30 * (PI/180) + PI) {
      n=1;
    }
    a+=speed*n;
    i++;

    }
  }
  
  
