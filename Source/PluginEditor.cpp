/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AngelSynthAudioProcessorEditor::AngelSynthAudioProcessorEditor (AngelSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ","OSC1FMDEPTH"), adsr(audioProcessor.apvts)
{
    setSize (400, 300);
//    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
//    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);
    // Make Oscillator Selector Visible
    addAndMakeVisible(osc);
    
    // Make ADSR visible
    addAndMakeVisible(adsr);

}

AngelSynthAudioProcessorEditor::~AngelSynthAudioProcessorEditor()
{
    //Set ADSR bounds
}

//==============================================================================
void AngelSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(draculaOrchid);
}

void AngelSynthAudioProcessorEditor::resized()
{
    osc.setBounds(10, 10, 180, 200);

    adsr.setBounds(getWidth()/2,0,getWidth()/2,getHeight() / 2);
}


