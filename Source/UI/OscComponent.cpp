/*
  ==============================================================================

    OscComponent.cpp
    Created: 22 May 2021 11:57:29pm
    Author:  Chirag Yadav

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts,juce::String waveSelectorId,juce::String fmFreqId, juce::String fmDepthId)
{
    juce::StringArray choices {"Sine","Saw","Square"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId,oscWaveSelector);
    
    setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqAttachment);
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttachment);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    
    g.drawRect(getLocalBounds());
}

void OscComponent::resized()
{
    const int sliderPosY = 80;
    const int sliderWidth = 80;
    const int sliderHeight = 80;
    const int labelYOffset = 20;
    const int labelHeight = 20;
    oscWaveSelector.setBounds(10, 10, 90, 20);
    fmFreqSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, sliderWidth, labelHeight);
    
    fmDepthSlider.setBounds(fmFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, sliderWidth, labelHeight);
    
    
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    slider.setLookAndFeel(&oscFeel);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    label.setFont(15.0f);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
