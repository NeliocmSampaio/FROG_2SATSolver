#include <stdio.h>
#include <vector>

#include "Graph.h"

#define Tlit int

typedef struct Tclause{
	std::vector< Tlit > vars;
}Tclause;

class Solver{
private:
	std::vector< Tclause > formula;
	int nbVar;							//number of variables
	int nbCl;							//number of clauses
public:
	Solver ( int v )
	{
		this->nbVar		=	v;
	}//Solver

	Solver (){};

	void addClause( Tclause * c )
	{
		(this->formula).push_back( *c );
		(this->nbCl)++;
	}//addClause()

	Tlit neg( int a )
	{
		if( a <= this->nbVar )
			return (this->nbVar) + a;
		else
			return (a-nbVar);
	}//neg()

	bool solve()
	{
		Graph G( (2*this->nbVar) );
		Tclause c;

		std::vector< Tclause >::iterator it;
		for( it=this->formula.begin(); it!=this->formula.end(); it++ )
		{
			G.addEdge( neg( it->vars[0] )-1, it->vars[1]-1 );
			G.addEdge( neg( it->vars[1] )-1, it->vars[0]-1 );
		}//for

		//G.print();

		std::vector< std::vector<Tvertex> > components;
		G.CFC( &components );
		int cMap[this->nbVar*2];

		int i;
		std::vector< std::vector<Tvertex> >::iterator itVec;
		std::vector< Tvertex >::iterator itIn;
		for( itVec=components.begin(), i=0; itVec!=components.end(); itVec++, i++ )
		{
			//printf("teste\n");
			for( itIn=itVec->begin(); itIn!=itVec->end(); itIn++ )
			{
				//printf( "%d\n", *itIn );
				cMap[ *itIn ] = i;
			}//for
		}//for

		bool flag = true;
		for( i=0; i<this->nbVar*2; i++ )
		{
			//printf("%d %d\n", cMap[i], cMap[neg(i)] );
			if( cMap[i] == cMap[ neg(i) ] ) 
			{
				flag = false;
				break;
				//printf("teste\n");
			}//if
		}//for

		return flag;
	}//solve()

	void print()
	{
		std::vector< Tclause >::iterator it;
		for( it=this->formula.begin(); it!=this->formula.end(); it++ )
		{
			printf( "%d %d\n", it->vars[0], it->vars[1] );
		}//for
	}//print()

	void read()
	{
		int v, cl, a, b;
		Tclause c;

		scanf( "%d", &v );
		this->nbVar = v;
		scanf( "%d", &cl );

		for( int i=0; i<cl; i++ )
		{
			scanf( "%d %d", &a, &b );
			if( a<0 ) a = neg( a*(-1) );
			if( b<0 ) b = neg( b*(-1) );
			c.vars.push_back(a);
			c.vars.push_back(b);
			this->addClause(&c);
			c.vars.clear();
		}//for
	}//read()

};//Solver

