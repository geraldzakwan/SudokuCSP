#include <iostream>
#include <fstream>
#include "Koordinat.cpp"
using namespace std;

class XMLComposer {

	int tileKeisi[82];

	private:
		ofstream outFile;
		const char* fileName;

	public:
		XMLComposer(const char* filename) {
			fileName = filename;
			isiArray();
		}

		void isiArray() {
			for (int i=0; i<82; i++) {
				if(i==4 || i==18 || i==75){
					tileKeisi[i] = 1;
				}else if(i==16 || i==50 || i==55 || i==67){
					tileKeisi[i] = 2;
				}else if(i==58){
					tileKeisi[i] = 3;
				}else if(i==23 || i==78){
					tileKeisi[i] = 4;
				}else if(i==9 || i==12 || i==79){
					tileKeisi[i] = 5;
				}else if(i==51 || i==63 ){
					tileKeisi[i] = 6;
				}else if(i==40 || i==80){
					tileKeisi[i] = 7;
				}else if(i==19 || i==32){
					tileKeisi[i] = 8;
				}else if(i==1 || i==14 || i==54 || i==76){
					tileKeisi[i] = 9;
				}else {
					tileKeisi[i] = 0;
				}
			}
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
			outFile << "</CSPIF>" << endl;
		}

		void writeAllVariables() {
			Koordinat pos(800,575);
			int min = 1;
			int max = 81;

			for(int i=min;i<=max;i++){
				outFile << "<VARIABLE TYPE=\"Integer\">" <<endl;

				/*
				string row = convertIntToStr((int)i/9);
				string col = convertIntToStr((int)(i%9));
				*/

				//outFile << " <NAME>T" << row << col << "</NAME>" <<endl;

				outFile << " <NAME>T" << i << "</NAME>" <<endl;

				if (tileKeisi[i]==0) {
					for(int j=1;j<=9;j++){
						outFile << " <VALUE>"<<j<<"</VALUE>" <<endl;
					}
				} else {
					outFile << " <VALUE>"<< convertIntToStr(tileKeisi[i]) <<"</VALUE>" <<endl;
				}
				
				//print
				if(i % 9==1){
					//pos.x = 300;
					pos.setX(300);
					//pos.y +=2000;
					pos.setY(pos.getY() + 500);
				}else{
					//pos.x += 2000;
					pos.setX(pos.getX() + 500);
				}

				outFile<<"<PROPERTY>position = ("<<pos.getX()<<".0, "<< pos.getY()<<".0)"<<"</PROPERTY>"<<endl;
				outFile << "</VARIABLE>"<<endl;
			}
		}

		void writeSingleConstraint(string constraintName, int var1, int var2) {
			if (tileKeisi[var1] == 0) {
				outFile << "<CONSTRAINT TYPE=\"Custom\">" << endl;
				outFile << "<CUSTOMNAME>" << constraintName << "</CUSTOMNAME>" << endl;
				outFile << "<GIVEN>T" << convertIntToStr(var1) << "</GIVEN>" << endl;
				outFile << "<GIVEN>T" << convertIntToStr(var2) << "</GIVEN>" << endl;
				outFile << "<TABLE>" << endl;
				if (tileKeisi[var2] == 0) {
					//Constraint 9x9
					for (int i=1; i<10; i++) {
						for (int j=1; j<10; j++) {
							if (i==j) {
								outFile << " F";
							} else {
								outFile << " T";
							}
						}	
					} 
				} else {
					//Constraint 9x1
					writeTrueFalse(tileKeisi[var2]);
				}
				outFile << endl;
				outFile << "</TABLE>" << endl;
				outFile << "<PROPERTY>position = (4622.507, 4338.3887)</PROPERTY>" << endl;
				outFile << "</CONSTRAINT>" << endl;
			} else {
				//Constraint 1x9
				if (tileKeisi[var2] == 0) {
					outFile << "<CONSTRAINT TYPE=\"Custom\">" << endl;
					outFile << "<CUSTOMNAME>" << constraintName << "</CUSTOMNAME>" << endl;
					outFile << "<GIVEN>T" << convertIntToStr(var1) << "</GIVEN>" << endl;
					outFile << "<GIVEN>T" << convertIntToStr(var2) << "</GIVEN>" << endl;
					outFile << "<TABLE>" << endl;
					writeTrueFalse(tileKeisi[var1]);
					outFile << endl;
					outFile << "</TABLE>" << endl;
					outFile << "<PROPERTY>position = (4622.507, 4338.3887)</PROPERTY>" << endl;
					outFile << "</CONSTRAINT>" << endl;
				} else {
				//Constraint-nya ngk perlu
				}
			}
		}

		void writeSingleHorizontalConstraint(int row) {
			string c = "C";
			string u = "_";
			string t = "T";

			for (int i=9*row; i<=8+9*row; i++) {
				/*
				string row1 = convertIntToStr((int)i/9);
				string col1 = convertIntToStr((int)(i%9));
				*/

				for (int j=i+1; j<=8+9*row; j++) {

					/*
					string row2 = convertIntToStr((int)j/9);
					string col2 = convertIntToStr((int)(j%9));
					*/

					/*
					string var1 = t + row1 + col1;
					string var2 = t + row2 + col2;
					*/

					/*
					string var1 = t + convertIntToStr(i+1);
					string var2 = t + convertIntToStr(j+1);
					*/

					int var1 = i+1;
					int var2 = j+1;

					string constraintName = c + u + convertIntToStr(var1) + u + convertIntToStr(var2);
					writeSingleConstraint(constraintName, var1, var2);
				}
			}
		}

		void writeSingleVerticalConstraint(int col) {
			string c = "C";
			string u = "_";
			string t = "T";

			for (int i=col; i<=col+9*8; i=i+9) {
				/*
				string row1 = convertIntToStr((int)i/9);
				string col1 = convertIntToStr((int)(i%9));
				*/

				for (int j=i+9; j<=col+9*8; j=j+9) {
					/*
					string row2 = convertIntToStr((int)j/9);
					string col2 = convertIntToStr((int)(j%9));

					string var1 = t + row1 + col1;
					string var2 = t + row2 + col2;
					*/

					/*
					string var1 = t + convertIntToStr(i+1);
					string var2 = t + convertIntToStr(j+1);
					*/

					int var1 = i+1;
					int var2 = j+1;

					string constraintName = c + u + convertIntToStr(var1) + u + convertIntToStr(var2);
					writeSingleConstraint(constraintName, var1, var2);
				}
			}
		}

		void writeBoxConstraint() {
			int start1 = 0;
			string C = "C";
			string U = "_";
			for(int i=0;i<9;i++){

			if(i==0){
				start1 = 1; //inisialisasi awal
			}else if(i % 3 ==0){
				start1+=21;
			}else{
				start1+=3;
			}
		
			//petakan ke index
			int index[9];
			int start2 = 0;
			for(int j=0;j<9;j++){
				if(j==0){
					start2 = start1;
				}else if(j % 3 == 0){
					start2 +=7; 
				}else{
					start2 ++;
				}
				index[j] = start2;
			}

			//dapatkan pair kombinasi
			for(int j=0;j<8;j++){
				for(int k=j+1;k<9;k++){
				
					if(!(index[j]+1==index[k] || index[j]+2==index[k] || index[j]+9==index[k] || index[j]+18==index[k])){ //kondisi yang belum ada constraint
					// panggil prosedur tulis constraint
					//cout << index[j] << " " << index[k]<<endl;
					int var1 = index[j];
					int var2 = index[k];

					string constraintName = C + U + convertIntToStr(var1) + U + convertIntToStr(var2);
					writeSingleConstraint(constraintName, var1, var2);
					}
				}
			//cout <<endl;	
			}
	}
		}

		void writeTrueFalse(int falsePlace) {
			if (falsePlace!=-1) {
				for (int i=1; i<=9; i++) {
					if (i==falsePlace) {
						outFile << " F";
					} else {
						outFile << " T";
					}
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
};