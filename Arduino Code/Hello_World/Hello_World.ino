#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

const int RED_LED_PIN = D8;
const int YELLOW_LED_PIN = D7;
const int GREEN_LED_PIN = D6;

class Light
{
private:
	int pin_number;
	String color;
	String state;
	unsigned int autoDelay;

public:
	Light(String color = "none", int pin_number = 0, int autoDelay = 1000, String state = "off")
	{
		this->color = color;
		this->pin_number = pin_number;
		this->state = "off";
		this->autoDelay = autoDelay;
	}
	void turnOn()
	{
		// Serial.println(this->color);
		// Serial.println("on");
		this->state = "on";
		digitalWrite(this->pin_number, HIGH);
	}
	void turnOff()
	{
		// Serial.println(this->color);
		// Serial.println("off");
		this->state = "off";
		digitalWrite(this->pin_number, LOW);
		//writeCon(this->print());
	}
	/*String print()
      {
      ostringstream s;
      s << this->color << " " << this->pin_number << " " << this->state << std::endl;
      return s.str();
      }*/
};

class TrafficLight
{
private:
	Light redLight;
	Light yellowLight;
	Light greenLight;
	String mode;
	int lastUpdate;

public:
	TrafficLight(unsigned int redPin, unsigned int yellowPin, unsigned int greenPin)
	{
		this->redLight = Light("red", redPin, 3, "off");
		this->yellowLight = Light("yellow", yellowPin, 3, "off");
		this->greenLight = Light("green", greenPin, 3, "off");
		this->mode = "manual";
		this->lastUpdate = millis();
	}
	void changeColor(String color)
	{
		// Serial.println("CHANGING COLOR");
		if (color == "red")
		{
			// Serial.print("red");
			this->redLight.turnOn();
			this->yellowLight.turnOff();
			this->greenLight.turnOff();
		}
		else if (color == "yellow")
		{
			// Serial.println("yellow");
			this->yellowLight.turnOn();
			this->redLight.turnOff();
			this->greenLight.turnOff();
		}
		else if (color == "green")
		{
			// Serial.println("green");
			this->greenLight.turnOn();
			this->redLight.turnOff();
			this->yellowLight.turnOff();
		}
	}

	void update()
	{
		if (this->mode == "automatic")
		{
			
			int time = (millis() / 1000) % 8;

			// Seconds 0 - 3: light is green
			if (time < 3) this->changeColor("green");
			// Seconds 3 - 4: light is yellow
			else if (time < 4) this->changeColor("yellow");
			// Seconds 4 - 7: light is red
			else if (time < 7) this->changeColor("red");

		}
	}

	String getMode()
	{
		return this->mode;
	}
	void setMode(String newMode = "manual")
	{
		this->mode = newMode;
	}
};

/*
    Json parametric GET REST response
     by Mischianti Renzo <https://www.mischianti.org>

    https://www.mischianti.org/

*/

const char *ssid = "SM-G935P168";
const char *password = "password";

TrafficLight t = TrafficLight(RED_LED_PIN, YELLOW_LED_PIN, GREEN_LED_PIN);

ESP8266WebServer server(80);

void getSettings()
{
	String response = "{";

	response += "\"ip\": \"" + WiFi.localIP().toString() + "\"";
	response += ",\"gw\": \"" + WiFi.gatewayIP().toString() + "\"";
	response += ",\"nm\": \"" + WiFi.subnetMask().toString() + "\"";

	if (server.arg("signalStrength") == "true")
	{
		response += ",\"signalStrengh\": \"" + String(WiFi.RSSI()) + "\"";
	}

	if (server.arg("chipInfo") == "true")
	{
		response += ",\"chipId\": \"" + String(ESP.getChipId()) + "\"";
		response += ",\"flashChipId\": \"" + String(ESP.getFlashChipId()) + "\"";
		response += ",\"flashChipSize\": \"" + String(ESP.getFlashChipSize()) + "\"";
		response += ",\"flashChipRealSize\": \"" + String(ESP.getFlashChipRealSize()) + "\"";
	}
	if (server.arg("freeHeap") == "true")
	{
		response += ",\"freeHeap\": \"" + String(ESP.getFreeHeap()) + "\"";
	}
	response += "}";

	server.send(200, "text/json", response);
}

void sendIndex()
{
	String response = "<title>Traffic Light</title><head> <style>.circle{width: 100px; height: 100px; -webkit-border-radius: 25px; -moz-border-radius: 25px; border-radius: 50px;}#red{background: red;}#yellow{background: yellow;}#green{background: green;}.modeButton{padding: 32px 64px; color: white;}#Auto{background-color: green;}#manual{background-color: red;}</style></head><h1>Traffic Light</h1><body> <button type=\"button\" id=\"manual\" class=\"modeButton\">Manual</button> <button type=\"button\" id=\"auto\" class=\"modeButton\">Automatic</button> <div id=\"red\" class=\"circle\"></div><div id=\"yellow\" class=\"circle\"></div><div id=\"green\" class=\"circle\"></div></body><footer> <script src='./control.js'></script></footer>";
	server.send(200, "text/html", response);
}

void sendJS()
{
	String response = "var url=\"control/\";var mode=\"manual\";sendRequestMode(mode);function sendRequest(color){let xhr=new XMLHttpRequest(); xhr.open(\"POST\", url, true); xhr.setRequestHeader(\"Content-Type\", \"application/json; charset=UTF-8\"); xhr.send(JSON.stringify({\"mode\": \"manual\", \"color\": color}));}function sendRequestMode(){let xhr=new XMLHttpRequest(); xhr.open(\"POST\", url, true); xhr.setRequestHeader(\"Content-Type\", \"application/json; charset=UTF-8\"); xhr.send(JSON.stringify({\"mode\": mode}));}document.getElementById(\"red\").addEventListener(\"click\", function (){sendRequest(\"red\");});document.getElementById(\"yellow\").addEventListener(\"click\", function (){sendRequest(\"yellow\");});document.getElementById(\"green\").addEventListener(\"click\", function (){sendRequest(\"green\");});document.getElementById(\"auto\").addEventListener(\"click\", function (){mode=\"auto\"; sendRequestMode();});document.getElementById(\"manual\").addEventListener(\"click\", function (){mode=\"manual\"; sendRequestMode();});";
	server.send(200, "text/html", response);
}

void controlLights()
{
	String postBody = server.arg("plain");
	Serial.println(postBody);

	DynamicJsonDocument doc(512);
	DeserializationError error = deserializeJson(doc, postBody);
	if (error)
	{
		// if the file didn't open, print an error:
		Serial.print(F("Error parsing JSON "));
		Serial.println(error.c_str());

		String msg = error.c_str();

		server.send(400, F("text/html"),
					"Error in parsin json body! <br>" + msg);
	}
	else
	{
		JsonObject postObj = doc.as<JsonObject>();

		Serial.print(F("HTTP Method: "));
		Serial.println(server.method());

		if (server.method() == HTTP_POST)
		{
			if (postObj.containsKey("mode"))
			{

				Serial.println(F("done."));
				// Serial.println("in the cool place yo");

				// Serial.println(server.arg("mode"));

				String mode = doc["mode"];
				String color = doc["color"];

				if (mode == "manual")
				{

					if (postObj.containsKey("color")){
						// Serial.println(mode);
						t.setMode(mode);
						t.changeColor(color);
					}
				}
				else if (mode == "auto")
				{
					Serial.println("automatic");
					t.setMode("automatic");
				}

				// Create the response
				// To get the status of the result you can get the http status so
				// this part can be unusefully
				DynamicJsonDocument doc(512);
				doc["status"] = "OK";

				Serial.print(F("Stream..."));
				String buf;
				serializeJson(doc, buf);

				server.send(201, F("application/json"), buf);
				Serial.print(F("done."));
			}
			else
			{
				DynamicJsonDocument doc(512);
				doc["status"] = "KO";
				doc["message"] = F("No data found, or incorrect!");

				Serial.print(F("Stream..."));
				String buf;
				serializeJson(doc, buf);

				server.send(400, F("application/json"), buf);
				Serial.print(F("done."));
			}
		}
	}
}

// void test()
// {
// 	String response = "{";
// 	response += "\"KEY\": \"VALUE\"";
// 	response += "}";
// 	server.send(200, "text/json", response);
// }

// Define routing
void restServerRouting()
{
	server.on("/", HTTP_GET, []()
			  { server.send(200, F("text/html"),
							F("<meta http-equiv=\"refresh\" content=\"0;URL='index.html'\" />")); });

	server.on(F("/settings"), HTTP_GET, getSettings);

	server.on(F("/index.html"), HTTP_GET, sendIndex);
	server.on(F("/control.js"), HTTP_GET, sendJS);
	server.on(F("/control/"), HTTP_POST, controlLights);
}

// Manage not found URL
void handleNotFound()
{
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++)
	{
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
}

void setup(void)
{
	Serial.begin(115200);
	Serial.print("starting!");
	pinMode(RED_LED_PIN, OUTPUT);
	pinMode(YELLOW_LED_PIN, OUTPUT);
	pinMode(GREEN_LED_PIN, OUTPUT);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	// Activate mDNS this is used to be able to connect to the server
	// with local DNS hostmane esp8266.local
	if (MDNS.begin("esp8266"))
	{
		Serial.println("MDNS responder started");
	}

	// Set server routing
	restServerRouting();
	// Set not found response
	server.onNotFound(handleNotFound);
	// Start server
	server.begin();
	Serial.println("HTTP server started");
}

void loop(void)
{
	t.update();
	server.handleClient();
}