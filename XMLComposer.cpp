#include <iostream>
#include <fstream>
#include "Koordinat.cpp"
using namespace std;

class XMLComposer {
	private:
		ofstream outFile;
		const char* fileName;

	public:
		XMLComposer(const char* filename) {
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

		void writeAllVariables() {
			Koordinat pos(800,575);
			int min = 0;
			int max = 80;
			
			outFile << "<CSPIF VERSION=\"0.01\">" <<endl;
			outFile << "<CSP>" <<endl;
			outFile << "<NAME>Untitled</NAME>" <<endl;
			outFile << "<DESCRIPTION>" <<endl;
			outFile << " <SHORT></SHORT>" <<endl;
			outFile << " <DETAILED></DETAILED>"<<endl;
			outFile << "</DESCRIPTION>" <<endl;

			for(int i=min;i<=max;i++){
				outFile << "<VARIABLE TYPE=\"Integer\">" <<endl;

				string row = convertIntToStr((int)i/9);
				string col = convertIntToStr((int)(i%9));

				outFile << " <NAME>T" << row << col << "</NAME>" <<endl;

				if(i==4 || i==18 || i==75){
					outFile << " <VALUE>"<<1<<"</VALUE>" <<endl;
				}else if(i==16 || i==50 || i==55 || i==67){
					outFile << " <VALUE>"<<2<<"</VALUE>" <<endl;
				}else if(i==58){
					outFile << " <VALUE>"<<3<<"</VALUE>" <<endl;
				}else if(i==23 || i==78){
					outFile << " <VALUE>"<<4<<"</VALUE>" <<endl;
				}else if(i==9 || i==12 || i==79){
					outFile << " <VALUE>"<<5<<"</VALUE>" <<endl;
				}else if(i==51 || i==63 ){
					outFile << " <VALUE>"<<6<<"</VALUE>" <<endl;
				}else if(i==40 || i==80){
					outFile << " <VALUE>"<<7<<"</VALUE>" <<endl;
				}else if(i==19 || i==32){
					outFile << " <VALUE>"<<8<<"</VALUE>" <<endl;
				}else if(i==1 || i==14 || i==54 || i==76){
					outFile << " <VALUE>"<<9<<"</VALUE>" <<endl;
				}else{
					for(int j=1;j<=9;j++){
						outFile << " <VALUE>"<<j<<"</VALUE>" <<endl;
					}
				}
				
				//print
				if(i % 9==1){
					//pos.x = 300;
					pos.setX(300);
					//pos.y +=2000;
					pos.setY(pos.getY() + 2000);
				}else{
					//pos.x += 2000;
					pos.setX(pos.getX() + 2000);
				}

				outFile<<"<PROPERTY>position = ("<<pos.getX()<<".0, "<< pos.getY()<<".0)"<<"</PROPERTY>"<<endl;
				outFile << "</VARIABLE>"<<endl;
			}
			outFile << "</CSP>" <<endl;
			outFile << "</CSPIF>" <<endl;
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

		void writeSingleHorizontalConstraint(int row) {
			string c = "C";
			string u = "_";
			string t = "T";

			for (int i=9*row; i<=8+9*row; i++) {
				string row1 = convertIntToStr((int)i/9);
				string col1 = convertIntToStr((int)(i%9));

				for (int j=i+1; j<=8+9*row; j++) {

					string row2 = convertIntToStr((int)j/9);
					string col2 = convertIntToStr((int)(j%9));

					string var1 = t + row1 + col1;
					string var2 = t + row2 + col2;

					string constraintName = c + u + var1 + u + var2;
					writeSingleConstraint(constraintName, var1, var2);
				}
			}
		}

		void writeSingleVerticalConstraint(int col) {
			string c = "C";
			string u = "_";
			string t = "T";

			for (int i=col; i<=col+9*8; i=i+9) {
				string row1 = convertIntToStr((int)i/9);
				string col1 = convertIntToStr((int)(i%9));

				for (int j=i+9; j<=col+9*8; j=j+9) {
					
					string row2 = convertIntToStr((int)j/9);
					string col2 = convertIntToStr((int)(j%9));

					string var1 = t + row1 + col1;
					string var2 = t + row2 + col2;

					string constraintName = c + u + var1 + u + var2;
					writeSingleConstraint(constraintName, var1, var2);
				}
			}
		}

		void writeSingleBoxConstraint(int box) {
			
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
};