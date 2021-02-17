#include <ESP8266WiFi.h>
#include "DHTesp.h"

DHTesp dht;
const char* ssid = "MR.K"; //nama wifi  Not Available
const char* password = "tentangkopi";
#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
 //password hotspotkugakkenek
const char* host = "192.168.137.75"; //IP PC server

void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
delay(10);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
dht.setup(D2, DHTesp::DHT11);

}
void loop() {
// put your main code here, to run repeatedly:
Serial.println("Koneksi ke SERVER dimulai ");
Serial.print("IP Server : ");
Serial.println(host);
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("Koneksi GAGAL");
return;
}
//sensors.requestTemperatures();
  delay(dht.getMinimumSamplingPeriod());


  int temperatureC = dht.getTemperature();

  Serial.print(dht.getStatusString());

delay(5000);
// membuat URL untuk koneksi ke server
String url = "/sensor/insert_suhu.php?";
url += "suhu="; url += temperatureC;
Serial.print("URL: ");
Serial.println(url);
// This will send the request to the server
client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +"Connection: close\r\n\r\n");
// memberi batas waktu
unsigned long timeout = millis();
while (client.available() == 0) {
if (millis() - timeout > 5000) {
Serial.println(">>> Batas waktu koneksi HABIS ! <<<<");
Serial.println(">>> koneksi dihentikan ! <<<<");
client.stop();
return;
}
}
// membaca balasan server dan menampilkan ke monitor menggunakan Serial
while (client.available()) {
String line = client.readStringUntil('\r');
//Serial.print(line);
if (line.indexOf("sukses") != -1) {
Serial.println();
Serial.println("INSERT data berhasil");
} else if (line.indexOf("gagal") != -1) {
Serial.println();
Serial.println("Maaf, INSERT data berhasil");
}
}
Serial.println();
Serial.println("Koneksi database dihentikan");
delay(50000);
}
