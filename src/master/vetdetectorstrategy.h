/**
* [
*  Copyright (c) 2016 by Vehicle-Eye Technology
*  ALL RIGHTS RESERVED.
*
*  The software and information contained herein are proprietary to,  and comprise
*  valuable trade secrets of, Vehicle-Eye Technology.  Disclosure of the software
*  and information will materially harm the business of Vehicle-Eye Technology.
*  This software is furnished pursuant to a written development agreement and may
*  be used, copied, transmitted, and stored only in accordance with the terms of
*  such agreement and with the inclusion of the above copyright notice.  This
*  software and information or any other copies thereof may not be provided or
*  otherwise made available to any other party.
* ]
*/


/*!
* \file vetdetectorstrategy.h
* \author [Zeyu Zhang]
* \version [0.1]
* \date 2016-02-18
*/


#ifndef VETDETECTORSTRATEGY_H
#define VETDETECTORSTRATEGY_H

#include <opencv2/opencv.hpp>

#include <iostream>

/*!
 * \brief Define the identifier for each detector
 */
#define HAAR_FRONT_CAR_DETECTOR 1

/*!
 * \brief Define the xml file path
 */
#define HAAR_CASCADE_FRONT_CAR_XML "./haar-cascades/haar_cascade_front_car.xml"
#define HAAR_CASCADE_REAR_CAR_XML "./haar-cascades/haar_cascade_rear_car.xml"

/*!
 * \brief The VetDetectorStrategy class
 */
class VetDetectorStrategy
{
public:
	VetDetectorStrategy();
	virtual ~VetDetectorStrategy();

public:
	virtual int detect(const cv::Mat &frame, std::vector<cv::Rect> &rois) = 0;
};


#endif	// VETDETECTORSTRATEGY_H