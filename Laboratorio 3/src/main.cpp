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

//Parámetro PWM servo motor
#define pwmChannelServo 3
#define freqPWMServo 50       //frecuencia en Hz
#define resolutionPWMServo 16 //16 bits
#define pinPWMServo 13        //GPIO  para tener la salida del PWM

int contador = 0;
//*****************************************************************************
//Prototipos de funcion
//*****************************************************************************
void configurarPWMServo(void);
void configurarBoton1(void);
void configurarBoton2(void);
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