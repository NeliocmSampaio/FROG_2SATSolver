#include <cstdio>

//#include "Graph.h"
//#include "Solver.cc"
#include "Frog2.h"

using namespace std;

int main()
{
	S s;
	//Tclause c;

	/*c.vars.push_back(1);
	c.vars.push_back(2);
	S.addClause( &c );
	c.vars.clear();
	c.vars.push_back(3);
	c.vars.push_back(2);
	S.addClause( &c );
	c.vars.clear();
	c.vars.push_back(1);
	c.vars.push_back(4);
	S.addClause( &c );
	c.vars.clear();*/

	s.read();
	//s.print();

	printf("\n");
	printf( s.solve() ? "Satisfiable\n" : "Not Satisfiable\n");

	/*int n;
	printf( "vertices number: " );
	scanf( "%d", &n );
	Graph G( n );
	G.read( 0 );

	//printf("\n");
	//G.print();
	
	printf("\n");
	std::vector< std::vector< Tvertex > > components;
	G.CFC( components );*/
}//main()