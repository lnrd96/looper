#pragma once
#include "PluginProcessor.h"
#include "States.h"
#include "StateChangeListener.h"

class PluginEditor : public juce::AudioProcessorEditor, public StateChangeListener, public juce::AsyncUpdater, 
                     juce::Button::Listener
{
public:
    explicit PluginEditor(PluginProcessor& p);
    ~PluginEditor() override;
    juce::TextEditor titleTextEditor;
    void stateChanged(ApplicationState newState) override;
    void handleAsyncUpdate() override;
    juce::TextButton footstepTrigger;
    juce::TextButton resetButton;
    void buttonClicked(juce::Button* button) override;


private:
    PluginProcessor& pluginProcessor;
    juce::Label statusLabel;  // label to display the current application state
    juce::GenericAudioProcessorEditor editor {processor};  // automatically displays all plugin parameters as sliders
    void paint(juce::Graphics&) override;
    void resized() override;
    void displayApplicationState(ApplicationState state);
};
