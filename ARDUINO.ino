#include <Servo.h>

Servo barrera; // se crea un objeto tipo servo (motor de la barrera)
 // Inicialización de constantes y asignacion de pines al sensor y a los leds.
  int Trig = 5;
  int Echo = 6;
  int coches = 0;
 const int LEDV=11;
 const int LEDR=13;
void setup() {
  
 Serial.begin(9600);
  // Declaración de pines
 pinMode(LEDV,OUTPUT);
 pinMode(LEDR, OUTPUT);
 pinMode(Trig, OUTPUT);
 pinMode(Echo, INPUT);
 
 // Si se inicializa el led rojo ecendido y el verde apagado (simulando un semáforo).
 digitalWrite(LEDV, LOW);
 digitalWrite(LEDR,HIGH);
 barrera.attach(9);// Pin de la barrera 9.
}

void loop() {

 barrera.write(0); // Se inicializa la barrera a 0 grados(bajada)
 // El sensor HC-SR04 calcula el tiempo que tarda en lanzar la señal y recibirla y mediante una fórmula calculamos la distancia a la cual esta el objeto más cercano.
 int limite=8;
 unsigned long DISTANCIA;
 unsigned long tiempo;
 // 
 digitalWrite(Trig, LOW);
 delayMicroseconds(4);
 digitalWrite(Trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(Trig, LOW);

 tiempo = pulseIn(Echo, HIGH);
 tiempo=tiempo/2;

 DISTANCIA=tiempo/29;
 
Serial.println(DISTANCIA); // Se imprime en el monitor la distancia en centimetros.
Serial.print("cm");

  

if (DISTANCIA<limite) // Si la distancia es inferior al limite (8cm) empezará el proceso de entrada del vehiculo al PARKING.
{
  
if (coches<3){ // Si ya hay 3 coches en el parking, no tendrá acceso al siguente.
    
  coches=coches+1; // Suma uno cada vez que pasa un coche.
  //Se activa el led verde y apaga el rojo del semaforo.
  digitalWrite(LEDR,LOW);
  digitalWrite(LEDV,HIGH);
  delay(500); // Metodo para esperar 500 microsegunos
  barrera.write(90); // El motor levantará la barrera 90 grados de su posición original.
  delay(3000); 

}

else 
{
  Serial.print("EL PARKING ESTA LLENO");
  }
}
else // Si la distancia no es inferior al limite el semáforo y la barrera permaneceran en su posicion original.
{
  digitalWrite(LEDR,HIGH);
  digitalWrite(LEDV,LOW);
  barrera.write(0);
}

delay(1000);
}
