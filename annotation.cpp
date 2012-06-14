#include "annotation.h"
#include "point.h"

#include <algorithm>

Annotation::~Annotation()
{
	delete _annotator;
	delete _signal_data;
	_samples.clear();
	_peak_type.clear();
	_points.clear();
}

void Annotation::AnnotateSignal()
{
	if (_annotator->AnalyzeSignal(*_signal_data, _samples, _peak_type) == true)  //Добавить проверку _signal_data.empty()
	{
		for (size_t i = 0; i < _samples.size(); i++) // Заменить magick numbers на enum 
		{
			switch (_peak_type[i])  //Заменить push_back на []
			{
			case 15: case 17:
				_points.push_back(Point(_samples[i], Point::wt_QRS, Point::pt_PeakQ));
				break;
			case 24:
				_points.push_back(Point(_samples[i], Point::wt_P, Point::pt_PeakP));
				break;
			case 27:
				_points.push_back(Point(_samples[i], Point::wt_T, Point::pt_PeakT));
				break;
			case 29:
				_points.push_back(Point(_samples[i], Point::wt_U, Point::pt_PeakU));
				break;
			case 39: case 1: case 46:
				_points.push_back(Point(_samples[i], Point::wt_QRS, Point::pt_Start));
				break;
			case 40:
				_points.push_back(Point(_samples[i], Point::wt_QRS, Point::pt_Finish));
				break;
			case 42:
				_points.push_back(Point(_samples[i], Point::wt_P, Point::pt_Start));
				break;
			case 43:
				_points.push_back(Point(_samples[i], Point::wt_P, Point::pt_Finish));
				break;
			case 44:
				_points.push_back(Point(_samples[i], Point::wt_T, Point::pt_Start));
				break;
			case 45:
				_points.push_back(Point(_samples[i], Point::wt_T, Point::pt_Finish));
				break;
			case 47: case 48:
				_points.push_back(Point(_samples[i], Point::wt_QRS, Point::pt_PeakR));
				break;
			case 49: case 50:
				_points.push_back(Point(_samples[i], Point::wt_QRS, Point::pt_PeakS));
				break;
			default:
				_points.push_back(Point(_samples[i], Point::wt_Unknown, Point::pt_Unknown));
				break;
			}
		}
		
		Point temp;
		std::vector<Point> temp_points;
		for (size_t i = 0; i < _points.size() - 10; i++)
		{
			if (_points[i].wave_type() == Point::wt_P &&  _points[i+1].wave_type() == Point::wt_P && _points[i+2].wave_type() == Point::wt_P && _points[i+10].wave_type() == Point::wt_T)
			{
				temp.set_sample(_points[i].sample());
				temp.set_wave_type(Point::wt_Cycle);
				temp.set_point_type(Point::pt_Start);
				temp_points.push_back(temp);
				std::copy(_points.begin() + i, _points.begin() + i + 11, std::back_inserter(temp_points));
				temp.set_sample(_points[i+10].sample());
				temp.set_wave_type(Point::wt_Cycle);
				temp.set_point_type(Point::pt_Finish);
				temp_points.push_back(temp);
			}
			else if (_points[i].wave_type() == Point::wt_P && _points[i + 1].wave_type() == Point::wt_P && _points[i + 2].wave_type() == Point::wt_P && _points[i + 7].wave_type() == Point::wt_T && _points[i + 8].wave_type() == Point::wt_T && _points[i + 9].wave_type() == Point::wt_T)
			{
				temp.set_sample(_points[i].sample());  // Добавить в лог ворнинг 
				temp.set_wave_type(Point::wt_Cycle);
				temp.set_point_type(Point::pt_Start);
				temp_points.push_back(temp);
				std::copy(_points.begin() + i, _points.begin() + i + 4, back_inserter(temp_points));
				temp.set_sample(_points[i + 3].sample());
				temp.set_wave_type(Point::wt_QRS);
				temp.set_point_type(Point::pt_PeakQ);
				temp_points.push_back(temp);
				std::copy(_points.begin() + i + 4, _points.begin() + i + 10, back_inserter(temp_points));
				temp.set_sample(_points[i + 10].sample());
				temp.set_wave_type(Point::wt_Cycle);
				temp.set_point_type(Point::pt_Finish);
				temp_points.push_back(temp);
			}
		}
		_points.clear();
		_points = temp_points;
	}
	else 
		std::cerr << "Error: could not get QRS complexes. make sure you have got \"filters\" directory in the ecg application dir." << std::endl; 
}