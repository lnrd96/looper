#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "States.h"
#include "AudioMemory.h"


class LooperProcessor {
public:
    explicit LooperProcessor(int nChannels, int bufferSize);
    void setApplicationState(juce::MidiBuffer& midiBuffer);
    ApplicationState getApplicationState();
    void processAudio(juce::AudioBuffer<float>& audioBuffer);
private:
    ApplicationState state;
    AudioMemory audioMemory;
};
