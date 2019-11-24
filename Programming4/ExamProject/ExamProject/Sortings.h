#ifndef SORTINGS_H
#define SORTINGS_H

#include <functional>
#include <algorithm>
#include <vector>

template <class Element>
using ReturnType =  std::function<void(typename std::vector<Element>::iterator, typename std::vector<Element>::iterator, std::function<bool(Element, Element)>)>;

template <class Element>
class Sortings
{
public:
	Sortings() = delete;
	static ReturnType<Element> getQuickSort();
	static ReturnType<Element> getMergeSort();
	static ReturnType<Element> getCountSort();
	static ReturnType<Element> getSelectionSort();
};

#include "Sortings.cpp"

#endif

