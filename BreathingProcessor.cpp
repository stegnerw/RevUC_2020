#include "BreathingProcessor.hpp"
#include <algorithm>
#include <cmath>

#define DEBUG
#define MAX_HISTORY 500

// Public functions
BreathingProcessor::BreathingProcessor(int sweepLength) :
  firstSweep(true),
  secondSweep(true),
  sweepAlpha(0.7),
  phaseWeightsAlpha(0.9),
  peakLocAlpha(0.95),
  envAlpha(0.95),
  maxHistory(MAX_HISTORY),
  breathHistory(MAX_HISTORY),
  lastSweep(sweepLength),
  lastEnv(sweepLength),
  lastPeakLoc(sweepLength),
  lastPhaseWeights(sweepLength)
{
  // intentionally blank
}

bool  BreathingProcessor::Process(Eigen::VectorXcf sweep, ProcessedFrame& outFrame){
  if (firstSweep) {
    lastSweep   = sweep;
    lastEnv     = lastSweep.array().abs();
    Eigen::VectorXf::Index max_idx;
    lastEnv.maxCoeff(&max_idx);
    lastPeakLoc = (float)max_idx;
    firstSweep = false;
    return false;
  }

  sweep = sweepAlpha * lastSweep + (1 - sweepAlpha) * sweep;
  Eigen::VectorXf env = sweep.array().abs();
  lastEnv = envAlpha * lastEnv + (1 - envAlpha) * env;
  Eigen::VectorXf::Index max_idx;
  lastEnv.maxCoeff(&max_idx);
  float peakLoc = (float)max_idx;
  lastPeakLoc = peakLocAlpha * lastPeakLoc + (1 - peakLocAlpha) * peakLoc;
  int peakLocInt = (int)(lastPeakLoc + 0.5);

  Eigen::VectorXcf peakSlice = 
      sweep(Eigen::seq(std::max(0, peakLocInt-50),
      std::min(peakLocInt+50, (int)sweep.size()-1)));
  std::complex<float> peak = peakSlice.mean();

  Eigen::VectorXcf delta = sweep * lastSweep.adjoint();

  Eigen::VectorXf phaseWeights = delta.imag();
  if (secondSweep) {
    lastPhaseWeights = phaseWeights;
    secondSweep = false;
  } else {
    lastPhaseWeights = phaseWeightsAlpha * lastPhaseWeights +  (1 - phaseWeightsAlpha) * phaseWeights;
  }
  Eigen::VectorXf absWeights = lastPhaseWeights.array().abs();
  Eigen::VectorXf weights = absWeights * env;
  Eigen::VectorXf deltaAngle(delta.size());
  for (int i = 0; i < delta.size(); i++) {
    deltaAngle[i] = atan2(delta[i].imag(), delta[i].real());
  }
  std::cout << weights << '\n';
  std::cout << deltaAngle << '\n';
  //Eigen::VectorXf deltaDist = weights.dot(deltaAngle);
  //deltaDist *= 2.5/ (2.0 * M_PI * (weights).sum());


  return true;
}

// Setters and Getters
void  BreathingProcessor::SetSweepAlpha(float a){
  if (a < 1 && a > 0) sweepAlpha = a;
}

float BreathingProcessor::GetSweepAlpha(){
  return sweepAlpha;
}

void  BreathingProcessor::SetPhaseWeightsAlpha(float a){
  if (a < 1 && a > 0) phaseWeightsAlpha = a;
}

float BreathingProcessor::GetPhaseWeightsAlpha(){
  return phaseWeightsAlpha;
}

void  BreathingProcessor::SetPeakLocAlpha(float a){
  if (a < 1 && a > 0) peakLocAlpha = a;
}

float BreathingProcessor::GetPeakLocAlpha(){
  return peakLocAlpha;
}

void  BreathingProcessor::SetEnvAlpha(float a){
  if (a < 1 && a > 0) envAlpha = a;

}

float BreathingProcessor::GetEnvAlpha(){
  return envAlpha;
}

#ifdef DEBUG
int main() {
  int sweep_len = 5;
  Eigen::VectorXcf sweep(sweep_len);
  sweep << std::complex<float>(0,0),
           std::complex<float>(1,1),
           std::complex<float>(2,2),
           std::complex<float>(3,3),
           std::complex<float>(4,4);
  ProcessedFrame frame;
  BreathingProcessor bp(sweep_len);
  bp.Process(sweep, frame);
  Eigen::VectorXcf sweep2(sweep_len);
  sweep2 << std::complex<float>(10,10),
           std::complex<float>(11,11),
           std::complex<float>(12,12),
           std::complex<float>(13,13),
           std::complex<float>(14,14);
  ProcessedFrame frame2;
  bp.Process(sweep2, frame2);
  return 0;
}
#endif

