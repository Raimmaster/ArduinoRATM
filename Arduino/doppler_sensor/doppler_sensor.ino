a termin/* HC-SR04 Sensor
 *  

  ***EL CIRCUITO***
  *VCC conectado a POWER +5V
  *GND conectado a GND
  *TRIG conectado al pin digital 2
  *ECHO conectado al pin digital 4
     
   Original code for Ping))) example was created by David A. Mellis
   Adapted for HC-SR04 by Tautvidas Sipavicius

   This example code is in the public domain.
   This code example by flakas in: https://gist.github.com/flakas/3294829#file-hc-sr04-ino
*/

const int trigPin = 2;
const int echoPin = 4;

void setup() {
  // inicializando comunicación serial
  Serial.begin(9600);
}

void loop()
{
  long duration, cm;

  //El sensor es activado por un pulso HIGH de 10 o más µs
  //Damos un pulso LOW Primero para asegurar un pulso HIGH limpio
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Leemos la señal del sensor: un pulso HIGH cuya duración
  //es el tiempo en µs del ping enviado a la recepción del eco
  //del objeto
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convertir el tiempo en distancia
  cm = microsecondsToCentimeters(duration);
  int l_byte = cm % 256;
  int h_byte = cm / 256;
  //Mandar la distancia en dos bytes para que
  //el puerto serial pueda manejar el tamaño
  Serial.write(l_byte);
  Serial.write(h_byte);
  //Serial.print(cm);
  //Serial.println(" cm");
  
  delay(1000);
}


long microsecondsToCentimeters(long microseconds)
{ 
  //Velocidad del sonido es 340 m/s o 29.4118 microsegundos por centímetro
  //Encontramos la mitad del tiempo (dividimos entre 58) porque 
  //el tiempo que obtenemos es el de ida y venida
  return microseconds / 58;
}
