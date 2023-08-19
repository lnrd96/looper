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

void LooperProcessor::setApplicationState(juce::MidiBuffer& midiBuffer) {
    // TODO: decode midiBuffer.
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
        // Do nothing ¯\_(ツ)_/¯
    } else if (this->state == ApplicationState::RECORD){
        // save current input buffer
        this->audioMemory.RecordOrOverdub(audioBuffer);
        this->audioMemory.incrementMemoryIndex();
    } else if (this->state == ApplicationState::PLAYBACK){
        this->audioMemory.incrementMemoryIndex();
    } else if (this->state == ApplicationState::PAUSE){

    }
}

void LooperProcessor::notifyStateChange() {
    listeners.call([this](StateChangeListener& listener) {
        listener.stateChanged(state);
    });
}
