#include <cstdio>

//#include "Graph.h"
//#include "Solver.cc"
#include "Frog.h"

using namespace std;

int main()
{
	Solver S;
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

	S.read();
	S.print();

	printf("\n");
	printf( S.solve() ? "Satisfiable\n" : "Not Satisfiable\n");

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