#include "helpers.h"
#include "Visualizer.h"
#include "Sortings.h"

using namespace sf;

void sort(Data& d) {
	std::sort(d.begin(), d.end(), Data::comp);
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "Visual sort");
	
	Data d(10, 500, 1000);
	Visualizer visualizer(d);
	visualizer.setSize({800, 50});
	visualizer.setPosition({0, 300});

	auto _comp = [&](Element a, Element b) {
		//std::this_thread::sleep_for(std::chrono::nanoseconds(10));
		return Data::comp(a, b);
	};

	//visualizer.sort(std::sort<decltype(d.begin()), decltype(_comp)>, _comp);

	Sortings s;
	visualizer.sort(s.getBubbleSort(), _comp);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
			{
				//visualizer.temp_thread->detach();
				//delete visualizer.temp_thread;
				window.close();
			}
		}

		window.clear();
		window.draw(visualizer);
		window.display();
		//window.clear(Color::Black);
	}
	//visualizer.temp_thread.join();
	//visualizer.temp_thread->detach();
	//if (visualizer.temp_thread) delete visualizer.temp_thread;
	return 0;
}