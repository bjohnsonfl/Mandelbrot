
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
//#include "ResourcePath.hpp"
#include <iostream>
#include <thread>
#include "mandelbrot.hpp"

#define window_width 1000
#define window_Height 1000


int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_width, window_Height), "SFML window");
    window.setFramerateLimit(30);

    mandelbrot img (window_width, window_Height, 5000, 15);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            
            
            
            if (event.type == sf::Event::KeyPressed && img.isFinished()){
                
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                         img.panImg(left);
                        break;
                        
                    case sf::Keyboard::Up:
                        img.panImg(up);
                        break;
                        
                    case sf::Keyboard::Right:
                        img.panImg(right);
                        break;
                        
                    case sf::Keyboard::Down:
                        img.panImg(down);
                        break;
                        
                    case sf::Keyboard::T:
                        img.zoomToTop();
                        break;
                   
                    
                    default:
                        break;
                }
                
            }
            
            
            
            
            
            if(event.type == sf::Event::MouseButtonPressed && img.isFinished())
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                if(event.mouseButton.button == sf::Mouse::Button::Left) img.zoomIn(mouse.x, mouse.y);
                else if( event.mouseButton.button == sf::Mouse::Button::Right) img.zoomOut();
                else if (event.mouseButton.button == sf::Mouse::Button::Middle) img.zoomToTop();
            }
            /*
            if(event.type == sf::Event::MouseWheelScrolled && img.isFinished())
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                if(event.mouseWheel.delta > 0) img.zoomIn(mouse.x, mouse.y);
                else img.zoomOut();
            }
          */
        }
        // Clear screen
        window.clear();

        window.draw(vertexPixels);

        // Update the window
        window.display();
    }
  
    
  
    return EXIT_SUCCESS;
}
