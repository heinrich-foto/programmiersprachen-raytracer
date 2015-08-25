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


class Composit : public Shape
{
public: 
	Composit();
	Composit(std::string const&, Material const&);

	~Composit();


	void add_child(std::shared_ptr<Shape> const&);

	/*virtual*/ Hit intersect(const Ray &r) const override;

	/*virtual*/ std::ostream& print(std::ostream& os) const override;

	friend std::istream& operator>>(std::istream& os, COMPOSIT & input);

protected:
	/*virtual*/ void readFromStream (std::istream & ins) override;

private:
	std::vector<std::shared_ptr<Shape>> shape;
};

#endif // BUW_COMPOSIT
