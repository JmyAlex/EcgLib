#ifndef POINT_H
#define POINT_H
#pragma once

class Point
{
public:
	enum WaveType { wt_Unknown, wt_P, wt_QRS, wt_T, wt_U, wt_Cycle };
	enum PointType
	{
		pt_Unknown,
		pt_Start,
		pt_PeakP,
		pt_PeakQ,
		pt_PeakR,
		pt_PeakS,
		pt_PeakT,
		pt_PeakU,
		pt_Finish
	};

	Point();
	Point(const Point &other);
	Point(double sample, WaveType wave_type, PointType point_type);
	//~Point();

	void set_sample(const double sample);
	void set_wave_type(const WaveType wavetype);
	void set_point_type(const PointType pointtype);

	double sample() const;
	WaveType wave_type() const;
	PointType point_type () const;

private:
	//int peakType;
	double _sample;
	WaveType _wave_type;
	PointType _point_type;
	
};

inline Point::Point()
{
	_sample = 0;
	_wave_type = wt_Unknown;
	_point_type = pt_Unknown;
}

inline Point::Point(const Point &other)
{
	_sample = other.sample();
	_wave_type = other.wave_type();
	_point_type = other.point_type();
}

inline Point::Point(double sample, WaveType wave_type, PointType point_type)
	: _sample(sample), _wave_type(wave_type), _point_type(point_type)
{

}

inline void Point::set_sample(const double sample)
{
	_sample = sample;
}

inline void Point::set_wave_type(const WaveType wave_type)
{
	_wave_type = wave_type;
}

inline void Point::set_point_type(const PointType point_type)
{
	_point_type = point_type;
}

inline double Point::sample() const
{
	return _sample;
}

inline Point::WaveType Point::wave_type() const
{
	return _wave_type;
}

inline Point::PointType Point::point_type() const
{
	return _point_type;
}

#endif // POINT_H
