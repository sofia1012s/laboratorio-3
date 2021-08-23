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
#define freqPWMServo 50       
#define resolutionPWMServo 16 
#define pinPWMServo 13       

//Parámetro PWM led Red
#define pwmChannelLedR 2
#define freqPWMLedR 5000   
#define resolutionPWMLedR 8 
#define pinPWMLedR 12     

//Parámetro PWM led Green
#define pwmChannelLedG 1
#define freqPWMLedG 5000   
#define resolutionPWMLedG 8 
#define pinPWMLedG 27     

//Parámetro PWM led Blue
#define pwmChannelLedB 3
#define freqPWMLedB 5000   
#define resolutionPWMLedB 8 
#define pinPWMLedB 26     

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
int contador = 0;
int contadorBoton3 = 0;
int contadorBoton4 = 0;

//*****************************************************************************
//ISR: interrupciones
//*****************************************************************************
void IRAM_ATTR ISRBoton1() //interrupción para botón 1 (Derecha)
{
  static unsigned long ultimo_tiempo_interrupcion3 = 0; //último tiempo de la interrupción
  unsigned long tiempo_interrupcion3 = millis();        //tiempo actual de la interrupción

  //Si la interrupcion dura menos de 200ms, asumir que es un rebote e ignorar
  if (tiempo_interrupcion3 - ultimo_tiempo_interrupcion3 > 200)
  {
    contador -= 20; //Disminuye 20 al contador de botón

    if (contador == 180) //el valor no puede ser mayor a 180
    {
      contador = 180;
    }

    else if (contador == 0) //el valor no puede ser menor a 0
    {
      contador = 0;
    }
  }
  ultimo_tiempo_interrupcion3 = tiempo_interrupcion3; //actualiza el valor del tiempo de la interrupción
}

void IRAM_ATTR ISRBoton2() //interrupción para botón 2 (izquierda)
{
  static unsigned long ultimo_tiempo_interrupcion4 = 0; //último tiempo de la interrupción
  unsigned long tiempo_interrupcion4 = millis();        //tiempo actual de la interrupción

  //Si la interrupcion dura menos de 200ms, asumir que es un rebote e ignorar
  if (tiempo_interrupcion4 - ultimo_tiempo_interrupcion4 > 200)
  {
    contador += 20; //Aumenta 20 al contador de botón

    if (contador == 180) //el valor no puede ser mayor a 180
    {
      contador = 180;
    }

    else if (contador == 0) //el valor no puede ser menor a 0
    {
      contador = 0;
    }
  }
  ultimo_tiempo_interrupcion4 = tiempo_interrupcion4; //actualiza el valor del tiempo de la interrupción
}

void IRAM_ATTR ISRBoton3() //interrupción para botón 3 (Seleccionar caso en switch)
{
  static unsigned long ultimo_tiempo_interrupcion1 = 0; //último tiempo de la interrupción
  unsigned long tiempo_interrupcion1 = millis();        //tiempo actual de la interrupción

  //Si la interrupcion dura menos de 200ms, asumir que es un rebote e ignorar
  if (tiempo_interrupcion1 - ultimo_tiempo_interrupcion1 > 200)
  {
    contadorBoton3++; //aumenta 1 al contador de botón

    if (contadorBoton3 > 4) //Si es mayor a 4 regresa a cero
    {
      contadorBoton3 = 0;
    }
  }
  ultimo_tiempo_interrupcion1 = tiempo_interrupcion1; //actualiza el valor del tiempo de la interrupción
}

void IRAM_ATTR ISRBoton4() //interrupción para botón 4 (Aumento nivel de brillo)
{
  static unsigned long ultimo_tiempo_interrupcion2 = 0; //último tiempo de la interrupción
  unsigned long tiempo_interrupcion2 = millis();        //tiempo actual de la interrupción

  //Si la interrupcion dura menos de 200ms, asumir que es un rebote e ignorar
  if (tiempo_interrupcion2 - ultimo_tiempo_interrupcion2 > 200)
  {
    contadorBoton4 += 50; //aumenta 50 al contador de botón

    if (contadorBoton4 > 255) //si es mayor a 255 regresa el valor a cero
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
  //Botones
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(boton3, INPUT_PULLUP);
  pinMode(boton4, INPUT_PULLUP);
  pinMode(pinPWMServo, OUTPUT);
  
  //Señales PWM
  configurarPWMServo();
  configurarPWMLedR();
  configurarPWMLedG();
  configurarPWMLedB();
  
  //Interrupciones Botones
  configurarBoton1();
  configurarBoton2();
  configurarBoton3();
  configurarBoton4();
}

//*****************************************************************************
//loop principal
//*****************************************************************************
void loop()
{
  moverServo(); //función para mover servo
  encenderLeds(); //función para encender leds
}

//*****************************************************************************
//Función para configurar módulo PWM de Servo
//*****************************************************************************
void configurarPWMServo(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelServo, freqPWMServo, resolutionPWMServo);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMServo, pwmChannelServo);
}

//*****************************************************************************
//Función para configurar módulo PWM Led Red
//*****************************************************************************
void configurarPWMLedR(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedR, freqPWMLedR, resolutionPWMLedR);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedR, pwmChannelLedR);
}

//*****************************************************************************
//Función para configurar módulo PWM Led Green
//*****************************************************************************
void configurarPWMLedG(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedG, freqPWMLedG, resolutionPWMLedG);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedG, pwmChannelLedG);
}

//*****************************************************************************
//Función para configurar módulo PWM Led Blue
//*****************************************************************************
void configurarPWMLedB(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannelLedB, freqPWMLedB, resolutionPWMLedB);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWMLedB, pwmChannelLedB);
}

//*****************************************************************************
//Función para mover servo con el contador
//*****************************************************************************
void moverServo()
{
  int ang = (((contador / 180.0) * 2000) / 20000.0 * 65536.0) + 1634;
  ledcWrite(pwmChannelServo, ang);
  delay(15);
}

//*****************************************************************************
//Función para configurar interrupción en botón 1
//*****************************************************************************
void configurarBoton1(void)
{
  //me coloca una interrupción en el botón 1 (durante el cambio de alto a bajo)
  attachInterrupt(digitalPinToInterrupt(boton1), ISRBoton1, RISING);
}

//*****************************************************************************
//Función para configurar interrupción en botón 2
//*****************************************************************************
void configurarBoton2(void)
{
  //me coloca una interrupción en el botón 1 (durante el cambio de alto a bajo)
  attachInterrupt(digitalPinToInterrupt(boton2), ISRBoton2, RISING);
}

//*****************************************************************************
//Función para configurar interrupción en botón 3
//*****************************************************************************
void configurarBoton3(void)
{
  //me coloca una interrupción en el botón 1 (durante el cambio de alto a bajo)
  attachInterrupt(digitalPinToInterrupt(boton3), ISRBoton3, RISING);
}

//*****************************************************************************
//Función para configurar interrupción en botón 4
//*****************************************************************************
void configurarBoton4(void)
{
  //me coloca una interrupción en el botón 1 (durante el cambio de alto a bajo)
  attachInterrupt(digitalPinToInterrupt(boton4), ISRBoton4, RISING);
}

//*****************************************************************************
//Función para comenzar modo servo en botón 4
//*****************************************************************************
void modoServo(void)
{
  if (contador < 45)
  {
    ledcWrite(pwmChannelLedR, 0);
    ledcWrite(pwmChannelLedG, 0);
    ledcWrite(pwmChannelLedB, 255);
  }

  else if (contador > 45 && contador < 120)
  {
    ledcWrite(pwmChannelLedR, 0);
    ledcWrite(pwmChannelLedG, 255);
    ledcWrite(pwmChannelLedB, 0);
  }

  else if (contador > 120)
  {
    ledcWrite(pwmChannelLedR, 255);
    ledcWrite(pwmChannelLedG, 0);
    ledcWrite(pwmChannelLedB, 0);
  }
}

//*****************************************************************************
//Función para encender leds y regular su brillos
//*****************************************************************************
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
  case 4:
    modoServo();
    break;
  }
}

