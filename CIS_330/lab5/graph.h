struct Edge; 

struct Vertex
{
    float  location[2];		/* x, y coordinates of this vertex */
    int    nEdges;			/* number of edges connect to this vertex */
    struct Edge *edges;		/* an array of edges that connect to this vertex */
};




struct Edge
{
    struct Vertex vertices[2];	/* stores 2 vertices */
};

