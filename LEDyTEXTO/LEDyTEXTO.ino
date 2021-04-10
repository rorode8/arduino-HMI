#include <LiquidCrystal.h> //Cargamos las librerías del lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Pines del LCD

String inputString = "";         // Una cadena para guardar la información que llegue
boolean stringComplete = false;  // iniciamos una bandera para verificar si llego el mensaje
String commandString = "";

//Leds verde, amarillo y rojo
int led1Pin = 13;
int led2Pin = 22;
int led3Pin = 23;

// Direcciones del motor
int derechaPin = 22; // M1 A una entrada del puente H
int izquierdaPin = 23; // M2 A una entrada del puente H
int paroPin = 24; // Velocidad por PWM


boolean isConnected = false; //Bander para saber si hay conexión




void setup() {
  
  Serial.begin(9600);
  pinMode(led1Pin,OUTPUT);
  initDisplay();
}


void loop() {

if(stringComplete)
{
  stringComplete = false;
  getCommand(); // Declaramos la función para leer las órdenes desde el HMI
  
  if(commandString.equals("INICIA"))// Si recibimos INICIA limpiamos el LCD
  {
    lcd.clear();
  }
  if(commandString.equals("PARA"))// Si recibimos STOP apagamos los leds
  {
    turnLedOff(led1Pin);
    lcd.clear();
    lcd.print("Listo para conectarse");    
  }
  else if(commandString.equals("TEXTO"))
  {
    String text = getTextToPrint(); //Cachamos el texto llegado
    printText(text);
  }
  else if(commandString.equals("LED1"))
  {
    boolean LedState = getLedState();
    if(LedState == true)
    {
      turnLedOn(led1Pin);
    }else
    {
      turnLedOff(led1Pin);
    }   
  }
    else if(commandString.equals("LED2"))
  {
    boolean LedState = getLedState();
    if(LedState == true)
    {
      turnLedOn(led2Pin);
    }else
    {
      turnLedOff(led2Pin);
    }   
  }
    else if(commandString.equals("LED3"))
  {
    boolean LedState = getLedState();
    if(LedState == true)
    {
      turnLedOn(led3Pin);
    }else
    {
      turnLedOff(led3Pin);
    }   
  }
  
  inputString = "";
}

}

void initDisplay()
{
  lcd.begin(16, 2);
  lcd.print("Listo para conetarse");
}

boolean getLedState()
{
  boolean state = false;
  if(inputString.substring(5,7).equals("ON"))
  {
    state = true;
  }else
  {
    state = false;
  }
  return state;
}

void getCommand()
{
  if(inputString.length()>0)
  {
     commandString = inputString.substring(1,5);
  }
}

void turnLedOn(int pin)
{
  digitalWrite(pin,HIGH);
}

void turnLedOff(int pin)
{
  digitalWrite(pin,LOW);
}


String getTextToPrint()
{
  String value = inputString.substring(5,inputString.length()-2);
  return value;
}

void printText(String text)
{
  lcd.clear();
  lcd.setCursor(0,0);
    if(text.length()<16)
    {
      lcd.print(text);
    }else
    {
      lcd.print(text.substring(0,16));
      lcd.setCursor(0,1);
      lcd.print(text.substring(16,32));
    }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
