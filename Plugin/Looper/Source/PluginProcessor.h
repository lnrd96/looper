#pragma once

#include "Parameters.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include "LooperProcessor.h"

class PluginProcessor : public PluginHelpers::ProcessorBase {
public:
    PluginProcessor();
    void processBlock(juce::AudioBuffer<float>& audioBuffer,
                      juce::MidiBuffer& midiBuffer) override;
    juce::AudioProcessorEditor* createEditor() override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    ~PluginProcessor() override;
    LooperProcessor looperProcessor;

private:
    int bufferSize;
    Parameters parameters;
};
