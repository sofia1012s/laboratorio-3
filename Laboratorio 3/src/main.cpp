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
#define boton1 
#define boton2
#define boton3
#define boton4

//Leds
#define Led rojo
#define Led verde
#define Led azul

//Parámetros PWM para led
#define pwmChannelLed  2// 16 canales 0-15
#define freqPWMLed 5000 //frecuencia en Hz
#define resolutionPWMLed 8 //8 bits de resolucion (0-255)
#define pinPWMLed     3//GPIO  para tener la salida del PWM


//Parámetro PWM servo motor
#define pwmChannelServo 1
#define freqPWMServo 50 //frecuencia en Hz
#define resolutionPWMServo 8 //8 bits de resolucion (0-255)
#define pinPWMServo 5//GPIO  para tener la salida del PWM

//*****************************************************************************
//Prototipos de funcion
//*****************************************************************************
void configurarPWMLed(void);
void configurarPWMServo(void);

//*****************************************************************************
//Varibles globales
//*****************************************************************************

//*****************************************************************************
//ISR: interrupciones
//*****************************************************************************
//void IRAM_ATTR ISR(){}

//*****************************************************************************
//configuracion
//*****************************************************************************
void setup()
{
  configurarPWMLed();
  
}

//*****************************************************************************
//loop principal
//*****************************************************************************
void loop()
{
  /**
   * for (int dutycycle = 0; dutycycle < 256; dutycycle++)
  {
    ledcWrite(pwmChannelLed, dutycycle);
    delay(10);
  }

  for (int dutycycle = 255; dutycycle > 0; dutycycle--)
  {
    ledcWrite(pwmChannelLed, dutycycle);
    delay(10);
  }*/
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

void configurarBoton1(void)
{
  ledcWrite(pwmChannelLed, 255);

}