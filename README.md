Programmiersprachen: Raytracer
===========

[![Build Status](https://travis-ci.org/heinrich-foto/programmiersprachen-raytracer.svg)](http://travis-ci.org/heinrich-foto/programmiersprachen-raytracer)

Framework for exercise 08.
# Klassendiagramm
http://www.nomnoml.com/#view/%23title%3A%20raytracer_classdiagramm%0A%23direction%3A%20down%0A%23arrowSize%3A%201.2%0A%23bendSize%3A%200.8%0A%23gutter%3A%2020%0A%23lineWidth%3A%204%0A%23padding%3A12%0A%23leading%3A%201.6%0A%23fontSize%3A19%0A%23spacing%3A80%0A%23edges%3A%20hard%0A%0A%5BWindow%7C...%7C...%5D-%3E%5BRenderer%5D%0A%0A%5BRenderer%0A%7C%09-%20width%3A%20unsigned%3B%0A%20%20%20%20-%20height%3A%20unsigned%3B%0A%20%20%20%20-%20filename%3A%20string%3B%0A%20%20%20%20-%20scenefile%3A%20string%3B%0A%20%20%20%20-%20ppm%3A%20ppmWriter%3B%0A%20%20%20%20-%20scene%3A%20Scene%0A%7C%0A%09%2B%20Renderer(w%2Ch%2Cfile)%3B%0A%20%20%20%20%2B%20Renderer(w%2Ch%2Cfile%2C%20scenefile)%3B%0A%20%20%20%20%2B%20optional%20Hit%20intersect(Ray%20const%20%26%20ray)%20const%0A%20%20%20%20%2B%20render()%3A%20void%3B%0A%20%20%20%20%2B%20write(p%3A%20Pixel)%3A%20void%0A%5Do-%3E%5BScene%5D%0A%0A%5BHit%7C%20%0A%09%2B%20hit%3A%20bool%0A%20%20%20%20%2B%20shape%3A%20Shape*%20%0A%20%20%20%20%2B%20distance%3A%20float%0A%5D%20%0A%0A%5BSDFLoader%20%7C%20%0A%20%20%20%20-%20scene%3A%20Scene%0A%20%20%20%20-%20instance%3A%20SDFLoader*%0A%7C%20%0A%20%20%20%20-%20%20SDFLoader()%0A%20%20%20%20%2B%20%20static%20instance%0A%20%20%20%20%2B%20%20load(filename)%3A%20Scene%0A%20%20%20%20-%20%20parse(line)%3A%20bool%0A%5D%0A%0A%5BScene%20%7C%0A%20%20%20%20%2B%20shape%3A%20vector%3CShape*%3E%0A%20%20%20%20%2B%20light%3A%20vector%3CLight%3E%0A%20%20%20%20%2B%20camera%3A%20vector%3CCamera%3E%0A%20%20%20%20%2B%20material%3A%20vector%3CMaterial%3E%0A%20%20%20%20%2B%20ambientColor%3A%20Color%0A%20%20%20%20%2B%20AmbientBrightness%3A%20float%0A%20%20%20%20%2B%20resX%3A%20unsigned%0A%20%20%20%20%2B%20resY%3A%20unsigned%0A%20%20%20%20%7C%0A%5D%0A%0A%5BColor%20%7C%0A%20%20%20%20%2B%20r%3A%20float%0A%20%20%20%20%2B%20g%3A%20float%0A%20%20%20%20%2B%20b%3A%20float%0A%5D%0A%0A%5BRay%20%7C%0A%09%2B%20origin%3A%20vec3%0A%20%20%20%20%2B%20direction%3A%20vec3%0A%5D%0A%0A%5BCamera%20%7C%0A%09-%20pos%3A%20vec3%0A%7C%0A%09%2B%20render()%3A%20void%0A%5D%0A%0A%5B%3Cabstract%3E%20Shape%20%7Babstract%7D%20%7C%0A%09-%20position%3A%20vec3%0A%20%20%20%20-%20material%3A%20Material%0A%20%20%20%20-%20name%3A%20String%0A%20%20%20%20%7C%0A%20%20%20%20%2B%20virtual%20intersect(ray)%20%3A%20pair%3Cbool%2C%20float%3E%0A%20%20%20%20%2B%20intersect(ray%2Ct)%3A%20bool%0A%20%20%5D%0A%0A%5BSphere%0A%7C%09-%20center%3A%20vec3%0A%09-%20radius%3A%20double%20(float)%3F%0A%7C%20%09Sphere(center%3A%20vec3%2C%20radius%3A%20float)%0A%5D-%3A%3E%5BShape%20%7Babstract%7D%5D%0A%0A%5BBox%20%7C%0A%20%20%20%20-%20min%3A%20vec3%0A%20%20%20%20-%20max%3A%20vec3%0A%7C%0A%20%20%20%20Box(min%2Cmax)%0A%5D-%3A%3E%5BShape%20%7Babstract%7D%5D%0A%0A%0A%5BMaterial%0A%7C%20%20%20-%20name%0A%20%20%20%20-%20ka%3A%20Color%0A%20%20%20%20-%20kd%3A%20Color%0A%20%20%20%20-%20ks%3A%20Color%0A%20%20%20%20-%20m%3A%20double%0A%7C%20%20%20%2B%20Material()%0A%20%20%20%20%2B%20name()%0A%20%20%20%20%2B%20ka()%0A%20%20%20%20%2B%20kd()%0A%20%20%20%20%2B%20ks()%0A%20%20%20%20%2B%20m()%0A%20%20%20%20%2B%20operator%3C%3C(Material)%0A%5D%0A%5BComposit%20%7C%20%0A%20%20%20%20-%20shape%3A%20vector%3CShape*%3E%20%0A%7C%20%0A%20%20%20%20%2B%20add_child(Shape*)%0A%5D-%3A%3E%5BShape%20%7Babstract%7D%5D%0A%0A%5BTriangle%20%7C%0A%20%20%20%20-%20a%3A%20vec3%0A%20%20%20%20-%20b%3A%20vec3%0A%20%20%20%20-%20c%3A%20vec3%0A%7C%0A%5D-%3A%3E%5BShape%20%7Babstract%7D%5D%0A%0A%5BLight%20%7C%C2%A0%0A%20%20%20%20-%20name%3A%20string%0A%20%20%20%20-%20position%3A%20vec3%0A%20%20%20%20-%20color%3A%20Color%0A%7C%0A%20%20%20%20%2B%20name%3A%20string%0A%20%20%20%20%2B%20pos%3A%20vec3%0A%20%20%20%20%2B%20color%3A%20Color%0A%5D%0A%0A%5BShape%20%7Babstract%7D%5Do-%3E%5BMaterial%5D%0A%5BShape%20%7Babstract%7D%5Do-%3E%5BHit%5D%0A%0A%5BComposit%5D-%3E__%20*%5BShape%20%7Babstract%7D%5D%0A%0A%5BSDFLoader%5Do-%3E%5BScene%5D%0A%5BSDFLoader%5Do-%3E%5BShape%20%7Babstract%7D%5D%0A%0A%5BScene%5Do-%3E%5BCamera%5D%0A%5BScene%5Do-%3E%5BShape%20%7Babstract%7D%5D%0A%5BScene%5Do-%3E%5BLight%5D%0A%0A%5BMaterial%5Do-%3E%5BColor%5D%0A%5BLight%5Do-%3E%5BColor%5D%0A%0A%5BRenderer%5Do-%3E%5BHit%5D%0A%5BRenderer%5Do-%3E%5BRay%5D%0A%0A%5B%3Cnote%3E%20vec3%20(aus%20glw)%7C%20%0Ax%2C%20y%2C%20z%20%3A%20int%20%0AKoordinaten%5D%0A