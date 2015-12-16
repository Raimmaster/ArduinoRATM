/* HC-SR04 Sensor
 * 
  ***EL CIRCUITO***
  *VCC conectado a POWER +5V
  *GND conectado a GND
  *Revisar abajo los pines individuales
     
   Original code for Ping))) example was created by David A. Mellis
   Adapted for HC-SR04 by Tautvidas Sipavicius

   This example code is in the public domain.
   This code originally based by flakas's example in: https://gist.github.com/flakas/3294829#file-hc-sr04-ino
*/

//Frontal sensor, pines
const int f_trigPin = 2;
const int f_echoPin = 4;
//Left sensor, pines
const int l_trigPin = 7;
const int l_echoPin = 8;
//Right sensor, pines
const int r_trigPin = 10;
const int r_echoPin = 12;

void setup() {
  Serial.begin(9600);
}

void loop()
{  
  //Frontal
  writeDistance(getDistance(f_trigPin, f_echoPin), 1);  
  //Left
  writeDistance(getDistance(l_trigPin, l_echoPin), 2);
  //Right  
  writeDistance(getDistance(r_trigPin, r_echoPin), 3);
  delay(1000);
}

/**
 *Escribe la distancia recibida 
 *a través del puerto serial
 */
void writeDistance(int distance, int sensor_id){
  //Mandar la distancia en dos bytes para que
  //el puerto serial pueda manejar el tamaño
  int l_byte = distance % 256;
  int h_byte = distance / 256;
  
  Serial.write(l_byte);
  Serial.write(h_byte);
  Serial.write(sensor_id);
  Serial.flush(); 
}

/**
 * Obtener la distancia recorrida
 */
int getDistance(int trig_pin, int echo_pin){
  //El sensor es activado por un pulso HIGH de 10 o más µs
  //Damos un pulso LOW Primero para asegurar un pulso HIGH limpio
  int duration = 0;
  pinMode(trig_pin, OUTPUT);
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  
  //Leemos la señal del sensor: un pulso HIGH cuya duración
  //es el tiempo en µs del ping enviado a la recepción del eco
  //del objeto
  pinMode(echo_pin, INPUT);
  duration = pulseIn(echo_pin, HIGH);    
  // convertir el tiempo en distancia
  return microsecondsToCentimeters(duration);
}

int microsecondsToCentimeters(int microseconds)
{ 
  //Velocidad del sonido es 340 m/s o 29.4118 microsegundos por centímetro
  //Encontramos la mitad del tiempo (dividimos entre 58) porque 
  //el tiempo que obtenemos es el de ida y venida
  return microseconds / 58;
}
