//file disjoint.h
#ifndef DISJOINTSETS
#define DISJOINTSETS

#include<iostream>
using namespace std;

class DisjointSets{
   private:
      int *rep;
      int n;
      int *rank;
   public:
      DisjointSets(){
         n = 100;
         rep = new int[n];
         rank = new int[n];
         for(int i=0;i<n;i++){
            rep[i] = -1;
            rank[i] = 0;
         }
      }
      DisjointSets(int newN);
      int findSet(int i);
      void unionSet(int u, int v);
};

DisjointSets::DisjointSets(int newN){
   n = newN;
   rep = new int[n];
   rank = new int[n];
   for(int i=0; i<n; i++){
      rep[i] = -1;
      rank[i] = 0;
   }
}

int DisjointSets::findSet(int i){
   int r = i;
   while(rep[r] != -1)
      r = rep[r];
   return r;
}

void DisjointSets::unionSet(int u, int v){
   if(u != v){
      if(rank[u] > rank[v]){
         rep[v] = u;
         rank[v] = rank[u];
      }
      else if(rank[v] > rank[u]){
         rep[u] = v;
         rank[u] = rank[v];
      }
      else{
         rep[v] = u;
         rank[v] = rank[u++];
      }
   }
}

#endif
