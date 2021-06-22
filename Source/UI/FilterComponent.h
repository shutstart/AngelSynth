/*
  ==============================================================================

    FilterComponent.h
    Created: 20 Jun 2021 4:48:57pm
    Author:  Chirag Yadav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterLookAndFeel: public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider(juce::Graphics &g,int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) override
    {
        //        bool mouseOver = slider.isMouseOver();
        bool mousePosition = slider.isMouseButtonDown();
        float diameter = juce::jmin(width, height)-5.0;
        float radius = diameter/2;
        float centreX = x+width/2;
        float centreY = y+height/2;
        float rx = centreX - radius;
        float ry = centreY - radius;
        float angle = rotaryStartAngle + (sliderPos*(rotaryEndAngle-rotaryStartAngle));
        
        
        juce::Rectangle<float> outtaBounds(rx,ry,diameter,diameter);
        auto innerBounds = outtaBounds.reduced(2);
        float glowArea = 1.0f - innerBounds.getWidth()/outtaBounds.getWidth();
        float adjust = angle==rotaryStartAngle?0.0f:2.5/(2.0*radius);
        juce::Colour dialTickColour = mousePosition?juce::Colour(116, 185, 255):juce::Colour(9, 132, 227);
        
        juce::Path knobRingGlow;
        
        knobRingGlow.addPieSegment(outtaBounds, rotaryStartAngle, angle+adjust, glowArea);
        g.setColour(dialTickColour);
        g.fillPath(knobRingGlow);
        
        g.setColour(juce::Colour (49, 56, 64));
        g.fillEllipse(innerBounds);
        g.setColour(dialTickColour);
        juce::Path dialTick;
        juce::Rectangle<float> dialTickerRect(0, -radius+2.0f, 2.5f, radius*0.5f);
        dialTick.addRoundedRectangle(dialTickerRect,2.5f);
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centreX,centreY));
        
    }
};

class FilterComponent  : public juce::Component
{
public:
    FilterComponent (juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    FilterLookAndFeel filterFeel;
    
    juce::ComboBox filterTypeSelector { "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;
    
    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> filterFreqAttachment;
    std::unique_ptr<Attachment> filterResAttachment;
    
    juce::Label filterSelectorLabel { "Filter Type", "Filter Type" };
    juce::Label filterFreqLabel { "Filter Freq", "Filter Freq" };
    juce::Label filterResLabel { "Filter Res", "FilterRes" };
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
