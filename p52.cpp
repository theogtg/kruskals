/* Name: Tyler Griffith
 * Class: CSC-2710
 * Date: 10-20-2012
 * Location: ~/HPU/csc2710/prims/prims.cpp
 *
 * This program processes a weighted undirectional graph to find the minimum cost
 * spanning tree using kruskals alorithm. Input to the program:
 * 1st line - number of edges (ecnt) followed by the number of cities (vcnt)
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

//class
class etype{
   public:
      int u;
      int v;
      int w;
      bool used;
};

typedef etype * eptr;

//prototypes
int find_and_insert(string cities[], int &cnt, string vertname);
void readEdges(eptr edges[], string cities[], int edgecnt);
void exchange(eptr &a, eptr &b);
void bubbleSort(eptr edges[], int edgecnt);
bool kruskal(int n, int m, eptr edges[], int nearest[]);
void outputMinSpanTree(eptr edges[], int n, string cities[], int nearest[]);

//driver
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

      readEdges(edges, cities, ecnt);
      bubbleSort(edges, ecnt);

      int nearest[vcnt];

      if(kruskal(vcnt, ecnt, edges, nearest)){
         outputMinSpanTree(edges, vcnt, cities, nearest);
      }
      else{
         cout << "No Solution!" << endl;
      }

   }
   return 0;
}

/* find_and_insert
 * Function used to keep track of unique vertice names.  If vertname is in
 * cities, then return it's position otherwise, add vertname to the cities
 * array and return the position.  NOTE: cnt is the number of elements in the
 * zero based array.  If we add vertname and increment cnt, cnt-1 will be the
 * position of the vertname.
 *
 * pre-condition: cities array contains cnt names
 *                vertname is the name in question,
 *
 * post-condition: if vertname is not in cities then vertname will be added
 *                 and cnt will be incremented.
 */
int find_and_insert(string cities[], int &cnt, string vertname)
{
   for(int i=0; i<cnt; i++){
      if(cities[i] == vertname)
         return i;
   }
   cities[cnt++] = vertname;
   return cnt-1;
}

/* Read from std-in the edges in the graph.
 * pre-condition: edges is a class array to hold the edges
 *                and vertices.
 *                cities is a 1D array of vertex names
 *                edgecnt is the number of edges to process
 *                Each undirected edge consists of a
 *                from vertex, to vertex, and a weight
 * post-condition: edges is loaded with the undirected edges.
 *                 cities are loaded with the vertex names
 */
void readEdges(eptr edges[], string cities[], int edgecnt)
{
   string city1, city2;
   int cost;
   int n=0;  //track how many cities have been found.
   int from_ndx, to_ndx;

   //read and store weights into adjacency matrix
   for(int i=0;i<edgecnt;i++) {
      getline(cin,city1,',');
      cin.get();
      getline(cin,city2,',');
      cin>>cost;
      while(isspace(cin.peek())){
         cin.get();
      }

      from_ndx = find_and_insert(cities,n,city1);
      to_ndx = find_and_insert(cities,n,city2);

      edges[i] = new etype;
      edges[i]->u = from_ndx;
      edges[i]->v = to_ndx;
      edges[i]->w = cost;
      edges[i]->used = false;
   }
}

/* Function: bubbleSort - rearrange all of the edges into ascending order
 *                        based on their weight
 * pre-condition: edges - an array holding the weights
 *                edgecnt is the number of edges to process
 * post-contidion: no output, sorts the edges array
 */
void bubbleSort(eptr edges[], int edgecnt){
   for(int i=0;i<edgecnt;i++){
      for(int j = i+1; j<edgecnt; j++){
         if(edges[j]->w < edges[i]->w){
            exchange(edges[i], edges[j]);
         }
      }
   }
}

/* Output the vertices on the min Cost Spanning Tree based on
 * a solution found using kruskal's algorith.
 * pre-condition: edges - an array holding the weights
 *                n the number of vertices
 *                cities - a 1D array of names of vertices
 *                nearest - a 1D array found in kruskal's
 * post-contidion: No parameters are altered, all std-output.
 */
void outputMinSpanTree(eptr edges[], int n, string cities[], int nearest[]){
   int from_ndx, to_ndx;
   int cost;
   int minCost=0;

   for(int i=1; i<n; i++) {
      from_ndx = i;
      to_ndx = nearest[i];
      cost = edges[i]->w;
      minCost+=cost;
      cout<<"("<<cities[from_ndx]<<", "<<cities[to_ndx]<<") "<<cost<<endl;
   }
   cout<<"min cost: "<<minCost<<endl;
}

/* Function: exchange - exchange two eptr pointers
 * a and b - used to store the ptr's to swap them
 */
void exchange(eptr &a, eptr &b){
   eptr tmp;
   tmp = a;
   a = b;
   b = tmp;
}

/* kruskal implements kruskal's algorithm for finding the mincost spanning tree.
 * pre-condition: edges is an array holding the weights
 *                n is the number of vertices
 *                m is the number of edges
 *                nearest is empty
 * post-condition: edges, m and n are not changed
 *                 nearest will contain the edges in the min cost spanning tree.
 */
bool kruskal(int n, int m, eptr edges[], int nearest[]){
   int i, j, distance[n], cnt = 0, Su, Sv;
   int e;
   DisjointSets d = DisjointSets(n);
   while(nearest[m] < n-1){
      e = edges[cnt]->u;
      if((Su = d.findSet(edges[cnt]->u)) != (Sv = d.findSet(edges[cnt]->v))){
         cnt++;
         d.unionSet(Su,Sv);
         nearest[cnt] = e;
      }
   }
   if(cnt == n-1){
      return true;
   }
   else{
      return false;
   }
}
