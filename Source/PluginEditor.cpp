/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AngelSynthAudioProcessorEditor::AngelSynthAudioProcessorEditor (AngelSynthAudioProcessor& p)
: AudioProcessorEditor (&p)
, audioProcessor (p)
, osc (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH")
, adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
, filterAdsr ("Mod Envelope", audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
, filter (audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
, keyboardComponent (audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)

{
    setSize (600, 500);
    addAndMakeVisible (osc);
    addAndMakeVisible (adsr);
    addAndMakeVisible (filterAdsr);
    addAndMakeVisible (filter);
    addAndMakeVisible (keyboardComponent);
}

AngelSynthAudioProcessorEditor::~AngelSynthAudioProcessorEditor()
{
}

//==============================================================================
void AngelSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void AngelSynthAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 10;
    
    
    const auto bounds = getLocalBounds().reduced(5);
    const auto width = (bounds.getWidth())/2;
    const auto height = (bounds.getHeight()-80)/2;
    const auto paddingY2 = height;
    
    
    osc.setBounds (paddingX, paddingY, width, height);
    adsr.setBounds (osc.getRight()+paddingX, paddingY, width, height);
    filterAdsr.setBounds (paddingX, paddingY2, width, height);
    filter.setBounds (filterAdsr.getRight()+paddingX, paddingY2, width, height);
    keyboardComponent.setBounds(paddingX, paddingY2+height, getWidth(), 90);
}


