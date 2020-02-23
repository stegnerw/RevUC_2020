#include "BreathingProcessor.hpp"

#define DEBUG
#define MAX_HISTORY 500

// Public functions
BreathingProcessor::BreathingProcessor() :
  firstSweep(false),
  sweepAlpha(0.7),
  phaseWeightsAlpha(0.9),
  peakLocAlpha(0.95),
  envAlpha(0.95),
  maxHistory(MAX_HISTORY),
  lastSweep(MAX_HISTORY)
{
  // intentionally blank
}

bool  BreathingProcessor::Process(std::vector<float> sweep, ProcessedFrame& outFrame){
  
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

// Private functions
void  BreathingProcessor::ComplexMatrixLPF(Eigen::VectorXcf& curr, Eigen::VectorXcf& prev, float alpha){
  curr = alpha * prev + (1 - alpha) * curr;
}

void  BreathingProcessor::FloatMatrixLPF(Eigen::VectorXf& curr, Eigen::VectorXf& prev, float alpha){
  curr = alpha * prev + (1 - alpha) * curr;
}

void  BreathingProcessor::FloatLPF(float& curr, float& prev, float alpha){
  curr = alpha * prev + (1 - alpha) * curr;
}

#ifdef DEBUG
int main() {
  return 0;
}
#endif

