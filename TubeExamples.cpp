#include"Tube.h"
#include<iostream>

void TubesExamples() {
	RemoteSession a = remote("service.std-frank.club", 7456);
	a.send("asdf\n");
	std::cout << a.recv();
}