#pragma once
#include <iostream>
#include <vector>

class Heap
{
private:
	std::vector<int> heap;
	size_t d;	//параметр кучи
	size_t size;	//количество элементов в куче на данный момент

public:
	Heap(size_t _d) { d = _d; size = 0; }
	Heap(const Heap& to_copy) {
		heap = to_copy.heap;
		d = to_copy.d;
		size = to_copy.size;
	}
	~Heap() {}
	/*
	//

	*/
	size_t leftChild(size_t i) {	//поиск левого ребёнка у элемента с индексом i в векторе
		size_t leftch = d * i + 1;
		if (leftch <= size - 1) return leftch;
		else return 0;		//значит левого ребёнка нет
	}
	size_t rightChild(size_t i) {	//поиск правого ребёнка
		size_t rightch = d * i + d;
		if (rightch <= size - 1) return rightch;
		else if (leftChild(i))	return (size - 1);	//если например у 3-кучи есть левый и средний дети, но нет левого, то правым ребёнком будет считаться средний. Когда будем просматриваться всех детей, нельзя им пренебречь
		else return 0;	//значит у дерева нет ни одного потомка, то возращаем ноль
	}
	size_t parent(size_t i) { //поиск родителя у элемента с индексом i
		if (i > 0) return ((i - 1) / d);
		else return 0;
	}
	size_t minChild(size_t i) {	//поиск минимального ребёнка у родителя с индексом i
		size_t left = leftChild(i), right = rightChild(i);
		if (left == 0) return 0;	//значит детей у элемента нет. Проверка на правого ребёнка не нужна 

		int ind_of_min = left, min = heap[left];	//дошли до сюда - значит, левый точно существует
		for (int i = left + 1; i <= right; i++)	//начинаем проверять со следующего индекса после left (т.к. приняли left за минимальный изначально)
			if (heap[i] < min)
			{
				min = heap[i];
				ind_of_min = i;
			}
		return ind_of_min;
	}

	void diving(size_t i) {	//погружение
		size_t j1 = i, j2 = minChild(i);
		while (j2 != 0 && heap[j1] > heap[j2]) {	//меняем два элемента местами, пока не установится порядок
			int tmp = heap[j1];
			heap[j1] = heap[j2];
			heap[j2] = tmp;
			j1 = j2;
			j2 = minChild(j1);
		}
	}
	void emersion(size_t i)	//всплытие элемента - обратная операция
	{
		size_t j1, j2;
		j1 = i;
		j2 = parent(i);
		while (j2 != 0 && heap[j1] < heap[j2]) {	//аналогичный алгоритм - меняем два элемента местами
			int tmp = heap[j1];
			heap[j1] = heap[j2];
			heap[j2] = tmp;
			j1 = j2;
			j2 = parent(j1);
		}
	}
	void insert(int k) {	//вставка элемента вела k
		heap.push_back(k);	//вставили в конец, теперь нужно сделать всплытие
		emersion(heap.size() - 1);	//для элемента с таким индексом
		size++;
	}
	int getMin() {
		if (size) return heap[0];
		else throw "Heap is empty";
	}
	void deleteMin() {	//удаление корневого узла
		heap[0] = heap[size - 1];	//последний элемент теперь наверху. Минимального элемента больше нет
		heap.pop_back();
		diving(0);	//теперь его нужно опустить вниз
		size--;
	}
	void decreaseWeight(size_t i, int delta) {	//изменение веса узла i на delta
		heap[i] -= delta;
		emersion(i);	//вес изменился. Возможно, теперь изменится и порядок элементов
	}
	void deleteElem(int i) {	//удаление узла i
		decreaseWeight(i, -10e10);
		deleteMin();
	}
	void makeHeap() {
		for (size_t i = size - 1; i >= 0; i--)
			diving(i);
	}
	void heapSort() {	//сортировка кучей
		std::vector<int> sort_heap;
		size_t sort_size = size;
		for (int i = 0; i < sort_size; i++)
		{
			sort_heap.push_back(heap[0]);
			deleteMin();
		}
		heap = sort_heap;
		size = sort_size;
	}

	//на основе этих операций может быть написан ещё один конструктор копирования...
};
