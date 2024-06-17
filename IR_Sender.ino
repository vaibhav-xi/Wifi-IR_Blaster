#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

#define IR_RECEIVE_PIN D1 // Pin connected to IR receiver
#define IR_SEND_PIN D2    // Pin connected to IR LED
#define BUTTON_PIN D3     // Pin connected to button
#define BAUD_RATE 115200  // Serial baud rate
#define IR_CODE 0x1FE48B7 // Replace with your IR Hex code

IRrecv irrecv(IR_RECEIVE_PIN);
IRsend irsend(IR_SEND_PIN);

decode_results results; // Variable to store IR code results

void setup() {
  Serial.begin(BAUD_RATE);
  irrecv.enableIRIn(); // Start the IR receiver
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button pin as input with internal pull-up
  irsend.begin(); // Initialize the IR sender
}

void loop() {
  // Check if button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Debounce delay
    delay(50);
    if (digitalRead(BUTTON_PIN) == LOW) {
      // Send the IR code
      irsend.sendNEC(IR_CODE, 32);
      Serial.println("IR code sent.");

      // Wait for button release
      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
    }
  }

  // Check if IR signal received
  if (irrecv.decode(&results)) {
    Serial.print("Received IR code: 0x");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Continue receiving IR signals
  }
}
