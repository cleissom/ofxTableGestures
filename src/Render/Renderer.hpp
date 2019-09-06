/*

    ofxTableGestures (formerly OF-TangibleFramework)
    Developed for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef _RENDERER
#define _RENDERER

#include <string>

class Renderer{
    public:
        ///Calibration data:
            ///height scale factor
        static float height_offset;
            ///width scale factor
		static float width_offset;
            ///x position
		static float center_x;
            ///y position
		static float center_y;
            ///y rotation angle
		static float angle_h;
            ///x rotation angle
		static float angle_w;
            ///z rotation angle
		static float angle;
		///Distortion path file
		std::string DistortionPath;
        ///Enable/disable distortion flag
        bool distortion_enabled;
    protected:
        ///Distortion matrix to be stored
        float matrix[16];
        void SetIdentity(float* _matrix);
        ///To be rewritted:
        ///Called before draw thing to be distortionate
        virtual void StartDistortion()=0;
        ///Called after draw things to be distortionate
        virtual void EndDistortion()=0;
    public:
        ///returns the distortion Matrix
        float * GetDistortionMatrix();
        ///constructor
        Renderer();
        virtual ~Renderer()=0;
        ///Loads distortion from configuration file
        virtual void LoadDistortion();
        ///Saves distortion to configuration file
        virtual void SaveDistortion();
        ///Called before draw thing to be distortionate
        void Start();
        ///Called after draw things to be distortionate
        void End();
        ///Enables distortion
        virtual void Enable();
        ///Disables distortion
        virtual void Disable();
        ///Returns true or fals depending on distortion
        virtual bool IsEnabled();
        ///Returns distortion values into a string
        virtual std::string ToString();
        ///Resets the distortion values
        void LoadDefaultValues();
};

#endif
