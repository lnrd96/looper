#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_basics/juce_gui_basics.h>

/*

FRONTEND

*/

PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), pluginProcessor(p)
{
    // window
    addAndMakeVisible(editor);
    setSize(400, 300);

    // title 
    titleTextEditor.setText("Looper");
    titleTextEditor.setColour(juce::TextEditor::textColourId, juce::Colours::black);  // Set text color
    titleTextEditor.setColour(juce::TextEditor::backgroundColourId, juce::Colours::white);  // Set background color
    addAndMakeVisible(titleTextEditor);  // Add the text field to the component

    // label, to display application state
    addAndMakeVisible(statusLabel);
    statusLabel.setFont(juce::Font(16.0f)); 

    p.looperProcessor.addStateChangeListener(this);

    triggerButton.setButtonText("Footstep Trigger");
    triggerButton.addListener(this);
    addAndMakeVisible(triggerButton);

}

void PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PluginEditor::resized()
{   // plugin is 400, 300
    editor.setBounds(getLocalBounds());
    statusLabel.setBounds(200 - 15, 200, getWidth() - 20, 30);
    triggerButton.setBounds(200 - 75, 100, 150, 30); // x, y, width, height
}

void PluginEditor::handleAsyncUpdate()
{
    // Update the GUI or do other necessary tasks in response to state change
    // This is called on the main message thread.
    displayApplicationState(pluginProcessor.looperProcessor.getApplicationState());
}


void PluginEditor::stateChanged(ApplicationState newState)
{
    // Trigger an asynchronous update.
    // The handleAsyncUpdate() method will be called on the main message thread.
    triggerAsyncUpdate();
}

void PluginEditor::displayApplicationState(ApplicationState state) {
        juce::String stateText;
    switch (state)
    {
        case ApplicationState::INIT: stateText = "Empty Loop"; break;
        case ApplicationState::PLAYBACK: stateText = "Playback"; break;
        case ApplicationState::PAUSE: stateText = "Paused"; break;
        case ApplicationState::RECORD: stateText = "Recording"; break;
        default: stateText = "Unknown State"; break;
    }
    
    statusLabel.setText(stateText, juce::dontSendNotification);

}

void PluginEditor::buttonClicked(juce::Button* button) {
    if (button == &triggerButton) {
        pluginProcessor.looperProcessor.detectApplicationState();
    }
}


PluginEditor::~PluginEditor()
{
    this->pluginProcessor.looperProcessor.removeStateChangeListener(this);
    cancelPendingUpdate();  // from AsyncUpdater
}