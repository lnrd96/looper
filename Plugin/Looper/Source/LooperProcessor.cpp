#include "LooperProcessor.h"
/*

Class to handle the processing logic and state management.

*/

/**
 * @brief Constructor
 */

LooperProcessor::LooperProcessor(int nChannels)
    : state(ApplicationState::INIT), previousState(ApplicationState::INIT), audioMemory(nChannels)
{}

void LooperProcessor::setApplicationState(juce::MidiBuffer& midiBuffer) {
    // TODO: decode midiBuffer.
    // TODO: Update prev state too.
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
        if (this->previousState == ApplicationState::INIT) return;
        this->audioMemory.deleteMemory();
    } else if (this->state == ApplicationState::RECORD){
        // save current input buffer
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
