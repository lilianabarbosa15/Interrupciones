volatile int estado = LOW;                  // Variable global de LOW o HIGH
int ISRPin = 2;                             // Pin que se transformará en una interrupción
unsigned short int ledISR = 7;              // Variable que se conecta a un led y muestra cómo se encuentra la variable estado
unsigned short int leds[3] = {13,12,8};     // Array con los números de los pines donde están conectados los LEDs en serie


void setup(){
  // Inicializamos los pines de los LEDs como salida y a estado bajo
  for (int i = 0; i < 3; i++)
  {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  // Inicialización del pin del LED que representa la variable estado 
  pinMode(ledISR, OUTPUT);
  digitalWrite(ledISR, estado);

  // Inicialización de el pin de la ISR
  pinMode(ISRPin,INPUT);

  //Se configura el pin de interrupción para que detecte un cambio de alto a bajo
  attachInterrupt(digitalPinToInterrupt(ISRPin), cambioEstado, FALLING);
}
 
void loop(){
  // Este bucle recorre el array de izquierda a derecha
  int i = 0;
  for (; i < 3; i++)
  {
    if (i > 0)                              // Solo para el segundo pin y consecutivos apagamos el pin anterior
      digitalWrite(leds[i-1], LOW);         // Apagamos el LED a la izquierda
 
    digitalWrite(leds[i], !estado);         // Encendemos/apagamos en el LED en el que se está
    delay(1000);                            // Esperamos 4000ms
  }
  digitalWrite(leds[i-1], LOW);             // Apagamos el último LED encendido, o sea el elemento 2 del array
}

void cambioEstado(){
  estado = !estado;                 // Cambia el valor de la variable estado (si está en LOW pasa a HIGH y HIGH a LOW)
  digitalWrite(ledISR, estado);     // Se actualiza el estado del LED que representa la interrupción
}
