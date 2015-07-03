// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// SDFLoader
// -----------------------------------------------------------------------------

#ifndef BUW_SDFLoader_HPP
#define BUW_SDFLoader_HPP

#include "scene.hpp"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream> 

class SDFLoader
{
public: 
	static SDFLoader* instance() {
		if ( s_instance_ == nullptr )
            s_instance_ = new SDFLoader;
        return s_instance_;
    };

    ~SDFLoader();

    Scene const& load(std::string const& filename);

private:
	bool parse(std::string const& line);

	Scene scene_;
	static SDFLoader* s_instance_;
};

#endif // BUW_SDFLoader
