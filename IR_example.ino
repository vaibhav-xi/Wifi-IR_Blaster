#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

#define IR_RECEIVE_PIN D1 // Pin connected to IR receiver
#define IR_SEND_PIN D2    // Pin connected to IR LED
#define BAUD_RATE 115200  // Serial baud rate

IRrecv irrecv(IR_RECEIVE_PIN);
IRsend irsend(IR_SEND_PIN);

decode_results results; // Variable to store IR code results

void setup() {
  Serial.begin(BAUD_RATE);
  irrecv.enableIRIn(); // Start the IR receiver
}

void loop() {
  if (Serial.available() > 0) {
    // Read input from serial console
    String input = Serial.readStringUntil('\n');

    // Check if input is a valid HEX IR code
    if (isHexString(input)) {
      unsigned long irCode = strtoul(input.c_str(), NULL, 16);

      // Send the IR code
      irsend.sendNEC(irCode);
      Serial.println("IR code sent.");
    } else {
      Serial.println("Invalid IR code format. Please enter a HEX code.");
    }
  }

  // Check if IR signal received
  if (irrecv.decode(&results)) {
    Serial.print("Received IR code: 0x");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Continue receiving IR signals
  }
}
