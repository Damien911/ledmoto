

#include <Adafruit_NeoPixel.h> //biblioteka diod


// Numer analogowego pinu do którego podłączony jest potencjometr
#define POTENCJOMETR_PIN A1
//#define brightPin A2

//#define pinPWM A0

Adafruit_NeoPixel line = Adafruit_NeoPixel(30, A0, NEO_GRB + NEO_KHZ800);

  void setHue(int pixel, int hue) {
    hue = hue % 360;
    int r,g,b;
    if(hue < 60) {
      r = 255;
      g = map(hue, 0, 59, 0, 254);
      b = 0;
    } else if(hue < 120) {
      r = map(hue, 60, 119, 254, 0);
      g = 255;
      b = 0;
    } else if(hue <  180) {
      r = 0;
      g = 255;
      b = map(hue, 120, 179, 0, 254);
    } else if(hue < 240) {
      r = 0;
      g = map(hue, 180, 239, 254, 0);
      b = 255;
    } else if(hue < 300) {
      r = map(hue, 240, 299, 0, 254);
      g = 0;
      b = 255;
    } else {
      r = 255;
      g = 0;
      b = map(hue, 300, 359, 254, 0);
    }

    line.setPixelColor(pixel, line.Color( r, g, b));
  }  

void setup()
{
  //pinMode(pinPWM, OUTPUT); // pin pwm 10 jako wyjscie
  //TCCR1B = TCCR1B & 0b11111000; //zmiana prescalera na 1 czyli 16MHz (full)

  line.begin(); //inicjalizacja
  
  // Ustawienie komunikacji z komputerem na 57600 bodów
  
  Serial.begin(57600);

  // Oczekiwanie na uaktywnienie portu w Arduino
  while (!Serial);
}

void loop()
{
  line.clear();
  // Odczyt wartości z potencjometru
  int value = analogRead(POTENCJOMETR_PIN);
  byte angle = map(value, 0, 1023, 0, 150);
  
  
  //int bright = analogRead(brightPin);
  //byte procentBright = map(bright, 0, 1023, 0, 120);
  //byte brightSendValue = map(bright, 0,1023, 0, 386);
  
  // Wysłanie wartości do komputera(monitor szeregowy)
  Serial.println(angle, DEC);
  //Serial.println(procentBright, DEC);


  for(int x = 0; x < 30; x++) {
   setHue(x, angle);
  }
  //line.setPixelColor(15, line.Color(0, 150, 0));
  line.show(); 
  //analogWrite(pinPWM,brightSendValue); //obraz migocze zmiana rejestru zegara, powodowała brak odpowiedniego napiecia do zasilenia ledu
//tzn czesc paska nie chciala swiecic
  
 // analogWrite(pinPWM,255);
  // Oczekiwanie 20 ms czyli wysyłanie 50x na sekundę
  //delay(20);
}