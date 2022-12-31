#include "PluginProcessor.h"
#include "PluginEditor.h"

/*

FRONTEND

*/

PluginEditor::PluginEditor(
    PluginProcessor& p)
    : AudioProcessorEditor(&p)
{
    addAndMakeVisible(editor);
    setSize(400, 300);
}

void PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PluginEditor::resized()
{
    editor.setBounds(getLocalBounds());
}
