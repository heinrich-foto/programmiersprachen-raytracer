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

std::string delete_double(std::string const& string, char sign) {
// Cleanup String from e.G. Spaces
	std::string line = string;
	bool leerzeichen = false;
	while (line.front()==sign) line.erase(line.begin());
	for (auto iter=line.begin();iter!=line.end();)
	{
		if (*iter==sign) {
			if (leerzeichen==true) {
				line.erase(iter);
			} else {
				leerzeichen = true;
				++iter;
			}
		} else {
			leerzeichen = false;
			++iter;
		}
	}
	while (line.back()==sign) line.pop_back();
	// End Cleanup
	return line;
}


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
					if (!parse(delete_double(line,' ')))
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
	std::string word;
	std::deque<std::string> words;
	while(stream.good())
	{
		stream >> word;
		words.push_back(word);
	}
	// Output with counter
	// int counter = 0;
	// for (auto iter = words.begin(); iter != words.end(); iter++)
	// {
	// 	std::cout << counter++ << " " << "\"" << *iter << "\"" << std::endl;
	// }
	// counter = 0;

	// Front Funktion to access and pop the front element.
	auto getpop_front = [&words](){ 
		auto front = words.front(); 
		words.pop_front(); 
		return front; 
	};
	if ((words.size()>2) && (getpop_front()=="define")) {
		if (getpop_front()=="material") {
			std::string name = getpop_front();
			if (words.size()==10){
				Color ka{std::stof(getpop_front()),std::stof(getpop_front()),std::stof(getpop_front())};
				Color kb{std::stof(getpop_front()),std::stof(getpop_front()),std::stof(getpop_front())};
				Color ks{std::stof(getpop_front()),std::stof(getpop_front()),std::stof(getpop_front())};

				float m = std::stof(getpop_front());

				scene_.material.push_back(Material{name,ka,kb,ks,m});
				return true;
			}
			else {
				return false; // to many or less arguments
			}
		} // end-if MATERIAL
	} // end-if DEFINE
	if (words.size()==0) return true; // Linebreake
	return false;
}