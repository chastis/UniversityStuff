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
	void check_mutex();
	void setData(Data &);
	//sort must be function, that takes iterator on firstm iterator on last and comparator
	template <typename SortFunc, typename Comp>
	void sort(SortFunc &, Comp &);
private:
	std::vector<Element> _elements;
	std::mutex sorting;
	std::vector<std::thread *>temp_thread;
	int num;
};




template<class SortFunc, class Comp>
inline void Visualizer::sort(SortFunc &sort, Comp &comp)
{
	try
	{
		auto _sort = [&]() {
			try
			{
				sort(_elements.begin(), _elements.end(), comp);
			}
			catch (...)
			{
				std::cout << "WTF" << std::endl;
			}
			std::cout << "done" << std::endl;
		};

		if (sorting.try_lock())
		{
			temp_thread[num % 15] = new std::thread(_sort);
			temp_thread[num++ % 15 ]->detach();
			sorting.unlock();
		}
		else {
			std::cout << "second" << std::endl;
			temp_thread[num % 15]->detach();
			delete temp_thread[num % 15];
			temp_thread[num % 15] = new std::thread(_sort);
			temp_thread[num++ % 15]->detach();
			sorting.unlock();
		}
	}
	catch (...)
	{
		std::cout << "WTF2" << std::endl;
	}
}

#endif //CLASS_VISUALIZER_H