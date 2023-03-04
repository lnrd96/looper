#include "AudioMemory.h"
/*

Class to store and handle the recorded audio.

*/

class AudioMemory {
public:
    /**
     * @brief Constructor
     */
    AudioMemory::AudioMemory(int nChannels, int bufferSize)
        : nChannels(nChannels), bufferSize(bufferSize)
    {}

    /// @brief Save the specified audio buffer to the memory member of this class.
    /// @param audioBuffer 
    void addBufferToMemory(juce::AudioBuffer<float>& audioBuffer){
        // TODO: distinguish between recording first loop and overdubbing
        juce::AudioBuffer<float>* newBuffer = new juce::AudioBuffer<float>(nChannels, bufferSize);
        newBuffer->copyFrom(0, 0, audioBuffer, 0, 0, bufferSize);  // channel 0
        newBuffer->copyFrom(1, 0, audioBuffer, 1, 0, bufferSize);  // channel 1
        this->memory.push_back(std::make_unique<juce::AudioBuffer<float>>(*newBuffer));
    }

    /// @brief Returns pointer to the next audio buffer. Increments memory index.
    juce::AudioBuffer<float>* getBufferFromMemory(){
        if (memory.size() < memoryIndex - 1){
            throw std::runtime_error("The memory index bigger than the size.");
        }
        juce::AudioBuffer<float>* buffer = memory[memoryIndex].get();
        memoryIndex++;
    }

    /// @brief Delete memory, all elements pointed to by unique_ptr, and clear the vector.
    void deleteMemory(){
        memory.clear();
    }

    /// @brief Sets the memory index to zero.
    void resetIndex(){
        memoryIndex = 0;
    }

private:
    int nChannels;
    int bufferSize;
    int memoryIndex = 0;
    // vector storing pointers to the buffers  https://cplusplus.com/reference/vector/vector/
    std::vector<std::unique_ptr<juce::AudioBuffer<float>>> memory;

};