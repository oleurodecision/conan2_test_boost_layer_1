#include <iostream>
#include "layer1Version.hh"
#include "layer1/fake.hh"

int main() {
    std::cout << Layer1_VERSION << std::endl;
	 layer1::fake();
}
