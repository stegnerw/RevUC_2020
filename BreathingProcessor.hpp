#ifndef BREATHING_PROCESS_HPP
#define BREATHING_PROCESS_HPP

#include <iostream>
#include <vector>
#include <complex>
#include "ProcessedFrame.hpp"

class BreathingProcessor {
  public:
    // Public functions
    BreathingProcessor(int);
    bool  Process(std::vector<std::complex<float>>, ProcessedFrame&);

  private:
    // Public functions
    void ComplexVectorAbs(std::vector<std::complex<float>>, std::vector<float>&);
    std::vector<std::complex<float>> ComplexVecLPF(std::vector<std::complex<float>>, std::vector<std::complex<float>>, float);
    std::vector<float> FloatVecLPF(std::vector<float>, std::vector<float>, float);
    // Private variables
    bool                              firstSweep;
    bool                              secondSweep;
    float                             sweepAlpha;
    float                             phaseWeightsAlpha;
    float                             peakLocAlpha;
    float                             envAlpha;
    int                               maxHistory;
    std::vector<std::complex<float>>  lastSweep;
    std::vector<float>                lastEnv;
    float                             lastPeakLoc;
    std::vector<float>                lastPhaseWeights;
    std::vector<float>                breathHistory;
};

#endif
