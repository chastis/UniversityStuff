#include "helpers.h"
#include "Visualizer.h"

using namespace sf;

void sort(Visualizer& v) {
	auto& vec = v._elements;
	for (size_t i = 0; i < vec.size() - 1; ++i) {
		if (Data::comp(vec[i], vec[i + 1])) {
			auto temp = vec[i];
			vec[i] = vec[i + 1];
			vec[i + 1] = temp;
			i = 0;
		}
	}
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "Visual sort");
	
	Data d(10, 500, 10);
	Visualizer visualizer(d);
	//visualizer.sort();
	visualizer.setSize({800, 50});
	//visualizer.sort();
	visualizer.setPosition({0, 300});
	
	
	//visualizer.setPosition({ 0, 300 });
	/*std::thread sort_thread(sort, std::ref(visualizer));*/

	//std::sort(visualizer._elements.begin(), visualizer._elements.end(), Data::comp);

	//visualizer.sort();
	visualizer.print();
	visualizer.sort();
	std::cout << "HERE WE ARE" << std::endl;
	visualizer.print();
	std::cout << "HERE WE ARE" << std::endl;
	window.clear(Color::Black);
	window.draw(visualizer);
	visualizer.setPosition({ 0, 400 });
	visualizer.sort();
	visualizer.print();
	std::cout << std::endl;
	//for (auto& v : visualizer._elements) window.draw(v);
	window.draw(visualizer);
	window.display();

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}
		//window.clear(Color::Black);
		
	}

	//sort_thread.join();
	return 0;
}