#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>

#include "Graph.h"

Graph::Graph( int vertices )
{
	this->verticesNumber	=	vertices;
	this->adj				=	new std::vector< Tvertex > [vertices];
}//Graph()

void Graph::addEdge( Tvertex a, Tvertex b)
{
	(this->adj)[a].push_back ( b );
	//(this->adj)[b].push_back ( a );	//In this case, the graph must be directed
}//addEdge()

void Graph::read( int n )
{
	Tvertex a, b;
	if( n==0 )
	{
		while( scanf( "%d %d", &a, &b) == 2 )
		{
			this->addEdge( a, b);
		}
	}else
	{
		for ( int i=0; i<n; i++ )
		{
			scanf( "%d %d", &a, &b);
			this->addEdge( a, b);
		}//for
	}//else
}//read()

void Graph::print()
{
	int i;
	int v;

	for( i=0; i<this->verticesNumber; i++ )
	{
		printf( "%d", i );

		std::vector< Tvertex >::iterator it;
		for( it=(this->adj)[i].begin(); it!=(this->adj)[i].end(); it++)
		{
			v = *it;

			printf( "-> %d", v );
		}//for
		printf( "\n" );
	}//for
}//print()

void Graph::CFC( std::vector< std::vector< Tvertex > > * components )
{
	std::vector< std::pair<int, int> > endingTime ( this->verticesNumber );
	Graph trans( this->verticesNumber );

	this->DFS( &endingTime );
	std::sort( endingTime.begin(), endingTime.begin()+this->verticesNumber, compare);

	this->transpose( &trans );
	//trans.print();

	trans.DFS( components, endingTime );

}//CFC()

void Graph::DFS( std::vector< std::vector< Tvertex > > * components, std::vector< std::pair<int, int> > endingTime )
{
	std::vector< std::vector< Tvertex > >::iterator index;

	Tcolor 	color [ this->verticesNumber ] = {0};
	Tvertex	v;
	int i;

	//std::vector< Tvertex > aux;		//used to initialize components
	//components.push_back( aux );
	//index = components.begin();

	for ( i=0; i<this->verticesNumber; i++ )
	{
		color[i] = unvisited;
	}//for

	for( i=0; i<endingTime.size(); i++ )
	{
		if( color[ endingTime[i].second ] == unvisited )
		{
			std::vector< Tvertex > aux;
			DFS_CFC( &aux, endingTime[i].second, color );
			(*components).push_back( aux );
			//printf("\n");
		}//if
	}//for
}//DFS

void Graph::visitDfs( std::vector<Tvertex>::iterator v, Tcolor * color, std::vector< std::pair<int, int> > * endingTime, int * time )
{
	*time = *time + 1;
	color [ *v ] = unfinished;
	//printf("%d\n", *v);

	std::vector<Tvertex>::iterator it;

	for( it=this->adj[*v].begin(); it!=this->adj[*v].end(); it++ )
	{
		if( color[*it] == unvisited )
		{
			visitDfs( it, color, endingTime, time );
		}//if
	}//for

	*time = *time + 1;
	(*endingTime)[ *v ].first = *time;
	(*endingTime)[ *v ].second = *v;
	//printf( "time: %d\n", *time );
	color [ *v ] = finished;
}//visitDfs()

void Graph::visitDfs( int v, Tcolor * color, std::vector< std::pair<int, int> > * endingTime, int * time )
{
	*time = *time + 1;
	color [ v ] = unfinished;
	//printf("%d\n", v);

	std::vector<Tvertex>::iterator it;

	for( it=this->adj[v].begin(); it!=this->adj[v].end(); it++ )
	{
		if( color[*it] == unvisited )
		{
			visitDfs( it, color, endingTime, time );
		}//if
	}//for

	*time = *time + 1;
	//printf( "time: %d\n", *time );
	(*endingTime)[ v ].first = *time;
	(*endingTime)[ v ].second = v;
	color [ v ] = finished;
}//visitDfs()

void Graph::DFS( std::vector< std::pair<int, int> > * endingTime )
{
	Tcolor 	color [ this->verticesNumber ] = {0};
	Tvertex	v;
	int time = 0;

	int i;
	for ( i=0; i<this->verticesNumber; i++ )
	{
		color[i] = unvisited;
	}//for

	for( i=0; i<this->verticesNumber; i++ )
	{
		if( color[i] == unvisited )
		{
			visitDfs( i, color, endingTime, &time );
		}//if
	}//for
}//DFS

/*void Graph::DFS(int * endingTime )
{
	Tcolor 	color [ this->verticesNumber ] = {0};
	Tvertex	v;
	int time = 0;

	int i;
	for ( i=0; i<this->verticesNumber; i++ )
	{
		color[i] = unvisited;
	}//for

	for( i=0; i<this->verticesNumber; i++ )
	{
		if( color[i] == unvisited )
		{
			//printf("number of vertices %d\n", this->verticesNumber);
			//printf("%d is unvisited\n", i);
			visitDfs( i, color, endingTime, &time );
		}//if
	}//for
}//DFS*/

//Transpose the graph. Ps. the graph G must be instanciated before calling the method
void Graph::transpose( Graph * G )
{
	int i;

	for( i=0; i<this->verticesNumber; i++ )
	{
		std::vector< Tvertex >::iterator it;
		for( it=(this->adj)[i].begin(); it!=(this->adj)[i].end(); it++)
		{
			G->addEdge( *it, i );
		}//for
	}//for
}//transpose()

/*
	Implement this function and finish the The Kozarajus Algorithm. Pay atention to the function
	CFC(), because its parameter may be wrong. It is probably better that it receives a vector of
	vectors, so we can add new components as many as needed.
*/
void Graph::DFS_CFC( std::vector< Tvertex > * components, 
	std::vector<Tvertex>::iterator v, Tcolor *color )
{
	//printf("%d\n", *v);
	(*components).push_back( *v );

	color [ *v ] = unfinished;

	std::vector<Tvertex>::iterator it;

	for( it=this->adj[*v].begin(); it!=this->adj[*v].end(); it++ )
	{
		if( color[ *it ] == unvisited )
		{
			DFS_CFC( components, it, color );
		}//if
	}//for

	color[ *v ] = finished;
}//DFS_CFC()

void Graph::DFS_CFC( std::vector< Tvertex > * components, 
	int v, Tcolor *color )
{
	//printf("%d\n", v);
	//printf("auto\n");
	(*components).push_back( v );

	color [ v ] = unfinished;

	std::vector< Tvertex >::iterator it;

	for( it=this->adj[v].begin(); it!=this->adj[v].end(); it++ )
	{
		if( color[ *it ] == unvisited )
		{
			DFS_CFC( components, it, color );
		}//if
	}//for

	color[ v ] = finished;
}//DFS_CFC()

bool compare( std::pair<int, int> a, std::pair<int, int> b )
{
	return a.first > b.first;
}//compare