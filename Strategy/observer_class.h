#pragma once
#include <string>

using namespace std;

class Subject;

class Observer {
public:
	Observer(Subject* sub) : subject(sub) {}
	virtual void update() = 0;

protected:
	Subject* subject;
};

