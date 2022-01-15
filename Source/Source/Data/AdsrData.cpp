/*
  ==============================================================================

    AdsrData.cpp
    Created: 14 Jun 2021 5:23:29pm
    Author:  Lewis Hamilton

  ==============================================================================
*/

#include "AdsrData.h"


void AdsrData::updateADSR(const float attack, const float decay, const float release, const float sustain) {
    
    
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters(adsrParams);
};
