#define GLM_FORCE_RADIANS

#include "sdfloader.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "composit.hpp"
#include "camera.hpp"

#include <deque>
#include <algorithm>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtx/string_cast.hpp>
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

				// Validation ob SDF -> valide Scene. und falls nicht, versuche es zu retten.
				
				// root Composite?
				if(!scene_.get_shape("root")) {
					std::cout << "Warning: A default constructed root object was generated. It contains every Shape Object." << std::endl 
					<< "add this to SDF File:\tdefine shape composite root child_shape child_shape ..." << std::endl;

					std::shared_ptr<Shape> shape (ShapeFactory("composite"));
					std::stringstream comp_stream;
					comp_stream << "root";
					comp_stream >> *shape;
					for (auto const& item : scene_.shape) {
						std::static_pointer_cast<Composit>(shape)->add_child(item);
					}
					scene_.shape.push_back(shape);
				}

				// Camera gesetzt?
				if(scene_.camera.name()=="default_camera") {
					std::cout << "Warning: A default camera was generated. " << scene_.camera << std::endl
					<< "add something like this to SDF File:\n\tcamera eye 60.0\n\trender eye image.ppm 600 600" << std::endl;
				}

				scene_.camera.compute_distance(scene_.resX);

				// Renderer gesetzt?
				// hat keine weiteren Auswirkungen, Kamera ist wichtig und setzt im Grunde schon alles.
				// denn wenn keine Kamera gesetzt ist, wurde auch kein Renderer gesetzt, somit kombinierte
				// Fehlermeldung. (siehe oben)
				
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
	return scene_;
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
				// throw std::invalid_argument("Not implemented.");
				// camera name FovX (horizontaler Öffnungswinkel)
				// camera name FovX eye (Position) dir (Blickrichtung) up (Up-Vector)
				Camera camera{"def_cam",{0,0,0}, 0, 0};
				stream >> camera;
				if (!stream.good()) {
					scene_.camera=camera;
					return true;
				} else { return false; }
			} else if (word=="render") {
				// throw std::invalid_argument("Not implemented.");
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

						std::cout << "added new "<< scene_.camera << std::endl;
						return true;
					} else { 
						throw std::invalid_argument("No valid Camera Found.");
						return false; 
					}
				} else { return false; }
			} else if (word == "transform") {
				// throw std::invalid_argument("Not implemented."); 
				// // Object is String Name in Shape
				// // transform object scale value
				// glm::scale(/*vector*/);
				// // transform object rotate angle vec (Grad)
				// glm::rotate(/*winkel, vector*/);
				// // transform object translate vec
				// glm::translate(/*vector*/);
				// // inverse funktion
				// glm::inverse(/*mat4*/);
				stream >> word;
				auto shape = scene_.get_shape(word);
				if (!shape) {
					throw std::invalid_argument("No Shape with input Name found.");
					return false;
				}
				stream >> *shape; // use Input Stream Operator of Shape.
				std::cout << "transformed " << shape->name() << " with " <<
					glm::to_string(shape->world_transformation()) << std::endl;
				return !stream.good();
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
	} else if (input == "composite" || input == "composit") {
		// define shape composite name child
		return std::make_shared<Composit> ();
	} else {
		throw std::invalid_argument("No valid Shape Object."); 
	}
	return nullptr;
}