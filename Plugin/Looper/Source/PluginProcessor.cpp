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
        juce::String logFileName = juce::String(LOG_DIRECTORY) + juce::String("/Log_") + timestamp + juce::String(".txt");
        juce::File logFile(logFileName);
        juce::Logger::setCurrentLogger (new juce::FileLogger (logFile, "Looper plugin loaded!", 10000));
    #else
        juce::Logger::setCurrentLogger(nullptr);
    #endif
    apvts.addParameterListener("Footstep Trigger", this);
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
        sampleRate = (int)getSampleRate();
        // -> forward info to audioMemory via looperProcessor
        looperProcessor.forwardAudioDeviceInfoToAudioMemory(bufferSize, sampleRate);
    } else if (bufferSize != getBlockSize() || sampleRate != getSampleRate()) {
        looperProcessor.setApplicationState(ApplicationState::INIT);
        // at least ext config change does not crash daw anymore, but
        // TODO: in buffer size other than state change detection does not work anymore
    }
    
    // delegate audio processing to LooperProcessor class by passing the reference
    looperProcessor.processAudio(audioBuffer);

    float gainValue = apvts.getRawParameterValue("Gain")->load();
    audioBuffer.applyGain(gainValue);
}

// when triggered via MIDI not via UI
void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "Footstep Trigger")
    {
        looperProcessor.detectApplicationState();
    }
    if (parameterID == "Reset Trigger")
    {
        looperProcessor.setApplicationState(ApplicationState::INIT);
    }
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

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"Gain", 1}, "Gain", 0.f, 1.f, 1.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"Footstep Trigger", 1},
        "Footstep Trigger",
        juce::StringArray{ "Off", "On" },
        0 // default
    ));
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"Reset Trigger", 1},
        "Reset Trigger",
        juce::StringArray{ "Off", "On" },
        0 // default
    ));


    return { params.begin(), params.end() };
}


PluginProcessor::~PluginProcessor()
{
    juce::Logger::setCurrentLogger(nullptr);  // This will delete the logger set above
    apvts.removeParameterListener("Footstep Trigger", this);
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


