#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1010;
const int inf=1e9;
bool mbe;

int n,tim,a[maxn];
int ask(int l,int r){
	// cout<<"? "<<l<<" "<<r<<endl;
	// return read();
	++tim;
	int s=0;for(int i=l;i<=r;i++)s+=a[i];
	return s;
}
mt19937 rnd(time(0));
const int B=50;
int id[maxn];
struct node{
	int l,r,s;
	bool operator<(const node &u)const{return s*(u.r-u.l+1)>u.s*(r-l+1);}
};
priority_queue<node> q;
bool vis[maxn];
void add(int l,int r,int s){
	if(r-l+1==2){
		if(s>n+1)return ;
		if(vis[s-1])return ;
	}
	// int v=0;for(int i=2,t=1;i<=n&&t<=r-l+1;i++)if(!vis[i])v+=i,t++;
	// if(v>s){
		// while(!q.empty())q.pop();
	// }
	if(l==r)vis[s]=1;
	q.push({l,r,s});
}
void work(){
	for(int i=1;i<=n;i++)a[i]=i;shuffle(a+1,a+n+1,rnd);
	for(int i=1;i<=n;i++)vis[i]=0;
	while(!q.empty())q.pop();
	int s=n*(n+1)/2;
	q.push({1,n,s});
	while(!q.empty()){
		auto[l,r,s]=q.top();q.pop();
		if(l==r){
			if(s==1){
				cout<<"! "<<l<<endl;
				return ;
			}else vis[s]=1;
			continue;
		}
		int mid=l+r>>1;
		int v=ask(l,mid);
		add(l,mid,v),add(mid+1,r,s-v);
		// q.push({l,mid,v}),q.push({mid+1,r,s-v});
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();n=read();
	while(T--)work();
	
	cout<<tim<<"\n";
}