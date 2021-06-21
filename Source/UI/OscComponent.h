/*
  ==============================================================================

    OscComponent.h
    Created: 22 May 2021 11:57:29pm
    Author:  Chirag Yadav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscLookAndFeel: public juce::LookAndFeel_V4
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


class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts,juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    OscLookAndFeel oscFeel;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> fmFreqAttachment;
    std::unique_ptr<Attachment> fmDepthAttachment;

    juce::Label fmFreqLabel { "FM Freq", "FM Freq" };
    juce::Label fmDepthLabel { "FM Depth", "FM Depth" };
    
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
