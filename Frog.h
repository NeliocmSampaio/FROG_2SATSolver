#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>

#define	Tvertex 	int
#define	Tcolor		int
#define unvisited	0
#define	unfinished	1
#define	finished	2
#define Tlit int

bool compare( std::pair<int, int> a, std::pair<int, int> b )
{
	return a.first > b.first;
}

class Graph{
private:
	std::vector< Tvertex > * 	adj;
	int					verticesNumber;
public:
	Graph( int vertices )
	{
		this->verticesNumber	=	vertices;
		this->adj				=	new std::vector< Tvertex > [vertices];
	}

	void addEdge( Tvertex a, Tvertex b)
	{
		(this->adj)[a].push_back ( b );
	}

	void CFC( std::vector< std::vector< Tvertex > > * components )
	{
		std::vector< std::pair<int, int> > endingTime ( this->verticesNumber );
		Graph trans( this->verticesNumber );

		this->DFS( &endingTime );
		std::sort( endingTime.begin(), endingTime.begin()+this->verticesNumber, compare);

		this->transpose( &trans );

		trans.DFS( components, endingTime );
	}

	void DFS( std::vector< std::vector< Tvertex > > * components, std::vector< std::pair<int, int> > endingTime )
	{
		std::vector< std::vector< Tvertex > >::iterator index;

		Tcolor 	color [ this->verticesNumber ] = {0};
		Tvertex	v;
		int i;

		for ( i=0; i<this->verticesNumber; i++ )
		{
			color[i] = unvisited;
		}

		for( i=0; i<endingTime.size(); i++ )
		{
			if( color[ endingTime[i].second ] == unvisited )
			{
				std::vector< Tvertex > aux;
				DFS_CFC( &aux, endingTime[i].second, color );
				(*components).push_back( aux );
			}
		}
	}

	void visitDfs( std::vector<Tvertex>::iterator v, Tcolor * color, std::vector< std::pair<int, int> > * endingTime, int * time )
	{
		*time = *time + 1;
		color [ *v ] = unfinished;

		std::vector<Tvertex>::iterator it;

		for( it=this->adj[*v].begin(); it!=this->adj[*v].end(); it++ )
		{
			if( color[*it] == unvisited )
			{
				visitDfs( it, color, endingTime, time );
			}
		}

		*time = *time + 1;
		(*endingTime)[ *v ].first = *time;
		(*endingTime)[ *v ].second = *v;
		color [ *v ] = finished;
	}

	void visitDfs( int v, Tcolor * color, std::vector< std::pair<int, int> > * endingTime, int * time )
	{
		*time = *time + 1;
		color [ v ] = unfinished;

		std::vector<Tvertex>::iterator it;

		for( it=this->adj[v].begin(); it!=this->adj[v].end(); it++ )
		{
			if( color[*it] == unvisited )
			{
				visitDfs( it, color, endingTime, time );
			}
		}

		*time = *time + 1;
		(*endingTime)[ v ].first = *time;
		(*endingTime)[ v ].second = v;
		color [ v ] = finished;
	}

	void DFS( std::vector< std::pair<int, int> > * endingTime )
	{
		Tcolor 	color [ this->verticesNumber ] = {0};
		Tvertex	v;
		int time = 0;

		int i;
		for ( i=0; i<this->verticesNumber; i++ )
		{
			color[i] = unvisited;
		}

		for( i=0; i<this->verticesNumber; i++ )
		{
			if( color[i] == unvisited )
			{
				visitDfs( i, color, endingTime, &time );
			}
		}
	}

	void transpose( Graph * G )
	{
		int i;

		for( i=0; i<this->verticesNumber; i++ )
		{
			std::vector< Tvertex >::iterator it;
			for( it=(this->adj)[i].begin(); it!=(this->adj)[i].end(); it++)
			{
				G->addEdge( *it, i );
			}
		}
	}

	void DFS_CFC( std::vector< Tvertex > * components, 
		std::vector<Tvertex>::iterator v, Tcolor *color )
	{
		(*components).push_back( *v );

		color [ *v ] = unfinished;

		std::vector<Tvertex>::iterator it;

		for( it=this->adj[*v].begin(); it!=this->adj[*v].end(); it++ )
		{
			if( color[ *it ] == unvisited )
			{
				DFS_CFC( components, it, color );
			}
		}

		color[ *v ] = finished;
	}

	void DFS_CFC( std::vector< Tvertex > * components, 
		int v, Tcolor *color )
	{
		(*components).push_back( v );

		color [ v ] = unfinished;

		std::vector< Tvertex >::iterator it;

		for( it=this->adj[v].begin(); it!=this->adj[v].end(); it++ )
		{
			if( color[ *it ] == unvisited )
			{
				DFS_CFC( components, it, color );
			}
		}

		color[ v ] = finished;
	}
};

typedef struct Tclause{
	std::vector< Tlit > vars;
}Tclause;

class Solver{
private:
	std::vector< Tclause > formula;
	int nbVar;
	int nbCl;
public:
	Solver ( int v )
	{
		this->nbVar		=	v;
	}

	Solver (){};

	void addClause( Tclause * c )
	{
		(this->formula).push_back( *c );
		(this->nbCl)++;
	}

	Tlit neg( int a )
	{
		if( a <= this->nbVar )
			return (this->nbVar) + a;
		else
			return (a-nbVar);
	}

	bool solve()
	{
		Graph G( (2*this->nbVar) );
		Tclause c;

		std::vector< Tclause >::iterator it;
		for( it=this->formula.begin(); it!=this->formula.end(); it++ )
		{
			G.addEdge( neg( it->vars[0] )-1, it->vars[1]-1 );
			G.addEdge( neg( it->vars[1] )-1, it->vars[0]-1 );
		}

		std::vector< std::vector<Tvertex> > components;
		G.CFC( &components );
		int cMap[this->nbVar*2];

		int i;
		std::vector< std::vector<Tvertex> >::iterator itVec;
		std::vector< Tvertex >::iterator itIn;
		for( itVec=components.begin(), i=0; itVec!=components.end(); itVec++, i++ )
		{
			for( itIn=itVec->begin(); itIn!=itVec->end(); itIn++ )
			{
				cMap[ *itIn ] = i;
			}
		}

		bool flag = true;
		for( i=0; i<this->nbVar*2; i++ )
		{
			if( cMap[i] == cMap[ neg(i) ] ) 
			{
				flag = false;
				break;
			}
		}

		return flag;
	}

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
		}
	}
};

#endif