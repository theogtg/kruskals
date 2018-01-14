/* Name: R. Shore
 * Class: CSC-2710
 * Date: 10-20-2012
 * Location: ~/HPU/csc2710/prims/prims.cpp
 *
 * This program processes a weighted undirectional graph to find the minimum cost
 * spanning tree using Prims alorithm. Input to the program:
 * 1st line - number of edges (ecnt) followed by the number of vertices (vcnt)
 * The next ecnt lines will be edges.  The format will be
 *    from name, to name, cost
 * Each item is separated by a comma and the names may contain spaces.
 * The output will be the edges used in the solution with the minimal cost.
 * Format of the edges used in the solution:
 * (from name, to name) cost
 * Last line - the minimum cost
 */
#include<iostream>
#include<climits>
#include "disjoint.h"
using namespace std;

#define MAX 100

class etype{
   public:
      int u;
      int v;
      int w;
      bool used;
};

typedef etype * eptr;

int find_and_insert(string cities[], int &cnt, string vertname);
void readEdges(eptr edges[], string cities[], int edgecnt);
void printEdges(eptr edges[], int edgecnt);
void quickSort(eptr edges[], int low, int high);
void partition(eptr edges[], int low, int high, int&);
void exchange(eptr &a, eptr &b);

int main ()
{
   int ecnt,vcnt;
   int cnt;
   cin>>cnt;
   for(int i=0;i<cnt;i++) {
      cin>>ecnt>>vcnt;
      cin.get();//get the new line char - prepare to use getline

      eptr edges[ecnt];
      string cities[vcnt];
      //cout << "vcnt: " << vcnt << endl;
      readEdges(edges, cities, ecnt);
      quickSort(edges, 0, ecnt-1);


      //printEdges(edges, ecnt);
   }
   return 0;
}

/* find_and_insert
 * Function used to keep track of unique vertice names.  If vertname is in
 * vertices, then return it's position otherwise, add vertname to the vertices
 * array and return the position.  NOTE: cnt is the number of elements in the
 * zero based array.  If we add vertname and increment cnt, cnt-1 will be the
 * position of the vertname.
 *
 * pre-condition: vertices array contains cnt names
 *                vertname is the name in question,
 *
 * post-condition: if vertname is not in vertices then vertname will be added
 *                 and cnt will be incremented.
 */
int find_and_insert(string cities[], int &cnt, string vertname)
{
   // cout << "count: " << cnt << endl;
   for(int i=0; i<cnt; i++){
      //cout << i << endl;
      //cout.flush();
      if(cities[i] == vertname)
         return i;
   }
   cout << "before cities: " << vertname << endl;
   cout.flush();
   cities[cnt++] = vertname;
   cout << "after cities" << endl;
   cout.flush();
   return cnt-1;
}

/* Read from std-in the edges in the graph.
 * pre-condition: adjMatrix is a 2D matrix initialized for
 *                a set of undirected edges.
 *                vertexcnt is the size of the 2D matrix.
 *                vertices is a 1D array of vertex names
 *                edgecnt is the number of edges to process
 *                Each undirected edge consists of a
 *                from vertex, to vertex, and a weight
 * post-condition: adjMatrix is loaded with the undirected edges.
 *                 vertices are loaded with the vertex names
 */
void readEdges(eptr edges[], string cities[], int edgecnt)
{
   string city1, city2;
   int cost;
   int n=0;  //track how many vertices have been found.
   int from_ndx, to_ndx;

   //read and store weights into adjacency matrix
   //cout << edgecnt << endl;
   for(int i=0;i<edgecnt;i++) {
     // cout << "loop: " << i << endl;
      //cout.flush();
      getline(cin,city1,',');
      //cin.get();//get the space
      cout << "[" << cin.get() << "]" << endl;
      getline(cin,city2,',');
      cin>>cost;
      //cin.get();//get the new line char
      cout << "[" << cin.get() << "]" << endl;

      from_ndx = find_and_insert(cities,n,city1);
      //cout << "ndx: " << endl;
      //cout.flush();
      to_ndx = find_and_insert(cities,n,city2);
/*
      edges[i] = new etype;
      edges[i]->u = from_ndx;
      edges[i]->v = to_ndx;
      edges[i]->w = cost;
      edges[i]->used = false;
      */
   }
}

void printEdges(eptr edges[], int edgecnt){
   for(int i=0;i<edgecnt;i++){
      cout << "edges[" << i << "].u: " << edges[i]->u << endl;
      cout << "edges[" << i << "].v: " << edges[i]->v << endl;
      cout << "edges[" << i << "].w: " << edges[i]->w << endl;
      cout << "edges[" << i << "].used: " << edges[i]->used << endl;
      cout << "---------------------------------------------" << endl;
   }
}


/* Function: quickSort - rearrange all of the people into ascending order
 * pt_ptr - used to store the info
 * int low - used as the lowest point in the array
 * int high - used as the highest point in the array
 * int pivotPoint - used as the marker to split the array
 */
void quickSort(eptr edges[], int low, int high){

   int pivotPoint;

   partition(edges, low, high, pivotPoint);
   quickSort(edges, low, pivotPoint-1);
   quickSort(edges, pivotPoint+1, high);
}

/* Function: partition - divide up the array into different sections so the
 *                       quickSort algorithm can reset the low and high points
 * pt_ptr - used to store the info
 * int low - used as the lowest point in the array
 * int high - used as the highest point in the array
 * int pivotPoint - used as the marker to split the array
 * int i and j - used as the high and low points
 */
void partition(eptr edges[], int low, int high, int& pivotPoint){
   int i, j;

   int pivotItem;
   pivotItem = edges[low]->w;
   j = low;
   for(i = low + 1; i <= high; i++){
      cout << "i: " << i << endl;
      cout << "j: " << j << endl;
      if(edges[i]->w < pivotItem){
         j++;
         exchange(edges[i], edges[j]);
      }
   }
   pivotPoint = j;
   exchange(edges[low], edges[pivotPoint]);

}

/* Function: exchange - exchange two tt_ptr pointers
 * n and b - used to store the ptr's to swap them
 */
void exchange(eptr &a, eptr &b){
   eptr tmp;
   tmp = a;
   a = b;
   b = tmp;
}
