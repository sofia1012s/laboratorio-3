//**********************************************************
//Universidad del Valle de Guatemala
//BE3015: Electrónica Digital 2
//**********************************************************

//**********************************************************
//Librerias
//**********************************************************
#include <Arduino.h>

//**********************************************************
//Definicion etiquetas
//**********************************************************

//Paso 1: selección de parámetros del PWM
#define pwmChannel 5 // 16 canales 0-15
#define freqPWM 5000 //frecuencia en Hz
#define resolution 8 //1-16 bits de resolucion
#define pinPWM 2     //GPIO 2 para tener la salida del PWM

//**********************************************************
//Prototipos de funcion
//**********************************************************
void configurarPWM(void);

//**********************************************************
//Varibles globales
//**********************************************************

//**********************************************************
//ISR: interrupciones
//**********************************************************
//void IRAM_ATTR ISR(){}

//**********************************************************
//configuracion
//**********************************************************
void setup()
{
  configurarPWM();
}

//**********************************************************
//loop principal
//**********************************************************
void loop()
{
  for (int dutycycle = 0; dutycycle < 256; dutycycle++)
  {
    ledcWrite(pwmChannel, dutycycle);
    delay(10);
  }

  for (int dutycycle = 255; dutycycle > 0; dutycycle--)
  {
    ledcWrite(pwmChannel, dutycycle);
    delay(10);
  }
}

//**********************************************************
//Función para configurar módulo PWM
//**********************************************************
void configurarPWM(void)
{
  //Paso 1: Configurar el modulo PWM
  ledcSetup(pwmChannel, freqPWM, resolution);

  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWM, pwmChannel);
}