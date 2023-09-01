#pragma once

#include "States.h"
#include <shared_plugin_helpers/shared_plugin_helpers.h>

class AudioMemory {

public:
    AudioMemory(int numChannels);
    
    void setAudioDeviceInfo(int bufferSize, int sampleRate);
    
    bool isFirstLoop = true;

    void recordOrOverdub(juce::AudioBuffer<float>& audioBuffer);
    void playBack(juce::AudioBuffer<float>& audioBuffer);

    void deleteMemory();
    void resetMemoryIndex();
    
    void applyCrossFade();
    // void addStateChangeListener(StateChangeListener* listener); // TODO: do we need several types of listeners actually pr only one class?
    // void removeStateChangeListener(StateChangeListener* listener);

private:
    int nChannels;
    int bufferSize;
    int sampleRate;
    
    unsigned long memoryIndex;
    
    const int CROSSFADE_MS = 200;
    
    void incrementMemoryIndex();
    
    juce::AudioBuffer<float>* getBufferPointerFromMemory();
    
    // vector to store the audio buffers
    // By using std::unique_ptr, the ownership and lifetime management of 
    // the juce::AudioBuffer<float> objects are handled automatically, 
    // ensuring proper memory deallocation and avoiding memory leaks.
    std::vector<std::unique_ptr<juce::AudioBuffer<float>>> memory;

    // juce::ListenerList<StateChangeListener> listeners;
    // inform listeners that loop is about to begin again, such that eventual cross fade can be applied
    // or the ui can be updated
    
};