#include "PluginProcessor.h"
#include "LooperProcessor.h"
#include "PluginEditor.h"

/*

BACKEND

*/

/**
 * @brief Constructor is implicit class declaration.
 */
PluginProcessor::PluginProcessor() {
    // initializes parameters variable and add this object to parameter tree
    parameters.add(*this);
}

/**
 * @brief Method is called by the host DAW to process a block of audio data.
 * 
 * @param buffer audio data to be processed
 * @param midiMessages object that contains any MIDI messages that have been received by the plugin
 */
void PluginProcessor::processBlock(juce::AudioBuffer<float>& audioBuffer,
                                   juce::MidiBuffer& midiBuffer) {
    juce::ignoreUnused(midiBuffer);
    
    // check for midi and set the state of the looper
    looperProcessor.setApplicationState(midiBuffer);
    
    // delegate audio processing to LooperProcessor class
    looperProcessor.processAudio(audioBuffer);

    if (parameters.enable->get())
        audioBuffer.applyGain(parameters.gain->get());
    else
        audioBuffer.clear();
}

/**
 * @brief The createEditor method is called by the host DAW to create the GUI of the plugin. 
 * 
 * @return juce::AudioProcessorEditor* 
 */
juce::AudioProcessorEditor* PluginProcessor::createEditor() {
    return new PluginEditor(*this);
}

/**
 * @brief 
 * 
 * @param destData The memoryblock to store the serialized data.
 */
void PluginProcessor::getStateInformation(juce::MemoryBlock& destData) {
    // Serializes parameters, and any other potential data into an XML:
    juce::ValueTree params("Params");
    for (auto& param: getParameters())
    {
        juce::ValueTree paramTree(PluginHelpers::getParamID(param));
        paramTree.setProperty("Value", param->getValue(), nullptr);
        params.appendChild(paramTree, nullptr);
    }
    juce::ValueTree pluginPreset("MyPlugin");
    pluginPreset.appendChild(params, nullptr);
    // This a good place to add any non-parameters to your preset
    copyXmlToBinary(*pluginPreset.createXml(), destData);
}

/**
 * @brief Set application state from XML.
 * 
 * @param data location of data.
 * @param sizeInBytes size of data.
 */
void PluginProcessor::setStateInformation(const void* data, int sizeInBytes) {
    auto xml = getXmlFromBinary(data, sizeInBytes);
    if (xml != nullptr) {
        auto preset = juce::ValueTree::fromXml(*xml);
        auto params = preset.getChildWithName("Params");

        for (auto& param: getParameters()) {
            auto paramTree = params.getChildWithName(PluginHelpers::getParamID(param));
            if (paramTree.isValid())
                param->setValueNotifyingHost(paramTree["Value"]);
        }
        // Load your non-parameter data now
    }
}

/**
 * @short
 * This function is called by the host DAW when the plugin is loaded,
 * and it allows the host DAW to create an instance of the plugin and communicate
 * with it through the AudioProcessor interface.
 * @return juce::AudioProcessor* 
 */

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new PluginProcessor();
}


