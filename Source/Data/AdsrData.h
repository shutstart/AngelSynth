/*
  ==============================================================================

    AdsrData.h
    Created: 18 May 2021 1:13:00pm
    Author:  Chirag Yadav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack,const float decay, const float sustain, const float release);
    
private:

    juce::ADSR::Parameters adsrParams;
};
