//
//  mandelbrot.cpp
//  mandelbrot
//
//  Created by Blake Johnson on 8/18/19.
//  Copyright © 2019 Blake Johnson. All rights reserved.
//

#include "mandelbrot.hpp"
#include <iostream>


int pixels[400][600];
sf::VertexArray vertexPixels = sf::VertexArray(sf::Points, 1);

mandelbrot::mandelbrot(){};

mandelbrot::mandelbrot(int width, int height, int max_iteration){
    this -> width = width;
    this -> height = height;
    this -> max_iteration = max_iteration;
    pixelCount = 0;
    vertexPixels.resize(width * height);
    vertexPixels.setPrimitiveType(sf::Points);
    finished = false;
    stream.open("mandelBrot.ppm");
    th = std::thread(&mandelbrot::loop, this);
    //loop();
}


void mandelbrot::loop(){
    
    stream << "P3\n" << width << " " << height<< "\n255\n";
    
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
            //vertexPixels[pixelCount].position = sf::Vector2f(x, y);
            //vertexPixels[pixelCount].color = sf::Color(0,0 ,x,255);
            calculatePixel(x, y);
            ++pixelCount;
            
        }
        stream<< "\n";
    }
    
    
    finished = true;
    
}


void mandelbrot::calculatePixel(int pix_X, int pix_Y){
    //std::cout << pix_X << " " << pix_Y << ":: ";
    double x0 = picToMand_x(double(pix_X));
    double y0 = picToMand_y(double(pix_Y));
   std::cout << pix_X << " " << x0 << " "<< pix_Y << " " << y0 << "\n" ;
    
    double x = 0;
    double y = 0;
    double xtemp = 0;
    double iter = 0;
    double rr = 0;
    double ii = 0;
    double zz = 0;
    
    while(((x*x + y*y) <= 4) && iter <= max_iteration ){
        xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
        iter = iter + 1;
    }
    /*
    while( ((rr + ii) <= 4) && iter <= max_iteration){
        x = rr - ii + x0;
        y = zz - rr - ii - ii + y0;
        rr = x*x;
        ii = y*y;
        zz = (x+y) * (x+y);
        iter++;
    }
    if(iter >= max_iteration) std::cout << "here ";
     */
    setColor(pix_X, pix_Y, iter);
}


void mandelbrot::setColor(int x, int y, int iterations){
    
    int color = 0;
    if(iterations >= max_iteration) color = 0;
    else color = 1;
    
    pixels[y][x] = color;
    vertexPixels[pixelCount].position = sf::Vector2f(x, y);
    vertexPixels[pixelCount].color = color == 1 ?
            sf::Color(0,0,iterations % 256,255) : sf::Color(0,0,0,255);
    if(color == 1){
        stream << "0 0 "<< iterations % 256 << " ";
    }
    else{
         stream << "0 0 0 ";
    }
    
}

