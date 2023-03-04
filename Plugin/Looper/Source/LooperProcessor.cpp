#pragma once

#include "States.h"
#include "LooperProcessor.h"

class LooperProcessor {
public:
    /// @brief  Initializes the member variables state using member initializer list.
    LooperProcessor() : state(ApplicationState::INIT) {}

    void setApplicationState(juce::MidiBuffer& midiBuffer) {
        // TODO: decode midiBuffer.
    }

    void processAudio(juce::AudioBuffer<float>& audioBuffer) {
        if (this->state == ApplicationState::INIT){

        } else if (this->state == ApplicationState::RECORD){

        } else if (this->state == ApplicationState::PLAYBACK){

        } else if (this->state == ApplicationState::PAUSE){

        }
    }

private:
    ApplicationState state;
};
