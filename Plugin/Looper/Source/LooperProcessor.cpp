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

    // Add the current timestamp to the list
    callTimestamps.add(currentTimeMs);

    // Remove any timestamps that are too old
    while (callTimestamps.size() > 0 && (currentTimeMs - callTimestamps.getFirst()) > triggerTimeSpanMs) {
        callTimestamps.remove(0);
    }

    int nTimesTriggeredInTimeSpan = callTimestamps.size();
    if (nTimesTriggeredInTimeSpan == 2) {
        state = ApplicationState::PAUSE;
    }
    else if (nTimesTriggeredInTimeSpan > 2) {
        state = ApplicationState::INIT;
    }
    else {
        switch(state){
            case ApplicationState::INIT:
                state = ApplicationState::RECORD;
                break;
            case ApplicationState::RECORD:
                state = ApplicationState::PLAYBACK;
                break;
            case ApplicationState::PLAYBACK:
                state = ApplicationState::RECORD;
                break;
            case ApplicationState::PAUSE:
                state = ApplicationState::PLAYBACK;
                break;
        }
    }
    notifyStateChange();
}

void LooperProcessor::setBufferSize(int bufferSize) {
    audioMemory.setBufferSize(bufferSize);
}

ApplicationState LooperProcessor::getApplicationState() {
    return state;
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
    if (this->state == ApplicationState::INIT){
        this->audioMemory.deleteMemory();
    } else if (this->state == ApplicationState::RECORD){
        this->audioMemory.RecordOrOverdub(audioBuffer);
    } else if (this->state == ApplicationState::PLAYBACK){
        this->audioMemory.PlayBack(audioBuffer);
    } else if (this->state == ApplicationState::PAUSE){
        this->audioMemory.resetIndex();
    }
}

void LooperProcessor::notifyStateChange() {
    listeners.call([this](StateChangeListener& listener) {
        listener.stateChanged(state);
    });
}
