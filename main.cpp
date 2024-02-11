/**
    @file main.cpp 
    @brief test d'uso della classe set templata
**/

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include "set.hpp"

using std::cout;
using std::endl;
using std::vector;

struct equal_char {
    bool operator()(const char &p1, const char &p2) const {
        return (p1==p2);
    }
};

struct equal_int {
    bool operator()(int a, int b) const {
        return a==b;
    }
};

struct is_equal_to {
    int num;

    is_equal_to(int num) : num(num) {}

    bool operator()(int other) const {
        return num == other;
    }
};

struct is_bigger_than {
    int num;

    is_bigger_than(int num) : num(num) {}

    bool operator()(int other) const {
        return num < other;
    }
};

typedef set<int, equal_int> IntSet;

/**
  @brief Test Base
*/
void test_base(void) {
    cout << "!!!! TEST_BASE START" << endl;
    IntSet intSetTest1;
    IntSet intSetTest2(50);

    assert(intSetTest1.size() == 0);
    assert(intSetTest2.size() == 0);

    cout << "!! ADD" << endl;

    assert(intSetTest1.add(12));
    assert(intSetTest1.add(13));
    assert(intSetTest1.add(15));
    assert(intSetTest1.add(2));
    assert(!intSetTest1.add(12));

    cout << "SET AFTER ADD : " << intSetTest1 << endl;

    assert(intSetTest1.size() == 4);

    cout << "!! REMOVE" << endl;

    assert(intSetTest1.remove(12));
    assert(!intSetTest1.remove(12));
    assert(intSetTest1.remove(15));
    assert(!intSetTest1.remove(15));

    cout << "SET AFTER REMOVE : " << intSetTest1 << endl;

    assert(intSetTest1.size() == 2);

    cout << "!! OPERATOR[]" << endl;
    auto testVar1 = intSetTest1[0];
    auto testVar2 = intSetTest1[1];
    assert(testVar1 != -1);
    assert(testVar2 != -1);

    cout << "!! CONTAINS" << endl;
    assert(!intSetTest1.contains(12));
    assert(intSetTest1.contains(2));
    assert(intSetTest1.contains(13));
    assert(intSetTest1.contains(testVar1));
    assert(intSetTest1.contains(testVar2));

    cout << "!! CONST_ITERATOR" << endl;
    int index = 0;
    for (auto curr = intSetTest1.begin(); curr != intSetTest1.end(); ++curr) {
        assert(*curr == intSetTest1[index++]);
    }

    cout << "!!!! TEST_BASE SUCCESS!" << endl;
}

/**
  @brief Test Special Ctor
*/
void test_special_ctor(void) {
    cout << "!!!! TEST_SPECIAL_CTOR START" << endl;

    cout << "!! COPY CONSTRUCTOR" << endl;

    IntSet intSet(10);
    assert(intSet.add(12));
    assert(intSet.add(13));
    assert(intSet.add(15));
    assert(!intSet.add(12));

    IntSet intSet2(intSet);    

    cout << "SET1 : " << intSet << endl;
    cout << "SET2(Copia di SET1) : " << intSet2 << endl;
    
    assert(intSet == intSet2);
    intSet2.add(1);
    assert(intSet2.size() == 4);
    assert(!(intSet == intSet2));

    cout << "!! OPERATOR=" << endl;

    IntSet intSet3 = intSet2;
    intSet2 = intSet2;
    intSet3 = intSet3;

    cout << "SET1 : " << intSet2 << endl;
    cout << "SET2(Copia di SET1) : " << intSet3 << endl;

    assert(intSet2 == intSet3);
    intSet3.add(17);
    assert(intSet3.size() == 5);
    assert(!(intSet3 == intSet2));

    cout << "!! CTOR WITH ITERATOR" << endl;

    vector<int> vector1 {1,2,3,4,5,1,3,4,5,8,6,7,8,1};

    cout << "VECTOR : ";
    for (int i: vector1)
        cout << i << ' ';
    cout << endl;

    IntSet intSetIter(vector1.begin(), vector1.end());

    cout << "SET (BEGIN FINO A END) : " << intSetIter << endl;

    IntSet intSetIter2(vector1.begin() + 2, vector1.end() - 2);

    cout << "SET (BEGIN + 2 FINO A END - 2) : " << intSetIter << endl;

    IntSet intSetIter3(vector1.begin(), vector1.end());

    assert(!(intSetIter == intSetIter2));
    assert(intSetIter == intSetIter3);

    intSetIter.add(11);

    assert(!(intSetIter == intSetIter3));

    cout << "TEST SET DA INT A CHAR (BEGIN FINO A END)" << endl;

    vector<int> vector2 {50,70,55,77,88,66};

    set<char, equal_char> charSetIter(vector2.begin(), vector2.end());

    cout << "SET DA INT A CHAR (BEGIN FINO A END) : " << charSetIter << endl;

    assert(charSetIter.contains(50));
    assert(charSetIter.contains(70));
    assert(charSetIter.contains(55));
    assert(charSetIter.contains(77));
    assert(charSetIter.contains(88));
    assert(charSetIter.contains(66));

    vector<int> vector3 {'a','b','s','p','q','l'};

    IntSet intSetIter4(vector3.begin(), vector3.end());

    cout << "SET DA CHAR A INT (BEGIN FINO A END) : " << intSetIter4 << endl;

    assert(intSetIter4.contains('a'));
    assert(intSetIter4.contains('b'));
    assert(intSetIter4.contains('s'));
    assert(intSetIter4.contains('p'));
    assert(intSetIter4.contains('q'));
    assert(intSetIter4.contains('l'));

    cout << "!!!! TEST_SPECIAL_CTOR SUCCESS!" << endl;
}

/**
  @brief Global Operators
*/
void test_global_operators(void) {
    cout << "!!!! TEST_GLOBAL_OPERATORS START" << endl;

    IntSet setToFilter;

    setToFilter.add(0);
    setToFilter.add(1);
    setToFilter.add(2);
    setToFilter.add(3);
    setToFilter.add(4);

    cout << "SET : " << setToFilter << endl;

    cout << "!! FILTER OUT" << endl;

    auto testFilter = filter_out(setToFilter, is_equal_to(0));

    cout << "SET FILTERED (VALUE == 0) : " << testFilter << endl;

    assert(testFilter.size() == 1);
    assert(testFilter.contains(0));

    auto test2 = filter_out(setToFilter, is_bigger_than(1));

    cout << "SET FILTERED (VALUE > 1) : " << test2 << endl;

    assert(test2.size() == 3);
    assert(test2.contains(2));
    assert(test2.contains(3));
    assert(test2.contains(4));

    cout << "!! OPERATOR+" << endl;
    
    auto testSum = testFilter + test2;

    cout << "SET FILTERED (VALUE == 0) + SET FILTERED (VALUE > 1) : " << testSum << endl;

    assert(testSum.size() == 4);
    assert(testSum.contains(0));
    assert(testSum.contains(2));
    assert(testSum.contains(3));
    assert(testSum.contains(4));

    cout << "!! OPERATOR-" << endl;

    auto testMinus = setToFilter - test2;

    cout << "SET - SET FILTERED (VALUE > 1) : " << testMinus << endl;

    assert(testMinus.size() == 3);
    assert(testMinus.contains(2));
    assert(testMinus.contains(3));
    assert(testMinus.contains(4));

    cout << "!! OPERATOR + AND -" << endl;

    IntSet intSet(10);
    IntSet intSet2(10);

    intSet.add(1);
    intSet.add(2);
    intSet.add(3);
    intSet.add(4);

    intSet2.add(10);
    intSet2.add(20);
    intSet2.add(30);
    intSet2.add(40);

    vector<int> g1 {1,2,3,4,5,6,7,8,9,10,11,30};

    auto intSetIter = set<int, equal_int>(g1.begin(), g1.end());

    assert(intSetIter.size() == 12);

    cout << "SET1: " << intSet << endl;
    cout << "SET2: " << intSet2 << endl;
    cout << "SET3: " << intSetIter << endl;

    auto test = intSetIter - intSet + intSet2;

    cout << "SET = SET3 - SET1 + SET2: " << test << endl;

    assert(!test.contains(5));
    assert(!test.contains(6));
    assert(!test.contains(7));
    assert(!test.contains(8));
    assert(!test.contains(9));
    assert(!test.contains(11));

    auto bigTest2 = intSetIter + intSet2 - intSet;

    cout << "SET = SET3 + SET2 - SET1: " << bigTest2 << endl;

    assert(!bigTest2.contains(5));
    assert(!bigTest2.contains(6));
    assert(!bigTest2.contains(7));
    assert(!bigTest2.contains(8));
    assert(!bigTest2.contains(9));
    assert(!bigTest2.contains(11));

    cout << "!! SAVE" << endl;

    struct stringEqual
    {
        bool operator()(const std::string &str1, const std::string &str2) const {
            return str1 == str2;
        }
    };

    set<std::string, stringEqual> setToSave;

    setToSave.add(std::string("best"));
    setToSave.add(std::string("corso"));
    setToSave.add(std::string("è"));
    setToSave.add(std::string("c++"));
    setToSave.add(std::string("c++"));

    cout << "SET TO SAVE : " << setToSave << endl;

    save(setToSave, std::string("file.txt"));

    cout << "!!!! TEST_GLOBAL_OPERATORS SUCCESS!" << endl;
}

/**
  @brief Test Const Set
*/
void test_const_set(void) {
    cout << "!!!! TEST_CONST_SET START" << endl;

    IntSet intSet(10);
    assert(intSet.add(12));
    assert(intSet.add(13));
    assert(intSet.add(15));
    assert(!intSet.add(12));

    const IntSet set = filter_out(intSet, is_bigger_than(12));

    cout << "SET : " << set << endl;

    assert(set.size() == 2);
    assert(set.contains(13));
    assert(set.contains(15));
    assert(set == set);
    assert(set[0] != -1);
    
    const IntSet set2(set.begin(), set.end());

    cout << "SET2 : " << set2 << endl;

    const IntSet set3 = set2;
    const IntSet set4(set3);

    const IntSet set5 = set - set3 + set4 - set4;

    const is_equal_to predicate(13);

    auto testFilter = filter_out(set, predicate);

    cout << "SET FILTERED WITH CONST PREDICATE (VALUE == 13) : " << testFilter << endl;

    assert(testFilter.size() == 1);
    assert(testFilter.contains(13));

    cout << "!!!! TEST_CONST_SET SUCCESS!" << endl;
}

/**
  @brief Test Base Last
*/
void test_base_last(void) {
    cout << "!!!! TEST_BASE_LAST START" << endl;
    IntSet set;

    for (int i = 0; i < 100; i++) {
        set.add(i);
    }
    
    for (int i = 0; i < 100; i++) {
        set.remove(i);
    }

    IntSet set2;
    IntSet set3;
    IntSet set4(set3);

    set2 = set3;

    cout << "!!!! TEST_BASE_LAST SUCCESS!" << endl;
}

struct KeyValueIntObj {
    int key;
    int value;

    KeyValueIntObj(): key(0), value(0) {}

    KeyValueIntObj(int key, int value): key(key), value(value) {}
};


struct KeyValueIntObj_equal {
    bool operator()(const KeyValueIntObj &obj1, const KeyValueIntObj &obj2) const {
        return obj1.key == obj2.key && obj1.value == obj2.value;
    }
};

struct KeyValueIntObjPointer_equal {
    bool operator()(const KeyValueIntObj* obj1, const KeyValueIntObj* obj2) const {
        if (obj1 == nullptr || obj2 == nullptr)
            return false;
        return obj1->key == obj2->key && obj1->value == obj2->value;
    }
};

struct KeyValueIntObjKeyIs {
    int testKey;

    KeyValueIntObjKeyIs(int testKey): testKey(testKey) {}

    bool operator()(const KeyValueIntObj &obj) const {
        return obj.key == testKey;
    }
};


std::ostream &operator<<(std::ostream &os, const KeyValueIntObj &obj) {
    std::cout<<"("<<obj.key<<" : "<<obj.value<<")";
    return os;
}

struct complexObj {
    std::string _key;
    int _value;
    std::string _info;

    complexObj(): _key(std::string()), _value(0), _info(std::string()) {}

    complexObj(std::string key, int value, std::string info): _key(key), _value(value), _info(info) {}
};


struct complexObj_equal {
    bool operator()(const complexObj &obj1, const complexObj &obj2) const {
        return obj1._key == obj2._key && obj1._value == obj2._value && obj1._info == obj2._info;
    }
};

std::ostream &operator<<(std::ostream &os, const complexObj &obj) {
    std::cout<<"(" << obj._key << " : " << obj._value << " : " << obj._info << ")";
    return os;
}

typedef set<KeyValueIntObj, KeyValueIntObj_equal> SimpleObjSet;

/**
  @brief Test Objects Base
*/
void test_objects_base(void) {
    cout << "!!!! TEST_OBJECTS_BASE START" << endl;
    cout << "!! BASE_TEST" << endl;
    SimpleObjSet simpleSet, simpleSet2;

    assert(simpleSet.add(KeyValueIntObj(2, 1)));
    assert(!simpleSet.add(KeyValueIntObj(2, 1)));
    assert(!simpleSet.remove(KeyValueIntObj(2, 2)));
    assert(simpleSet.remove(KeyValueIntObj(2, 1)));
    assert(simpleSet.add(KeyValueIntObj(1, 2)));
    assert(simpleSet.add(KeyValueIntObj(1, 3)));
    assert(simpleSet.add(KeyValueIntObj(2, 4)));
    assert(simpleSet.add(KeyValueIntObj(2, 5)));
    assert(simpleSet.contains(KeyValueIntObj(2, 5)));
    auto eql = KeyValueIntObj_equal();
    int index = 0;
    for (auto curr = simpleSet.begin(); curr != simpleSet.end(); ++curr) {
        assert(eql(*curr, simpleSet[index++]));
    }
    
    cout << "Set : " << simpleSet << endl;

    cout << "!! FILTER_OUT" << endl;
    const SimpleObjSet filteredSet = filter_out(simpleSet, KeyValueIntObjKeyIs(2));
    const SimpleObjSet filteredSet2 = filter_out(filteredSet, KeyValueIntObjKeyIs(2));

    cout << "Filtered Set (Key == 2) : " << filteredSet << endl;

    assert(filteredSet.size() == 2);
    assert(filteredSet2.size() == 2);
    assert(!KeyValueIntObj_equal()(filteredSet[0], KeyValueIntObj()));
    assert(filteredSet.contains(KeyValueIntObj(2,4)));

    cout << "!! ITERATOR CTOR/COPY CTOR/OPERATOR=" << endl;
    const SimpleObjSet iteratorSet(filteredSet.begin() + 1, filteredSet.end());
    const SimpleObjSet iteratorSet2(filteredSet.begin() + 2, filteredSet.end());

    const SimpleObjSet iteratorSet3(iteratorSet);
    const SimpleObjSet iteratorSet4 = iteratorSet2;

    cout << "Set from iterator : " << iteratorSet << endl;

    index = 0;
    for (auto curr = filteredSet.begin() + 1; curr != filteredSet.end(); ++curr) {
        assert(eql(*curr, iteratorSet[index++]));
    }

    assert(iteratorSet == iteratorSet3);
    assert(iteratorSet2 == iteratorSet4);

    assert(iteratorSet.size() == 1);
    assert(iteratorSet2.size() == 0);

    cout << "!! OPERATOR-/+" << endl;
    const auto testminus = simpleSet - filteredSet;
    cout << "Set1  : " << simpleSet << endl;
    cout << "Set2  : " << filteredSet << endl;
    cout << "Set1 - Set2  : " << testminus << endl;

    for (auto curr = testminus.begin(); curr != testminus.end(); ++curr) {
        assert(simpleSet.contains(*curr) && filteredSet.contains(*curr));
    }

    const auto testsum = simpleSet + filteredSet;
    cout << "Set1 + Set2  : " << testsum << endl;

    for (auto curr = testsum.begin(); curr != testsum.end(); ++curr) {
        assert(simpleSet.contains(*curr) || filteredSet.contains(*curr));
    }

    cout << "!!!! TEST_OBJECTS_BASE SUCCESS!" << endl;
}

typedef set<KeyValueIntObj *, KeyValueIntObjPointer_equal> SimpleObjSetPointer;
typedef set<complexObj, complexObj_equal> ObjSet;

struct value_less_than {
    int less;

    value_less_than() : less(0) {}

    value_less_than(int value) : less(value) {}

    bool operator()(const complexObj &obj) const {
        return obj._value < less;
    }
};

struct info_equal_to {
    std::string value;

    info_equal_to() : value(std::string()) {}

    info_equal_to(std::string value) : value(value) {}

    bool operator()(const complexObj &obj) const {
        return obj._info == value;
    }
};

/**
  @brief Test Objects Complex
*/
void test_objects_complex(void) {
    cout << "!!!! TEST_OBJECTS_COMPLEX START" << endl;
    using std::string;
    ObjSet set;

    set.add(complexObj(string("c++"), 9, string("corso informatica")));
    set.add(complexObj(string("business inteligence"), 5, string("corso informatica")));
    set.add(complexObj(string("algoritmi e strutture dati"), 6, string("corso informatica")));
    set.add(complexObj(string("intelligenza artificiale"), 8, string("corso informatica")));
    set.add(complexObj(string("analisi e progetto di algoritmi"), 5, string("corso informatica")));
    set.add(complexObj(string("analisi 1"), 8, string("corso informatica")));
    set.add(complexObj(string("psicologia 1"), 5, string("corso psicologia")));
    set.add(complexObj(string("analisi dei comportamenti"), 9, string("corso psicologia")));
    set.add(complexObj(string("studio espressioni facciali"), 4, string("corso psicologia")));
    set.add(complexObj(string("psicoterapia 1"), 9, string("corso psicologia")));

    cout << "SET : " << set << endl;

    const auto filter = value_less_than(7);
    auto filtered = filter_out(set, filter);
    
    cout << "SET FILTERED : " << filtered << endl;

    for (auto curr = filtered.begin(); curr != filtered.end(); ++curr) {
        assert((*curr)._value < 7);
    }

    const auto filter2 = info_equal_to("corso psicologia");
    auto filtered2 = filter_out(set, filter2);
    
    cout << "SET FILTERED2 : " << filtered2 << endl;

    for (auto curr = filtered2.begin(); curr != filtered2.end(); ++curr) {
        assert((*curr)._info == "corso psicologia");
    }

    cout << "!! SET DI PUNTATORI A UN OGGETTO" << endl;
    SimpleObjSetPointer setPointer;
    auto var = new KeyValueIntObj(2, 1);
    auto var2 = new KeyValueIntObj(2, 1);
    assert(setPointer.add(nullptr));
    assert(setPointer.add(var));
    assert(!setPointer.add(var2));
    assert(setPointer.contains(var));

    delete var;
    delete var2;

    cout << "!!!! TEST_OBJECTS_COMPLEX SUCCESS!" << endl;
}

/**
  @brief Test Set Capacity
*/
void test_set_capacity(void) {
    cout << "!!!! TEST_SET_CAPACITY START" << endl;
    IntSet set;

    for (size_t i = 0; i < 10; i++) {
        cout << "SET Capacity After " << i << " add : " << set.capacity() << endl;

        set.add(i);
    }
    cout << "SET AFTER ADDS : " << set << endl;

    for (size_t i = 0; i < 10; i++) {
        cout << "SET Capacity After " << i << " remove : " << set.capacity() << endl;

        set.remove(i);
    }

    cout << "SET AFTER REMOVES : " << set << endl;

    cout << "!!!! TEST_SET_CAPACITY SUCCESS!" << endl;
}

int main() {

    test_base();

    test_special_ctor();

    test_global_operators();

    test_const_set();

    test_base_last();

    test_objects_base();

    test_objects_complex();

    test_set_capacity();

    return 0;
}