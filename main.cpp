
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




int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML window");
    window.setFramerateLimit(30);

    mandelbrot img (600, 400, 256, 2);

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
            
            if(event.type == sf::Event::MouseButtonPressed && img.isFinished())
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                img.threadWork(mouse.x, mouse.y);
            
            }
          
        }
        // Clear screen
        window.clear();

        window.draw(vertexPixels);

        // Update the window
        window.display();
    }
  
    
  
    return EXIT_SUCCESS;
}
