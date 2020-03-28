#include "Rbtree.h"
#include <iostream>
int main()
{
	RBtree<int, char> map;
	map.insert(1, 'a');
	map.insert(2, 'b');
	map.insert(3, 'c');
	map.insert(4, 'd');
	map.insert(5, 'e');
	map.insert(6, 'f');
	map.insert(7, 'g');
	map.insert(8, 'h');
	map.insert(9, 'i');
	map.remove(5);
	map.remove(7);
	List<int> keys = map.get_keys();
	List<char> values = map.get_values();
	map.print();
	keys.print_to_console();
	values.print_to_console();
	system("pause");
	return 0;
}