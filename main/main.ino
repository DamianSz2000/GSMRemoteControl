#include <SoftwareSerial.h>

SoftwareSerial sim800(7, 8);

String dtmfCode = "";
String correctCode = "1234";
bool callAnswered = false;
const int ledPin = 4;

void setup() {
  Serial.begin(9600);
  sim800.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  delay(1000);

  sim800.println("AT+CPIN=\"5574\"");
  delay(3000);

  bool registered = false;
  while (!registered) {
    sim800.println("AT+CREG?");
    delay(1000);
    if (sim800.available()) {
      String netStatus = sim800.readStringUntil('\n');
      if (netStatus.indexOf("+CREG: 0,1") != -1 || netStatus.indexOf("+CREG: 0,5") != -1) {
        registered = true;
        Serial.println("Zalogowano do sieci");
      }
    }
  }

  sim800.println("AT+DDET=1");
}

void loop() {
  if (sim800.available()) {
    String response = sim800.readStringUntil('\n');
    response.trim();

    if (response == "RING" && !callAnswered) {
      Serial.println("Odebrano RING. Odbieranie połączenia...");
      sim800.println("ATA");
      callAnswered = true;
      delay(1000);
      return;
    }

    if (response.startsWith("+DTMF:")) {
      char digit = response.charAt(response.length() - 1);
      Serial.println("Odebrano DTMF: " + String(digit));
      dtmfCode += digit;

      if (dtmfCode.length() == 4) {
        if (dtmfCode == correctCode) {
          Serial.println("Poprawny kod.");
          sim800.println("ATH");
          digitalWrite(ledPin, HIGH);
          delay(5000);
          digitalWrite(ledPin, LOW);
        } else {
          Serial.println("Niepoprawny kod.");
          sim800.println("ATH");
        }

        dtmfCode = "";
        callAnswered = false;
      }
    }

    Serial.println("SIM800: " + response);
  }
}
