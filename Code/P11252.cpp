#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int maxn=200010;
	
void construct_two_trees(int N, std::vector<int> U, std::vector<int> V);
int add_vertex(int i, int j, int k);
void report(std::vector<std::array<int, 2>> tree);

int n;
vector<int> e[maxn];
vector<array<int, 2>> t1,t2;
bool in(int u,int l,int r){return (l<=u&&u<=r)||(l<=u+n&&u+n<=r);}
void sovle(int l,int r){
	if(l+1==r)return ;
	rotate(e[r%n].begin(),upper_bound(e[r%n].begin(),e[r%n].end(),l%n),e[r%n].end());
	int lst=l;
	for(int x:e[r%n])if(in(x,l+1,r)){
		t1.pb({r%n,x});
		t2.pb({lst%n,x});
		sovle(lst,x+(x<l)*n);
		lst=x+(x<l)*n;
	}
}
void construct_two_trees(int N,vector<int> U,vector<int> V){
	n=N;
	for(int i=0;i<n;i++)e[i].pb((i+1)%n),e[(i+1)%n].pb(i);
	int p=0;
	for(int i=0;i<n-3;i++){
		int u=U[i],v=V[i];
		e[u].pb(v),e[v].pb(u);
		if(u>v)swap(u,v);
		if(u+2==v)p=u;
	}
	add_vertex(p,p+1,p+2);
	for(int i=0;i<n;i++)sort(e[i].begin(),e[i].end());
	t1.pb({p+1,n}),t1.pb({p,n}),t1.pb({p,p+2});
	t2.pb({p,p+1}),t2.pb({p+1,p+2}),t2.pb({p+2,n});
	sovle(p+2,p+n);
	report(t1);report(t2);
}

// static int N, C = 0;
// static bool reported = false;
// static std::vector<std::array<int,3>>added;
// 
// 
// void my_assert(bool x, char *msg){
	// if(!x){
	    // printf("%s\n", msg);
		// exit(0);
	// }
// }
// 
// int add_vertex(int i, int j, int k){
    // my_assert(!reported, "add_vertex called after report");
    // added.push_back({i,j,k});
    // N++;
    // return N-1;
// }
// 
// void report(std::vector<std::array<int, 2>> tree){
    // reported = true;
    // C++;
    // printf("%d\n%d\n", C, (int)(tree.size()));
    // for(auto &[u, v]: tree){
        // printf("%d %d\n",u, v);
    // }
// }
// 
// int main(){
	// scanf("%d", &N);
	// std::vector<int> U(N-3), V(N-3);
	// for(int i = 0; i < N-3; i++){
	    // scanf("%d%d",&U[i],&V[i]);
	// }
	// construct_two_trees(N, U, V);
    // printf("%d\n",(int)added.size());
    // for(auto &triangle: added){
        // printf("%d %d %d\n",triangle[0],triangle[1],triangle[2]);
    // }
// }