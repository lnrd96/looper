#include "LooperProcessor.h"


/**
 * @brief Constructor
 */

LooperProcessor::LooperProcessor(int nChannels, int bufferSize)
    : state(ApplicationState::INIT), audioMemory(nChannels, bufferSize)
{}

void LooperProcessor::setApplicationState(juce::MidiBuffer& midiBuffer) {
    // TODO: decode midiBuffer.
}

ApplicationState LooperProcessor::getApplicationState() {
    return state;
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
