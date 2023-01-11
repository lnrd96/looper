#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>


class LooperProcessor {
public:
    void setApplicationState(juce::MidiBuffer& midiBuffer);
};