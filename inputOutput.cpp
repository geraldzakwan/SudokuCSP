#include <iostream>
#include <fstream>
using namespace std;

class inputOutput {
	private:
		ofstream outFile;
		const char* fileName;

	public:
		inputOutput(const char* filename) {
			fileName = filename;
		}

		void open() {
			outFile.open(fileName);
		}

		void close() {
			outFile.close();
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
					for (int j=1; j<10; j++) {
						if (i==j) {
							outFile << " F";
						} else {
							outFile << " T";
						}
					}	
				}
			}
			outFile << endl;
			outFile << "</TABLE>" << endl;
		}

		void writeHorizontalConstraint(int row) {
			for (int i=1+9*(row-1); i<=9+9*(row-1); i++) {
				for (int j=i+1; j<=9+9*(row-1); j++) {
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

		void writeVerticalConstraint(int col) {
			for (int i=col; i<=col+9*8; i=i+9) {
				for (int j=i+9; j<=col+9*8; j=j+9) {
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

		static string convertIntToStr(int input) {
			switch (input) {
				case 0 : return "0"; break;
				case 1 : return "1"; break;
				case 2 : return "2"; break;
				case 3 : return "3"; break;
				case 4 : return "4"; break;
				case 5 : return "5"; break;
				case 6 : return "6"; break;
				case 7 : return "7"; break;
				case 8 : return "8"; break;
				case 9 : return "9"; break;
				default : return convertIntToStr(input/10) + convertIntToStr(input%10); break;
			}
		}

		bool isSingleDomain () {
			return false;
		}

		void writeSingleVerticalConstraint() {
			
		}

		void writeSingleBoxConstraint() {
			
		}
};

int main() {
	inputOutput a("test.txt");
	a.open();
	//a.write("oi");

	//a.writeHeader();
	//a.writeSingleConstraint("c_t1_t2", "t1", "t2");
	//a.writeHorizontalConstraint(1);
	a.writeVerticalConstraint(1);
	a.close();

	//cout << inputOutput::convertIntToStr(50) << endl;

	cout << "\"" << endl;
	return 0;
}