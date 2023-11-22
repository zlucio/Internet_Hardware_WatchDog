/******************************************************
  test Ping   libreira  dvarrel 
  https://github.com/dvarrel/ESPping/blob/main/examples/test_ping/test_ping.ino
  compilato per generic Esp8266
******************************************************/

#include <ESPping.h>

int RELAY = 5; //uso gpio5 per evitare segnali spuri durante boot
int LED4 = 4;
int LED5 = 12; // select the pin for the red LED
int LED3 = 14; // select the pin for the blue LED
int LED6 = 13; // select the pin for the green LED

int fail_count  = 0;  // Incrementa errore ping

//#define RELAY D0
//#define LED4  D4	// GPIO4    LED SCHEDA
//#define LED3  D14	// GPIO14   LED BLU 
//#define LED6  D13	// GPIO13   LED VERDE
//#define LED5  D12	// GPIO12   LED ROSSO

void setup()
{
  Serial.begin(115200);
  delay(100);

  /** Define the pin modes **/
  pinMode(RELAY, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  digitalWrite(LED4, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(RELAY, LOW);

  WiFi.begin("CS_interno14","CondominioBrostolade14");      // attende connessione
  Serial.print("\nConnection");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnection OK, IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("Puoi provare a contattarmi ;-)");
}

void loop()
{
  // Ping IP
  const IPAddress remote_ip(8,8,8,8);
  bool pingTest = Ping.ping(remote_ip);

  Serial.print("Remote IP =  ");
  Serial.print(remote_ip);
  Serial.print("\t");
  if (Ping.ping(remote_ip) > 0)
  {
    fail_count = 0;
    Serial.printf("Response time : %d / %.2f / %d ms\t", Ping.minTime(), Ping.averageTime(), Ping.maxTime());
    Serial.print("pingTest = ");
    Serial.print(pingTest);
    Serial.print("\t");
    Serial.print("errori ping = ");
    Serial.print(fail_count);
    Serial.println("");
   
  lampeggia(LED6,10,300);
  digitalWrite(LED6, HIGH);
  delay(1 * 60 * 1000UL);  // ritardo 1 minuto per rilettura ping senza errori

  } 
  else {
    Serial.print(" Error !");
    Serial.print("\t");
    Serial.print("pingTest = ");
    Serial.print(pingTest);
    Serial.print("\t");
    Serial.print("errori ping = ");
    Serial.print(fail_count);
    Serial.println("");

    lampeggia(LED5,10,300);
    digitalWrite(LED5, HIGH);  fail_count++;  
      /** Ping Completely Failed **/
    if ( fail_count >= 8 )     // Resetta  router se conteggio errori >= 6
    {   
      digitalWrite(RELAY, HIGH);
      delay(20000);   // attiva relè x 15 secondi --- tempi non precisi 
      digitalWrite(RELAY, LOW);
      delay(2 * 60 * 1000UL);  // ritardo 2 minuti per rilettura ping dopo reset
      fail_count = 0;
    }
    digitalWrite(RELAY, LOW);
    delay(1 * 60 * 1000UL);  // ritardo 1 minuto per rilettura ping con errori
  }
  delay(1000);

}

 // esempio  lampeggia(LED2,10,300);

void lampeggia(int pin,int volte, int periodo)  
     {
     //fa lampeggiare un pin e il suo led collegato.
     int h=0;
     for (h=1; h<=volte ; h++)
         {       
         digitalWrite(pin, HIGH);             
         delay(periodo);
         digitalWrite(pin, LOW);             
         delay(periodo);
         }
     } 

