#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <vector>
#include <iostream>

#include "Stopwatch.h"

#include <windows.h>

#include <random>
#include <map>

#include <windows.h>

#define  OUT(x)  cout << x << endl

//Must Not Use In NEW ARRAY!!!
#define  LEN(x)  (sizeof(x)/sizeof(x[0]))

#define OutArray(x,loop)  for (size_t i = 0; i < loop; i++) cout<<(x[i])<<"  "; cout<<endl;


