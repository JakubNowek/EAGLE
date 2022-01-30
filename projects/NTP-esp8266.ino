/*
  This is an example file for using the time function in ESP8266 or ESP32 tu get NTP time
  It offers two functions:
  - getNTPtime(struct tm * info, uint32_t ms) where info is a structure which contains time
  information and ms is the time the service waits till it gets a response from NTP.
  Each time you cann this function it calls NTP over the net.
  If you do not want to call an NTP service every second, you can use
  - getTimeReducedTraffic(int ms) where ms is the the time between two physical NTP server calls. Betwwn these calls,
  the time structure is updated with the (inaccurate) timer. If you call NTP every few minutes you should be ok
  The time structure is called tm and has teh following values:
  Definition of struct tm:
  Member  Type  Meaning Range
  tm_sec  int seconds after the minute  0-61*
  tm_min  int minutes after the hour  0-59
  tm_hour int hours since midnight  0-23
  tm_mday int day of the month  1-31
  tm_mon  int months since January  0-11
  tm_year int years since 1900
  tm_wday int days since Sunday 0-6
  tm_yday int days since January 1  0-365
  tm_isdst  int Daylight Saving Time flag
  because the values are somhow akwardly defined, I introduce a function makeHumanreadable() where all values are adjusted according normal numbering.
  e.g. January is month 1 and not 0 And Sunday or monday is weekday 1 not 0 (according definition of MONDAYFIRST)
  Showtime is an example on how you can use the time in your sketch
  The functions are inspired by work of G6EJD ( https://www.youtube.com/channel/UCgtlqH_lkMdIa4jZLItcsTg ),
  and code of mr Andreas Spiess (https://www.youtube.com/watch?v=r2UAmBLBBRM). Many thanks.
*/

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#else
#include <WiFi.h>
#endif
#include <time.h>
// #include <credentials.h>
ESP8266WiFiMulti wifiMulti; //  MOD
const uint32_t connectTimeoutMs = 6000; //MOD
boolean connectioWasAlive = true;

#ifdef CREDENTIALS
const char* ssid = mySSID;
const char* password = myPASSWORD;
#else
const char* ssid_1 = "Your_WIFI_name";
const char* password_1 = "here_put_your_passwd";

const char* ssid_2 = "Your_neighbour_WIFI_name";
const char* password_2 = "here_put_your_neighbour's_passwd";

#endif

const char* NTP_SERVER = "ch.pool.ntp.org";
const char* TZ_INFO    = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";  // enter your time zone (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)

tm timeinfo;
time_t now;
long unsigned lastNTPtime;
unsigned long lastEntryTime;
int timer;

void setup() {
  Serial.begin(/*115200*/9600);
  Serial.println("\n\nNTP_Time_Test\n");
  //WiFi.begin(ssid, password); //MOD
  WiFi.mode(WIFI_STA); //MOD
  wifiMulti.addAP("Straż Miejska 47853","12345678" ); //MOD
  wifiMulti.addAP(ssid_1,password_1 ); //MOD
  wifiMulti.addAP(ssid_2,password_2 ); //MOD
  int counter = 0;
  while (wifiMulti.run(connectTimeoutMs) != WL_CONNECTED) { //MOD
    boolean connectioWasAlive = false;
    delay(200);
    if (++counter > 100) ESP.restart();
    Serial.print ( "." );
  }
  Serial.println("\n\nWiFi_connected\n\n");
  Serial.printf("connected to %s\n",WiFi.SSID().c_str());
  configTime(0, 0, NTP_SERVER);
  // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
  setenv("TZ", TZ_INFO, 1);

  if (getNTPtime(10)) {  // wait up to 10sec to sync
  } else {
    Serial.println("Time_not_set");
     ESP.restart();
  }
  showTime(timeinfo);
  lastNTPtime = time(&now);
  lastEntryTime = millis();
}

void loop() {
  getNTPtime(10);
  showTime(timeinfo);
  delay(1000);
}

bool getNTPtime(int sec) {

  {
    uint32_t start = millis();
    do {
      time(&now);
      localtime_r(&now, &timeinfo);
      //Serial.print(".");
      delay(10);
    } while (((millis() - start) <= (1000 * sec)) && (timeinfo.tm_year < (2016 - 1900)));
    if (timeinfo.tm_year <= (2016 - 1900)) return false;  // the NTP call was not successful
    char time_output[30];
    strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now+1)); //MOD (+1)
  }
  return true;
}
// Data is send through serial port in form "s(seconds)m(minutes)h(hours)D(day_of_the_week)M(month)Y(year)R(number_of_the_day_of_the_week)"
void showTime(tm localTime) {
  Serial.print('s');
  if(localTime.tm_sec/10 == 0)
  Serial.print('0');
  Serial.print(localTime.tm_sec);
  //Serial.print(':');
  Serial.print('m');
  if(localTime.tm_min/10 == 0)
  Serial.print('0');
  Serial.print(localTime.tm_min);
  //Serial.print(':');
  Serial.print('h');
  if(localTime.tm_hour/10 == 0)
  Serial.print('0');
  Serial.print(localTime.tm_hour);
  //Serial.print('-');
  Serial.print('D');
  if(localTime.tm_mday/10 == 0)
  Serial.print('0');
  Serial.print(localTime.tm_mday);
  //Serial.print('/');
  Serial.print('M');
  if((localTime.tm_mon+1)/10 == 0)
  Serial.print('0');
  Serial.print(localTime.tm_mon + 1);
  //Serial.print('/');
  Serial.print('Y');
  if(localTime.tm_year/10 == 0)
  Serial.print('0');
  Serial.print(localTime.tm_year - 100);
  Serial.print('R');
  if (localTime.tm_wday == 0)   Serial.println(7);
  else Serial.println(localTime.tm_wday);
}
