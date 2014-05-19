// =============================================================================
//
// Copyright (c) 2010-2014 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


ofApp::ofApp():
    hash(points),
    radius(DEFAULT_RADIUS)
{
    points.resize(NUM_POINTS);
}


void ofApp::setup()
{
    ofEnableAlphaBlending();

    for (std::size_t i = 0; i < NUM_POINTS; ++i)
    {
        points.push_back(ofVec2f(ofRandomWidth(), ofRandomHeight()));
    }

    hash.buildIndex();
}


void ofApp::update()
{
    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());

    radiusResults.resize(NUM_POINTS / 4);
    hash.findPointsWithinRadius(mouse, radius, radiusResults);
}


void ofApp::draw()
{
    ofBackground(0);

    ofNoFill();
    ofSetColor(255, 127);

    for (std::size_t i = 0; i < points.size(); ++i)
    {
        ofCircle(points[i], 5);
    }

    ofFill();
    ofSetColor(255, 255, 0, 80);

    for (std::size_t i = 0; i < radiusResults.size(); ++i)
    {
        float normalizedDistance = ofMap(radiusResults[i].second, radius * radius, 0, 0, 1);

        ofSetColor(255, 255, 0, normalizedDistance * 127);

        ofCircle(points[radiusResults[i].first], 5 * normalizedDistance);
    }
}
