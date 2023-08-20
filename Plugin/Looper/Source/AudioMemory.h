#pragma once

#include "States.h"
#include <shared_plugin_helpers/shared_plugin_helpers.h>

class AudioMemory {

public:
    AudioMemory(int numChannels);
    
    juce::AudioBuffer<float>* getBufferPointerFromMemory();
    
    void RecordOrOverdub(juce::AudioBuffer<float>& audioBuffer);
    void PlayBack(juce::AudioBuffer<float>& audioBuffer);
    void resetMemoryPointer();
    void deleteMemory();
    void resetIndex();
    void incrementMemoryIndex();
    void setBufferSize(int bufferSize);

private:
    int nChannels;
    int bufferSize;
    
    // vector to store the audio buffers
    // By using std::unique_ptr, the ownership and lifetime management of 
    // the juce::AudioBuffer<float> objects are handled automatically, 
    // ensuring proper memory deallocation and avoiding memory leaks.
    std::vector<std::unique_ptr<juce::AudioBuffer<float>>> memory;
    unsigned long memoryIndex;
    
};