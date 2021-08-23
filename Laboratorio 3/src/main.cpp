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
#define boton1 1
#define boton2 22
#define boton3 21
#define boton4 19

//Parámetro PWM servo motor
#define pwmChannelServo 5
#define freqPWMServo 50       //frecuencia en Hz
#define resolutionPWMServo 16 //16 bits
#define pinPWMServo 13        //GPIO  para tener la salida del PWM

//Parámetro PWM led Red
#define pwmChannelLedR 2
#define freqPWMLedR 5000    //frecuencia en Hz
#define resolutionPWMLedR 8 //8 bits
#define pinPWMLedR 12       //GPIO  para tener la salida del PWM

//Parámetro PWM led Green
#define pwmChannelLedG 1
#define freqPWMLedG 5000    //frecuencia en Hz
#define resolutionPWMLedG 8 //8 bits
#define pinPWMLedG 27       //GPIO  para tener la salida del PWM

//Parámetro PWM led Blue
#define pwmChannelLedB 3
#define freqPWMLedB 5000    //frecuencia en Hz
#define resolutionPWMLedB 8 //8 bits
#define pinPWMLedB 26       //GPIO  para tener la salida del PWM

int contador = 0;
int contadorBoton3 = 0;
int contadorBoton4 = 0;

//*****************************************************************************
//Prototipos de funcion
//*****************************************************************************
void configurarPWMLedR(void);
void configurarPWMLedG(void);
void configurarPWMLedB(void);
void configurarPWMServo(void);
void configurarBoton1(void);
void configurarBoton2(void);
void configurarBoton3(void);
void configurarBoton4(void);
void encenderLeds(void);
void moverServo();

//*****************************************************************************
//Varibles globales
//*****************************************************************************

//*****************************************************************************
//ISR: interrupciones
//*****************************************************************************
void IRAM_ATTR ISRBoton3() //interrupción para botón 1 (Aumento)
{
  static unsigned long ultimo_tiempo_interrupcion1 = 0; //último tiempo de la interrupción
  unsigned long tiempo_interrupcion1 = millis();        //tiempo actual de la interrupción

  //Si la interrupcion dura menos de 200ms, asumir que es un rebote e ignorar
  if (tiempo_interrupcion1 - ultimo_tiempo_interrupcion1 > 200)
  {
    contadorBoton3++; //aumenta 1 al contador de botón

    if (contadorBoton3 > 3) //si es mayor a 15 regresa el valor a cero
    {
      contadorBoton3 = 0;
    }
  }
  ultimo_tiempo_interrupcion1 = tiempo_interrupcion1; //actualiza el valor del tiempo de la interrupción
}

void IRAM_ATTR ISRBoton4() //interrupción para botón 1 (Aumento)
{
  static unsigned long ultimo_tiempo_interrupcion2 = 0; //último tiempo de la interrupción
  unsigned long tiempo_interrupcion2 = millis();        //tiempo actual de la interrupción

  //Si la interrupcion dura menos de 200ms, asumir que es un rebote e ignorar
  if (tiempo_interrupcion2 - ultimo_tiempo_interrupcion2 > 200)
  {
    contadorBoton4 += 50; //aumenta 1 al contador de botón

    if (contadorBoton4 > 255) //si es mayor a 15 regresa el valor a cero
    {
      contadorBoton4 = 0;
    }
  }
  ultimo_tiempo_interrupcion2 = tiempo_interrupcion2; //actualiza el valor del tiempo de la interrupción
}
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
  configurarPWMLedG();
  configurarPWMLedB();
  configurarBoton3();
  configurarBoton4();
}

//*****************************************************************************
//loop principal
//*****************************************************************************
void loop()
{
  if (digitalRead(boton1) == 0)
  {
    contador -= 2;
    moverServo();
  }

  if (digitalRead(boton2) == 0)
  {
    contador += 2;
    moverServo();
  }

  encenderLeds();
}

//*****************************************************************************
//Función para configurar módulo PWM
//*****************************************************************************
void configurarPWMServo(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelServo, freqPWMServo, resolutionPWMServo);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMServo, pwmChannelServo);
}

void configurarPWMLedR(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedR, freqPWMLedR, resolutionPWMLedR);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedR, pwmChannelLedR);
}

void configurarPWMLedG(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedG, freqPWMLedG, resolutionPWMLedG);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedG, pwmChannelLedG);
}

void configurarPWMLedB(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedB, freqPWMLedB, resolutionPWMLedB);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedB, pwmChannelLedB);
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

void configurarBoton3(void)
{
  //me coloca una interrupción en el botón 1 (durante el cambio de alto a bajo)
  attachInterrupt(digitalPinToInterrupt(boton3), ISRBoton3, RISING);
}

void configurarBoton4(void)
{
  //me coloca una interrupción en el botón 1 (durante el cambio de alto a bajo)
  attachInterrupt(digitalPinToInterrupt(boton4), ISRBoton4, RISING);
}

void encenderLeds(void)
{
  switch (contadorBoton3)
  {
  case 1:
    ledcWrite(pwmChannelLedR, contadorBoton4);
    break;
  case 2:
    ledcWrite(pwmChannelLedG, contadorBoton4);
    break;
  case 3:
    ledcWrite(pwmChannelLedB, contadorBoton4);
    break;
  }
}