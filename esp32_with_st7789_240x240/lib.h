#include <Arduino.h>


//connect_tft_st7789_240x240
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_ST7789.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#define TFT_MOSI 23  // SDA Pin on ESP32
#define TFT_SCLK 18  // SCL Pin on ESP32
#define TFT_CS -1    // Chip select control pin
#define TFT_DC 2     // Data Command control pin
#define TFT_RST 4    // Reset pin (could connect to RST pin)

//connect_json
#include <HTTPClient.h>
#include <WiFi.h>
#include <Arduino_JSON.h>
const char* ssid = "Iphone";
const char* password = "0382780890";
String openWeatherMapApiKey = "4455d3b14a1f08c648288279e73693ac";
String latitude = "21.02";    //vĩ độ
String longitude = "105.83";  //kinh độ
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
String jsonBuffer;
//https://api.openweathermap.org/data/2.5/weather?lat=21.02&lon=105.83&appid=4455d3b14a1f08c648288279e73693ac  ====> Hanoi

//connect_time
#include <time.h>
int timezone = 7 * 3600;
int dst = 0;