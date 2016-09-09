#include "XMLComposer.cpp"

int main() {
	XMLComposer a("Variabel.xml");
	XMLComposer b("HorizontalConstraintBaris0.xml");
	XMLComposer c("VerticalConstraintKolom0.xml");
	XMLComposer d("Final.xml");

	d.open();

	d.writeHeader();
	d.writeAllVariables();
	for (int i=0; i<9; i++) {
		d.writeSingleHorizontalConstraint(i);
		d.writeSingleVerticalConstraint(i);
	}
	d.writeBoxConstraint();
	d.writeFooter();

	d.close();
	return 0;
}