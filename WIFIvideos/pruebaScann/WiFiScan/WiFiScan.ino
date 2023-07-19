#include "WiFi.h"
int i = 0;
int n = 2;
void setup()
{
  bool flagm = false;
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  while (!Serial.available()) {
      delay(100);
      switch (Serial.read()) {
      case 'a':
        n = 2;
        break;
      case 'b':
        n = 3;
        break;
      case 'c':
        n = 4;
        break;
      case 'd':
        n = 5;
        break;
      case 'e':
        n = 6;
        break;
      case 'f':
        n = 7;
        break;
      default:
        n = 8;
    }
  }
      

  Serial.printf("Setup done with %d time per chanel", n * 500);
  Serial.println("");
}

void loop()
{
  bool flag1 = false;
  bool flag2 = false;

  Serial.printf("scan start... -> ");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks(false, false, true, 500 * n,10);//, 10); //scanNetworks();
  Serial.printf("scan %d: ", i);
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    for (int i = 0; i < n; ++i) {
      // Serial.println(WiFi.SSID(i));
      if (WiFi.SSID(i) == "ES1") {
        flag1 = true;
        Serial.print("ESP32: ");
   Serial.print(WiFi.SSID(i));
   Serial.print("   ");
        Serial.println(WiFi.RSSI(i));
      }
      else if (WiFi.SSID(i) == "Hr") {
        flag2 = true;
        Serial.print("Hr : ");
        Serial.println(WiFi.RSSI(i));
      }
    }
    if ( flag1 == false) {
      Serial.println("dato perdido");
    }
 //   else {
//
  //  }
 //   i++;
  }
  // Wait a bit before scanning again
  delay(100);
}
