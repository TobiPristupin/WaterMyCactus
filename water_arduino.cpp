#include <VariableTimedAction.h>

int relayPin = 8;
int sensorPin = 0;

class MoistureData : public VariableTimedAction {
private:

    unsigned long run() {
        Serial.println(readMoisture());
        return 0;
    }


    int readMoisture(){
        int readings = 0;
        for (int i = 0; i < 10; i++){
            readings += analogRead(sensorPin);
            delay(10);
        }

        return readings / 10;
    }
};

class Watering : public VariableTimedAction {
private:

    unsigned long run(){
        digitalWrite(relayPin, HIGH);
        delay(1000);
        digitalWrite(relayPin, LOW);
        return 0;
    }
};


long waterDelay = 86400000; //One day
long updateMoistureDelay = 1000
MoistureData moistureData;
Watering Watering;

void setup() {
   Serial.begin(9600);
   pinMode(relayPin, OUTPUT);
   digitalWrite(relayPin, LOW);
   delay(1000); //Moisture sensor needs a second to calibrate after power

   watering.start(waterDelay);
   moistureData.start(updateMoistureDelay, false);
}


void loop() {
    VariableTimedAction::updateActions();
}


