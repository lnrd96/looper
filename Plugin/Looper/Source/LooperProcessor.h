#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "States.h"
#include "StateChangeListener.h"
#include "AudioMemory.h"


class LooperProcessor {
public:
    explicit LooperProcessor(int nChannels);
    void detectApplicationState();
    ApplicationState getApplicationState();
    void setApplicationState(ApplicationState newState);
    void processAudio(juce::AudioBuffer<float>& audioBuffer);
    void addStateChangeListener(StateChangeListener* listener);
    void removeStateChangeListener(StateChangeListener* listener);
    void forwardAudioDeviceInfoToAudioMemory(int bufferSize, int sampleRate);

private:
    static constexpr juce::int64 triggerTimeSpanMs = 1000;
    juce::Array<juce::int64> callTimestamps;  // Holds the timestamps of function calls to setApplicationState()
    juce::ListenerList<StateChangeListener> listeners;
    void notifyStateChange();
    ApplicationState state;
    AudioMemory audioMemory;
};
