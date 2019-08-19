# Mandelbrot Set Explorer
This C++ program explores the recursive function Zn+1 = Zn + C where Zn is the complex number a + bi.

This program uses the basic escape algorithm described here https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings

The Mandelbrot set is the set of complex numbers C that prevents the function above from diverging. When numbers outside the set diverge, they do at varying points in time which is represented by colors in the pictures and videos you see online. The black regions are the Mandelbrot set, the color regions are not. 

# How to use this repository
This program uses sfml to render a window to display the plots. You can download it here https://www.sfml-dev.org/index.php. You will then have to compile the code. A makefile will be up later. 

# Future work
Panning, mouse features, and other UI related fixes. Multi threading and SIMD optimizations are also intereting to look into.

Enjoy!
