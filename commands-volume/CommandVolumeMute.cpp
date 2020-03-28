#include "CommandVolumeMute.h"
#include <stdio.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>

const char* CommandVolumeMute::getName() const {
    return "volume.mute";
}

void CommandVolumeMute::execute(const std::map<std::string, std::string>& params) {

    auto directionIt = params.find("direction");
    if (directionIt == params.end()) {
        setMute(!getMute());
        return;
    }

    std::string directionStr = directionIt->second;
    if (directionStr == "on") {
        setMute(true);
        return;
    }
    if (directionStr == "off") {
        setMute(false);
        return;
    }
    if (directionStr == "toggle") {
        setMute(!getMute());
        return;
    }

};

bool CommandVolumeMute::getMute() {

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

    BOOL currentMute = 0;
    endpointVolume->GetMute(&currentMute);
    endpointVolume->Release();
    CoUninitialize();

    return currentMute;

}

void CommandVolumeMute::setMute(bool val) {

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

    endpointVolume->SetMute(val, NULL);
    endpointVolume->Release();
    CoUninitialize();

}
