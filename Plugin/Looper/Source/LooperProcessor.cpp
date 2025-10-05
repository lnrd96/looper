#include "LooperProcessor.h"
/*

Class to handle the processing logic and state management.

*/

/**
 * @brief Constructor
 */

LooperProcessor::LooperProcessor(int nChannels)
    : state(ApplicationState::INIT), audioMemory(nChannels)
{}

/**
 * @brief Is called when the trigger button is pressed.
 * Sets next state according to state machine properties.
 * 
 */
void LooperProcessor::detectApplicationState() {
    juce::int64 currentTimeMs = juce::Time::currentTimeMillis();

    // add the current timestamp to the list
    callTimestamps.add(currentTimeMs);

    // remove any timestamps that are too old
    while (callTimestamps.size() > 0 && (currentTimeMs - callTimestamps.getFirst()) > triggerTimeSpanMs) {
        callTimestamps.remove(0);
    }

    int nTimesTriggeredInTimeSpan = callTimestamps.size();
    if (nTimesTriggeredInTimeSpan == 2) {
        state = ApplicationState::PAUSE;
    }
    else if (nTimesTriggeredInTimeSpan > 2) {
        state = ApplicationState::INIT;
        audioMemory.isFirstLoop = true;
    }
    else {
        switch(state){
            case ApplicationState::INIT:
                state = ApplicationState::RECORD;
                break;
            case ApplicationState::RECORD:
                audioMemory.applyCrossFade();
                state = ApplicationState::PLAYBACK;
                break;
            case ApplicationState::PLAYBACK:
                if (audioMemory.isFirstLoop == true){
                    audioMemory.isFirstLoop = false;
                }
                state = ApplicationState::RECORD;
                break;
            case ApplicationState::PAUSE:
                state = ApplicationState::PLAYBACK;
                break;
        }
    }
    notifyStateChange();
}
void LooperProcessor::forwardAudioDeviceInfoToAudioMemory(int bufferSize, int sampleRate){
    audioMemory.setAudioDeviceInfo(bufferSize, sampleRate);
}

ApplicationState LooperProcessor::getApplicationState() {
    return state;
}

void LooperProcessor::setApplicationState(ApplicationState newState) {
    state = newState;
    notifyStateChange();
}

void LooperProcessor::addStateChangeListener(StateChangeListener* listener) {
    listeners.add(listener);
}

void LooperProcessor::removeStateChangeListener(StateChangeListener* listener) {
    listeners.remove(listener);
}

/// @brief process current audio block
/// @param audioBuffer reference to the buffer that will be output after the current frame
void LooperProcessor::processAudio(juce::AudioBuffer<float>& audioBuffer) {
    if (state == ApplicationState::INIT){
        audioMemory.deleteMemory();
    } else if (state == ApplicationState::RECORD){
        audioMemory.recordOrOverdub(audioBuffer);
    } else if (state == ApplicationState::PLAYBACK){
        audioMemory.playBack(audioBuffer);
    } else if (state == ApplicationState::PAUSE){
        audioMemory.resetMemoryIndex();
    }
}

void LooperProcessor::notifyStateChange() {
    listeners.call([this](StateChangeListener& listener) {
        listener.stateChanged(state);
    });
}
