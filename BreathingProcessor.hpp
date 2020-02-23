#ifndef BREATHING_PROCESS_HPP
#define BREATHING_PROCESS_HPP

#include <iostream>
#include <vector>
#include <complex>
#include "lib/eigen/Eigen/Eigen"
#include "ProcessedFrame.hpp"

class BreathingProcessor {
  public:
    // Public functions
    BreathingProcessor(int);
    bool  Process(Eigen::VectorXcf, ProcessedFrame&);
    // Setters and Getters
    void  SetSweepAlpha(float);
    float GetSweepAlpha();
    void  SetPhaseWeightsAlpha(float);
    float GetPhaseWeightsAlpha();
    void  SetPeakLocAlpha(float);
    float GetPeakLocAlpha();
    void  SetEnvAlpha(float);
    float GetEnvAlpha();

  private:
    // Private functions
    void  ComplexMatrixLPF(Eigen::VectorXcf&, Eigen::VectorXcf&, float, Eigen::VectorXcf&);
    void  FloatMatrixLPF(Eigen::VectorXf&, Eigen::VectorXf&, float, Eigen::VectorXcf&);
    void  FloatLPF(float&, float&, float, float&);
    // Private variables
    bool                firstSweep;
    bool                secondSweep;
    float               sweepAlpha;
    float               phaseWeightsAlpha;
    float               peakLocAlpha;
    float               envAlpha;
    int                 maxHistory;
    Eigen::VectorXcf    lastSweep;
    Eigen::VectorXf     lastEnv;
    float               lastPeakLoc;
    Eigen::VectorXf     lastPhaseWeights;
    std::vector<float>  breathHistory;
};

#endif
