//Zdefiniowanie polaczenia ESP8266 do Arduino UNO
String ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz"; //alfabet ASCII
int buff; // bufor do wczytanych danych
int czas[13];//={0,1,2,3,4,5,6,7,8,9,10,11,12}; //tablica na sekundy, minuty, godzine i date
//baza do sekretnych wiadomosci
unsigned int d = B01111010, u = B01111100, p = B11001110, a = B11101110;  
// Define Connections to 74HC595
#define TIME 3  //Zmienna okreslajaca czas, po ktorym ma nastapic przelaczenie wyswietlacza 
#define INTERVAL 1000
#define HOW_LATE 1
// Zdediniowanie połączeń z 74HC595
// ST_CP pin 12
const int latchPin = 10;
// SH_CP pin 11
const int clockPin = 11;
// DS pin 14
const int dataPin = 12;


// szesnastkowy zapis segmentów wyświetlacza użytych do wyświetlenia cyfr 0,1,2,3,4,5,6,7,8,9
int numArray[16] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
/*piny odpowiedzialne za przelaczanie wyswietlaczy
//dig_1 = 7;
//dig_2 = 6;
//dig_3 = 5;
//dig_4 = 4;
//dig_5 = 3;
//dig_6 = 2;*/
int digArray[6] = {7,6,5,4,3,2}; 

unsigned long previousMillis = 0; //stosujemy w funkcji millis() zamiast delay(1000)
unsigned long currentMillis; 


void setup ()
{
  // Ustawienie wyjść
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(digArray[0], OUTPUT);
  pinMode(digArray[1], OUTPUT);
  pinMode(digArray[2], OUTPUT);
  pinMode(digArray[3], OUTPUT);
  pinMode(digArray[4], OUTPUT);
  pinMode(digArray[5], OUTPUT);
  digitalWrite(digArray[0],LOW); //low zamiast high bo tu jest NPN (gdyby było 6xPNP to tu byłoby HIGH)
  digitalWrite(digArray[1],HIGH);
  digitalWrite(digArray[2],HIGH);
  digitalWrite(digArray[3],HIGH);
  digitalWrite(digArray[4],HIGH);
  digitalWrite(digArray[5],HIGH);
  for(int i=0;i<13;i++)
  czas[i] = 8;
  //inicjalizacja portu szeregowego
  Serial.begin(9600);
  delay(1000);
}

void print(int digit)
{
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);
}

void printTime(int hours, int minutes, int seconds) // moze wypisywac czas albo date
{
  // #1
  print(~numArray[hours/10]);
  digitalWrite(digArray[0],HIGH); //zalaczenie wyswiwietlacza #1 (tu high/low na odwrot bo NPN zamiast PNP)
  delay(TIME);
  digitalWrite(digArray[0],LOW); //wylaczenie wyswietlacza #1
  // #2
  print(~(numArray[hours%10] | 0x01)); // dziesiata czesc godziny + separator
  digitalWrite(digArray[1],LOW); //zalaczenie wyswiwietlacza #2
  delay(TIME);
  digitalWrite(digArray[1],HIGH); //wylaczenie wyswietlacza #2
  // #3
  print(~numArray[minutes/10]);
  digitalWrite(digArray[2],LOW);
  delay(TIME);
  digitalWrite(digArray[2],HIGH);
  //#4
  print(~(numArray[minutes%10]| 0x01));// dziesiata czesc minuty + separator
  digitalWrite(digArray[3],LOW);
  delay(TIME);
  digitalWrite(digArray[3],HIGH);
  //#5
  print(~numArray[seconds/10]);
  digitalWrite(digArray[4],LOW);
  delay(TIME);
  digitalWrite(digArray[4],HIGH);
  //#6
  print(~numArray[seconds%10]);
  digitalWrite(digArray[5],LOW);
  delay(TIME);
  digitalWrite(digArray[5],HIGH);
  
}

void printTimeLong(/*int s1, int s2, int m1, int m2,int h1, int h2*/ ) // moze wypisywac czas albo date
{
  /*----------sekundy-------------*/
  //#5 - czesci dziesiate sekund
  print(~numArray[czas[0]]);
  digitalWrite(digArray[4],LOW);
  delay(TIME);
  digitalWrite(digArray[4],HIGH);
  //#6 - jednosci sekund
  print(~numArray[czas[1]]);
  digitalWrite(digArray[5],LOW);
  delay(TIME);
  digitalWrite(digArray[5],HIGH);
  /*----------minuty-------------*/
    // #3 - czesci dziesiate minut
  print(~numArray[czas[2]]);
  digitalWrite(digArray[2],LOW);
  delay(TIME);
  digitalWrite(digArray[2],HIGH);
  //#4 - jednosci minut
  print(~(numArray[czas[3]]| 0x01));// dziesiata czesc minuty + separator
  digitalWrite(digArray[3],LOW);
  delay(TIME);
  digitalWrite(digArray[3],HIGH);
  /*----------godziny-------------*/
  // #1 - dziesiate czesci godzin
  print(~numArray[czas[4]]);
  digitalWrite(digArray[0],HIGH); //zalaczenie wyswiwietlacza #1 (tu high/low na odwrot bo NPN zamiast PNP)
  delay(TIME);
  digitalWrite(digArray[0],LOW); //wylaczenie wyswietlacza #1
  // #2 - jednosci godzin
  print(~(numArray[czas[5]] | 0x01)); // jednosci godzin + separator (kropka)
  digitalWrite(digArray[1],LOW); //zalaczenie wyswiwietlacza #2
  delay(TIME);
  digitalWrite(digArray[1],HIGH); //wylaczenie wyswietlacza #2
}

void printMessage(int a, int b, int c, int d, int e, int f){

  // #1
  print(~a);
  digitalWrite(digArray[0],HIGH); //zalaczenie wyswiwietlacza #1 (tu high/low na odwrot bo NPN zamiast PNP)
  delay(TIME);
  digitalWrite(digArray[0],LOW); //wylaczenie wyswietlacza #1
  // #2
  print(~b); // dziesiata czesc godziny + separator
  digitalWrite(digArray[1],LOW); //zalaczenie wyswiwietlacza #2
  delay(TIME);
  digitalWrite(digArray[1],HIGH); //wylaczenie wyswietlacza #2
  // #3
  print(~c);
  digitalWrite(digArray[2],LOW);
  delay(TIME);
  digitalWrite(digArray[2],HIGH);
  //#4
  print(~d | 0x01);// dziesiata czesc minuty + separator
  digitalWrite(digArray[3],LOW);
  delay(TIME);
  digitalWrite(digArray[3],HIGH);
  //#5
  print(~e);
  digitalWrite(digArray[4],LOW);
  delay(TIME);
  digitalWrite(digArray[4],HIGH);
  //#6
  print(~f);
  digitalWrite(digArray[5],LOW);
  delay(TIME);
  digitalWrite(digArray[5],HIGH);
}

void serialRead()
{
  int indeks = 0;
      while(Serial.available()>0) //czytanie calej informacji o aktualnej dacie
    {
      buff = Serial.read(); 
      if(buff<48 || buff>57)
      Serial.print(ASCII[buff-65]);
      else {
            czas[indeks] = (buff-48);
            Serial.print(buff - 48);
            //if(indeks<6)
            indeks++;
           }
    }
  Serial.print('\n');
}


void loop()
{
  currentMillis = millis();
  
  if(currentMillis - previousMillis >= INTERVAL)
  {
    serialRead(); 
    previousMillis = currentMillis;
  }
  if(czas[4] == 0 && czas[5] == 0 && czas[2] == 0 && czas[3] == 0) //wyswietlanie wiadomosci o polnocy
  printMessage(a,p,u,d,numArray[czas[0]], numArray[czas[1]]);
  else{  printTimeLong();  }
}
