#include "BLEController.h"
#include <M5Atom.h>

void BLEController::init() {
    BLEDevice::init("D+IO");
}

void BLEController::startAdvertise(const char *message) {
    pAdvertising = BLEDevice::getAdvertising();

    BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

    oAdvertisementData.setFlags(0x06);

    std::string strServiceData = "";
    strServiceData += (uint8_t)(1 + strlen(message));
    strServiceData += (uint8_t)0xff;
    strServiceData += message;
    oAdvertisementData.addData(strServiceData);

    pAdvertising->setAdvertisementData(oAdvertisementData);
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();
}

void BLEController::stopAdvertise() {
    pAdvertising->stop();
}

void BLEController::deinit() {
    BLEDevice::deinit();
}