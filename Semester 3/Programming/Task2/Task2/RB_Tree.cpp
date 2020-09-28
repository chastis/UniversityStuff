#include "RB_Tree.h"
#include<stdio.h>
#include<stdlib.h>

//! выделение новой вершины
node_st * RBTree::NewItem(int value)
{
	stat.nodes_count++;
	node_st *node = new node_st;
	node->value = value;
	node->p1 = node->p2 = 0;
	node->red = true;
	return node;
}

//! удаление вершины
void RBTree::DelItem(node_st *node)
{
	stat.nodes_count--;
	delete node;
}

//! снос дерева (рекурсивная часть)
void RBTree::Clear(node_st *node)
{
	if (!node) return;
	Clear(node->p1);
	Clear(node->p2);
	DelItem(node);
}

//! вывод дерева, рекурсивная часть
//! \param node узел
//! \param depth глубина
//! \param dir   значёк
//! \code Show(root,0,'*'); \endcode
void RBTree::Show(node_st *node, int depth, char dir)
{
	int n;
	if (!node) return;
	for (n = 0; n<depth; n++) putchar(' ');
	printf("%c[%d] (%s)\n", dir, node->value, node->red ? "red" : "black");
	Show(node->p1, depth + 2, '-');
	Show(node->p2, depth + 2, '+');
}


//! вращение влево
//! \param index индеск вершины
//! \result новая вершина дерева
node_st * RBTree::Rotate21(node_st *node)
{
	stat.turn_count++;
	node_st *p2 = node->p2;
	node_st *p21 = p2->p1;
	p2->p1 = node;
	node->p2 = p21;
	return p2;
}

//! вращение вправо
//! \param index индеск вершины
//! \result новая вершина дерева
node_st * RBTree::Rotate12(node_st *node)
{
	stat.turn_count++;
	node_st *p1 = node->p1;
	node_st *p12 = p1->p2;
	p1->p2 = node;
	node->p1 = p12;
	return p1;
}

//! балансировка вершины
void RBTree::BalanceInsert(node_st **root)
{
	node_st *p1, *p2, *px1, *px2;
	node_st *node = *root;
	if (node->red) return;
	p1 = node->p1;
	p2 = node->p2;
	if (p1 && p1->red) {
		px2 = p1->p2;				// задача найти две рядом стоящие крастне вершины
		if (px2 && px2->red) p1 = node->p1 = Rotate21(p1);
		px1 = p1->p1;
		if (px1 && px1->red) {
			node->red = true;
			p1->red = false;
			if (p2 && p2->red) {	// отделаемся перекраской вершин
				px1->red = true;
				p2->red = false;
				return;
			}
			*root = Rotate12(node);
			//return;
		}
	}
	// тоже самое в другую сторону
	if (p2 && p2->red) {
		px1 = p2->p1;				// задача найти две рядом стоящие крастне вершины
		if (px1 && px1->red) p2 = node->p2 = Rotate12(p2);
		px2 = p2->p2;
		if (px2 && px2->red) {
			node->red = true;
			p2->red = false;
			if (p1 && p1->red) {	// отделаемся перекраской вершин
				px2->red = true;
				p1->red = false;
				return;
			}
			*root = Rotate21(node);
			//return;
		}
	}
}

bool RBTree::BalanceRemove1(node_st **root)
{
	node_st *node = *root;
	node_st *p1 = node->p1;
	node_st *p2 = node->p2;
	if (p1 && p1->red) {
		p1->red = false; return false;
	}
	if (p2 && p2->red) { // случай 1
		node->red = true;
		p2->red = false;
		node = *root = Rotate21(node);
		if (BalanceRemove1(&node->p1)) node->p1->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st *p21 = p2->p1;
	node_st *p22 = p2->p2;
	if (p21 && p21->red) mask |= 1;
	if (p22 && p22->red) mask |= 2;
	switch (mask)
	{
	case 0:		// случай 2 - if((!p21 || !p21->red) && (!p22 || !p22->red))
		p2->red = true;
		return true;
	case 1:
	case 3:		// случай 3 - if(p21 && p21->red)
		p2->red = true;
		p21->red = false;
		p2 = node->p2 = Rotate12(p2);
		p22 = p2->p2;
	case 2:		// случай 4 - if(p22 && p22->red)
		p2->red = node->red;
		p22->red = node->red = false;
		*root = Rotate21(node);
	}
	return false;
}

bool RBTree::BalanceRemove2(node_st **root)
{
	node_st *node = *root;
	node_st *p1 = node->p1;
	node_st *p2 = node->p2;
	if (p2 && p2->red) { p2->red = false; return false; }
	if (p1 && p1->red) { // случай 1
		node->red = true;
		p1->red = false;
		node = *root = Rotate12(node);
		if (BalanceRemove2(&node->p2)) node->p2->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st *p11 = p1->p1;
	node_st *p12 = p1->p2;
	if (p11 && p11->red) mask |= 1;
	if (p12 && p12->red) mask |= 2;
	switch (mask) {
	case 0:		// случай 2 - if((!p12 || !p12->red) && (!p11 || !p11->red))
		p1->red = true;
		return true;
	case 2:
	case 3:		// случай 3 - if(p12 && p12->red)
		p1->red = true;
		p12->red = false;
		p1 = node->p1 = Rotate21(p1);
		p11 = p1->p1;
	case 1:		// случай 4 - if(p11 && p11->red)
		p1->red = node->red;
		p11->red = node->red = false;
		*root = Rotate12(node);
	}
	return false;
}

//! рекурсивная часть вставки
//! \result true если изменений небыло или балансировка в данной вершине не нужна
bool RBTree::Insert(int value, node_st **root)
{
	node_st *node = *root;
	if (!node) *root = NewItem(value);
	else {
		if (value == node->value) return true;
		if (Insert(value, value<node->value ? &node->p1 : &node->p2)) return true;
		BalanceInsert(root);
	}
	return false;
}

//! найти и убрать максимальный узел поддерева
//! \param root корень дерева в котором надо найти элемент
//! \retval res эелемент который был удалён
//! \result true если нужен баланс
bool RBTree::GetMin(node_st **root, node_st **res)
{
	node_st *node = *root;
	if (node->p1) {
		if (GetMin(&node->p1, res)) return BalanceRemove1(root);
	}
	else {
		*root = node->p2;
		*res = node;
		return !node->red;
	}
	return false;
}

//! рекурсивная часть удаления
//! \result true если нужен баланс
bool RBTree::Remove(node_st **root, int value)
{
	node_st *t, *node = *root;
	if (!node) return false;
	if (node->value<value) {
		if (Remove(&node->p2, value))	return BalanceRemove2(root);
	}
	else if (node->value>value) {
		if (Remove(&node->p1, value))	return BalanceRemove1(root);
	}
	else {
		bool res;
		if (!node->p2) {
			*root = node->p1;
			res = !node->red;
			DelItem(node);
			return res;
		}
		res = GetMin(&node->p2, root);
		t = *root;
		t->red = node->red;
		t->p1 = node->p1;
		t->p2 = node->p2;
		DelItem(node);
		if (res) res = BalanceRemove2(root);
		return res;
	}
	return 0;
}

//===== внешние функции =========================================

//! обновление статистики вставки/удаления
void RBTree::UpdateStat(stat_st::st &item)
{
	if (item.max_count<stat.turn_count) item.max_count = stat.turn_count;
	item.sum_count += stat.turn_count; item.sum_divider++;
}

//! вывод дерева
void RBTree::Show()
{
	printf("[tree]\n");
	Show(tree_root, 0, '*');
}

//! функция вставки
void RBTree::Insert(int value)
{
	stat.turn_count = 0;
	Insert(value, &tree_root);
	if (tree_root) tree_root->red = false;
	UpdateStat(stat.insert);
}

//! удаление узла
void RBTree::Remove(int value)
{
	stat.turn_count = 0;
	Remove(&tree_root, value);
	UpdateStat(stat.remove);
}

//! снос дерева
void RBTree::Clear()
{
	Clear(tree_root);
	tree_root = 0;
}


// проверки

//! проверка дерева (рекурсивная часть)
//! \param tree дерево
//! \param b_d  текущая чёрная глубина
//! \param d    текущая обычная глубина
//! \param h    эталонная чёрная глубина
//! \result 0 или код ошибки
int RBTree::Check(node_st *tree, int b_d, int d)
{
	int n;
	if (!tree) {
		// количество чёрных вершин на любом пути одинаковое
		if (stat.max_depth<d) stat.max_depth = d;
		if (stat.black_depth<0) stat.black_depth = b_d;
		return stat.black_depth == b_d ? 0 : ERROR_BALANCE;
	}
	node_st *p1 = tree->p1;
	node_st *p2 = tree->p2;
	// красная вершина должна иметь чёрных потомков
	if (tree->red && (p1 && p1->red || p2 && p2->red)) return ERROR_STRUCT;
	if (p1 && tree->value<p1->value || p2 && tree->value>p2->value) return ERROR_STRUCT;
	if (!tree->red) b_d++;
	n = Check(p1, b_d, d + 1); if (n) return n;
	return Check(p2, b_d, d + 1);
}

//! проверка дерева
int RBTree::Check()
{
	int d = 0;
	stat.black_depth = -1;
	if (!tree_root) return 0;
	if (tree_root->red) return ERROR_STRUCT;
	return Check(tree_root, d, 0);
}

//! обход дерева и сверка значений с массивом (рекурсивная часть)
//! \param node  корень дерева
//! \param array массив для сверки
//! \param size  размер массива
bool RBTree::TreeWalk(node_st *node, bool *array, int size)
{
	if (!node) return false;
	int value = node->value;
	if (value<0 || value >= size || !array[value]) return true;
	array[value] = false;
	return TreeWalk(node->p1, array, size) || TreeWalk(node->p2, array, size);
}

//! обход дерева и сверка значений с массивом
//! \param array массив для сверки
//! \param size  размер массива
bool RBTree::TreeWalk(bool *array, int size)
{
	if (TreeWalk(tree_root, array, size)) return true;
	for (int n = 0; n<size; n++) if (array[n]) return true;
	return false;
}
