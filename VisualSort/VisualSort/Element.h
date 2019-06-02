#ifndef CLASS_ELEMET_H
#define CLASS_ELEMET_H

#include "helpers.h"

class Element : public sf::Drawable
{
public:
	Element();
	Element(sf::Vector2f);
	~Element() = default;

	void setPosition(const sf::Vector2f&);
	void setSize(const sf::Vector2f&);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	void setColor(sf::Color);
	sf::Color getColor() const;

	long long getValue() const;
	void setValue(long long);

	Element& operator=(const Element&);

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	
private:
	sf::RectangleShape _shape;
	long long _value;
};

#endif //CLASS_ELEMET_H