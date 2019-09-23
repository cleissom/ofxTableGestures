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

#include "Grid.hpp"
#include "ofMain.h"
#include "ofPath.h"

Grid::Grid(int _w_lines, int _h_lines)
{
    w_lines=_w_lines;
    h_lines=_h_lines;
}

Grid::~Grid()
{
}

void Grid::Resize()
{
}

void Grid::Draw(bool calibration_enabled, int calibration_mode)
{
    if(calibration_enabled)
    {
        ofPushMatrix();
        ofSetLineWidth(4.0f);
        ofSetColor(255,255,255);
        CallList1();
        glColor4f(1,0,0,0.6f);
        switch(calibration_mode)
        {
            case 0: CallList2(); break;
            case 1: CallList3(); break;
            case 2: CallList4(); break;
            case 3: CallList5(); break;
        }
        ofPopMatrix();
    }
}

int Grid::getLineLength(){
    int width = ofGetWidth();
    int height = ofGetHeight();
    int linelength;
    if(width>height)
    {
        linelength = height;
    }else
    {
        linelength = width;
    }
    return linelength;

}void Grid::drawLines(){
    int width = ofGetWidth();
    int height = ofGetHeight();
    int linelength;
    if(width>height)
    {
        linelength = height;
        glTranslatef((width-height)/2,0,0);
        for (int i =0; i<=w_lines; i++)
            ofDrawLine( i*(linelength/w_lines) ,  0 , i*(linelength/w_lines), linelength);
        for (int i =0; i<=h_lines; i++)
            ofDrawLine(0, i*(linelength/h_lines) , linelength, i*(linelength/h_lines));
    }else
    {
        glTranslatef(0,(height-width)/2,0);
        linelength = width;
        for (int i =0; i<=w_lines; i++)
            ofDrawLine( i*(linelength/w_lines) ,  0 , i*(linelength/w_lines), linelength);
        for (int i =0; i<=h_lines; i++)
            ofDrawLine(0, i*(linelength/h_lines) , linelength, i*(linelength/h_lines));
    }
}

void Grid::CallList1(){
    ofSetColor(255,255,255);
    ofSetLineWidth(4.0f);
    int linelength = getLineLength();

    ofPushMatrix();
    ///Draws the line-grid depending the dimensions of the screen,
    ///for the reactable, the grid must be square shaped.
	drawLines();

    ofNoFill();
    ///Draws the helping circles of the grid.
    ofSetCircleResolution(60);
    for (int i =0; i<=w_lines/2; i++)
        ofDrawCircle(linelength/2,linelength/2,(i*(linelength/w_lines)));
    ofFill();
    ofSetCircleResolution(20);
    ofPopMatrix();
}

void Grid::CallList2(){
    int width = ofGetWidth();
    int height = ofGetHeight();
    ofSetColor(255,255,255);
    ofSetLineWidth(4.0f);
    int linelength = getLineLength();


    ofPushMatrix();
     if(width>height) glTranslatef((width-height)/2,0,0);
        else glTranslatef(0,(height-width)/2,0);
		glTranslatef(0.5f*linelength,0.55f*linelength,0);
		RenderArrow_two(linelength/2);
		glTranslatef(-0.05*linelength,-0.05f*linelength,0);
		glRotatef(90,0,0,1);
		RenderArrow_two(linelength/2);
    ofPopMatrix();
}

void Grid::CallList3(){
    int width = ofGetWidth();
    int height = ofGetHeight();
    ofSetColor(255,255,255);
    ofSetLineWidth(4.0f);
    int linelength = getLineLength();

    ofPushMatrix();
    if(width>height) glTranslatef((width-height)/2,0,0);
        else glTranslatef(0,(height-width)/2,0);
		ofPushMatrix();
		glTranslatef(0.5f*linelength,0.9f*linelength,0);
		RenderArrow_one(linelength);
		glTranslatef(0,-0.8f*linelength,0);
		glRotatef(180,0,0,1);
		RenderArrow_one(linelength);
		ofPopMatrix();
		glTranslatef(0.9f*linelength,0.5f*linelength,0);
		ofPushMatrix();
		glRotatef(-90,0,0,1);
		RenderArrow_one(linelength);
		ofPopMatrix();
		glTranslatef(-0.8f*linelength,0,0);
		ofPushMatrix();
		glRotatef(90,0,0,1);
		RenderArrow_one(linelength);
		ofPopMatrix();
    ofPopMatrix();
}

void Grid::CallList4(){
    int width = ofGetWidth();
    int height = ofGetHeight();
    ofSetColor(255,255,255);
    ofSetLineWidth(4.0f);
    int linelength = getLineLength();

    ofPushMatrix();
    if(width>height) glTranslatef((width-height)/2,0,0);
        else glTranslatef(0,(height-width)/2,0);
		glTranslatef(0.5f*linelength,0.5f*linelength,0);
		glRotatef(-90,0,0,1);
		DrawArrow_three(linelength);

    ofPopMatrix();
}

void Grid::CallList5(){
    int width = ofGetWidth();
    int height = ofGetHeight();
    ofSetColor(255,255,255);
    ofSetLineWidth(4.0f);
    int linelength = getLineLength();

    ofPushMatrix();
    if(width>height) glTranslatef((width-height)/2,0,0);
        else glTranslatef(0,(height-width)/2,0);
		ofPushMatrix();
		glTranslatef(0.05f*linelength,0.5f*linelength,0);
		ofPushMatrix();
		glRotatef(-90,0,0,1);
		glScalef(1,0.5f,1);
		DrawArrow_three(linelength);
		ofPopMatrix();
		ofPushMatrix();
		glTranslatef(0.9f*linelength,0,0);
		glRotatef(-90,0,0,1);
		glScalef(1,0.5f,1);
		DrawArrow_three(linelength);
		ofPopMatrix();
		ofPopMatrix();
		ofPushMatrix();
		glTranslatef(0.5f*linelength,0.05f*linelength,0);
		ofPushMatrix();
		glRotatef(-90,0,0,1);
		glScalef(0.5f,1,1);
		DrawArrow_three(linelength);
		ofPopMatrix();
		ofPushMatrix();
		glTranslatef(0,0.9f*linelength,0);
		glRotatef(-90,0,0,1);
		glScalef(0.5f,1,1);
		DrawArrow_three(linelength);
		ofPopMatrix();
		ofPopMatrix();

    ofPopMatrix();
}


void Grid::GenerateOpenGL_lists()
{
}

void Grid::RenderArrow_one(int size)
{
    ofPath Arrow;

    ofPushMatrix();

    Arrow.moveTo(-0.05*size,0);
    Arrow.lineTo(0,0.1*size);
    Arrow.lineTo(0.05*size,0);
    Arrow.close();
    Arrow.setStrokeColor(ofColor::blue);
    Arrow.setFillColor(ofColor::red);
    Arrow.setFilled(true);
    Arrow.setStrokeWidth(2);
    Arrow.draw();

    Arrow.moveTo(-0.025*size,0);
    Arrow.lineTo(0-0.0125*size,-0.1*size);
    Arrow.lineTo(0.0125*size,-0.1*size);
    Arrow.lineTo(0.025*size,0);
    Arrow.close();
    Arrow.draw();

    ofPopMatrix();

    // ofPushMatrix();
    // glBegin(GL_TRIANGLE_STRIP);
    // glVertex2d(-0.05*size,0);
    // glVertex2d(0,0.1*size);
    // glVertex2d(0.05*size,0);
    // glEnd();
    // glBegin(GL_TRIANGLE_FAN);
    // glVertex2d(-0.025*size,0);
    // glVertex2d(-0.0125*size,-0.1*size);
    // glVertex2d(0.0125*size,-0.1*size);
    // glVertex2d(0.025*size,0);
    // glEnd();
    // ofPopMatrix();
}

void Grid::RenderArrow_two(int size)
{
    ofPath Arrow;

    ofPushMatrix();

    Arrow.moveTo(-0.025*size,0);
    Arrow.lineTo(0,0.1*size);
    Arrow.lineTo(0.025*size,0);
    Arrow.close();
    Arrow.setStrokeColor(ofColor::blue);
    Arrow.setFillColor(ofColor::red);
    Arrow.setFilled(true);
    Arrow.setStrokeWidth(2);
    Arrow.draw();

    Arrow.moveTo(-0.0125*size,0);
    Arrow.lineTo(-0.0125*size,-0.2*size);
    Arrow.lineTo(0.0125*size,-0.2*size);
    Arrow.lineTo(0.0125*size,0);
    Arrow.close();
    Arrow.draw();

    Arrow.moveTo(-0.025*size,-0.2*size);
    Arrow.lineTo(0,-0.3*size);
    Arrow.lineTo(0.025*size,-0.2*size);
    Arrow.close();
    Arrow.draw();

    ofPopMatrix();


    // glBegin(GL_TRIANGLE_STRIP);
    // glVertex2d(-0.025*size,0);
    // glVertex2d(0,0.1*size);
    // glVertex2d(0.025*size,0);
    // glEnd();
    // glBegin(GL_TRIANGLE_FAN);
    // glVertex2d(-0.0125*size,0);
    // glVertex2d(-0.0125*size,-0.2*size);
    // glVertex2d(0.0125*size,-0.2*size);
    // glVertex2d(0.0125*size,0);
    // glEnd();
    // glBegin(GL_TRIANGLE_STRIP);
    // glVertex2d(-0.025*size,-0.2*size);
    // glVertex2d(0,-0.3*size);
    // glVertex2d(0.025*size,-0.2*size);
    // glEnd();
}

void Grid::DrawArrow_three(int size){
    ofPath Arrow;

    ofPushMatrix();

    float arc = M_PI*2-0.7;
    float sinus = 0;
    float cosinus = 0;
    float angle;
    float offset = M_PI /20;
	for (angle=0; angle<arc; angle+=arc/60 ){
		sinus = sin(angle+offset);
		cosinus = cos(angle+offset);
		Arrow.lineTo(0.08*sinus*size, 0.08*cosinus*size);
        Arrow.lineTo(0.1*sinus*size, 0.1*cosinus*size);
	}
    Arrow.setStrokeColor(ofColor::blue);
    Arrow.setFillColor(ofColor::red);
    Arrow.setFilled(true);
    Arrow.setStrokeWidth(2);
    Arrow.close();


    float ax = 0.08*sinus - 0.1*sinus;
    float ay = 0.08*cosinus - 0.1*cosinus;
    float mod = sqrt(ax*ax + ay*ay);
    ax = ax/mod;
    ay = ay/mod;
    Arrow.moveTo(0.055*sinus*size, 0.055*cosinus*size);
    Arrow.lineTo(0.125*sinus*size, 0.125*cosinus*size);
    Arrow.lineTo((-ay*0.05*size)+0.09*sinus*size, (ax*0.05*size)+0.09*cosinus*size);
    Arrow.close();
    
    Arrow.draw();


    ofPopMatrix();


    // glBegin(GL_TRIANGLE_STRIP);
    // float arc = M_PI*2-0.7;
    // float sinus = 0;
    // float cosinus = 0;
    // float angle;
    // float offset = M_PI /20;
	// for (angle=0; angle<arc; angle+=arc/60 ){
	// 	sinus = sin(angle+offset);
	// 	cosinus = cos(angle+offset);
	// 	glVertex2d(0.08*sinus*size, 0.08*cosinus*size);
    //     glVertex2d(0.1*sinus*size, 0.1*cosinus*size);
	// }
	// glEnd();

    // float ax = 0.08*sinus - 0.1*sinus;
    // float ay = 0.08*cosinus - 0.1*cosinus;
    // float mod = sqrt(ax*ax + ay*ay);
    // ax = ax/mod;
    // ay = ay/mod;
	// glBegin(GL_TRIANGLES);
    //     glVertex2d(0.055*sinus*size, 0.055*cosinus*size);
    //     glVertex2d(0.125*sinus*size, 0.125*cosinus*size);
    //     glVertex2d((-ay*0.05*size)+0.09*sinus*size, (ax*0.05*size)+0.09*cosinus*size);
	// glEnd();
}
