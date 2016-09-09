#include "XMLComposer.cpp"

int main() {
	XMLComposer a("Variabel.xml");
	XMLComposer b("HorizontalConstraintBaris0.xml");
	XMLComposer c("VerticalConstraintKolom0.xml");

	a.open();
	b.open();
	c.open();

	a.writeAllVariables();
	b.writeSingleHorizontalConstraint(0);
	c.writeSingleVerticalConstraint(0);

	a.close();
	b.close();
	c.close();
	return 0;
}