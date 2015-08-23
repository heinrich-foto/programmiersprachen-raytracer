#include "sdfloader.hpp"
#include "material.hpp"
#include "shape.hpp"
// mit angepassten Shape Stream redundant.
   #include "box.hpp"
   #include "sphere.hpp"
#include <deque>
#include <algorithm>
// ------- c++14
// #include <experimental/filesystem>
// namespace fs = std::experimental::filesystem;
//-------- boost
// #include <boost/filesystem.hpp>
// namespace fs = boost::filesystem;

SDFLoader* SDFLoader::s_instance_ = nullptr;

// std::string delete_double(std::string const& string, char sign) {
// // Cleanup String from e.G. Spaces
// 	std::string line = string;
// 	bool leerzeichen = false;
// 	while (line.front()==sign) line.erase(line.begin());
// 	for (auto iter=line.begin();iter!=line.end();)
// 	{
// 		if (*iter==sign) {
// 			if (leerzeichen==true) {
// 				line.erase(iter);
// 			} else {
// 				leerzeichen = true;
// 				++iter;
// 			}
// 		} else {
// 			leerzeichen = false;
// 			++iter;
// 		}
// 	}
// 	while (line.back()==sign) line.pop_back();
// 	// End Cleanup
// 	return line;
// }


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
						// if (!parse(delete_double(line,' ')))
						{	if (line!="") {
								std::cout //<< "-- ->\tInvalid Format in SDF File: \n" 
									  << "!! ->\t|" 
									  << line << "| 62"<< std::endl;
							}
						}
					} catch (std::length_error& e) {
						std::cout << "vector lengt error: " << e.what() << std::endl;
					} catch (std::invalid_argument& e) {
						std::cout << "!! ->\t" << e.what() << " => |" << line << "| 67"<< std::endl;
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
        std::cout << "!! -> 86\t" << e.what() << std::endl;
	}
	// catch (std::length_error& e) {
	// 	std::cout << "!! ->\t vector lengt error: " << e.what() << std::endl;
	// }
	catch (...)
	{
		std::cout << "!! -> 93\t" << "Error of unknown type." << std::endl;
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
				} else if (word=="shape") {
					stream >> word;
					try {
						std::shared_ptr<Shape> shape (ShapeFactory(word));
						Color color{}; std::string color_name = "";
						
						stream >> *shape >> color_name;
						if (!stream.good()) {
							shape->material(scene_.get_material(color_name));
							scene_.shape.push_back(shape);
							std::cout << "added new "<< shape << " " << *shape << std::endl;
							return true;
						} else { return false; }
					}
					catch (const std::invalid_argument& e) {
						std::cout << e.what() << "> in " << word << std::endl;
						return false;
					}
					
				}

			} else if (word=="camera") {
				throw std::invalid_argument("Not implemented.");
			} else if (word=="render") {
				throw std::invalid_argument("Not implemented.");
			} else if (word == "transform") {
				throw std::invalid_argument("Not implemented."); 
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
		throw std::invalid_argument("Not implemented."); 
		// könnte komplett im Streamoperator von Composite überladen werden.
		// sollte vielleicht auch. (somit nur stream >> comp anstelle von word.)
		// stream >> word;
		// // Composite comp{word};
		// while (stream.good()) {
		// 	stream >> word;
		// 	// auto it = std::find(scene_.shape.begin(), scene_.shape.end(),word);
		// 	// comp.add_child(it);
		// }
		// // scene_.shape.push_back(comp);
		
		// folgendes könnte dann bleiben
		// Composite comp{};
		// stream >> comp;

		// folgendes kommt in Composite Streamoperator --> ach ne... Problem ist Zugriff auf Scene Member für Pointer.
		// stream >> name_;
		// while (stream.good()) {
		// 	stream >> word;
		// 	auto it = std::find(scene_.shape.begin(), scene_.shape.end(),word);
		// 	comp.add_child(it);
		// }
		// scene_.shape.push_back(comp);
	} else {
		throw std::invalid_argument("No valid Shape Object."); 
	}
	return nullptr;
}