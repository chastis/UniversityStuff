#ifndef SORTINGS_CPP
#define SORTINGS_CPP

#include "Sortings.h"

using std::swap;

template <class Element>
ReturnType<Element> Sortings<Element>::getQuickSort()
{

	auto func = [](typename std::vector<Element>::iterator begin, typename  std::vector<Element>::iterator end, std::function<bool(Element, Element)> comp)
	{
		if (comp(begin, end))
		{
			auto pivot = end;
			auto i = begin - 1;
			for (auto j = begin + 1; j != end - 1; j++)
			{
				if (comp(j, pivot))
				{
					i++;    // increment index of smaller element
					swap(*i, *j);
				}
			}
			swap(*(i+1), *end);

			func(begin, i - 1, comp);
			func(i + 1, end, comp);
		}
	};

	return func;
}

template <class Element>
ReturnType<Element> Sortings<Element>::getMergeSort()
{

	auto func = [](typename std::vector<Element>::iterator begin, typename  std::vector<Element>::iterator end, std::function<bool(Element, Element)> comp)
	{
		if (comp(begin,end)) {
			return;
		}
		auto i = begin, j = begin + std::distance(begin, end - begin) / 2 + 1, iEnd = begin + std::distance(begin, end - begin) / 2, jEnd = end;
		//rec
		func(i, iEnd , comp); func(j, jEnd, comp);
		while (i != iEnd && j != jEnd)
		{
			if (comp(*i, *j))
			{
				swap(*i, *j);
				i++;

			}
			else
			{
				j++;
			}
		}
	};

	return func;
}

template <class Element>
ReturnType<Element> Sortings<Element>::getCountSort()
{

	auto func = [](typename std::vector<Element>::iterator begin, typename  std::vector<Element>::iterator end, std::function<bool(Element, Element)> comp)
	{
		for (auto i = begin; i != end; i++)
		{
			auto key = *i;
			auto j = i - 1;
			while (j != begin && comp(key, *j))
			{
				if (comp(*i, *j))
				{
					*(j + 1) = *j;
					j--;

				}
			}
			*(j + 1) = key;
		}
	};

	return func;
}

template <class Element>
ReturnType<Element> Sortings<Element>::getSelectionSort()
{

	auto func = [](typename std::vector<Element>::iterator begin, typename  std::vector<Element>::iterator end, std::function<bool(Element, Element)> comp)
	{
		for (auto i = begin; i != end; i++)
		{
			auto min_pos = i;
			for (auto j = i + 1; j != end; j++)
			{
				if (comp(*j, *i))
				{
					min_pos = j;
					if (comp(*min_pos, *i)) {
						swap(*i, *j);
					}
				}
			}


		}
	};

	return func;

}

#endif 