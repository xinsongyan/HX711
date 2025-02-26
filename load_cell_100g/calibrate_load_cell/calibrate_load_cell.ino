#include "HX711.h"

#define DT  2  // Data pin
#define SCK   3  // Clock pin

HX711 scale;

void setup() {
    Serial.begin(38400);
    scale.begin(DT, SCK);
    Serial.println("Make sure there is nothing on the scale! If not, clean and rerun this script!");
    scale.set_scale(); // No parameter means using the default scale
    scale.tare();      // Reset the scale to zero
    Serial.println("Place a known weight on the scale and then input the known weight value in gram:");
}

void loop() {

    if (Serial.available()) {
        
        float knownWeight = Serial.parseFloat(); // Read user input for known weight
        if (knownWeight > 0) {
            float reading = scale.get_units(10); // Take multiple readings for accuracy
            float scaleFactor = reading / knownWeight;
            Serial.print("Calibration factor: ");
            Serial.println(scaleFactor);
            
            scale.set_scale(scaleFactor); // Apply the new scale factor
            Serial.println("Calibration complete. Scale is now accurate.");
        }
    }
    delay(500);
}
