#ifndef RBTREE_H
#define RBTREE_H

#include<stdio.h>
#include<stdlib.h>

// коды ошибок
#define ERROR_STRUCT	1
#define ERROR_BALANCE	2
#define SIZE 1000	//!< размер массива проверки


//! статистика (можно удалить для ускорения процесса)
struct stat_st {
	struct st {
		int max_count;		//!< рекодрное количество поворотов за раз
		int sum_count;		//!< сумарное число поворотов
		int sum_divider;	//!< количество операций, для вычисления среднего
	};
	int max_depth;		//!< глубина маскимального узла
	int black_depth;	//!< чёрная глубина дерева
	int nodes_count;	//!< количество вершин в дереве
	int turn_count;		//!< количество выполненых за раз поворотов (включая вложенные)
	st insert;			//!< статистика вставки
	st remove;			//!< статистика удаления
};

// value - значение
// p1,p2 - левая правая ветка
// red   - цвет (true - если красный)
struct node_st { node_st *p1, *p2; int value; bool red; }; // структура узла

														   // класс красно-черноое дерево
class RBTree {
private:
	node_st *tree_root;	//!< корень

						// внутрение функции 

	//! выделение новой вершины
	node_st *NewItem(int value);

	//! удаление вершины
	void DelItem(node_st *node);

	//! снос дерева (рекурсивная часть)
	void Clear(node_st *node);

	//! вывод дерева, рекурсивная часть
	//! \param node узел
	//! \param depth глубина
	//! \param dir   значёк
	//! \code Show(root,0,'*'); \endcode
	void Show(node_st *node, int depth, char dir);

	//! вращение влево
	//! \param index индеск вершины
	//! \result новая вершина дерева
	node_st *Rotate21(node_st *node);

	//! вращение вправо
	//! \param index индеск вершины
	//! \result новая вершина дерева
	node_st *Rotate12(node_st *node);

	//! балансировка вершины
	void BalanceInsert(node_st **root);

	bool BalanceRemove1(node_st **root);

	bool BalanceRemove2(node_st **root);

	//! рекурсивная часть вставки
	//! \result true если изменений небыло или балансировка в данной вершине не нужна
	bool Insert(int value, node_st **root);

	//! найти и убрать максимальный узел поддерева
	//! \param root корень дерева в котором надо найти элемент
	//! \retval res эелемент который был удалён
	//! \result true если нужен баланс
	bool GetMin(node_st **root, node_st **res);

	//! рекурсивная часть удаления
	//! \result true если нужен баланс
	bool Remove(node_st **root, int value);

	//проверки

	//! проверка дерева (рекурсивная часть)
	//! \param tree дерево
	//! \param b_d  текущая чёрная глубина
	//! \param d    текущая обычная глубина
	//! \param h    эталонная чёрная глубина
	//! \result 0 или код ошибки
	int Check(node_st *tree, int b_d, int d);

	//! обход дерева и сверка значений с массивом (рекурсивная часть)
	//! \param node  корень дерева
	//! \param array массив для сверки
	//! \param size  размер массива
	bool TreeWalk(node_st *node, bool *array, int size);

public:
	stat_st stat; //! статистика (можно удалить для ускорения процесса)

				  // внешние функции

	// конструктор
	RBTree() {
		tree_root = NULL;
	}

	//! обновление статистики вставки/удаления
	void UpdateStat(stat_st::st &item);

	//! вывод дерева
	void Show();

	//! функция вставки
	void Insert(int value);

	//! удаление узла
	void Remove(int value);

	//! снос дерева
	void Clear();

	//! проверка дерева
	int Check();

	//! обход дерева и сверка значений с массивом
	//! \param array массив для сверки
	//! \param size  размер массива
	bool TreeWalk(bool *array, int size);
};

#endif // RBTREE_H

