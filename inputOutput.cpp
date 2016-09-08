#include <iostream>
#include <fstream>
using namespace std;

class inputOutput {
	private:
		ofstream outFile;
		const char* fileName;

	public:
		inputOutput(const char* filename) {
			outFile.open(filename);
			fileName = filename;
		}

		void write(string out) {
			outFile << out;
		}

		void writeHeader() {
			outFile << "<CSPIF VERSION=\"0.01\">" << endl;
			outFile << "<CSP>" << endl;
			outFile << "<NAME>" << fileName << "</NAME>" << endl;
			outFile << "<DESCRIPTION>" << endl;
			outFile << "<SHORT></SHORT>" << endl;
			outFile << "<DETAILED></DETAILED>" << endl;
			outFile << "</DESCRIPTION>" << endl;
		}

		void writeFooter() {
			outFile << "</CSP>" << endl;
			outFile << "</CSPIF" << endl;
		}

		void writeSingleVariable(string name, int domain[]) {
			
		}

		void writeSingleConstraint(string constraintName, string var1, string var2) {
			outFile << "<CONSTRAINT TYPE=\"Custom\">" << endl;
			outFile << "<CUSTOMNAME>" << constraintName << "</CUSTOMNAME>" << endl;
			outFile << "<GIVEN>" << var1 << "</GIVEN>" << endl;
			outFile << "<GIVEN>" << var2 << "</GIVEN>" << endl;
			outFile << "<TABLE>" << endl;
			if (!isSingleDomain()) {
				for (int i=1; i<10; i++) {
					for (int j=1; j<10; i++) {
						if (i==j) {
							outFile << " F" << endl;
						} else {
							outFile << " T" << endl;
						}
					}	
				}
			}
			outFile << "</TABLE>" << endl;
		}

		void writeHorizontalConstraint(int row) {
			for (int i=1+9*(row-1); i<=9+9*(row-1); i++) {
				for (int j=i+1; j<=i+9; j++) {
					string c = "c";
					string u = "_";
					string t = "t";
					string constraintName = c + u + t + convertIntToStr(i) + u + t + convertIntToStr(j);
					string var1 = t + convertIntToStr(i);
					string var2 = t + convertIntToStr(j);
					writeSingleConstraint(constraintName, var1, var2);
				}
			}
		}

		string convertIntToStr(int input) {
			switch (input) {
				case 1 : return "1"; break;
				case 2 : return "2"; break;
				case 3 : return "3"; break;
				case 4 : return "4"; break;
				case 5 : return "5"; break;
				case 6 : return "6"; break;
				case 7 : return "7"; break;
				case 8 : return "8"; break;
				case 9 : return "9"; break;
				default : return convertIntToStr(input/10) + convertIntToStr(input%10);
			}
		}

		bool isSingleDomain () {
			return false;
		}

		void writeSingleVerticalConstraint() {
			
		}

		void writeSingleBoxConstraint() {
			
		}

		~inputOutput() {
			outFile.close();
		}
};

int main() {
	inputOutput a("test.txt");
	//a.write("oi");

	a.writeSingleConstraint("c_t1_t2", "t1", "t2");

	cout << "\"" << endl;
	return 0;
}