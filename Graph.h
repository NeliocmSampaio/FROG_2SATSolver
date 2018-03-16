#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <utility>

#define	Tvertex 	int
#define	Tcolor		int
#define unvisited	0
#define	unfinished	1
#define	finished	2

class Graph{
private:
	std::vector< Tvertex > * 	adj;
	int					verticesNumber;
public:
	Graph(int vertices);

	void	addEdge		( Tvertex a, Tvertex b );
	void	read 		( int n );
	void	print 		();
	void	CFC			( std::vector< std::vector< Tvertex > > * components );		//Return in components the CFCs
	void	transpose	( Graph * G );
	void	visitDfs	(std::vector<Tvertex>::iterator v, Tcolor * color, std::vector< std::pair<int, int> > * endingTime, int * time);
	void	visitDfs	(int v, Tcolor * color, std::vector< std::pair<int, int> > * endingTime, int * time);
	//void	DFS			( int * endingTime );
	void	DFS			( std::vector< std::pair<int, int> > * endingTime );
	void 	DFS 		( std::vector< std::vector< Tvertex > > * v, std::vector< std::pair<int, int> > endingTime );
	//void	DFS_CFC		( std::vector< Tvertex > components, std::vector<Tvertex>::iterator v, Tcolor *color );
	void 	DFS_CFC		( std::vector< Tvertex > * components, int v, Tcolor *color );
	void	DFS_CFC		( std::vector< Tvertex > * components, std::vector<Tvertex>::iterator v, Tcolor *color );
};//Graph

bool	compare		(std::pair<int, int> a, std::pair<int, int> b);

#endif //GRAPH_H_INCLUDED