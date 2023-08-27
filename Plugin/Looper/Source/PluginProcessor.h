#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "LooperProcessor.h"

class PluginProcessor : public PluginHelpers::ProcessorBase, juce::AudioProcessorValueTreeState::Listener {
public:
    PluginProcessor();
    void processBlock(juce::AudioBuffer<float>& audioBuffer,
                      juce::MidiBuffer& midiBuffer) override;
    juce::AudioProcessorEditor* createEditor() override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    ~PluginProcessor() override;
    LooperProcessor looperProcessor;
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String& parameterID, float newValue) override;

private:
    int bufferSize;
    int sampleRate;
    juce::UndoManager undoManager;
};
