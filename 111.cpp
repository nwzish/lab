//LUP


#include<iostream>
using namespace std;
//#include<conio>
int main()
{
    int n,i,k,j,p;
    float a[10][10],l[10][10]={0},u[10][10]={0},sum,b[10],z[10]={0},x[10]={0};
    //clrscr();
    cout<<"Enter the order of matrix ! ";
    cin>>n;
    cout<<"Enter all coefficients of matrix : ";
    for(i=1;i<=n;i++)
    {
        cout<<"\nRow "<<i<<"  ";
        for(j=1;j<=n;j++)
            cin>>a[i][j];
    }
    cout<<"Enter elements of b matrix"<<endl;
    for(i=1;i<=n;i++)
        cin>>b[i];
    //********** LU decomposition *****//
    for(k=1;k<=n;k++)
    {
        u[k][k]=1;
        for(i=k;i<=n;i++)
        {
            sum=0;
            for(p=1;p<=k-1;p++)
                sum+=l[i][p]*u[p][k];
            l[i][k]=a[i][k]-sum;
        }

        for(j=k+1;j<=n;j++)
        {
            sum=0;
            for(p=1;p<=k-1;p++)
                sum+=l[k][p]*u[p][j];
            u[k][j]=(a[k][j]-sum)/l[k][k];
        }
    }
    //******** Displaying LU matrix**********//
    cout<<endl<<endl<<"LU matrix is "<<endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<l[i][j]<<"  ";
        cout<<endl;
    }
    cout<<endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<u[i][j]<<"  ";
        cout<<endl;
    }

    //***** FINDING Z; LZ=b*********//

    for(i=1;i<=n;i++)
    {                                        //forward subtitution method
        sum=0;
        for(p=1;p<i;p++)
        sum+=l[i][p]*z[p];
        z[i]=(b[i]-sum)/l[i][i];
    }
    //********** FINDING X; UX=Z***********//

    for(i=n;i>0;i--)
    {
        sum=0;
        for(p=n;p>i;p--)
            sum+=u[i][p]*x[p];
        x[i]=(z[i]-sum)/u[i][i];
    }
    //*********** DISPLAYING SOLUTION**************//
    cout<<endl<<"Set of solution is"<<endl;
    for(i=1;i<=n;i++)
        cout<<endl<<x[i];

 //   getch();
    return 0;
}






/////////////////////////////////////////////////////////
// fftrecusive

#include <bits/stdc++.h> 
using namespace std; 
  
// For storing complex values of nth roots 
// of unity we use complex<double> 
typedef complex<double> cd; 
  
// Recursive function of FFT 
vector<cd> fft(vector<cd>& a) 
{ 
    int n = a.size(); 
  
    // if input contains just one element 
    if (n == 1) 
        return vector<cd>(1, a[0]); 
  
    // For storing n complex nth roots of unity 
    vector<cd> w(n); 
    for (int i = 0; i < n; i++) { 
        double alpha = 2 * M_PI * i / n; 
        w[i] = cd(cos(alpha), sin(alpha)); 
    } 
  
    vector<cd> A0(n / 2), A1(n / 2); 
    for (int i = 0; i < n / 2; i++) { 
  
        // even indexed coefficients 
        A0[i] = a[i * 2]; 
  
        // odd indexed coefficients 
        A1[i] = a[i * 2 + 1]; 
    } 
  
    // Recursive call for even indexed coefficients 
    vector<cd> y0 = fft(A0);  
  
    // Recursive call for odd indexed coefficients 
    vector<cd> y1 = fft(A1); 
  
    // for storing values of y0, y1, y2, ..., yn-1. 
    vector<cd> y(n); 
  
    for (int k = 0; k < n / 2; k++) { 
        y[k] = y0[k] + w[k] * y1[k]; 
        y[k + n / 2] = y0[k] - w[k] * y1[k]; 
    } 
    return y; 
} 
  
// Driver code 
int main() 
{ 
    vector<cd> a{2, 2, 3, 4}; 
    vector<cd> b = fft(a); 
    for (int i = 0; i < 4; i++) 
        cout << b[i] << endl; 
  
    return 0; 
} 



/////////////////////////////////////////////////
//fft iterative

#include <bits/stdc++.h> 
using namespace std; 
  
typedef complex<double> cd; 
const double PI = 3.1415926536; 
  
// Utility function for reversing the bits 
// of given index x 
unsigned int bitReverse(unsigned int x, int log2n) 
{ 
    int n = 0; 
    for (int i = 0; i < log2n; i++) 
    { 
        n <<= 1; 
        n |= (x & 1); 
        x >>= 1; 
    } 
    return n; 
} 
  
// Iterative FFT function to compute the DFT 
// of given coefficient vector 
void fft(vector<cd>& a, vector<cd>& A, int log2n) 
{ 
    int n = 4; 
  
    // bit reversal of the given array 
    for (unsigned int i = 0; i < n; ++i) { 
        int rev = bitReverse(i, log2n); 
        A[i] = a[rev]; 
    } 
  
    // j is iota 
    const complex<double> J(0, 1); 
    for (int s = 1; s <= log2n; ++s) { 
        int m = 1 << s; // 2 power s 
        int m2 = m >> 1; // m2 = m/2 -1 
        cd w(1, 0); 
  
        // principle root of nth complex  
        // root of unity. 
        cd wm = exp(J * (PI / m2));  
        for (int j = 0; j < m2; ++j) { 
            for (int k = j; k < n; k += m) { 
  
                // t = twiddle factor 
                cd t = w * A[k + m2];  
                cd u = A[k]; 
  
                // similar calculating y[k] 
                A[k] = u + t;  
  
                // similar calculating y[k+n/2] 
                A[k + m2] = u - t;  
            } 
            w *= wm; 
        } 
    } 
} 
  
int main() 
{ 
    vector<cd> a{ 1, 2, 3, 4 }; 
    vector<cd> A(4); 
    fft(a, A, 2); 
    for (int i = 0; i < 4; ++i) 
        cout << A[i] << "\n"; 
} 

///////////////////////////////////////
//kd tree


#include<bits/stdc++.h> 
using namespace std; 
  
const int k = 2; 
struct Node 
{ 
    int point[k]; // To store k dimensional point 
    Node *left, *right; 
}; 
struct Node* newNode(int arr[]) 
{ 
    struct Node* temp = new Node; 
  
    for (int i=0; i<k; i++) 
       temp->point[i] = arr[i]; 
  
    temp->left = temp->right = NULL; 
    return temp; 
} 
Node *insertRec(Node *root, int point[], unsigned depth) 
{ 
    if (root == NULL) 
       return newNode(point); 
    unsigned cd = depth % k; 
    if (point[cd] < (root->point[cd])) 
        root->left  = insertRec(root->left, point, depth + 1); 
    else
        root->right = insertRec(root->right, point, depth + 1); 
  
    return root; 
} 
Node* insert(Node *root, int point[]) 
{ 
    return insertRec(root, point, 0); 
} 
bool arePointsSame(int point1[], int point2[]) 
{ 
    for (int i = 0; i < k; ++i) 
        if (point1[i] != point2[i]) 
            return false; 
  
    return true; 
} 
bool searchRec(Node* root, int point[], unsigned depth) 
{ 
    if (root == NULL) 
        return false; 
    if (arePointsSame(root->point, point)) 
        return true; 
    unsigned cd = depth % k; 
    if (point[cd] < root->point[cd]) 
        return searchRec(root->left, point, depth + 1); 
  
    return searchRec(root->right, point, depth + 1); 
} 
bool search(Node* root, int point[]) 
{ 
    return searchRec(root, point, 0); 
} 
int main() 
{ 
    struct Node *root = NULL; 
    int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, 
                       {9, 1}, {2, 7}, {10, 19}}; 
  
    int n = sizeof(points)/sizeof(points[0]); 
  
    for (int i=0; i<n; i++) 
       root = insert(root, points[i]); 
  
    int point1[] = {10, 19}; 
    (search(root, point1))? cout << "Found\n": cout << "Not Found\n"; 
  
    int point2[] = {12, 19}; 
    (search(root, point2))? cout << "Found\n": cout << "Not Found\n"; 
  
    return 0; 
} 


////////////////////////////////////////////////////////////
// line segment sweep 

#define x second
#define y first
typedef pair<int,int >point;
struct event 
{
    point p1,p2;
    int type;
    event() {};
    event(point p1,point p2, int type) : p1(p1), p2(p2),type(type) {};  //initialization of event
};
int n,e;
event events[MAX];
bool compare(event a, event b) 
{ 
    return a.p1.x<b.p1.x; 
}
set<point >s;
void hv_intersection()
{
    for (int i=0;i<e;++i)
        {
                event c = events[i];
                if (c.type==0) s.insert(c.p1);//insert starting point of line segment into set
                else if (c.type==1) s.erase(c.p2);//remove starting point of line segment from set, equivalent to removing line segment
                else
                {
                        for (typeof(s.begin()) it=s.lower_bound(make_pair(c.p1.y,-1));it!=s.end() && it->y<=c.p2.y; it++) // Range search
                                printf("%d, %d\n", events[i].p1.x, it->y);//intersections
                }
        }
}
int main () 
{
    scanf("%d", &n);
    int p1x,p1y,p2x,p2y;
        for (int i=0;i<n;++i) 
        {
                scanf("%d %d %d %d", &p1x, &p1y,&p2x, &p2y);
        if(p1x==p2x)                //if vertical line, one event with type=2
        {
            events[e++]=event(make_pair(p1y,p1x),make_pair(p2y,p2x),2);
        }
        else                    //if horizontal line, two events one for starting point and one for ending point
        {
            //store both starting points and ending points
            events[e++]=event(make_pair(p1y,p1x),make_pair(p2y,p2x),0);
            //store both ending and starting points, note the order in the second, this is because we sort on p1, so ending points first, then we remove a line when we hit its ending point , so we need its starting point for removal of line
            events[e++]=event(make_pair(p2y,p2x),make_pair(p1y,p1x),1);
        }
        }
    sort(events, events+e,compare);//on x coordinate
    hv_intersection();
    return 0;
}

/////////////////////////////////////////////////////
// line intersection

#include <iostream> 
using namespace std; 
  
struct Point 
{ 
    int x; 
    int y; 
}; 
bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
       return true; 
  
    return false; 
} 
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
int main() 
{ 
    struct Point p1 = {1, 1}, q1 = {10, 1}; 
    struct Point p2 = {1, 2}, q2 = {10, 2}; 
  
    doIntersect(p1, q1, p2, q2)? cout << "Yes\n": cout << "No\n"; 
  
    p1 = {10, 0}, q1 = {0, 10}; 
    p2 = {0, 0}, q2 = {10, 10}; 
    doIntersect(p1, q1, p2, q2)? cout << "Yes\n": cout << "No\n"; 
  
    p1 = {-5, -5}, q1 = {0, 0}; 
    p2 = {1, 1}, q2 = {10, 10}; 
    doIntersect(p1, q1, p2, q2)? cout << "Yes\n": cout << "No\n"; 
  
    return 0; 
} 


/////////////////////////////////////////////////////////////
//kmp 

/*
 * C++ Program to Implement Knuth–Morris–Pratt Algorithm (KMP)
 */
#include <iostream>
#include <cstring>
using namespace std;
void preKMP(string pattern, int f[])
{
    int m = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}
 
//check whether target string contains pattern 
bool KMP(string pattern, string target)
{
    int m = pattern.length();
    int n = target.length();
    int f[m];     
    preKMP(pattern, f);     
    int i = 0;
    int k = 0;        
    while (i < n)
    {
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (target[i] == pattern[k])
        {
            i++;
            k++;
            if (k == m)
                return 1;
        }
        else
            k = f[k];
    }
    return 0;
}
 
int main()
{
    string tar = "san and linux training";
    string pat = "lin";
    if (KMP(pat, tar))
        cout<<"'"<<pat<<"' found in string '"<<tar<<"'"<<endl;
    else
        cout<<"'"<<pat<<"' not found in string '"<<tar<<"'"<<endl;
    pat = "sanfoundry";
    if (KMP(pat, tar))
        cout<<"'"<<pat<<"' found in string '"<<tar<<"'"<<endl;
    else
        cout<<"'"<<pat<<"' not found in string '"<<tar<<"'"<<endl;
    return 0;
}


////////////////////////////////////////////////////////
//automata

#include<stdio.h>
#include<string.h>
#define NO_OF_CHARS 256
 
int getNextState(char *pat, int M, int state, int x)
{
    // If the character c is same as next character in pattern,
    // then simply increment state
    if (state < M && x == pat[state])
        return state + 1;
 
    int ns, i; // ns stores the result which is next state
 
    // ns finally contains the longest prefix which is also suffix
    // in "pat[0..state-1]c"
 
    // Start from the largest possible value and stop when you find
    // a prefix which is also suffix
    for (ns = state; ns > 0; ns--)
    {
        if (pat[ns - 1] == x)
        {
            for (i = 0; i < ns - 1; i++)
            {
                if (pat[i] != pat[state - ns + 1 + i])
                    break;
            }
            if (i == ns - 1)
                return ns;
        }
    }
 
    return 0;
}
 
/* This function builds the TF table which represents Finite Automata for a
 given pattern  */
void computeTF(char *pat, int M, int TF[][NO_OF_CHARS])
{
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF[state][x] = getNextState(pat, M, state, x);
}
 
/* Prints all occurrences of pat in txt */
void search(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
 
    int TF[M + 1][NO_OF_CHARS];
 
    computeTF(pat, M, TF);
 
    // Process txt over FA.
    int i, state = 0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][txt[i]];
        if (state == M)
        {
            printf("\n pattern found at index %d", i - M + 1);
        }
    }
}
 
// Driver program to test above function
int main()
{
    char *txt = "AABAACAADAABAAABAA";
    char *pat = "AABA";
    search(pat, txt);
    return 0;
}

/////////////////////////////////////////////////////
//rabincarp 

/*
 * C++ Program to Implement Rabin-Karp Algorithm
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define d 256
/*
 * search a substring in a string 
 */
void search(char *pat, char *txt, int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;
    for (i = 0; i < M; i++)
    {
        p = (d *p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }
    for (i = 0; i <= N - M; i++)
    {
        if (p == t)
        {
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == M)
            {
                cout<<"Pattern found at index: "<<i<<endl;
            }
        }
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
              t = (t + q);
        }
    }
}
 
/* Main */
int main()
{
    char *txt = "Sanfoundry Linux Training";
    char *pat = "nux";
    int q = 101;
    search(pat, txt, q);
    return 0;
}


///////////////////////////////////////////////////
//dijkstra

#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
 
typedef pair< int, int > pii;
 
const int MAX = 1024;
const int INF = 0x3f3f3f3f;
 
vector< pii > G[MAX];
int d[MAX];
 
void dijkstra(int start) {
    int u, v, i, c, w;
 
    priority_queue< pii, vector< pii >, greater< pii > > Q;

    memset(d, 0x3f, sizeof d);
    Q.push(pii(0, start));
    d[start] = 0;
 
    while(!Q.empty()) {
        u = Q.top().second; // node
        c = Q.top().first; // node cost so far
        Q.pop(); // remove the top item.
 
        if(d[u] < c) continue;
 
        for(i = 0; i < G[u].size(); i++) {
            v = G[u][i].first; // node
            w = G[u][i].second; // edge weight
 
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                Q.push(pii(d[v], v));
            }
        }
    }
}
 
int main() {
    int n, e, i, u, v, w, start;
    while(scanf("%d %d", &n, &e) == 2) {
 
        for(i = 1; i <= n; i++) G[i].clear();
 
        for(i = 0; i < e; i++) {
            scanf("%d %d %d", &u, &v, &w);
            G[u].push_back(pii(v, w));
            G[v].push_back(pii(u, w)); // only if bi-directional
        }
 
        scanf("%d", &start);
 
        dijkstra(start);
 
        printf("Shortest path from node %d:\n", start);
        for(i = 1; i <= n; i++) {
            if(i == start) continue;
            if(d[i] >= INF) printf("\t to node %d: unreachable\n", i);
            else printf("\t to node %d: %d\n", i, d[i]);
        }
    }
    return 0;
}


////////////////////////////////////////////////////////////
//bellman 

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
using namespace std;
 
struct Edge
{
    int source, destination, weight;
};
struct Graph
{
    int V, E; 
    struct Edge* edge;
};
 
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph));
    graph->V = V;   
    graph->E = E;
 
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
    return graph;
}
 
void FinalSolution(int dist[], int n)
{
    cout<<"\nVertex\tDistance from Source Vertex\n";
    int i;
 
    for (i = 0; i < n; ++i){
        cout<<i<<"\t\t"<<dist[i]<<"\n";
    }
}
 
void BellmanFord(struct Graph* graph, int source)
{
    int V = graph->V;
 
    int E = graph->E;
 
    int StoreDistance[V];
 
    int i,j;
 
    for (i = 0; i < V; i++)
        StoreDistance[i] = INT_MAX;
 
    StoreDistance[source] = 0;
    for (i = 1; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = graph->edge[j].source;
 
            int v = graph->edge[j].destination;
 
            int weight = graph->edge[j].weight;
 
            if (StoreDistance[u] + weight < StoreDistance[v])
                StoreDistance[v] = StoreDistance[u] + weight;
        }
    }
    for (i = 0; i < E; i++)
    {
        int u = graph->edge[i].source;
 
        int v = graph->edge[i].destination;
 
        int weight = graph->edge[i].weight;
 
        if (StoreDistance[u] + weight < StoreDistance[v])
            cout<<"\nThis graph contains negative edge cycle\n";
    }
 
    FinalSolution(StoreDistance, V);
 
    return;
}
 
int main()
{
    int V,E,S;  //V = no.of Vertices, E = no.of Edges, S is source vertex
 
    cout<<"Enter number of vertices in graph\n";
    cin>>V;
 
    cout<<"Enter number of edges in graph\n";
    cin>>E;
 
    cout<<"Enter your source vertex number\n";
    cin>>S;
 
    struct Graph* graph = createGraph(V, E);     
    int i;
    for(i=0;i<E;i++){
        cout<<"\nEnter edge "<<i+1<<" properties Source, destination, weight respectively\n";
        cin>>graph->edge[i].source;
        cin>>graph->edge[i].destination;
        cin>>graph->edge[i].weight;
    }
 
    BellmanFord(graph, S);
 
    return 0;
}


////////////////////////////////////////////////////////////////
// johnson

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <exception>
#include <set>

using namespace std;

struct Edge {
  int head;
  long cost;
};

using Graph = vector<vector<Edge>>;
using SingleSP = vector<long>;
using AllSP = vector<vector<long>>;
const long INF = LONG_MAX;

// first line is in the format <N> <M> where N is the number of vertices, M is the number of edges that follow
// each following line represents a directed edge in the form <Source> <Dest> <Cost>
Graph loadgraph(istream& is) {
  Graph g;

  int n, m;
  is >> n >> m;
  cout << "Graph has " << n << " vertices and " << m << " edges." << endl;
  g.resize(n+1);
  while (is) {
    int v1, v2, c;
    is >> v1 >> v2 >> c;
    if (is) {
      g[v1].push_back({v2, c});
    }
  }

  return g;
}

Graph addZeroEdge(Graph g) {
  // add a zero-cost edge from vertex 0 to all other edges
  for (int i = 1; i < g.size(); i++) {
    g[0].push_back({i, 0});
  }

  return g;
}

SingleSP bellmanford(Graph &g, int s) {
  vector<vector<long>> memo(g.size()+2, vector<long>(g.size(), INF));

  // initialise base case
  memo[0][s] = 0;

  for (int i = 1; i < memo.size(); i++) {
    // compute shortest paths from s to all vertices, with max hop-count i
    for (int n = 0; n < g.size(); n++) {
      if (memo[i-1][n] < memo[i][n]) {
        memo[i][n] = memo[i-1][n];
      }
      for (auto& e : g[n]) {
        if (memo[i-1][n] != INF) {
          if (memo[i-1][n] + e.cost < memo[i][e.head]) {
            memo[i][e.head] = memo[i-1][n] + e.cost;
          }
        }
      }
    }
  }

  // check if the last iteration differed from the 2nd-last
  for (int j = 0; j < g.size(); j++) {
    if (memo[g.size()+1][j] != memo[g.size()][j]) {
      throw string{"negative cycle found"};
    }
  }

  return memo[g.size()];
}

SingleSP djikstra(const Graph& g, int s) {
  SingleSP dist(g.size(), INF);
  set<pair<int,long>> frontier;

  frontier.insert({0,s});

  while (!frontier.empty()) {
    pair<int,long> p = *frontier.begin();
    frontier.erase(frontier.begin());

    int d = p.first;
    int n = p.second;

    // this is our shortest path to n
    dist[n] = d;

    // now look at all edges out from n to update the frontier
    for (auto e : g[n]) {
      // update this node in the frontier if we have a shorter path
      if (dist[n]+e.cost < dist[e.head]) {
        if (dist[e.head] != INF) {
          // we've seen this node before, so erase it from the set in order to update it
          frontier.erase(frontier.find({dist[e.head], e.head}));
        }
        frontier.insert({dist[n]+e.cost, e.head});
        dist[e.head] = dist[n]+e.cost;
      }
    }
  }

  return dist;
}

AllSP johnson(Graph &g) {
  // now build "g prime" which is g with a new edge added from vertex 0 to all other edges, with cost 0
  Graph gprime = addZeroEdge(g);

  // now run Bellman-Ford to get single-source shortest paths from s to all other vertices
  SingleSP ssp;
  try {
    ssp = bellmanford(gprime, 0);
  } catch (string e) {
    cout << "Negative cycles found in graph.  Cannot compute shortest paths." << endl;
    throw e;
  }

  // no re-weight each edge (u,v) in g to be: cost + ssp[u] - ssp[v].
  for (int i = 1; i < g.size(); i++) {
    for (auto &e : g[i]) {
      e.cost = e.cost + ssp[i] - ssp[e.head];
    }
  }

  // now that we've re-weighted our graph, we can invoke N iterations of Djikstra to find
  // all pairs shortest paths
  AllSP allsp(g.size());
  for (int i = 1; i < g.size(); i++) {
    allsp[i] = djikstra(g, i);
  }

  // now re-weight the path costs back to their original weightings
  for (int u = 1; u < g.size(); u++) {
    for (int v = 1; v < g.size(); v++) {
      if (allsp[u][v] != INF) {
        allsp[u][v] += ssp[v] - ssp[u];
      }
    }
  }

  return allsp;
}

int main (int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <infile>" << endl;
    return 1;
  }

  ifstream is {argv[1]};
  if (!is) {
    cerr << "Couldn't open input file: " << argv[1] << endl;
    return 1;
  }

  Graph g = loadgraph(is);

  // run Johnson's algorithm to get all pairs shortest paths
  AllSP asp = johnson(g);

  // find the "shortest shortest path", ie. the path with lowest cost,
  // amongst all shortest path pairs.
  long shortest = INF;
  for (int i = 1; i < g.size(); i++) {
    for (int j = 1; j < g.size(); j++) {
      if (asp[i][j] < shortest) {
        shortest = asp[i][j];
      }
    }
  }

  cout << "Shortest shortest path = " << shortest << endl;
}



///////////////////////////////////////////////////////////////////////////
//extended euclid

#include <stdio.h> 

int gcdExtended(int a, int b, int *x, int *y) 
{ 
    if (a == 0) 
    { 
        *x = 0; 
        *y = 1; 
        return b; 
    } 
  
    int x1, y1; // To store results of recursive call 
    int gcd = gcdExtended(b%a, a, &x1, &y1); 
  
    *x = y1 - (b/a) * x1; 
    *y = x1; 
  
    return gcd; 
} 
  
int main() 
{ 
    int x, y; 
    int a = 35, b = 15; 
    int g = gcdExtended(a, b, &x, &y); 
    printf("gcd(%d, %d) = %d", a, b, g); 
    return 0; 
} 




