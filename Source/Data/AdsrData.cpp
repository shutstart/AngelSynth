/*
  ==============================================================================

    AdsrData.cpp
    Created: 18 May 2021 1:13:00pm
    Author:  Chirag Yadav

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::update (const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters (adsrParams);
}
