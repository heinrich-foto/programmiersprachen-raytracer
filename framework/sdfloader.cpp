#include "sdfloader.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "composit.hpp"
#include "camera.hpp"

#include <deque>
#include <algorithm>
// ------- c++14
// #include <experimental/filesystem>
// namespace fs = std::experimental::filesystem;
//-------- boost
// #include <boost/filesystem.hpp>
// namespace fs = boost::filesystem;

SDFLoader* SDFLoader::s_instance_ = nullptr;

Scene const& SDFLoader::load(std::string const& filename){
	try { 
		if (s_instance_!=nullptr)
		{
			if (filename.rfind(".sdf")!=filename.size()-4) {
				throw std::invalid_argument("Invalid File extention.\n");
			}
			std::ifstream ifs;
			ifs.open(filename);
			if (ifs.is_open()) {
				
				std::string line;
				while(getline(ifs, line))
				{	try {
						if (!parse(line))
						{	
							if (line!="") {
								std::cout //<< "-- ->\tInvalid Format in SDF File: \n" 
									  << "!! ->\t|" 
									  << line << "| 36"<< std::endl;
							}
						}
					} catch (std::length_error& e) {
						std::cout << "vector lengt error: " << e.what() << std::endl;
					} catch (std::invalid_argument& e) {
						std::cout << "!! ->\t" << e.what() << " => |" << line << "| 45"<< std::endl;
					}
				}
				ifs.close();

				return scene_;
			}
			else {
				// std::string path{};
				// path = fs::current_path().string()
				throw std::invalid_argument("File dosn´t exist.\n");
			}
		}
		else
		{
			throw std::invalid_argument("ProgrammError: no Instanz of SDFLoader.\n");
		}
	} 
	catch ( const std::invalid_argument& e ) {
        std::cout << "!! -> 64\t" << e.what() << std::endl;
	}
	// catch (std::length_error& e) {
	// 	std::cout << "!! ->\t vector lengt error: " << e.what() << std::endl;
	// }
	catch (...)
	{
		std::cout << "!! -> 71\t" << "Error of unknown type." << std::endl;
	}
}

bool SDFLoader::parse(std::string const& line) {
	if (line.find("#")!=std::string::npos) {
		// std::cout << "?? ->\t" << line << std::endl;
		return true; //its a comment line
	}

	std::stringstream stream(line);

	if(stream.good())
	{	
		std::string word="";
		while (stream >> word)
		{
			if (word=="define") {
				stream >> word;
				if (word =="material") {
					Material mat;
					stream >> mat >> std::ws;
					if (!stream.good()) {
						scene_.material.push_back(mat);
						return true;
					} else { return false; }

				} else if (word=="light") {
					throw std::invalid_argument("Not implemented.");
					// define light name pos La Ld
					// define light name     La Ld
				} else if (word=="shape") {
					stream >> word;
					try {
						std::shared_ptr<Shape> shape (ShapeFactory(word));
						if (word!="composite") {
							Color color{}; std::string color_name = "";
						
							stream >> *shape >> color_name;
							if (!stream.good()) {
								shape->material(scene_.get_material(color_name));
								scene_.shape.push_back(shape);
								std::cout << "added new "<< shape << " " << *shape << std::endl;
								return true;
							} else { return false; }
						} else { // if composite
							stream >> *shape;
							while (stream.good()) {
								stream >> word;
								if (!std::static_pointer_cast<Composit>(shape)->add_child(scene_.get_shape(word))) return false;
							}
							scene_.shape.push_back(shape);
							return true;
						}
						
					}
					catch (const std::invalid_argument& e) {
						std::cout << e.what() << "> in " << word << std::endl;
						return false;
					}
					
				}

			} else if (word=="camera") {
				throw std::invalid_argument("Not implemented.");
				// camera name FovX (horizontaler Öffnungswinkel)
				// camera name FovX eye (Position) dir (Blickrichtung) up (Up-Vector)
				Camera camera{"def_cam",{0,0,0}, 0, 0};
				stream >> camera;
				if (!stream.good()) {
					scene_.camera=camera;
					return true;
				} else { return false; }
			} else if (word=="render") {
				throw std::invalid_argument("Not implemented.");
				// render cam-name filename resx resy
				
				std::string cameraName;
				std::string filename;
				unsigned resX, resY;
				stream >> cameraName >> filename >> resX >> resY;

				if (!stream.good()) {
					// mehrere Cameras speichern - einlesen und rendern? 
					// Oder darf es nur eine Kamera geben und somit nur einen Render Aufruf. (Could be?)
					if (cameraName==scene_.camera.name()) {
						scene_.resX = resX;
						if (scene_.camera.compute_distance(scene_.resX) == -1) { 
							throw std::invalid_argument("No valid Camera generated.");
							return false;
						}
						scene_.resY = resY;
						scene_.filename = filename;
						return true;
					} else { 
						throw std::invalid_argument("No valid Camera Found.");
						return false; 
					}
				} else { return false; }
			} else if (word == "transform") {
				throw std::invalid_argument("Not implemented."); 
				// Object is String Name in Shape
				// transform object scale value
				// transform object rotate angle vec (Grad)
				// transform object translate vec
			}
		}
	}
	return false;
}

std::shared_ptr<Shape> SDFLoader::ShapeFactory(std::string const& input) {
	// vielleicht ein Switch Case Statement.
	if (input == "sphere") {
		return std::make_shared<Sphere> ();
	} else if (input == "box") {
		return std::make_shared<Box> ();
	} else if (input=="triangle") {
		throw std::invalid_argument("Not implemented."); 
		// return std::make_shared<Triangle> ();
	} else if (input == "composite") {
		// define shape composite name child
		return std::make_shared<Composit> ();
	} else {
		throw std::invalid_argument("No valid Shape Object."); 
	}
	return nullptr;
}