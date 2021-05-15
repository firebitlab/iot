// Pakai dynamic IP

#include <ESP8266WiFi.h>
WiFiClient client;
char ssid[] = "SSID2";
char password[] = "240494ti";
byte mac[6];

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
MySQL_Connection conn((Client *)&client);
char INSERT_SQL[] = "INSERT INTO u3372604_ta_wemos.tb_wemos(temperature, humidity, pressure, light) VALUES (%f, %.2f, %d, %d)";
char query[128];
//Primary Domain  roboteducation.info
//Shared IP Address 156.67.212.89

IPAddress server_addr(156, 67 , 212, 89);   // MySQL server IP
char db_user[] = "u3372604_ta";            // MySQL user
char db_password[] = "127616616TA";       // MySQL password


void setup()
{
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  Serial.println("");


  Serial.println("Connecting to mysql server");
  while (conn.connect(server_addr, 3306, db_user, db_password) != true) 
  {
    delay(200);
    Serial.print ( "." );
  }
  Serial.println("");
  Serial.println("Connected to mysql server!");
}

float temperature = 2.1; 
float humidity = 2.2;
int pressure = 2;
int light = 4;

void loop()
{
  light++;
  delay(10000); //10 sec
  sprintf(query, INSERT_SQL, temperature,humidity,pressure,light);
  Serial.println("Recording data.");
  Serial.println(query);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(query);
  delete cur_mem;

}
