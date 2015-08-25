// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Composit of Shape Objects
// -----------------------------------------------------------------------------

#ifndef BUW_COMPOSIT_HPP
#define BUW_COMPOSIT_HPP

#include "shape.hpp"
#include "ray.hpp"
#include "material.hpp"

#include <vector>


class Composit : public Shape
{
public: 
	Composit();
	Composit(std::string const&, Material const&);

	~Composit() {};


	bool add_child(std::shared_ptr<Shape> const&);

	/*virtual*/ Hit intersect(const Ray &r) const override;

	/*virtual*/ std::ostream& print(std::ostream& os) const override;

	friend std::istream& operator>>(std::istream& os, Composit & input);

protected:
	/*virtual*/ void readFromStream (std::istream & ins) override;

private:
	std::vector<std::shared_ptr<Shape>> shape_;
};

#endif // BUW_COMPOSIT
