#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "States.h"
#include "StateChangeListener.h"
#include "AudioMemory.h"


class LooperProcessor {
public:
    explicit LooperProcessor(int nChannels);
    void setBufferSize(int bufferSize);
    void setApplicationState(juce::MidiBuffer& midiBuffer);
    ApplicationState getApplicationState();
    void processAudio(juce::AudioBuffer<float>& audioBuffer);
    void addStateChangeListener(StateChangeListener* listener);
    void removeStateChangeListener(StateChangeListener* listener);

private:
    juce::ListenerList<StateChangeListener> listeners;
    void notifyStateChange();
    ApplicationState state;
    ApplicationState previousState;
    AudioMemory audioMemory;
};
