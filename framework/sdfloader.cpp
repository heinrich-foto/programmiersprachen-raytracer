#include "sdfloader.hpp"
#include "material.hpp"
#include <deque>
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
				{
					if (!parse(line))
					{
						std::cout << "Invalid Format in SDF File: \n!! ->\t" << line << std::endl;
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
	std::string word;
	std::deque<std::string> words;
	while(stream.good())
	{
		stream >> word;
		words.push_back(word);
	}
	if ((words.size()>2) & (words.front()=="define")) {
		words.pop_front();
		if (words.front()=="material") {
			words.pop_front();
			std::string name = words.front();
			words.pop_front();
			if (words.size()==10){
				Color ka{std::stof(words.at(0)),std::stof(words.at(2)),std::stof(words.at(3))};
				words.pop_front(); words.pop_front(); words.pop_front();
				Color kb{std::stof(words.at(0)),std::stof(words.at(2)),std::stof(words.at(3))};
				words.pop_front(); words.pop_front(); words.pop_front();
				Color ks{std::stof(words.at(0)),std::stof(words.at(2)),std::stof(words.at(3))};
				words.pop_front(); words.pop_front(); words.pop_front();

				float m = std::stof(words.front());

				scene_.material.push_back(Material{name,ka,kb,ks,m});
				return true;
			}
			else {
				return false;
			}
		} // end-if MATERIAL
	} // end-if DEFINE
	return false;
}