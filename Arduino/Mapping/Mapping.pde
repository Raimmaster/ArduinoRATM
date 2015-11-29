import processing.serial.*;

Serial myPort;  //lector de puertos seriales
int c = 0;
int[] distancias;
//Variables de distancia
int l_byte = 0;
int h_byte = 0;
boolean has_read = false;
//Lista de objetos detectados
PVector[] detected;
//Constantes de dibujo
static final int E_WIDTH = 10;
static final int baud_rate = 9600;
static final int MAX_DETECTED = 3;//cantidad máxima de objetos que puede detectar el Arduino

void setup() 
{
  size(1080, 700);
  String serialPort = "/dev/ttyACM0";//cambiar dependiendo de computadora
  myPort = new Serial(this, serialPort, baud_rate);    
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  textFont(f, 12);
  detected = new PVector[MAX_DETECTED];
  distancias = new int[MAX_DETECTED];
  //String[] fontList = PFont.list();
  //printArray(fontList);
  //distancia = 200;
}

void draw() {   
  readFromSerialPort();
  background(255, 255, 150);
  fill(c);
  drawSensor();
  drawDetectedObjects();
}

/**
  Reads data from the serial port if and only if it hasn't been read before
**/
void readFromSerialPort(){
  if(/*!has_read && */myPort.available() > 0) {
    for(int i = 0; i < MAX_DETECTED; i++){
      l_byte = myPort.read();
      h_byte = myPort.read();
      
      distancias[i] = (h_byte * 256) + l_byte;//obtener la distancia verdadera con los bytes recibidos
      int cx = 0;
      int cy = 0;
      switch(i){
        case 1://frontal
            cx = width/2 - E_WIDTH + distancias[i];
            cy = height/2 - E_WIDTH;      
            break;
        case 2://left
            cx = width/2 - E_WIDTH;
            cy = height/2 - E_WIDTH - distancias[i];      
            break;
        case 3://right
            cx = width/2 - E_WIDTH;
            cy = height/2 - E_WIDTH + distancias[i];      
            break;
      }        
     
     detected[i] = new PVector(cx, cy);
    }
    //has_read = true;    
  }
}


/**
  Dibuja donde se encuentra el sensor
**/
void drawSensor(){
  int x = width/2 - E_WIDTH, y = height/2 - E_WIDTH;//coordenadas de donde se encuentra el sensor
  ellipseMode(CENTER);
  ellipse(x, y, 10, 10);
  text("o", x, y + 7);  
}

/**
  Dibuja los objetos detectados por el sensor ultrásonico
**/
void drawDetectedObjects(){
  for(int i = 0; i < MAX_DETECTED; i++){    
    if(detected[i] != null){
      ellipseMode(CENTER);
      ellipse(detected[i].x, detected[i].y, 10, 10);
      String actual_dist = (distancias[i]) + " cm ";
      text(actual_dist, detected[i].x + 12, detected[i].y);      
    }
  }
}