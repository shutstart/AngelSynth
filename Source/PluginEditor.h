/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"

//==============================================================================
/**
*/

class AngelSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AngelSynthAudioProcessorEditor (AngelSynthAudioProcessor&);
    ~AngelSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void setSliderParams(juce::Slider& slider);

private:
    
//    juce::ComboBox oscSelector;
//    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    
    juce:: Colour electronBlue = juce::Colour(9, 132, 227);
    juce:: Colour draculaOrchid = juce::Colour (30, 39, 46);
    
    AngelSynthAudioProcessor& audioProcessor;
    OscComponent osc;
    AdsrComponent adsr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AngelSynthAudioProcessorEditor)
};
