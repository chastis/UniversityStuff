#ifndef HELPERS_H
#define HELPERS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <thread>
#include <mutex>

enum class sort_type { std, bubble };

constexpr float DEFAULT_EL_SIZE = 10.f;
using Point = sf::Vector2f;
static bool shut_down = false;

#endif // !HELPERS
