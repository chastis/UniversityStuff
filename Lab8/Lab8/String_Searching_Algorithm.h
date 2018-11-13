#ifndef STRING_SEARCHONG_ALGORITHM
#define STRING_SEARCHONG_ALGORITHM
#include <string>;
using namespace std;

//наивная сортировка
int Simple_Search(const string &where, const string &what);

//сортировка Рабина-Карпа
int RK_Search(const string &where, const string &what);

//сортировка Хорспула
int Horsool_Search(const string &where, const string &what);

//сортировка Боера-Мура
int Boyer_Moore_Search(const string &where, const string &what);

//сортировка Кнута-Морриса-Пратта
int KMP_Search(const string &where, const string what);


#endif // !STRING_SEARCHONG_ALGORITHM
