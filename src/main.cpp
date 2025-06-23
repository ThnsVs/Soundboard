#include <iostream>
#include <cmath>
#include <Portaudio/portaudio.h>

#define M_PI 3.14
#define SAMPLE_RATE 44100
#define FREQUENCY 440.0
#define DURATION_SECONDS 5
#define AMPLITUDE 0.5

static int paCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {

    static double phase = 0.0;
    float* out = (float*)outputBuffer;

    for (unsigned int i = 0; i < framesPerBuffer; i++) {
        out[i] = (float)(AMPLITUDE * sin(phase));
        phase += 2.0 * M_PI * FREQUENCY / SAMPLE_RATE;
        if (phase >= 2.0 * M_PI)
            phase -= 2.0 * M_PI;
    }

    return paContinue;
}

int main() {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    PaStream* stream;
    err = Pa_OpenDefaultStream(&stream,
        0, // no input
        1, // mono output
        paFloat32, // 32-bit float samples
        SAMPLE_RATE,
        256, // frames per buffer
        paCallback,
        nullptr);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    Pa_Sleep(DURATION_SECONDS * 1000);

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    std::cout << "Finished playing sine wave." << std::endl;
    return 0;
}
