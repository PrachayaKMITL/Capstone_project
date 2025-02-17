#include <NimBLEDevice.h>
#include <WiFi.h>

// Define BLE characteristics
NimBLECharacteristic *inputCharacteristic;
NimBLECharacteristic *sensorCharacteristic;
int sensorData[4] = {1, 2, 3, 4}; // Simulated sensor data (array with 4 elements)

class MyServerCallbacks : public NimBLEServerCallbacks {
public:
    void onConnect(NimBLEServer* pServer) {
        Serial.println("Device connected");
    }

    void onDisconnect(NimBLEServer* pServer) {
        Serial.println("Device disconnected");
        NimBLEDevice::startAdvertising();  // Restart advertising after disconnect
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing BLE Server...");

    // Initialize BLE
    NimBLEDevice::init("ESP32-Server");
    NimBLEServer *server = NimBLEDevice::createServer();
    server->setCallbacks(new MyServerCallbacks());

    // Create BLE Service
    NimBLEService *service = server->createService("12345678-1234-1234-1234-123456789abc");

    // Create Input Characteristic (Write)
    inputCharacteristic = service->createCharacteristic(
        "A1B2C3D4-5678-1234-5678-9ABCDEF01234",
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
    );
    inputCharacteristic->setValue("Ready to receive input");

    // Create Sensor Characteristic (Read/Notify)
    sensorCharacteristic = service->createCharacteristic(
        "B2C3D4E5-6789-2345-6789-ABCDEF123456",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    sensorCharacteristic->setValue("Feedback initialized");

    // Start the service
    service->start();

    // Start BLE advertising
    NimBLEAdvertising *advertising = NimBLEDevice::getAdvertising();
    advertising->addServiceUUID(service->getUUID());
    advertising->start();

    Serial.println("BLE Server is now advertising...");
}

void loop() {
    // Update sensor data (you can modify the values as needed)
    sensorData[0] = random(100); // Example of updating the first value with a random integer

    // Convert the integer array to a byte array
    uint8_t dataToSend[4 * sizeof(int)];  // Array to hold the byte data of the sensorData array

    for (int i = 0; i < 4; i++) {
        // Copy each int as 4 bytes into the dataToSend array
        memcpy(dataToSend + i * sizeof(int), &sensorData[i], sizeof(int));
    }

    // Set the new data in the sensor characteristic (raw byte data)
    sensorCharacteristic->setValue(dataToSend, sizeof(dataToSend));

    // Send the data via notification
    sensorCharacteristic->notify();  // Notify the console app with the updated sensor data

    // Output the sent data to the serial monitor
    Serial.print("Sent data: ");
    for (int i = 0; i < 4; i++) {
        Serial.print(sensorData[i]);
        if (i < 3) Serial.print(" ");
    }
    Serial.println();

    delay(50);  // Wait 1 second before sending new data
}
