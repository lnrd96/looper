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
void AudioMemory::recordOrOverdub(juce::AudioBuffer<float>& audioBuffer){
    if (isFirstLoop) {
        auto newBuffer = std::make_unique<juce::AudioBuffer<float>>(nChannels, bufferSize);
        for (int channel = 0; channel < nChannels; ++channel) {
            newBuffer->copyFrom(channel, 0, audioBuffer, channel, 0, bufferSize);
        }
        this->memory.push_back(std::move(newBuffer));
        this->incrementMemoryIndex();
    } else if (!isFirstLoop) {
        if (memory.empty()) {
            DBG("Warning: Tried to overdub but memory is empty.");
            return;
        }

        // overdubbing -> combine buffers
        juce::AudioBuffer<float>* memoryBufferP = getBufferPointerFromMemory();
        if (memoryBufferP == nullptr) {
            DBG("Warning: memoryBufferP is null.");
            return;
        }
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
void AudioMemory::playBack(juce::AudioBuffer<float>& audioBuffer){
    if (this->memory.size() == 0) {
        juce::Logger::writeToLog("Tried to play back empty audio memory.");
    } else if (memory.size() > 0) {
        juce::AudioBuffer<float>* memoryBufferP = getBufferPointerFromMemory();
        // add memory to current buffer -> audioBuffer becomes the combined buffer 
        for (int channel = 0; channel < nChannels; ++channel) {
            audioBuffer.addFrom(channel, 0, *memoryBufferP, channel, 0, bufferSize);
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
        this->resetMemoryIndex();
    } else {
        this->memoryIndex++;
    }
}

/// @brief Delete memory, all elements pointed to by unique_ptr, and clear the vector.
void AudioMemory::deleteMemory(){
    this->memory.clear();
    this->resetMemoryIndex();
}

/// @brief Sets the memory index to zero.
void AudioMemory::resetMemoryIndex(){
    this->memoryIndex = 0;
}

/// @brief Set or update the buffer size and sample rate
void AudioMemory::setAudioDeviceInfo(int bufferSize, int sampleRate) {
    this->bufferSize = bufferSize;
    this->sampleRate = sampleRate;
}

/**
 * @brief Applies an Equal Power (or Cosine) crossfade of AudioMemory::CROSSFADE_MS ms to the memory.
 *        The number of buffers needed to do so depends on the samplerate and the buffer size.
 *        The absolute duration (in time) of the signal doesn't change
 *        Future note: If several audio layers exist, it is only applied to the most recent one.
 */
void AudioMemory::applyCrossFade() {
    int nSamplesRequired = CROSSFADE_MS / 1000 * sampleRate;
    int nBuffersRequired = std::ceil(static_cast<float>(nSamplesRequired) / bufferSize);

    // loop over relevant buffers
    for (int beginBufferIdx = 0; beginBufferIdx < nBuffersRequired; beginBufferIdx++) {
        int endBufferIdx = memory.size() - nBuffersRequired + beginBufferIdx; // find the right buffer in the end for fade-out
        auto& fadeOutBuffer = *memory[endBufferIdx];
        auto& fadeInBuffer = *memory[beginBufferIdx];

        // loop over samples
        for (int sampleIdx = 0; sampleIdx < bufferSize && (endBufferIdx * bufferSize + sampleIdx) < nSamplesRequired; sampleIdx++) {
            // calc crossfade gain
            float t = static_cast<float>(endBufferIdx * bufferSize + sampleIdx) / nSamplesRequired;  // where we are in the cross fade
            float fadeOutGain = std::sqrt(0.5 * (1.0 + std::cos(juce::MathConstants<float>::pi * t)));
            float fadeInGain = std::sqrt(0.5 * (1.0 - std::cos(juce::MathConstants<float>::pi * t)));

            // apply the gain
            for (int channel = 0; channel < nChannels; ++channel) {
                float fadedOutSample = fadeOutBuffer.getSample(channel, sampleIdx) * fadeOutGain;
                float fadedInSample = fadeInBuffer.getSample(channel, sampleIdx) * fadeInGain;
                // mix the faded out end of the recording with the faded in start
                float mixedSample = fadedOutSample + fadedInSample;
                // set the mixed samples to the buffers
                fadeOutBuffer.setSample(channel, sampleIdx, mixedSample);
                fadeInBuffer.setSample(channel, sampleIdx, mixedSample);
            }
        }
    }

}