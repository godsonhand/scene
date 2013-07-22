// AOI.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "scene.h"
#include "SceneMgr.H"
#include <iostream>
using namespace std;

int main() {
	/*
	int i = 0;
	Scene scene;

	srand(time(NULL));
	printf("\nbegin add object=============\n");
	for (i = 0; i < 10; ++i) {
		scene.Add(i + 1, rand() % 50, rand() % 50);
	}

	printf("\nbegin move object=============\n");
	for (i = 0; i < 100; ++i) {
		int x = rand() % 50;
		int y = rand() % 50;
		scene.Move(i % 10, x, y);
	}

	printf("\nbegin leave object=============\n");
	for (i = 0; i < 10; ++i) {
		scene.Leave(i + 1);
	}
	*/

//  	Scene scene;
//  	scene.Add(1, 1, 2, 2);
//  	scene.Add(2, 4, 5, 2);
//  	scene.Add(3, 2, 3, 2);
//  	scene.Add(4, 4, 6, 2);
//  	scene.Add(5, 1, 3, 2);

 	cout << "###############我是分隔线################" << endl;
  	SceneMgr mgr;
  	mgr.Enter(1, 1, 2, 2);
  	mgr.Enter(2, 4, 5, 2);
  	mgr.Enter(3, 2, 3, 2);
  	mgr.Enter(4, 4, 6, 2);
  	mgr.Enter(5, 1, 3, 2);
 	cout << "###############我是分隔线################" << endl;
 	mgr.Moving(3, 1, 3);
 	cout << "###############我是分隔线################" << endl;
 	mgr.Leave(3);
 	mgr.Leave(1);
 	mgr.Leave(5);
 	mgr.Leave(4);
 	mgr.Leave(2);
 	cout << "###############我是分隔线################" << endl;
 	mgr.printXList();
 	cout << "###############我是分隔线################" << endl;
 	mgr.printYList();

// 	int i = 0;
// 	SceneMgr scene;
// 
// 	clock_t start = clock();
// 	srand(time(NULL));
// 	printf("\nbegin add object=============\n");
// 	for (i = 0; i < 1000; ++i) {
// 		scene.Enter(i + 1, rand() % 500, rand() % 500, 50);
// 	}
// 	double elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
// 	cout << "Elapsed time: " << elapsedTime << endl;
// 
// 	start = clock();
// 	printf("\nbegin move object=============\n");
// 	for (i = 0; i < 1000; ++i) {
// 		int x = rand() % 500;
// 		int y = rand() % 500;
// 		scene.Moving(i % 1000 + 1, x, y);
// 	}
// 	elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
// 	cout << "Elapsed time: " << elapsedTime << endl;
// 
// 	start = clock();
// 	printf("\nbegin leave object=============\n");
// 	for (i = 0; i < 1000; ++i) {
// 		scene.Leave(i + 1);
// 	}
// 	elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
// 	cout << "Elapsed time: " << elapsedTime << endl;

	//list usage test
//  	list<int> lst;
//  	lst.push_back(10);
//  	lst.push_back(20);
//  	lst.push_back(30);
//  	lst.push_back(40);
//  	list<int>::iterator iter = lst.end();
//  	for(list<int>::iterator iter2 = lst.begin(); iter2 != lst.end(); ++iter2)
//  	{
//  		if(*iter2 == 35)
//  		{
//  			iter = iter2;
//  			break;
//  		}
//  	}
//  
//  	iter = lst.insert(iter, 35);
//  	for(list<int>::iterator iter2 = lst.begin(); iter2 != lst.end(); ++iter2)
//  	{
//  		cout << *iter2 << endl;
//  	}

	//cout << *(lst.end()--) << endl; //wrong

	system("pause");
	return 0;
}
