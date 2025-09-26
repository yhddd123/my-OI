// #include "festival.h"
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const ll inf=1e17;

struct node{
	int k;ll b;int id;
};
ll f[200010][65];
std::vector<int> max_coupons(int A, std::vector<int> P, std::vector<int> T) {
	int n=P.size();ll v=A;
	vector<node> a,b;
	for(int i=0;i<n;i++)(T[i]>1?a:b).pb({T[i],-1ll*P[i]*T[i],i});
	sort(a.begin(),a.end(),[&](node u,node v){return u.k*v.b+u.b<v.k*u.b+v.b;});
	sort(b.begin(),b.end(),[&](node u,node v){return u.b>v.b;});
	// for(auto[k,b,id]:a)cout<<k<<" "<<b<<" "<<id<<"\n";
	vector<int> id;
	int p=0;while(p<a.size()&&a[p].k*v+a[p].b>=v){
		id.pb(a[p].id);
		v=min(inf,a[p].k*v+a[p].b);
		p++;
	}
	memset(f,-1,sizeof(f));
	f[p][0]=v;
	for(int i=p;i<a.size();i++){
		for(int j=0;j<64;j++)if(f[i][j]>=0){
			f[i+1][j]=max(f[i+1][j],f[i][j]);
			if(a[i].k*f[i][j]+a[i].b>=0)f[i+1][j+1]=max(f[i+1][j+1],a[i].k*f[i][j]+a[i].b);
		}
	}
	pii mx={0,0};
	for(int i=64,j=0,s=0;~i;i--)if(f[a.size()][i]>=0){
		while(j<b.size()&&s-b[j].b<=f[a.size()][i])s-=b[j].b,j++;
		mx=max(mx,{i+j,i});
	}
	// cout<<mx.fi<<" "<<mx.se<<"\n";
	vector<int> id1;
	for(int i=a.size(),j=mx.se;i>p;i--){
		if(f[i][j]==f[i-1][j]){}
		else id1.pb(a[i-1].id),j--;
	}
	reverse(id1.begin(),id1.end());
	for(int u:id1)id.pb(u);
	v=f[a.size()][mx.se];
	for(int j=0;j<b.size();j++){
		if(v+b[j].b>=0)id.pb(b[j].id),v+=b[j].b;
	}
	return id;
}

// int main() {
  // int N, A;
  // assert(2 == scanf("%d %d", &N, &A));
  // std::vector<int> P(N), T(N);
  // for (int i = 0; i < N; i++)
    // assert(2 == scanf("%d %d", &P[i], &T[i]));
  // fclose(stdin);
// 
  // std::vector<int> R = max_coupons(A, P, T);
// 
  // int S = R.size();
  // printf("%d\n", S);
  // for (int i = 0; i < S; i++)
    // printf("%s%d", (i == 0 ? "" : " "), R[i]);
  // printf("\n");
  // fclose(stdout);
// 
  // return 0;
// }