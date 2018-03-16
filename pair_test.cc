#include <stdio.h>
#include <utility>
#include <vector>
using namespace std;

/*void func( vector< pair<int, int> > * v, int length )
{
	for( int i=0; i<length; i++ )
	{
		(*v)[i].first = i;
		(*v)[i].second = i * 2;
	}//for
}//func()

void pair()
{
	int length = 5;
	vector< pair<int, int> > v ( length );	

	func( &v, length );

	for( int i=0; i<length; i++ )
	{
		printf( "v[%d] = %d, %d\n", i, v[i].first, v[i].second );
	}//for
}//pair()*/

void add( vector<int> * it, int a)
{
	(*it).push_back( a );
	(*it).push_back( 6 );
	(*it).push_back( 5 );
	(*it).push_back( a+1 );
}//add()

void vectorAdd()
{
	int a=0;
	vector< vector<int> > v;
	vector<int>::iterator it;

	vector<int> aux;

	for( ;; )
	{
		if(a==5) break;
		a++;

		vector<int> vt;
		add( &vt, a );
		v.push_back( vt);
		printf("auto\n");
		v.clear();

		for( it=vt.begin(); it!=vt.end(); it++ )
		{
			printf("%d ", *it);
		}//for
		printf("\n");
	}//for 

	for( int i=0; i<v.size(); i++ )
	{
		for( vector< int >::iterator h = v[i].begin(); h != v[i].end(); h++ )
		{
			printf( "%d ", *h );
		}//for
		printf("\n");
	}//for
}//vectorAdd()

int main()
{
	vectorAdd();
	return 0;
}//main()