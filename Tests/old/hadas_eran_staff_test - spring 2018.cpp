#include <iostream>
#include <vector>
#include <cassert>
#include <list>
#include <map>
#include <vector>
#include <cstring>
#include <set>

#include "Stream.h"

template <typename T>
struct Cell {
	T value;
	
	Cell(const T value) : value(value) {}
	
	bool operator==(const Cell<T>& other) const {
		return other.value == value;
	}
	
	void print() {
		std::cout << "Cell: " << value << std::endl;
	}
};

template <typename T>
bool compareValues(std::vector<T*> vPointer, std::vector<T> v) {
	for(int i = 0 ; i < vPointer.size() ; i++){
		if(*vPointer[i] != v[i]){
			return false;
		}
	}
	return true;
}



//----------------------------STAFF-----------------------------------
void staff_test() {
	
	std::cout << "given Test...";

	int array[10] = { 1, 2, 3, 2, 4, 6, 5, 7, 8, 9 };
	std::vector<int*> vector;
	for(int i = 0 ; i < 10 ; i++) vector.push_back(array + i);
	
	assert(Stream<int>::of(vector).filter([](const int* val) {
		return *val != 2; } ).count() == 8);

	assert(Stream<int>::of(vector).distinct().count() == 9);
	
	std::vector<int> other = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	assert(compareValues(Stream<int>::of(vector).distinct().sorted().collect<std::vector<int*>>(), other));
	
	assert(Stream<int>::of(vector).map<Cell<int>>([](const int* a) { return new Cell<int>(*a); }).distinct().count() == 9);
	
	int initial = 0;
	assert(*Stream<int>::of(vector).reduce(&initial, [](const int* a, const int* b) { auto * c = new int; *c = *a + *b; return c; }) == 47);
	
	std::cout << "PASSED" << std::endl;

	
}



//-------------Hadas Orgad's Test-------------------


void super_duper_basic_test() {
	std::cout << "super_duper_basic_test...";
	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int *> vec2;
	for (int i = 0; i < 8; i++) {
		vec2.push_back(&vec[i]);
	}
	Stream<int> st = Stream<int>::of(vec2);
	auto filter_fun = [](const int *n) -> bool {
		return ((*n) % 2 == 0);
	};
	st = st.filter(filter_fun);
	std::vector<int *> res = st.collect<std::vector<int *>>();
	
	assert(res.size() == 4);
	for (int i = 0; i < 4; i++) {
		assert(*res[i] = (i + 1) * 2);
	}
	
	std::map<char, int *> mymap;
	mymap['a'] = &vec[0];
	mymap['b'] = &vec[1];
	mymap['c'] = &vec[2];
	mymap['d'] = &vec[3];
	auto res2 = Stream<int>::of(mymap).filter(filter_fun).collect<std::list<int *>>();
	for (int i = 0; i < 2; i++) {
		auto it = res2.begin();
		std::advance(it, i);
		assert(*(*it) = (i + 1) * 2);
	}
	
	auto res3 = Stream<int>::of(vec2).collect<std::vector<int *>>();
	for (int i = 0; i < 8; i++) {
		assert(res3[i] == &vec[i]);
	}
	
	std::cout << "PASSED" << std::endl;
}


void basic_filter_test() {
	std::cout << "basic_map_test...";
	std::vector<std::string> vec = {"hadas", "michael", "oop", "natan", "omer"};
	std::vector<std::string *> vec_ptr = {&vec[0], &vec[1], &vec[2], &vec[3], &vec[4]};
	
	auto fun = [](const std::string *s) -> bool {
		return s->size() > 4;
	};
	auto res = Stream<std::string>::of(vec_ptr).filter(fun).collect<std::vector<std::string *>>();
	
	assert(res.size() == 3);
	assert(res[0] == &vec[0]);
	assert(res[1] == &vec[1]);
	assert(res[2] == &vec[3]);
	
	std::cout << "PASSED" << std::endl;
}

void basic_map_test() {
	std::cout << "basic_map_test...";
	
	//same type map test
	std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6};
	std::vector<int *> vec_ptr;
	for (int i = 0; i < 7; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	auto fun = [](const int *n) -> int * {
		return new int((*n) * 2);
	};
	auto res = Stream<int>::of(vec_ptr).map<int>(fun).collect<std::vector<int *>>();
	
	assert(res.size() == 7);
	for (int i = 0; i < 7; i++) {
		assert(*res[i] == i * 2);
		delete res[i];
	}
	
	// different type
	auto fun2 = [](const int *n) -> char * {
		return new char('a');
	};
	
	auto res2 = Stream<int>::of(vec_ptr).map<char>(fun2).collect<std::vector<char *>>();
	assert(res2.size() == 7);
	for (int i = 0; i < 7; i++) {
		assert(*res2[i] == 'a');
		delete res2[i];
	}
	
	std::cout << "PASSED" << std::endl;
}

void basic_distinct_test() {
	std::cout << "basic_distinct_test...";
	std::vector<int> vec = {1, 2, 3, 4, 4, 1};
	std::vector<int *> vec_ptr;
	
	for (int i = 0; i < 6; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	auto fun = [](const int *n1, const int *n2) -> bool {
		return (((*n1) % 2) == ((*n2) % 2));
	};
	auto res = Stream<int>::of(vec_ptr).distinct(fun).collect<std::vector<int *>>();
	
	assert(res.size() == 2);
	assert(*res[0] == 1);
	assert(*res[1] == 2);
	
	auto res2 = Stream<int>::of(vec_ptr).distinct().collect<std::vector<int *>>();
	assert(res2.size() == 4);
	assert(*res2[0] == 1);
	assert(*res2[1] == 2);
	assert(*res2[2] == 3);
	assert(*res2[3] == 4);
	
	std::cout << "PASSED" << std::endl;
}

void basic_sorted_test() {
	std::cout << "basic_sorted_test...";
	std::vector<int> vec = {3, 2, 1, 4};
	std::vector<int *> vec_ptr;
	
	for (int i = 0; i < 4; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	auto res = Stream<int>::of(vec_ptr).sorted().collect<std::vector<int *>>();
	assert(res.size() == 4);
	assert(*res[0] == 1);
	assert(*res[1] == 2);
	assert(*res[2] == 3);
	assert(*res[3] == 4);
	
	std::cout << "PASSED" << std::endl;
}

void basic_forEach_test() {
	std::cout << "basic_forEach_test...";
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::vector<int *> vec_ptr;
	for (int i = 0; i < 5; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	std::vector<int *> *res = new std::vector<int *>();
	auto fun = [res](int *n) -> void {
		res->push_back(n);
	};
	
	Stream<int>::of(vec_ptr).forEach(fun);
	
	for (int i = 0; i < 5; i++) {
		assert((*res)[i] == vec_ptr[i]);
	}
	
	delete res;
	
	std::cout << "PASSED" << std::endl;
}

void basic_reduce_test() {
	std::cout << "basic_reduce_test...";
	std::vector<int> vec = {10, 20, 30, 40};
	std::vector<int *> vec_ptr;
	for (int i = 0; i < 4; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	int num = 0;
	std::function<int *(const int *, const int *)> fun = [](const int *n1, const int *n2) -> int * {
		return new int(*n1 + *n2);
	};
	int *res = Stream<int>::of(vec_ptr).reduce(&num, fun);
	assert(*res == 100);
	
	std::cout << "PASSED" << std::endl;
}

void basic_min_max_test() {
	std::cout << "basic_min_max_test...";
	std::vector<int> vec = {10, 20, 30, 40};
	std::vector<int *> vec_ptr;
	for (int i = 0; i < 4; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	assert(*(Stream<int>::of(vec_ptr).min()) == 10);
	assert(*(Stream<int>::of(vec_ptr).max()) == 40);
	
	std::cout << "PASSED" << std::endl;
}

void basic_count_test() {
	std::cout << "basic_count_test...";
	std::vector<int> vec = {10, 20, 30, 40};
	std::vector<int *> vec_ptr;
	for (int i = 0; i < 4; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	assert(Stream<int>::of(vec_ptr).count() == 4);
	
	std::cout << "PASSED" << std::endl;
	
}

void basic_anyMatch_allMatch_test() {
	std::cout << "basic_anyMatch_allMatch_test...";
	std::vector<int> vec = {10, 20, 30, 40};
	std::vector<int *> vec_ptr;
	for (int i = 0; i < 4; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	//all match
	std::function<bool(const int *)> fun1 = [](const int *n) -> bool {
		return (*n % 10 == 0);
	};
	bool res = Stream<int>::of(vec_ptr).allMatch(fun1);
	assert(res == true);
	
	
	std::function<bool(const int *)> fun2 = [](const int *n) -> bool {
		return (*n == 10 || *n == 20 || *n == 30);
	};
	res = Stream<int>::of(vec_ptr).allMatch(fun2);
	assert(res == false);
	
	//any match
	std::function<bool(const int *)> fun3 = [](const int *n) -> bool {
		return (*n == 20);
	};
	res = Stream<int>::of(vec_ptr).anyMatch(fun3);
	assert(res == true);
	
	std::function<bool(const int *)> fun4 = [](const int *n) -> bool {
		return (*n == 99);
	};
	res = Stream<int>::of(vec_ptr).anyMatch(fun4);
	assert(res == false);
	
	std::cout << "PASSED" << std::endl;
	
}

void basic_findFirst_test() {
	std::cout << "basic_findFirst_test...";
	std::vector<int> vec = {1, 2, 3, 4};
	std::vector<int *> vec_ptr;
	for (int i = 0; i < 4; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	auto fun = [](const int *n) -> bool {
		return ((*n) % 2 == 0);
	};
	
	int *num = Stream<int>::of(vec_ptr).findFirst(fun);
	assert(*num == 2);
	
	std::vector<std::string> vec2 = {"a", "bb", "ccc", "ddd"};
	std::vector<std::string *> vec_ptr2;
	for (int i = 0; i < 4; i++) {
		vec_ptr2.push_back(&vec2[i]);
	}
	auto fun2 = [](const std::string *s) -> bool {
		return (s->length() > 2);
	};
	auto fun3 = [](const std::string *s) -> bool {
		return (s->length() > 3);
	};
	
	std::string *str = Stream<std::string>::of(vec_ptr2).findFirst(fun2);
	assert(str == vec_ptr2[2]);
	str = Stream<std::string>::of(vec_ptr2).findFirst(fun3);
	assert(str == nullptr);
	
	std::cout << "PASSED" << std::endl;
	
	
}

void testSimpleMapCollection() {
	std::cout << "testSimpleMapCollection...";
	
	std::map<std::string, int *> mapCollection;
	int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	mapCollection.insert(std::pair<std::string, int *>("a", &values[1]));
	mapCollection.insert(std::pair<std::string, int *>("c", &values[3]));
	mapCollection.insert(std::pair<std::string, int *>("e", &values[5]));
	mapCollection.insert(std::pair<std::string, int *>("b", &values[2]));
	mapCollection.insert(std::pair<std::string, int *>("f", &values[6]));
	
	Stream<int> s = Stream<int>::of(mapCollection);
	std::set<int *> res = s.collect<std::set<int *>>(); //this line doesn't compile because set doesn't have push back
	assert(res.count(&values[1]) == 1);
	assert(res.count(&values[3]) == 1);
	assert(res.count(&values[5]) == 1);
	assert(res.count(&values[2]) == 1);
	assert(res.count(&values[6]) == 1);
	assert(res.size() == 5);
	
	std::cout << "PASSED" << std::endl;
}


void testCombinedOperations() {
	std::cout << "testCombinedOperations...";
	
	char *charArray = (char *) "bfzzzziadzzzzeczzghzz";
	std::vector<char *> values;
	for (int i = 0; i < strlen(charArray); i++) {
		values.push_back(charArray + i);
	}
	
	
	std::vector<char *> res = Stream<char>::of(values).sorted().distinct().sorted().collect<std::vector<char *>>();
	assert(res.size() == 10);
	assert(*res.at(0) == 'a');
	assert(*res.at(1) == 'b');
	assert(*res.at(2) == 'c');
	assert(*res.at(3) == 'd');
	assert(*res.at(4) == 'e');
	assert(*res.at(5) == 'f');
	assert(*res.at(6) == 'g');
	assert(*res.at(7) == 'h');
	assert(*res.at(8) == 'i');
	assert(*res.at(9) == 'z');
	
	res = Stream<char>::of(values).sorted().distinct().sorted().distinct().collect<std::vector<char *>>();
	assert(res.size() == 10);
	assert(*res.at(0) == 'a');
	assert(*res.at(1) == 'b');
	assert(*res.at(2) == 'c');
	assert(*res.at(3) == 'd');
	assert(*res.at(4) == 'e');
	assert(*res.at(5) == 'f');
	assert(*res.at(6) == 'g');
	assert(*res.at(7) == 'h');
	assert(*res.at(8) == 'i');
	assert(*res.at(9) == 'z');
	
	auto funToAscii = [](const char *ch) -> int * {
		char c = *ch;
		return new int((int) (c));
	};
	
	std::vector<int *> res2 = Stream<char>::of(values).map<int>(funToAscii).distinct().collect<std::vector<int *>>();
	int size = Stream<char>::of(values).map<int>(funToAscii).distinct().count();
	assert(size == 10);
	assert(res2.size() == 10);
	assert(*res2.at(0) == (int) 'b');
	assert(*res2.at(1) == (int) 'f');
	assert(*res2.at(2) == (int) 'z');
	assert(*res2.at(3) == (int) 'i');
	assert(*res2.at(4) == (int) 'a');
	assert(*res2.at(5) == (int) 'd');
	assert(*res2.at(6) == (int) 'e');
	assert(*res2.at(7) == (int) 'c');
	assert(*res2.at(8) == (int) 'g');
	assert(*res2.at(9) == (int) 'h');
	
	std::cout << "PASSED" << std::endl;
}

void test_laziness(){
	std::cout << "test_laziness...";
	
	auto fun = [](const int *n) -> bool {
		throw -1;
	};
	
	std::vector<int> vec = {10, 20, 30, 40};
	std::vector<int *> vec_ptr;
	for (int i = 0; i < 4; i++) {
		vec_ptr.push_back(&vec[i]);
	}
	
	auto st = Stream<int>::of(vec_ptr).filter(fun).filter(fun);
	bool flag = false;
	
	try{
		st.collect<std::vector<int *>>();
	}
	catch(int n){
		if (n == -1) flag = true;
	}
	
	assert(flag);
	
	
	std::cout << "PASSED" << std::endl;
}































//-------------Eran Flashin's Test-------------------

template<typename R,typename T>
class Pair{
private:
	R x;
	T y;
	
public:
	Pair(R x, T y):x(x),y(y){   };
	
	bool operator==(const Pair& pair) const{
		return (pair.x==x && pair.y==y);
	}
	
	bool operator<(const Pair &rhs) const {
		if (x < rhs.x)
			return true;
		if (rhs.x < x)
			return false;
		return y < rhs.y;
	}
	
	R getX() const {
		return x;
	}
	
	T getY() const {
		return y;
	}
	
};



class TestClass{
private:
	std::map<int,Pair<string,string>*> map;
	std::list<Pair<int,double>*> list;
	std::set<Pair<string,string>*> set;
	
public:
	TestClass(){
		map[1]=new Pair<string,string>("a","abc");
		map[2]=new Pair<string,string>("ab","aa");
		map[3]=new Pair<string,string>("cba","cab");
		map[4]=new Pair<string,string>("aaa","aa");
		map[5]=new Pair<string,string>("bb","aa");
		map[6]=new Pair<string,string>("ab","aa");
		map[7]=new Pair<string,string>("ab","aa");
		
		list.push_back(new Pair<int, double>(1,3.1));
		list.push_back(new Pair<int, double>(3,3));
		list.push_back(new Pair<int, double>(4,2.8));
		list.push_back(new Pair<int, double>(6,7.1));
		list.push_back(new Pair<int, double>(1,1));
		
		set.insert(new Pair<string,string>("1","1"));
		set.insert(new Pair<string,string>("4","3"));
		set.insert(new Pair<string,string>("3","3"));
		set.insert(new Pair<string,string>("34","345"));
		set.insert(new Pair<string,string>("50","2"));
	}
	
	void testCreation(){
		assert((Stream<Pair<string,string>>::of(map).count()) == 7);
		assert((Stream<Pair<int,double>>::of(list).count()) == 5);
		assert((Stream<Pair<string,string>>::of(set).count()) == 5);
		
		std::cout<<"creation...PASSED\n";
	}
	
	void testFilter(){
		assert((Stream<Pair<string,string>>::of(map).filter([](const Pair<string,string>* mem){return mem->getX()<mem->getY();}).count())==1);
		assert((Stream<Pair<int,double >>::of(list).filter([](const Pair<int,double>* mem){return mem->getX()+mem->getY()>5;}).count())==3);
		auto result=Stream<Pair<string,string>>::of(set).filter([](const Pair<string,string>* mem){return mem->getY()==mem->getX();}).collect<std::set<Pair<string,string>*>>();

		assert(result.size() == 2);

		std::cout<<"Filter...PASSED\n";

	}

	void testMap(){
		auto result=Stream<Pair<string,string>>::of(map).map<int>([](const Pair<string,string>* mem){ return new int(mem->getY().size());}).collect<std::list<int*>>();

		int arr[7]={3,2,3,2,2,2,2};

		int idx=0;
		for(auto& mem:result){
			assert(*mem==arr[idx]);
			idx++;
		}

		std::cout<<"Map...PASSED\n";
	}

	void testDistinct(){
		assert((Stream<Pair<string,string>>::of(map).distinct().count())==5);
		assert((Stream<Pair<int,double>>::of(list).distinct().count())==5);
		assert((Stream<Pair<string,string>>::of(set).distinct([](const Pair<string,string> *t,const Pair<string,string>* h){return t->getX()>t->getY() && h->getX()>h->getY();})).count()==4);

		std::cout<<"Distinct...PASSED\n";
	}

	void testSorted(){
		auto result1=Stream<Pair<int,double>>::of(list).sorted().collect<std::vector<Pair<int,double>*>>();
		auto result2=Stream<Pair<string,string>>::of(set).sorted([](const Pair<string,string> *t,const Pair<string,string>* h){ return t->getX().size()+t->getY().size()<h->getY().size()+h->getX().size() ;}).collect<std::vector<Pair<string,string>*>>();

		double arr[5]={1,3.1,3,2.8,7.1};

		int idx=0;
		for(auto& mem : result1){
			assert(mem->getY()==arr[idx]);
			idx++;
		}

		string arr2[]={"1","4","3","50","34"};

		idx=0;

		for(auto& mem : result2){
			assert(mem->getX()==arr2[idx]);
			idx++;
		}

		std::cout<<"Sorted...PASSED\n";
	}

	void testForEach(){
		double sum=0;
		Stream<Pair<int,double>>::of(list).forEach([&sum](const Pair<int,double>* t){sum+=t->getY()+t->getX();});

		assert(sum == 32);

		std::cout<<"forEach...PASSED\n";
	}

	void testReduce(){
		Pair<int,double> sum(0,0);
		auto result=Stream<Pair<int,double>>::of(list).
		reduce(&sum,[](const Pair<int,double>* t1,const Pair<int, double>* t2){ return new Pair<int,double>(t1->getX()+t2->getX(),t1->getY()+t2->getY());});

		assert(result->getY()+result->getX()==32);

		std::cout<<"reduce...PASSED\n";

	}

	void testMin(){
		auto result=Stream<Pair<int,double>>::of(list).min();

		assert(result->getX()==1 && result->getY()==1);

		auto result1=Stream<Pair<string,string>>::of(set).min();

		assert(result1->getX()=="1" && result1->getY()=="1");

		std::cout<<"min...PASSED\n";

	}

	void testMax(){
		auto result=Stream<Pair<int,double>>::of(list).max();

		assert(result->getX()==6 && result->getY()==7.1);

		auto result1=Stream<Pair<string,string>>::of(map).max();

		assert(result1->getX()=="cba" && result1->getY()=="cab");

		std::cout<<"max...PASSED\n";

	}

	void testAllMatch(){
		assert((Stream<Pair<int,double>>::of(list).allMatch([](const Pair<int,double>* t){ return t->getY() < 10 && t->getX() < 10;})));

		assert(!(Stream<Pair<int,double>>::of(list).allMatch([](const Pair<int,double>* t){ return t->getY() <= 3 && t->getX() < 10;})));

		assert((Stream<Pair<string,string>>::of(map).allMatch([](const Pair<string,string>* t){ return t->getX().length()<5;})));

		std::cout<<"allMatch...PASSED\n";

	}

	void testAnyMatch(){
		assert((Stream<Pair<int,double>>::of(list).anyMatch([](const Pair<int,double>* t){ return t->getY() < 4 && t->getX() < 4;})));

		assert(!(Stream<Pair<int,double>>::of(list).allMatch([](const Pair<int,double>* t){ return t->getX() + t->getY() == 100;})));

		assert(!(Stream<Pair<string,string>>::of(map).allMatch([](const Pair<string,string>* t){ return t->getY().length()==1;})));


		std::cout<<"anyMatch...PASSED\n";

	}

	void testFindFirst(){
		auto result1=Stream<Pair<string,string>>::of(map).findFirst([](const Pair<string,string>* t){ return t->getY()=="cab";});
		auto result2=Stream<Pair<string,string>>::of(map).findFirst([](const Pair<string,string>* t){ return t->getY()=="bac";});


		assert(result1 != nullptr && result1->getX()=="cba");

		assert(result2== nullptr);

		auto result3=Stream<Pair<string,string>>::of(set).findFirst([](const Pair<string,string>* t){ return t->getX()<t->getY();});

		assert(result3->getX()=="34");

		std::cout<<"findFirst...PASSED\n";
	}

	void testMixed(){
		auto result=Stream<Pair<string,string>>::of(map).map<Pair<char,char>>([](const Pair<string,string>* t){ return new Pair<char,char>(t->getX().at(0),t->getY().at(0));})
		.filter([](const Pair<char, char>* t){ return t->getY()==t->getX();}).distinct();

		assert(result.count()==2);
		assert(result.max()->getX()=='c');
		assert(result.min()->getY()=='a');
		assert(result.allMatch([](const Pair<char,char>* t){return t->getY()==t->getX();}));

		auto container=result.map<char>([](const Pair<char,char>* t){ return new char(t->getX());}).collect<std::vector<char*>>();

		assert(container.size()==2 && *container.at(0)=='a' && *container.at(1)=='c');


	};

	
	
};














int main() {
	std::cout << "-----------------Staff's Test---------------------" << std::endl;

	staff_test();
	
	std::cout << "-------------Hadas Orgad's Test-------------------" << std::endl;

	super_duper_basic_test();
	basic_filter_test();
	basic_map_test();
	basic_distinct_test();
	basic_sorted_test();
	basic_forEach_test();
	basic_reduce_test();
	basic_min_max_test();
	basic_count_test();
	basic_anyMatch_allMatch_test();
	basic_findFirst_test();
	testSimpleMapCollection();
	testCombinedOperations();
	test_laziness();
	
	
	
	std::cout << "-------------Eran Flashin's Test-------------------" << std::endl;
	TestClass test;
	test.testCreation();
	test.testFilter();
	test.testMap();
	test.testDistinct();
	test.testSorted();
	test.testForEach();
	test.testReduce();
	test.testMin();
	test.testMax();
	test.testAllMatch();
	test.testAnyMatch();
	test.testFindFirst();
	test.testMixed();
	
	
	
	
}

