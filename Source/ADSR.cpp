/*
  ==============================================================================

    AR.cpp
    Created: 30 Apr 2018 1:44:02pm
    Author:  Richard Yang

  ==============================================================================
*/

#include "ADSR.h"
#include "maximilian.h"
//==============================================================================

double ADSREnv::adsr(double input, int trigger) {
    
    if (trigger==1 && attackphase!=1 && holdphase!=1 && decayphase!=1){
        holdcount=0;
        decayphase=0;
        sustainphase=0;
        releasephase=0;
        attackphase=1;
    }
    
    if (attackphase==1) {
        releasephase=0;
        amplitude+=(1*attack);
        output=input*amplitude;
        
        if (amplitude>=1) {
            amplitude=1;
            attackphase=0;
            decayphase=1;
        }
    }
    
    
    if (decayphase==1) {
        output=input*(amplitude*=decay);
        if (amplitude<=sustain) {
            decayphase=0;
            holdphase=1;
        }
    }
    
    if (holdcount<holdtime && holdphase==1) {
        output=input*amplitude;
        holdcount++;
    }
    
    if (holdcount>=holdtime && trigger==1) {
        output=input*amplitude;
    }
    
    if (holdcount>=holdtime && trigger!=1) {
        holdphase=0;
        releasephase=1;
    }
    
    if (releasephase==1 && amplitude>0.) {
        output=input*(amplitude*=release);
        
    }
    
    return output;
}


void ADSREnv::setAttack(double attackMS) {
    attack = 1-pow( 0.01, 1.0 / ( attackMS * maxiSettings::sampleRate * 0.001 ) );
}

void ADSREnv::setRelease(double releaseMS) {
    release = pow( 0.01, 1.0 / ( releaseMS * maxiSettings::sampleRate * 0.001 ) );
}

void ADSREnv::setSustain(double sustainL) {
    sustain = sustainL;
}

void ADSREnv::setDecay(double decayMS) {
    decay = pow( 0.01, 1.0 / ( decayMS * maxiSettings::sampleRate * 0.001 ) );
}
