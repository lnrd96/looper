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

/// @brief Add the audio buffer to the current loop and combine it with
///        already recorded content.
/// @param audioBuffer 
void AudioMemory::RecordOrOverdub(juce::AudioBuffer<float>& audioBuffer){
    if (this->memory.size() == 0) {
        // first loop
        juce::AudioBuffer<float>* newBuffer = new juce::AudioBuffer<float>(nChannels, bufferSize);
        newBuffer->copyFrom(0, 0, audioBuffer, 0, 0, bufferSize);  // channel 0
        newBuffer->copyFrom(1, 0, audioBuffer, 1, 0, bufferSize);  // channel 1
        this->memory.push_back(std::make_unique<juce::AudioBuffer<float>>(*newBuffer));
    } else if (memory.size() > 0) {
        // overdubbing -> combine buffers
        juce::AudioBuffer<float>* memoryBufferP = getBufferPointerFromMemory();
        // add memory to current buffer -> audioBuffer becomes the combined buffer 
        audioBuffer.addFrom(0, 0, *memoryBufferP, 0, 0, bufferSize); // TODO this may lead to overflow if `addFrom` does not handle sample normalisation
        audioBuffer.addFrom(1, 0, *memoryBufferP, 1, 0, bufferSize);
        // update memory with combined buffer, the same that will be output by the plugin
        memoryBufferP->copyFrom(1, 0, audioBuffer, 1, 0, bufferSize);
        memoryBufferP->copyFrom(1, 0, audioBuffer, 1, 0, bufferSize);
    } else {
        throw std::runtime_error("Invalid memory size.");
    }
}

/// @brief Get the audio buffer corresponding to current position in the loop.
/// @return Returns pointer to the next audio buffer.
juce::AudioBuffer<float>* AudioMemory::getBufferPointerFromMemory(){
    juce::AudioBuffer<float>* pBuffer = memory[memoryIndex].get();
    return pBuffer;
}

/// @brief Updates memory index circularly to point to next buffer.
///        This function should only be used by the LooperProcessor class.
void AudioMemory::incrementMemoryIndex(){
    if (this->memory.size() <= this->memoryIndex + 1 ){
        // Start loop from beginning
        this->resetIndex();
    } else {
        this->memoryIndex++;
    }
}

/// @brief Delete memory, all elements pointed to by unique_ptr, and clear the vector.
void AudioMemory::deleteMemory(){
    this->memory.clear();
}

/// @brief Sets the memory index to zero.
void AudioMemory::resetIndex(){
    this->memoryIndex = 0;
}