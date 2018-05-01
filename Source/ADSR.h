/*
 ==============================================================================
 
 AR.h
 Created: 30 Apr 2018 1:44:02pm
 Author:  Richard Yang

 
 ==============================================================================
 */




class ADSREnv {
    
    
public:
    double adsr(double input,int trigger);
    double input;
    double output;
    double attack;
    double decay;
    double sustain;
    double release;
    double amplitude;
    void setAttack(double attackMS);
    void setDecay(double decayMS);
    void setSustain(double sustainL);
    void setRelease(double releaseMS);
    int trigger;
    long holdtime=1;
    long holdcount;
    int attackphase,decayphase,sustainphase,holdphase,releasephase;
};
