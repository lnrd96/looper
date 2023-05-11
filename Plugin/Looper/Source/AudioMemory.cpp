#include "AudioMemory.h"
/*

Class to store and handle the recorded audio.

*/

/**
 * @brief Constructor
 */
AudioMemory::AudioMemory(int nChannels, int bufferSize)
    : nChannels(nChannels), bufferSize(bufferSize), memoryIndex(0)
{}

/// @brief Save the specified audio buffer to the memory member of this class.
/// @param audioBuffer 
void AudioMemory::addBufferToMemory(juce::AudioBuffer<float>& audioBuffer){
    if (this->memory.size() == 0) {
        // first loop
        juce::AudioBuffer<float>* newBuffer = new juce::AudioBuffer<float>(nChannels, bufferSize);
        newBuffer->copyFrom(0, 0, audioBuffer, 0, 0, bufferSize);  // channel 0
        newBuffer->copyFrom(1, 0, audioBuffer, 1, 0, bufferSize);  // channel 1
        this->memory.push_back(std::make_unique<juce::AudioBuffer<float>>(*newBuffer));
    } else if (memory.size() > 0) {
        // overdubbing
        juce::AudioBuffer<float>* buffer = memory[memoryIndex].get();
        // TODO: Combine content of buffer and 
    } else {
        throw std::runtime_error("Invalid memory size.");
    }
}

/// @brief Returns pointer to the next audio buffer. Increments memory index.
juce::AudioBuffer<float>* AudioMemory::getBufferFromMemory(){
    if (memory.size() < memoryIndex - 1){
        // Start loop from beginning
        this->resetIndex();
    }
    juce::AudioBuffer<float>* pBuffer = memory[memoryIndex].get();
    memoryIndex++;
    return pBuffer;
}

/// @brief Delete memory, all elements pointed to by unique_ptr, and clear the vector.
void AudioMemory::deleteMemory(){
    this->memory.clear();
}

/// @brief Sets the memory index to zero.
void AudioMemory::resetIndex(){
    this->memoryIndex = 0;
}