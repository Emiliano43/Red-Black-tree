#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Progr1/RBtree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		RBtree<int, char> map;
	public:
		TEST_METHOD_INITIALIZE(init)
		{
			map.insert(1, 'a');
			map.insert(2, 'b');
			map.insert(3, 'c');
		}
		TEST_METHOD(test_insert)
		{
			map.insert(4, 'd');
			Assert::AreEqual('d', map.find(4));
			try {
				map.insert(1, 'b');
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "This element is already in the map");
			}
		}
		TEST_METHOD(test_remove) {
			map.remove(1);
			try {
				map.find(1);

			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "This element isn't in the map");
			}
			map.clear();
			try {
				map.remove(1);
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "Map is empty");
			}
		}
		TEST_METHOD(test_find) { 
			Assert::AreEqual(map.find(1), 'a'); 
			try { 
				map.find(4);
			} 
			catch (invalid_argument e) { 
				Assert::AreEqual(e.what(), "This element isn't in the map"); 
			} 
		} 
		TEST_METHOD(test_clear) { 
			Assert::AreEqual(map.find(1), 'a'); 
			map.clear(); 
			try { 
				map.find(1); 
			} 
			catch (invalid_argument e) { 
				Assert::AreEqual(e.what(), "Map is empty"); 
			}
		}
		TEST_METHOD(test_print) {
			map.clear();
			try {
				map.print();
			}
			catch (runtime_error e) {
				Assert::AreEqual(e.what(), "Map is empty");
			}
		}
	};
}