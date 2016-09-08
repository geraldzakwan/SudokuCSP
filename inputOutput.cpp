#include <iostream>
#include <fstream>
using namespace std;

class inputOutput {
	private:
		ofstream outFile;

	public:
		inputOutput(const char* filename) {
			outFile.open(filename);
		}

		void write(string out) {
			outFile << out;
		}

		~inputOutput() {
			outFile.close();
		}
};

int main() {
	inputOutput a("test.txt");
	a.write("oi oi oi");
	return 0;
}