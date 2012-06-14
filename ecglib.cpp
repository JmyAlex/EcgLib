#include "ecglib.h"
#include "signaldata.h"
#include "annotation.h"
#include "libannotator.h"

extern "C" __declspec(dllexport) int analyzer(const double* signal, 
											  const int signal_size, 
											  const int sample_rate, 
											  sPoint*& points, 
											  int& out_size)
{
	out_size = 0;
	std::vector<double> temp(signal_size);
	for (int i = 0; i < signal_size; i++)
		temp[i] = signal[i];
	SignalData *signal_data = new SignalData;
	signal_data->set_size(signal_size);
	signal_data->set_sample_rate(1000);
	signal_data->set_data(temp);
	Annotation *lib_annotation = new Annotation(new LibAnnotator);
	lib_annotation->set_signal_data(*signal_data);
	lib_annotation->AnnotateSignal();
	std::vector<Point> annotation;
	annotation = lib_annotation->annotation();
	points = new sPoint [annotation.size()];
	for (size_t i = 0; i < annotation.size(); i++)
	{
		points[i].sample = annotation[i].sample();
		points[i].wave_type = static_cast<WaveType>(annotation[i].wave_type());
		points[i].point_type = static_cast<PointType>(annotation[i].point_type());
	}
	//for (size_t i = 0; i < 20; i++)
	//	std::cout << annotation[i].sample() << '\t' << annotation[i].wave_type() << '\t' << annotation[i].point_type() << std::endl;
	out_size = annotation.size();
	delete lib_annotation;
	return 0;
}