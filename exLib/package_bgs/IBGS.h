/*
This file is part of BGSLibrary.

BGSLibrary is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

BGSLibrary is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with BGSLibrary.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <QDir>

using namespace std;
class IBGS
{
    public:
        IBGS()
        {
            QDir currDir = QDir::current();
                ///check if file exists and if yes: Is it really a file and no directory?
                if (!currDir.exists("config") )
                {
                    currDir.mkdir("config");
                    cerr<<"config Directory has been Created";
                }
        }

      virtual void process(const cv::Mat &img_input, cv::Mat &img_foreground, cv::Mat &img_background) = 0 ;
      virtual ~IBGS(){}

    //private:

        virtual void saveConfig() = 0;
        virtual void loadConfig() = 0;
};
