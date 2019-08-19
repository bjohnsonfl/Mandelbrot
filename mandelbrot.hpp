//
//  mandelbrot.hpp
//  mandelbrot
//
//  Created by Blake Johnson on 8/18/19.
//  Copyright © 2019 Blake Johnson. All rights reserved.
//

#ifndef mandelbrot_hpp
#define mandelbrot_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <thread>
#include <fstream>

extern int pixels [400][600];
extern sf::VertexArray vertexPixels;

class mandelbrot {
    
private:
    int width;
    int height;
    
    double centerX;
    double centerY;
    int max_iteration;
    
    int pixelCount;
    std::thread th;
    
    bool finished;
    std::ofstream stream;
public:
    
    
    mandelbrot();
    ~mandelbrot() {th.join();}
    mandelbrot(int width, int height, int max_iteration);
    
    
    void loop();
    
    void calculatePixel (int x, int y);
    
    void setColor(int x, int y, int iterations);
    
    double picToMand_x (double x);
    double picToMand_y (double y);
    
    bool isFinished ();
    
};

inline double mandelbrot::picToMand_x(double x) {
   // return ((x * 3.5)/600) - 2.5;
   // return (x - (width/2)) /float(300);
    
    return (x * ((0.7 + 1.5) / width)) - 1.5;
    //return x * (1/120) +2.5;
}

inline double mandelbrot::picToMand_y (double y){
    return -((2* y)/height) + 1;
   // return (y * ((1 + 1) / height)) -1 ;
   // return ((y * 3.5)/400) - 2.5;
   // return (y - (height/2)) / float(300);
    //return -(y/80) - 2.5;
}


inline bool mandelbrot::isFinished(){
    return finished;
}


#endif /* mandelbrot_hpp */
