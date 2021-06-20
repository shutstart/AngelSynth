/*
  ==============================================================================

    SynthSound.h
    Created: 13 May 2021 10:13:08pm
    Author:  Chirag Yadav

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override{
        return true;
    }
    bool appliesToChannel(int midiChannel) override{
        return true;
    }
};
