#pragma once

#include "States.h"
#include "AudioMemory.h"
#include "LooperProcessor.h"

class LooperProcessor {
public:
    /**
     * @brief Constructor
     */
    LooperProcessor::LooperProcessor(int nChannels, int bufferSize)
        : state(ApplicationState::INIT), audioMemory(nChannels, bufferSize)
    {}

    void setApplicationState(juce::MidiBuffer& midiBuffer) {
        // TODO: decode midiBuffer.
    }

    void processAudio(juce::AudioBuffer<float>& audioBuffer) {
        if (this->state == ApplicationState::INIT){
            // Do nothing ¯\_(ツ)_/¯
        } else if (this->state == ApplicationState::RECORD){
            audioMemory.addBufferToMemory(audioBuffer);
        } else if (this->state == ApplicationState::PLAYBACK){

        } else if (this->state == ApplicationState::PAUSE){

        }
    }

private:
    AudioMemory audioMemory;
    ApplicationState state;
};
