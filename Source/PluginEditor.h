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
#include "UI/FilterComponent.h"
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

private:
    
    AngelSynthAudioProcessor& audioProcessor;
    OscComponent osc;
    AdsrComponent adsr;
    AdsrComponent filterAdsr;
    FilterComponent filter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AngelSynthAudioProcessorEditor)
};
