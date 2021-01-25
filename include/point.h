#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <initializer_list>
#include <stdlib.h>

using namespace std;

#define CordType char

#define ATTR(ATTRTYPE, point) ((ATTRTYPE*)(point->attr))
#define PSETATTR(point, ATTR) point->attr = (void*)(ATTR)
#define SETATTR(point, ATTR) point.attr = (void*)(ATTR)

#define SETATTRINT(point, val) (point->attr = (void*)val)
#define ATTRINT(point) ((unsigned long)point->attr)

template <class T>
struct Point{
	T *cord{NULL};
	void *attr{NULL};
	Point(int num = 0, bool randcord = true, int val = 1){
		if(num <= 0) cord = NULL;
		else{
			cord = new T[num];
			if(randcord){
				for(int i = 0; i < num; i++) cord[i] = rand() % val;
			}
			else{
				for(int i = 0; i < num; i++) cord[i] = val;
			}
		}
		attr = NULL;
	}
	Point(initializer_list<T> l){
		if(l.size() <= 0) cord = NULL;
		else{
			T *p;
			cord = new T[l.size()];
			p = cord;
			for(auto val : l) *p++ = val;
		}
		attr = NULL;
	}
	~Point(){
		if(cord != NULL) delete cord;
	}

	void print(int num, char symbol = '\n'){
		cout << "< ";
		for(int i = 0; i < num; i++){       
	    	cout << (int)cord[i] << " ";
		}
	 	cout << ">" << symbol;
	}
	template < class C >
	void print(C& points, int num, int colspan = 5, char symbol = '\n'){
		int i = 0;
		cout << "--------------------start---------------------" << endl;
		for(auto p : points){
			p->print(num, symbol);
			i++;
			if(i % colspan == 0){
				i = 0;
				cout << endl;
			}
		}
		cout << "\n---------------------end----------------------" << endl;
	}

};


#endif // POINT_H
