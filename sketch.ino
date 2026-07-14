#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <ArduinoJson.h>

// =====================
// MAX7219 Configuration
// =====================
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES   8

#define DATA_PIN 11
#define CLK_PIN  13
#define CS_PIN   10

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// =====================
// Scoreboard Variables
// =====================
String score;
String target;
String overs;

String batter1;
String batter2;

int batter1Runs;
int batter2Runs;

// =====================
// JSON Data
// =====================
const char* jsonData = R"rawliteral(
{
  "score":"52/1",
  "target":90,
  "overs":"6",
  "batters":[
    {
      "name":"Khaleel",
      "runs":30
    },
    {
      "name":"Prashanth",
      "runs":22
    }
  ]
}
)rawliteral";

StaticJsonDocument<512> doc;

void loadScoreboard()
{
  deserializeJson(doc, jsonData);

  score = doc["score"].as<String>();

  target = String(doc["target"].as<int>());

  overs = doc["overs"].as<String>();

  batter1 = doc["batters"][0]["name"].as<String>();
  batter1Runs = doc["batters"][0]["runs"];

  batter2 = doc["batters"][1]["name"].as<String>();
  batter2Runs = doc["batters"][1]["runs"];
}

void setup()
{
  display.begin();

  display.setIntensity(3);

  display.displayClear();

  loadScoreboard();
}

void loop()
{
  String msg;

  msg += "Score ";
  msg += score;

  msg += "   ";

  msg += "Target ";
  msg += target;

  msg += "   ";

  msg += "Overs ";
  msg += overs;

  msg += "   ";

  msg += batter1;

  msg += " ";

  msg += batter1Runs;

  msg += "   ";

  msg += batter2;

  msg += " ";

  msg += batter2Runs;

  msg += "     ";

  display.displayText(
      msg.c_str(),
      PA_LEFT,
      50,
      0,
      PA_SCROLL_LEFT,
      PA_SCROLL_LEFT);

  while (!display.displayAnimate())
  {
  }
}


