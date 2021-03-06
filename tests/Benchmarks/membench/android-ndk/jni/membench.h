/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
 * membench.h
 *
 *  Created on: 13 jul 2011
 *      Author: Alex
 */

#ifndef MEMBENCH_H_
#define MEMBENCH_H_

#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib> //give access to rand()
#include <time.h>
#include <jni.h>

#define ALOT 1024 //used as number of iterations when we want to do a lot of operations
#define	RUNNING_TIME 1.0f //running time per test in msecs

// Pointers to the java environment and object
static JNIEnv  *glob_env;
static jobject *glob_obj;

/* Test types */
#define MAUTIL_STRING 0
#define MALLOC 1
#define ARRAY 2
#define VECTOR_ADD 3
#define VECTOR_ACCESS 4
#define DUMMY 5
#define DUMMY_MIX 6
#define DUMMY_STRUCT 7
#define DUMMY_ACCESS 8
#define DUMMY_MIX_ACCESS 9
#define DUMMY_STRUCT_ACCESS 10

struct DummyStruct {
	int a;
	int b;
	int c;
};

class DummyObject {
public:
	int a;
	int b;
	int c;
};

class DummyObjectMix {
public:
	inline int getA(){return a;};
	inline int getB(){return b;};
	inline int getC(){return c;};
	inline float getD(){return d;};
	inline float getE(){return e;};
	inline float getF(){return f;};
	inline float getG(){return g;};

	inline std::vector<std::string> & getStrVec(){return str_vec;};
	inline std::string & getStr(){return str;};

	int a;
	int b;
	int c;
	float d;
	float e;
	float f;
	float g;
	std::vector<std::string> str_vec;
	std::string str;

};

class MemBench {
public:
	MemBench();
	~MemBench();

	/* start benching! */
	void bench();

private:

	float heapBench(int numRuns, int size, int testType);
	float memAccess(int numRuns, int size, int testType);

	/* Timer functions */
	float currTime();

	/* member variables */
	char *mArray;
	std::vector<int> mVector;
	DummyObject mDo;
	DummyObjectMix mDom;
	DummyStruct mDs;

};



#endif /* MEMBENCH_H_ */
