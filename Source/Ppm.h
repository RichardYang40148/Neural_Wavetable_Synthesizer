#if !defined(__Ppm_hdr__)
#define __Ppm_hdr__

#include "ErrorDef.h"
#include <cmath>

class CPpm
{
public:
    static Error_t createInstance (CPpm*& pCPpm);
    static Error_t destroyInstance (CPpm*& pCPpm);

    Error_t initInstance (float fSampleRateInHz, int iNumChannels);

    Error_t process (const float **ppfInputBuffer, float *pfVppOutputBuffer, int iNumberOfFrames);

protected:
    CPpm ();
    virtual ~CPpm ();

private:
    float m_fCurrVppm;
    float m_fAlphaAT;
    float m_fAlphaRT;
    float m_fEpsilon;
    float m_fSampleRate;
    int m_iNumChannels;

    float *m_pfVppMaxOfBlock;
    float *m_pfPrevVppm;
};

#endif // #if !defined(__Ppm_hdr__)
