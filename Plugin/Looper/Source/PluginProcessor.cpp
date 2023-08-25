#include "PluginProcessor.h"
#include "PluginEditor.h"

/*

BACKEND

*/

/**
 * @brief Constructor is implicit class declaration.
 */
PluginProcessor::PluginProcessor() : looperProcessor(getTotalNumInputChannels()),
                                     apvts(*this, &undoManager, "PARAMETERS", createParameterLayout())
{
    bufferSize = -1;
    #if ENABLE_LOGGING
        juce::Time currentTime = juce::Time::getCurrentTime();
        juce::String timestamp = currentTime.toString(true, true); // Format: YYYY-MM-DD HH:mm:ss
        juce::String logFileName = juce::String(LOG_DIRECTORY) + juce::String("/pluginLog_") + timestamp + juce::String(".txt");
        juce::File logFile(logFileName);
        juce::Logger::setCurrentLogger (new juce::FileLogger (logFile, "Your Plugin Logs", 10000));
    #else
        juce::Logger::setCurrentLogger(nullptr);
    #endif
}

/**
 * @brief Method is called by the host DAW to process a block of audio data.
 * 
 * @param buffer audio data to be processed
 * @param midiMessages object that contains any MIDI messages that have been received by the plugin
 */
void PluginProcessor::processBlock(juce::AudioBuffer<float>& audioBuffer,
                                   juce::MidiBuffer& midiBuffer) {
    // set buffer size and update it if it changed
    if (bufferSize == -1) {  // first run
        // buffer size & samplerate is only guaranteed to be correctly obtained from within this method
        bufferSize = getBlockSize();
        sampleRate = getSampleRate();
        // -> forward info to audioMemory via looperProcessor
        looperProcessor.forwardAudioDeviceInfoToAudioMemory(sampleRate, bufferSize);
    } else if (bufferSize != getBlockSize()) {
        throw std::runtime_error("The Plugin does currently not support block size changes during runtime.");
        // TODO: Reinitialize audioMemory as quick fix?
        // looperProcessor.setBufferSize(getBlockSize());
    }
    
    // delegate audio processing to LooperProcessor class by passing the reference
    looperProcessor.processAudio(audioBuffer);

    float gainValue = apvts.getRawParameterValue("Gain")->load();
    audioBuffer.applyGain(gainValue);
}

/**
 * @brief The createEditor method is called by the host DAW to create the GUI of the plugin. 
 * 
 * @return juce::AudioProcessorEditor* 
 */
juce::AudioProcessorEditor* PluginProcessor::createEditor() {
    return new PluginEditor(*this);
}

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData) {
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation(const void* data, int sizeInBytes) {
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Gain", "Gain", 0.f, 1.f, 1.0f)); // TODO one should set parameter version for Logic and Garageband
    params.push_back(std::make_unique<juce::AudioParameterBool>("Footstep Trigger", "Footstep Trigger", false));

    return { params.begin(), params.end() };
}


PluginProcessor::~PluginProcessor()
{
    juce::Logger::setCurrentLogger(nullptr);  // This will delete the logger set above
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


