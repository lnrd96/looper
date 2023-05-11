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

void LooperProcessor::processAudio(juce::AudioBuffer<float>& audioBuffer) {
    if (this->state == ApplicationState::INIT){
        // Do nothing ¯\_(ツ)_/¯
    } else if (this->state == ApplicationState::RECORD){
        this->audioMemory.addBufferToMemory(audioBuffer);
    } else if (this->state == ApplicationState::PLAYBACK){

    } else if (this->state == ApplicationState::PAUSE){

    }
}
