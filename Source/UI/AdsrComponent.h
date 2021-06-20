/*
  ==============================================================================

    AdsrComponent.h
    Created: 18 May 2021 1:11:34pm
    Author:  Chirag Yadav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

class OtherLookAndFeel: public juce::LookAndFeel_V4
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

class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent (juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider);
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    OtherLookAndFeel otherLookAndFeel;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    juce:: Colour draculaOrchid = juce::Colour (30, 39, 46);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
