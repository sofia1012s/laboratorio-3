//*****************************************************************************
//Universidad del Valle de Guatemala
//BE3015: Electrónica Digital 2
//*****************************************************************************

//*****************************************************************************
//Librerias
//*****************************************************************************
#include <Arduino.h>

//*****************************************************************************
//Definicion etiquetas
//*****************************************************************************

//Botones
#define boton1 23
#define boton2 22
#define boton3
#define boton4

//Leds
#define Led rojo
#define Led verde
#define Led azul

//Parámetros PWM para led
#define pwmChannelLed 3    // 16 canales 0-15
#define freqPWMLed 5000    //frecuencia en Hz
#define resolutionPWMLed 8 //8 bits de resolucion (0-255)
#define pinPWMLed 3        //GPIO  para tener la salida del PWM

//Parámetro PWM servo motor
#define pwmChannelServo 0
#define freqPWMServo 50       //frecuencia en Hz
#define resolutionPWMServo 16 //8 bits de resolucion (0-255)
#define pinPWMServo 13        //GPIO  para tener la salida del PWM

int contador = 0;
//*****************************************************************************
//Prototipos de funcion
//*****************************************************************************
void configurarPWMLed(void);
void configurarPWMServo(void);
void configurarBoton1(void);
void moverServo();
void SetServoPos(float pos);

//*****************************************************************************
//Varibles globales
//*****************************************************************************

//*****************************************************************************
//ISR: interrupciones
//*****************************************************************************

//*****************************************************************************
//configuracion
//*****************************************************************************
void setup()
{
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(pinPWMServo, OUTPUT);
  configurarPWMServo();
}

//*****************************************************************************
//loop principal
//*****************************************************************************
void loop()
{
  if (digitalRead(boton1) == 0)
  {
    contador-=2;
    moverServo();
  }

  if (digitalRead(boton2) == 0)
  {
    contador+=2;
    moverServo();
  }
}

//*****************************************************************************
//Función para configurar módulo PWM
//*****************************************************************************
void configurarPWMLed(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLed, freqPWMLed, resolutionPWMLed);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLed, pwmChannelLed);
}

void configurarPWMServo(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelServo, freqPWMServo, resolutionPWMServo);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMServo, pwmChannelServo);
}

//Botón para mover servo a la derecha
void moverServo()
{
  if (contador == 180)
  {
    contador = 180;
  }

  else if (contador == 0)
  {
    contador = 0;
  }
  else
  {
    int ang = (((contador / 180.0) * 2000) / 20000.0 * 65536.0) + 1634;
    ledcWrite(pwmChannelServo, ang); // tell servo to go to position in variable 'pos'
    delay(15);
  }

  /*
  for (pos = 180; pos >= 0; pos -= 1)
  { // goes from 180 degrees to 0 degrees
    int ang = (((pos / 180.0) * 2000) / 20000.0 * 65536.0) + 1634;
    ledcWrite(pwmChannelServo, ang); // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }*/
}
