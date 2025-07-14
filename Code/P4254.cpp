#include<bits/stdc++.h>
#define db double
using namespace std;
const int maxn=50010;
const int inf=1e9;
const db eps=1e-9;

int n,m;
struct line{
	db k,b;
}p[maxn<<1];
char opt[8];
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
int tree[maxn<<2];
db calc(int u,int x){return 1.0*(x*p[u].k+p[u].b);}
void upd(int nd,int l,int r,int id){
	if(l==r){
		if(calc(id,l)-calc(tree[nd],l)>eps)tree[nd]=id;
		return ;
	}
	if(calc(id,mid)-calc(tree[nd],mid)>eps)swap(tree[nd],id);
	if(calc(id,l)-calc(tree[nd],l)>eps)upd(ls,l,mid,id);
	else upd(rs,mid+1,r,id);
}
int query(int nd,int l,int r,int p){
	if(l==r)return tree[nd];
	int res;
	if(p<=mid)res=query(ls,l,mid,p);
	else res=query(rs,mid+1,r,p);
	if(calc(tree[nd],p)-calc(res,p)>eps)return tree[nd];
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	ios::sync_with_stdio(false);
	cin>>n;
	while(n--){
		cin>>opt+1;
		if(opt[1]=='P'){
			double s,d;
			cin>>s>>d;
			p[++m]={d,s-d};
			upd(1,1,maxn-10,m);
		}
		else{
			int u;cin>>u;
			int ans=query(1,1,maxn-10,u);
			cout<<(max(0,(int)(p[ans].k*u+p[ans].b))/100)<<"\n";
		}
	}
}
