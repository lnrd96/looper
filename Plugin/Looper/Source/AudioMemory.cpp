#include "AudioMemory.h"
/*

Class to store and handle the recorded audio.

*/

/**
 * @brief Constructor
 */
AudioMemory::AudioMemory(int nChannels)
    : nChannels(nChannels), memoryIndex(0)
{}

/// @brief Add the audio buffer to the current loop and combine it with
///        already recorded content.
/// @param audioBuffer 
void AudioMemory::RecordOrOverdub(juce::AudioBuffer<float>& audioBuffer){
    if (isFirstLoop) {
        auto newBuffer = std::make_unique<juce::AudioBuffer<float>>(nChannels, bufferSize);
        for (int channel = 0; channel < nChannels; ++channel) {
            newBuffer->copyFrom(channel, 0, audioBuffer, channel, 0, bufferSize);
        }
        this->memory.push_back(std::move(newBuffer));
        this->incrementMemoryIndex();
    } else if (!isFirstLoop) {
        // overdubbing -> combine buffers
        juce::AudioBuffer<float>* memoryBufferP = getBufferPointerFromMemory();
        for (int channel = 0; channel < nChannels; ++channel) {
            // add memory to current buffer -> audioBuffer becomes the combined buffer 
            audioBuffer.addFrom(channel, 0, *memoryBufferP, channel, 0, bufferSize);
            // update memory with combined buffer, the same that will be output by the plugin
            memoryBufferP->copyFrom(channel, 0, audioBuffer, channel, 0, bufferSize);
        }
        this->incrementMemoryIndex();
    } else {
        juce::Logger::writeToLog("Invalid audio memory size.");
    }
}

/// @brief Combine audio memory content with with current input buffer
void AudioMemory::PlayBack(juce::AudioBuffer<float>& audioBuffer){
    if (this->memory.size() == 0) {
        juce::Logger::writeToLog("Tried to play back empty audio memory.");
    } else if (memory.size() > 0) {
        juce::AudioBuffer<float>* memoryBufferP = getBufferPointerFromMemory();
        // add memory to current buffer -> audioBuffer becomes the combined buffer 
        for (int channel = 0; channel < nChannels; ++channel) {
            audioBuffer.addFrom(channel, 0, *memoryBufferP, channel, 0, bufferSize);  // TODO: overflow-add?
        }
        this->incrementMemoryIndex();
    } else {
        juce::Logger::writeToLog("Invalid audio memory size.");
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
    this->resetIndex();
}

/// @brief Sets the memory index to zero.
void AudioMemory::resetIndex(){
    this->memoryIndex = 0;
}

/// @brief Update the buffer size.
void AudioMemory::setBufferSize(int bufferSize) {
    this->bufferSize = bufferSize;
}