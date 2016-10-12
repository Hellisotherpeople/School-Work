#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

void InitializeVertex( struct Vertex *v );
void EdgeConnectsTwoVertices( struct Edge *e, 
							  struct Vertex *v1, 
							  struct Vertex *v2);
void UpdateVertex( struct Edge *e, struct Vertex *v );

int main()
{
	/* create a graph with 2 vertices and 1 edge, 
		looking like:  	*----* 					*/

	struct Vertex v1, v2;
	struct Edge e1;

	InitializeVertex( &v1 );
	InitializeVertex( &v2 );
	
	v2.location[0] = 1.0;
	v2.location[1] = 0.0;
	EdgeConnectsTwoVertices( &e1, &v1, &v2 );

	PrintEdgeInfo( &e1 );
}

void InitializeVertex( struct Vertex *v )
{
	v->location[0] = 0.0;			/* vertex default at the origin */
	v->location[1] = 0.0;			
	v->nEdges = 0;					/* default has no edge on it */
	v->edges = NULL;
}

void EdgeConnectsTwoVertices( struct Edge *e, 
							  struct Vertex *v1, 
							  struct Vertex *v2) 
{
	UpdateVertex( e, v1 );		/* v1 knows e connecting to it */
	UpdateVertex( e, v2 );		/* v2 knows e connecting to it */

	e->vertices[0] = *v1;		/* edge knows its two vertices */
	e->vertices[1] = *v2;
}

void UpdateVertex( struct Edge *e, struct Vertex *v )
{
	if( v->edges == NULL )		/* start from memory enough for 10 edges */
	{
		v->edges = malloc( 10 * sizeof(struct Edge*) );
	}
	else if( v->nEdges % 10 == 0 )	/* increase memory for 10 more edges */
	{
		v->edges = realloc( v->edges, (v->nEdges+10) * sizeof(struct Edge*) );
				   /* realloc: resize a chunck of memory */
	}
	v->edges[v->nEdges] = *e;		/* v keeps track of e */
	v->nEdges++;					
}

void PrintEdgeInfo( struct Edge *e )
{
	printf("This edge connects two vertices:\n (%f, %f) and (%f, %f).\n",
			e->vertices[0].location[0], e->vertices[0].location[1], 
			e->vertices[1].location[0], e->vertices[1].location[1] );
}
