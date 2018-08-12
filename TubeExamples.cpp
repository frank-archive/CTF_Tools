#include"Tube.h"

void TubesExamples() {
	RemoteSession a = remote("service.std-frank.club", 7456);
	a.send("asdf\n");
	cout << a.recv();
}