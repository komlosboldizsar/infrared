#include "CommandVolumeAdjust.h"
#include <stdio.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>

const char* CommandVolumeAdjust::getName() const {
    return "volume.adjust";
}

void CommandVolumeAdjust::execute(const std::map<std::string, std::string>& params) {

    float volume = getVolume();

    auto directionIt = params.find("direction");
    auto amountIt = params.find("amount");
    if ((directionIt == params.end()) || (amountIt == params.end()))
        return;
    std::string directionStr = directionIt->second;
    if ((directionStr != "up") && (directionStr != "down"))
        return;
    std::string amountStr = amountIt->second;

    int amountInt;
    sscanf(amountStr.c_str(), "%d", &amountInt);
    float amount = ((float)amountInt)/100;
    if (directionStr == "down")
        amount *= -1;
    volume += amount;

    if (volume < 0)
        volume = 0;
    if (volume > 1)
        volume = 1;

    setVolume(volume);

};

double CommandVolumeAdjust::getVolume() {

    HRESULT hr;

    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
    endpointVolume->Release();
    CoUninitialize();

    return currentVolume;

}

void CommandVolumeAdjust::setVolume(double val) {

    HRESULT hr;

    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    endpointVolume->SetMasterVolumeLevelScalar(val, NULL);
    endpointVolume->Release();
    CoUninitialize();

}
