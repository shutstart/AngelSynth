/*
  ==============================================================================

    OscData.h
    Created: 18 May 2021 2:19:38pm
    Author:  Chirag Yadav

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParams (const float depth, const float freq);
    
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin(x);} };
    float fmMod {0.0f};
    float fmDepth {0.0f};
    int lastMidiNote {0};
};
