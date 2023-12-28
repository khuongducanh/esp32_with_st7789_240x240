#include "lib.h"

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  //http
  WiFi.begin(ssid, password);
  Serial.println("Connecting to wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  tft.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  //time
  configTime(timezone,dst,"pool.ntp.org","time.nist.gov");
  //tft
  tft.init(240, 240, SPI_MODE2);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_WHITE);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(2);
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?lat=" + latitude + "&lon=" + longitude + "&appid=" + openWeatherMapApiKey;

      jsonBuffer = httpGETRequest(serverPath.c_str());
      JSONVar myObject = JSON.parse(jsonBuffer);

      //print_json
      double temp = (double)(myObject["main"]["temp"]) - 273.14;
      int humi = (int)(myObject["main"]["humidity"]) + 1;

      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print("*C  ");
      Serial.print("Humidity: ");
      Serial.print(humi);
      Serial.print("%  ");
      Serial.print("City:");
      Serial.print(myObject["name"]);
      Serial.print("    ");
      //print_time
      time_t now = time(nullptr);
      struct tm* p_tm = localtime(&now);
      Serial.print(p_tm->tm_mday);Serial.print("/");Serial.print(p_tm->tm_mon + 1);Serial.print("/");Serial.print(p_tm->tm_year + 1900);Serial.print(" ");
      Serial.print(p_tm->tm_hour);Serial.print(":");Serial.print(p_tm->tm_min);Serial.print(":");Serial.println(p_tm->tm_sec);Serial.println("............");
      //print_tft
      tft.setCursor(5, 55);
      tft.print(temp);
      tft.println("*C");
      tft.setCursor(5, 75);
      tft.print(humi);
      tft.println("%");
      tft.setCursor(5, 95);
      tft.print("City:");
      tft.print(myObject["name"]);
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  String payload = "{}";
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    tft.setCursor(5, 20);
    tft.print("HTTP Response code: ");
    tft.println(httpResponseCode);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    tft.setCursor(5, 20);
    tft.print("Error code: ");
    tft.println(httpResponseCode);
  }
  http.end();
  return payload;
}
