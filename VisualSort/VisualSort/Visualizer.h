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
	void setWidth(float);
	void setHeight(float);
	void setSize(sf::Vector2f);
	const sf::Vector2f getSize();

	//sort must be function, that takes iterator on firstm iterator on last and comparator
	template <typename SortFunc, typename Comp>
	void sort(SortFunc, Comp);

private:
	std::vector<Element>& _elements;
	bool sorting;
};




template<class SortFunc, class Comp>
inline void Visualizer::sort(SortFunc sort, Comp comp)
{
	sorting = true;
	auto _sort = [&]() {
		sort(_elements.begin(), _elements.end(), comp);
		sorting = false;
	};

	std::thread t1(_sort);
	t1.detach();
}

#endif //CLASS_VISUALIZER_H