#include "Ppm.h"
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;


Error_t CPpm::createInstance(CPpm *&pCPpm)
{
    pCPpm = new CPpm ();

    if (!pCPpm)
        return kUnknownError;

    return kNoError;
}

Error_t CPpm::destroyInstance(CPpm *&pCPpm)
{
    if (!pCPpm)
        return kUnknownError;

    delete pCPpm;
    pCPpm = 0;

    return kNoError;
}

Error_t CPpm::initInstance (float fSampleRateInHz, int iNumChannels)
{
    m_fSampleRate = fSampleRateInHz;
    m_iNumChannels = iNumChannels;

    // Init the attack and release alpha
    m_fAlphaAT = 1.0f - exp(-2.2f / (m_fSampleRate * 0.01f));  // alpha = 1 - [exp(-2.2 / (f_s * 0.01)), exp(-2.2 / (f_s * 1.5))];
    m_fAlphaRT = 1.0f - exp(-2.2f / (m_fSampleRate * 1.5f));

    // Init the epsilon value
    m_fEpsilon = 1.0f * pow(10.0f,-5.0f); // if signal is 0 we should get -100dB

    // Init an array to store the computed VPPM per channel per block
    m_pfVppMaxOfBlock = new float[m_iNumChannels];
    for (int i=0; i < m_iNumChannels; i++) {
        m_pfVppMaxOfBlock[i] = -INFINITY;
    }

    // Init an array to store the previous VPPM per channel per block
    m_pfPrevVppm = new float[m_iNumChannels];
    for (int i=0; i < m_iNumChannels; i++) {
        m_pfPrevVppm[i] = 0.0f;
    }

    return kNoError;
}

CPpm::CPpm()
{
    m_fCurrVppm =         0.0f;
    m_fAlphaAT =          0.0f;
    m_fAlphaRT =          0.0f;
    m_fEpsilon =          0.0f;
    m_fSampleRate =       0.0f;
    m_iNumChannels =        0;
}

CPpm::~CPpm()
{
    delete [] m_pfVppMaxOfBlock;
    delete [] m_pfPrevVppm;
}

Error_t CPpm::process(const float **ppfInputBuffer, float *pfVppOutputBuffer, int iNumberOfFrames)
{
    // reset the vector holding the max vppm per channel
    for (int c=0; c < m_iNumChannels; c++)
    {
        m_pfVppMaxOfBlock[c] = -INFINITY;
    }

    for (int c = 0; c < m_iNumChannels; c++)
    {
        for (int i = 0; i < iNumberOfFrames; i++)
        {
            if (m_pfPrevVppm[c] > abs(ppfInputBuffer[c][i])) {
                // release state
                m_fCurrVppm = (1-m_fAlphaRT) * m_pfPrevVppm[c]; // MATLAB ==> ppmout(i) = (1-alpha_RT) * filterbuf; // We call `filterbuf` as `m_fPrevVppm` here
            }
            else {
                // attack state
                m_fCurrVppm = (m_fAlphaAT * abs(ppfInputBuffer[c][i])) + ((1-m_fAlphaAT) * m_pfPrevVppm[c]); // MATLAB ==>  ppmout(i) = alpha_AT * x(i) + (1-alpha_AT) * filterbuf;
            }
            m_pfPrevVppm[c] = m_fCurrVppm; // MATLAB ==>  filterbuf = ppmout(i);

            // Compare maximum, update if larger
            if (m_fCurrVppm > m_pfVppMaxOfBlock[c]) {
                m_pfVppMaxOfBlock[c] = m_fCurrVppm;
            }
        }
    }
    // `m_pfVppMaxOfBlock` now contains the max Vpp of each channel
    for (int c=0; c < m_iNumChannels; c++)
    {
        if (m_pfVppMaxOfBlock[c] < m_fEpsilon)
        {
            // Ensure there are no peak values in `m_pfVppMaxOfBlock` smaller than epsilon, otherwise log(0) in the next line returns an error
            m_pfVppMaxOfBlock[c] = m_fEpsilon;
        }
        // Convert to dB
        m_pfVppMaxOfBlock[c] = 20*log10(m_pfVppMaxOfBlock[c]);
    }

    // Now copy values in  `m_pfVppMaxOfBlock` into the output buffer
    for (int c=0; c < m_iNumChannels; c++)
    {
        pfVppOutputBuffer[c] = m_pfVppMaxOfBlock[c];
    }
    //DBG(pfVppOutputBuffer[0]);

    return kNoError;
}
