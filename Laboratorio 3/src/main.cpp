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
#define boton3 21
#define boton4 19

//Parámetros PWM para led rojo
#define pwmChannelLedR 1    // 16 canales 0-15
#define freqPWMLedR 5000    //frecuencia en Hz
#define resolutionPWMLedR 8 //8 bits de resolucion (0-255)
#define pinPWMLedR 12        //GPIO  para tener la salida del PWM

//Parámetros PWM para led verde
#define pwmChannelLedV 2    // 16 canales 0-15
#define freqPWMLedV 5000    //frecuencia en Hz
#define resolutionPWMLedV 8 //8 bits de resolucion (0-255)
#define pinPWMLedV 14       //GPIO  para tener la salida del PWM

//Parámetros PWM para led azul
#define pwmChannelLedA 3    // 16 canales 0-15
#define freqPWMLedA 5000    //frecuencia en Hz
#define resolutionPWMLedA 8 //8 bits de resolucion (0-255)
#define pinPWMLedA 27        //GPIO  para tener la salida del PWM

//Parámetro PWM servo motor
#define pwmChannelServo 0
#define freqPWMServo 50       //frecuencia en Hz
#define resolutionPWMServo 16 //16 bits
#define pinPWMServo 13        //GPIO  para tener la salida del PWM

int contador = 0;
//*****************************************************************************
//Prototipos de funcion
//*****************************************************************************
void configurarPWMLedR(void);
void configurarPWMLedV(void);
void configurarPWMLedA(void);
void configurarPWMServo(void);
void configurarBoton1(void);
void LedV();
void moverServo();

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
  pinMode(boton3, INPUT_PULLUP);
  pinMode(boton4, INPUT_PULLUP);
  pinMode(pinPWMServo, OUTPUT);
  configurarPWMServo();
  configurarPWMLedR();
  configurarPWMLedV();
  configurarPWMLedA();
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
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(pinPWMLedR, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(pinPWMLedR, dutyCycle);   
    delay(15);
  }
}

//*****************************************************************************
//Función para configurar módulo PWM
//*****************************************************************************
void configurarPWMLedR(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedR, freqPWMLedR, resolutionPWMLedR);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedR, pwmChannelLedR);
}

void configurarPWMLedV(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedV, freqPWMLedV, resolutionPWMLedV);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedV, pwmChannelLedV);
}

void configurarPWMLedA(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedA, freqPWMLedA, resolutionPWMLedA);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedA, pwmChannelLedA);
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
}

void LedV(){
  ledcWrite(pwmChannelServo, 255); // tell servo to go to position in variable 'pos'
}