#include <Adafruit_NeoPixel.h>
const uint8_t PROGMEM gamma8[] = {

0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,

1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,

2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,

5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,

10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,

17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,

25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,

37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,

51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,

69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,

90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,

115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,

144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,

177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,

215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255

};

int Brightness = 20;
int r = 0;
int b = 0;
int g = 0;

#define N_LEDS 23
#define LPIN1 12
#define LPIN2 11
#define LPIN3 10


Adafruit_NeoPixel s1 = Adafruit_NeoPixel (N_LEDS, LPIN1,NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel s2 = Adafruit_NeoPixel (N_LEDS, LPIN2,NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel s3 = Adafruit_NeoPixel (N_LEDS, LPIN3,NEO_BRG + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  s1.begin();
  s2.begin();
  s3.begin();
  s1.setBrightness(Brightness);
  s2.setBrightness(Brightness);
  s3.setBrightness(Brightness);
  

  pinMode(2,INPUT);
}

void loop() {

  
  // put your main code here, to run repeatedly:

  int raw = analogRead(A0);
  
  int raw2 = analogRead(A0);
  //Serial.println(raw);
  int amp = abs(raw - 514);
  if(amp == 1){
    amp = 0;
  }
  //Serial.println(amp);

  int val = map(amp,0,15,0,100);
  if(val>100){
    val = 100;
  }
  //Serial.println(val);

if(digitalRead(2) == HIGH){
    idle();
    //Serial.println("meter");
  }  else{
    meter(s1,val);
    meter(s2,val);
    meter(s3,val);
  }
    
    //s1.setPixelColor(1,0,255,0);
    //s1.show();
    //idle(s2);
    //idle(s3);
    //Serial.println("hello");
    //delay(20);
  
  

  delay(60);
}

static void meter(Adafruit_NeoPixel & strip, int val){
  strip.clear();
  int height = map(val,0,100,0,23);
  //Serial.println(height);

  int c = map(val,0,23,0,255);
  uint32_t bg = strip.Color(80,255,20);
  int samp = 23 - height;
  
  

  for(uint16_t i=23; i>samp; i--){
    int b = 255/height;
    //int b = 255 - 255/height;
    int r = 255 - 255/height;

    uint32_t fc = strip.Color(r,b,0);
    strip.setPixelColor(i,fc);
    
  }
  strip.fill(bg,0,samp);
  strip.show();
}

static void idle(){
  s1.setBrightness(Brightness - 10);
  s2.setBrightness(Brightness - 10);
  s3.setBrightness(Brightness - 10);
  for(uint16_t i = 23; i > 0; i--){
    //strip.setBrightness(Brightness/i + 10);
    r = random(0,40);
    b = 50 + 100/i;
    g = 150/i;
    s1.setPixelColor(i,s1.Color(r,b,g));
    s2.setPixelColor(i,s2.Color(r,b,g));
    s3.setPixelColor(i,s3.Color(r,b,g));
    s1.show();
    s2.show();
    s3.show();
    delay(150 - i*6);
  }
  //delay(500);
  for(uint16_t i = 20; i > 0; i--){
    s1.setBrightness(Brightness - Brightness/i);
    s2.setBrightness(Brightness - Brightness/i);
    s3.setBrightness(Brightness - Brightness/i);
    s1.show();
    s2.show();
    s3.show();
    delay(40);
  }
  s1.clear();
  s2.clear();
  s3.clear();
  Serial.println("idle");
  delay(2000);

}
