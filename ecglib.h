#ifndef ECGLIB_H
#define ECGLIB_H
#pragma once

enum WaveType { wt_Unknown, wt_P, wt_QRS, wt_T, wt_U, wt_Cycle };
enum PointType { pt_Unknown, pt_Start, pt_PeakP, pt_PeakQ, pt_PeakR, pt_PeakS, pt_PeakT, pt_PeakU, pt_Finish };

struct sPoint
{
	//int peak_type;		   //Peak type from ecg_annotation library to verify data
	double sample;
	WaveType wave_type;
	PointType point_type;
};

extern "C" __declspec(dllexport) int analyzer(const double* signal, 
											  const int signal_size, 
											  const int sample_rate, 
											  sPoint*& points, 
											  int& out_size);

#endif // ECGLIB_H
