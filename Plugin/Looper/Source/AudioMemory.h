#pragma oncek

#include "States.h"

#include <shared_plugin_helpers/shared_plugin_helpers.h>

class AudioMemory {

public:
    AudioMemory(int numChannels, int numSamples);
    
    juce::AudioBuffer<float>& getBufferFromMemory();
    
    void addBufferToMemory(juce::AudioBuffer<float>& audioBuffer);
    void resetMemoryPointer();
    void deleteMemory();
    void resetIndex();

private:
    // vector to store the audio buffers
    std::vector<std::unique_ptr<juce::AudioBuffer<float>>> memory;
    
    int nChannels;
    int bufferSize;
    
};