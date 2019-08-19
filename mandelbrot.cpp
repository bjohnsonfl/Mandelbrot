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

mandelbrot::mandelbrot(int width, int height, int max_iteration, int zoomScalar){
    this -> width = width;
    this -> height = height;
    this -> max_iteration = max_iteration;
    zoom = 1;
    this -> zoomScalar = zoomScalar;
    /*
    man_Wid = 0.7 + 1.5;
    man_Height = -1 - 1;
    offsetX = 1.5;
    offsetY = -1;
    */
    man_Wid = 5;
    man_Height = 5;
    offsetX =  -2.5;
    offsetY =  2.5;
    
    centerX = 0;
    centerY = 0;
    
    pixelCount = 0;
    vertexPixels.resize(width * height);
    vertexPixels.setPrimitiveType(sf::Points);
    finished = false;
    stream.open("mandelBrot.ppm");
    th = std::thread(&mandelbrot::loop, this);
    //threadWork(300, 200);
    //loop();
}

void mandelbrot::zoomIn(int x, int y){
    th.join();
    std::cout << x << " " << y << "\n";
    centerX = picToMand_x(x);
    centerY = picToMand_y(y);
    zoomScalar = 15;
    man_Wid /= zoomScalar;
    man_Height /= zoomScalar;
    offsetX = (centerX - man_Wid / 2);
  
    offsetY = centerY + man_Height / 2;
    
    //std::cout << centerX << " " << centerY <<" " <<man_Wid << " "<<man_Height <<" " << offsetX << " " << offsetY << "\n" ;
    std::cout << "X: "<<centerX << " " <<man_Wid << " " << offsetX <<  "\n" ;
    std::cout << "Y: " << centerY << " " <<man_Height << " " << offsetY <<  "\n" ;
    th = std::thread(&mandelbrot::loop, this);
}


void mandelbrot::zoomOut(){
    th.join();
    man_Wid *= zoomScalar;
    man_Height *= zoomScalar;
    offsetX = (centerX - man_Wid / 2);
    
    offsetY = centerY + man_Height / 2;
    
    th = std::thread(&mandelbrot::loop, this);
}

void mandelbrot::loop(){
    
    stream << "P3\n" << width << " " << height<< "\n255\n";
    finished = false;
    pixelCount = 0;
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
    LD x0 = picToMand_x(double(pix_X));
    LD y0 = picToMand_y(double(pix_Y));
  // std::cout << pix_X << " " << x0 << " "<< pix_Y << " " << y0 << "\n" ;
    
    LD x = 0;
    LD y = 0;
    LD xtemp = 0;
    LD iter = 0;
    LD rr = 0;
    LD ii = 0;
    LD zz = 0;
    
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
    //if(iter >= max_iteration) std::cout << "here ";
    
    setColor(pix_X, pix_Y, iter);
}


void mandelbrot::setColor(int x, int y, int iterations){
    
    int color = 0;
    if(iterations >= max_iteration) color = 0;
    else color = 1;
    
    
    
    int red = iterations / 4;
    int green = iterations / 2;
    int blue = iterations;
    
    //pixels[-y][x] = color;
    vertexPixels[pixelCount].position = sf::Vector2f(x, y);
    vertexPixels[pixelCount].color = color == 1 ?
            sf::Color(red,green,blue % 256,255) : sf::Color(0,0,0,255);
    if(color == 1){
       
        stream << "0 0 "<< iterations % 256 << " ";
       
    }
    else{
         stream << "0 0 0 ";
    }
    
}

