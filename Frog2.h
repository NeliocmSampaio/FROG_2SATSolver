#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>

#define VEC vector

#define	Tv 			int
#define	Tc			int
#define UV			0
#define	UF			1
#define	FN			2
#define Tlit 		int
#define p<int> 		pair<int, int>
#define PB			push_back
#define T>			this->
#define RT 			return

using namespace std;

bool CMP( p<int> a, p<int> b )
{
	RT a.first > b.first;
}

class Graph{
private:
	VEC< Tv > * 	adj;
	int					VN;
public:
	Graph( int v )
	{
		T>VN	=	v;
		T>adj				=	new VEC< Tv > [v];
	}

	void add( Tv a, Tv b)
	{
		(T>adj)[a].PB ( b );
	}

	void CFC( VEC< VEC< Tv > > * components )
	{
		VEC< p<int> > endingTime ( T>VN );
		Graph trans( T>VN );

		T>DFS( &endingTime );
		sort( endingTime.begin(), endingTime.begin()+T>VN, CMP);

		T>TRSP( &trans );

		trans.DFS( components, endingTime );
	}

	void DFS( VEC< VEC< Tv > > * components, VEC< p<int> > endingTime )
	{
		VEC< VEC< Tv > >::iterator index;

		Tc 	color [ T>VN ] = {0};
		Tv	v;
		int i;

		for ( i=0; i<T>VN; i++ )
		{
			color[i] = UV;
		}

		for( i=0; i<endingTime.size(); i++ )
		{
			if( color[ endingTime[i].second ] == UV )
			{
				VEC< Tv > aux;
				DFS( &aux, endingTime[i].second, color );
				(*components).PB( aux );
			}
		}
	}

	void vDfs( VEC<Tv>::iterator v, Tc * color, VEC< p<int> > * endingTime, int * time )
	{
		*time = *time + 1;
		color [ *v ] = UF;

		VEC<Tv>::iterator it;

		for( it=T>adj[*v].begin(); it!=T>adj[*v].end(); it++ )
		{
			if( color[*it] == UV )
			{
				vDfs( it, color, endingTime, time );
			}
		}

		*time = *time + 1;
		(*endingTime)[ *v ].first = *time;
		(*endingTime)[ *v ].second = *v;
		color [ *v ] = FN;
	}

	void vDfs( int v, Tc * color, VEC< p<int> > * endingTime, int * time )
	{
		*time = *time + 1;
		color [ v ] = UF;

		VEC<Tv>::iterator it;

		for( it=T>adj[v].begin(); it!=T>adj[v].end(); it++ )
		{
			if( color[*it] == UV )
			{
				vDfs( it, color, endingTime, time );
			}
		}

		*time = *time + 1;
		(*endingTime)[ v ].first = *time;
		(*endingTime)[ v ].second = v;
		color [ v ] = FN;
	}

	void DFS( VEC< p<int> > * endingTime )
	{
		Tc 	color [ T>VN ] = {0};
		Tv	v;
		int time = 0;

		int i;
		for ( i=0; i<T>VN; i++ )
		{
			color[i] = UV;
		}

		for( i=0; i<T>VN; i++ )
		{
			if( color[i] == UV )
			{
				vDfs( i, color, endingTime, &time );
			}
		}
	}

	void TRSP( Graph * G )
	{
		int i;

		for( i=0; i<T>VN; i++ )
		{
			VEC< Tv >::iterator it;
			for( it=(T>adj)[i].begin(); it!=(T>adj)[i].end(); it++)
			{
				G->add( *it, i );
			}
		}
	}

	void DFS( VEC< Tv > * components, 
		VEC<Tv>::iterator v, Tc *color )
	{
		(*components).PB( *v );

		color [ *v ] = UF;

		VEC<Tv>::iterator it;

		for( it=T>adj[*v].begin(); it!=T>adj[*v].end(); it++ )
		{
			if( color[ *it ] == UV )
			{
				DFS( components, it, color );
			}
		}

		color[ *v ] = FN;
	}

	void DFS( VEC< Tv > * components, 
		int v, Tc *color )
	{
		(*components).PB( v );

		color [ v ] = UF;

		VEC< Tv >::iterator it;

		for( it=T>adj[v].begin(); it!=T>adj[v].end(); it++ )
		{
			if( color[ *it ] == UV )
			{
				DFS( components, it, color );
			}
		}

		color[ v ] = FN;
	}
};

typedef struct TCL{
	VEC< Tlit > vars;
}TCL;

class Solver{
private:
	VEC< TCL > FM;
	int nbVar;
	int nbCl;
public:
	Solver ( int v )
	{
		T>nbVar		=	v;
	}

	Solver (){};

	void add( TCL * c )
	{
		(T>FM).PB( *c );
		(T>nbCl)++;
	}

	Tlit neg( int a )
	{
		if( a <= T>nbVar )
			RT (T>nbVar) + a;
		else
			RT (a-nbVar);
	}

	bool solve()
	{
		Graph G( (2*T>nbVar) );
		TCL c;

		VEC< TCL >::iterator it;
		for( it=T>FM.begin(); it!=T>FM.end(); it++ )
		{
			G.add( neg( it->vars[0] )-1, it->vars[1]-1 );
			G.add( neg( it->vars[1] )-1, it->vars[0]-1 );
		}

		VEC< VEC<Tv> > components;
		G.CFC( &components );
		int cMap[T>nbVar*2];

		int i;
		VEC< VEC<Tv> >::iterator itVec;
		VEC< Tv >::iterator itIn;
		for( itVec=components.begin(), i=0; itVec!=components.end(); itVec++, i++ )
		{
			for( itIn=itVec->begin(); itIn!=itVec->end(); itIn++ )
			{
				cMap[ *itIn ] = i;
			}
		}

		bool flag = true;
		for( i=0; i<T>nbVar*2; i++ )
		{
			if( cMap[i] == cMap[ neg(i) ] ) 
			{
				flag = false;
				break;
			}
		}

		RT flag;
	}

	void read()
	{
		int v, cl, a, b;
		TCL c;

		scanf( "%d", &v );
		T>nbVar = v;
		scanf( "%d", &cl );

		for( int i=0; i<cl; i++ )
		{
			scanf( "%d %d", &a, &b );
			if( a<0 ) a = neg( a*(-1) );
			if( b<0 ) b = neg( b*(-1) );
			c.vars.PB(a);
			c.vars.PB(b);
			T>add(&c);
			c.vars.clear();
		}
	}
};

#endif