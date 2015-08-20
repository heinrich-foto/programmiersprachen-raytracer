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
				{
					if (!parse(line))
					// if (!parse(delete_double(line,' ')))
					{
						std::cout << "-- ->\tInvalid Format in SDF File: \n!! ->\t|" << line << "|"<< std::endl;
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
        std::cout << "!! ->\t" << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "!! ->\t" << "Error of unknown type." << std::endl;
	}
}

bool SDFLoader::parse(std::string const& line) {
	if (line.find("#")!=std::string::npos) {
		std::cout << "?? ->\t" << line << std::endl;
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
					} else {
						return false;
					}
				} else if (word=="light") {

				} else if (word=="shape") {
					// shape einlesen in Shape Klasse erledigen? Problematisch Shape weiß seine Abgeleiteten Klassen nicht.
					// und kann somit nicht den jeweiligen Stream Operator aufrufen. Es müssten alle durchprobiert werden, 
					// um zu schauen ob einer passt... der Folgende Code ist somit noch sehr redundant. Vermutlich ist es aber 
					// in gewisser Weise sinnvoll über diesen kleinen Umweg im Stream Operator des Shape zu gehen, damit wir ein
					// Shape Objekt statt der abgeleiteten Objekte in der Hand haben und nicht immer den gleichen Code leicht an-
					// gepasst benötigen...
					stream >> word;
					if (word == "sphere") {
						std::shared_ptr<Sphere> sphere (new Sphere{});
						Color color{};
						std::string color_name = "";
						stream >> *sphere >> color_name;
						if (!stream.good()) {
							sphere->material(scene_.get_material(color_name));
							scene_.shape.push_back(sphere);
						}
					} else if (word == "box") {
						std::shared_ptr<Box> box (new Box{});
						Color color{};
						std::string color_name = "";
						stream >> *box >> color_name;
						if (!stream.good()) {
							box->material(scene_.get_material(color_name));
							scene_.shape.push_back(box);
						}
					} else if (word=="triangle") {
						// std::shared_ptr<Triangle> shape (new Triangle{});
						// Color color{};
						// std::string color_name = "";
						// stream >> *shape >> color_name;
						// if (!stream.good()) {
						// 	shape->material(scene_.get_material(color_name));
						// 	scene_.shape.push_back(shape);
						// }
					} else if (word == "composite") {
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
					}
				}

			} else if (word=="camera") {

			} else if (word=="render") {

			} else if (word == "transform") {

			}
		}
	}
	return false;
}