#ifndef CLASS_VISUALIZER_H
#define CLASS_VISUALIZER_H

#include "helpers.h"
#include "Data.h"

class Visualizer : public sf::Drawable
{
public:
	explicit Visualizer(Data&);
	~Visualizer() = default;

	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	void setPosition(const sf::Vector2f&);
	const sf::Vector2f getPosition() const;
	void setWidth(size_t);
	void setHeight(size_t);
	void setSize(sf::Vector2f);
	const sf::Vector2f getSize();
	void print();
	void sort();
	std::vector<sf::RectangleShape>::iterator& el_begin();
	std::vector<sf::RectangleShape>::iterator& el_end();
	std::vector<sf::RectangleShape> _elements;
private:
	sf::Vector2f pos;
	Data _data;
};

#endif //CLASS_VISUALIZER_H