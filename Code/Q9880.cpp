#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=2010;
const int inf=2e9;
bool mbe;

int n,q;
vector<int> a[4];
void work(){
	n=read();
	for(int i=0;i<4;i++)a[i].clear();
	bool fl=0,flo=1;
	for(int i=1;i<=n;i++){
		int u=read(),v=read(),x=read(),y=read();
		int dx=u-x,dy=v-y;
		if(dx==dy)a[0].pb(v-u);
		else if(dx+dy==0)a[1].pb(u+v);
		else if(!dx)a[2].pb(u);
		else if(!dy)a[3].pb(v);
		else fl=1;
		flo&=(u*y==x*v);
	}
	q=read();
	if(fl&&flo){
		while(q--){
			int u=read(),v=read(),x=read(),y=read();
			if(u*u+v*v==x*x+y*y)puts("Yes");
			else puts("No");
		}
		return ;
	}
	if(fl){
		while(q--){
			int u=read(),v=read(),x=read(),y=read();
			puts("Yes");
		}
		return ;
	}
	if(!a[0].size()&&!a[1].size()){
		int gx=0,gy=0;
		for(int d:a[2])gx=__gcd(gx,abs(2*d));
		for(int d:a[3])gy=__gcd(gy,abs(2*d));
		auto get=[&](int u,int v){
			if(!gx)u=abs(u);
			else u=abs(((u%gx)+gx)%gx-gx/2);
			if(!gy)v=abs(v);
			else v=abs(((v%gy)+gy)%gy-gy/2);
			return mkp(u,v);
		};
		while(q--){
			int u=read(),v=read(),x=read(),y=read();
			if(get(u,v)==get(x,y))puts("Yes");
			else puts("No");
		}
		return ;
	}
	int g=0;
	for(int op=0;op<4;op++){
		for(int d:a[op])g=__gcd(g,abs(2*d));
	}
	bool op0=0,op1=0;
	if(!g)op0=1;
	else{
		for(int d:a[0]){
			if(((d+g)%g+g)%g==0)op0=1;
			else op1=1;
		}
		for(int d:a[1]){
			if(((d+g)%g+g)%g==0)op0=1;
			else op1=1;
		}
	}
	auto get=[&](int u,int v){
		if(!g)u=abs(u),v=abs(v);
		else{
			u=((u+g)%g+g)%g,v=((v+g)%g+g)%g;
			if(u>g/2)u=g-u;
			if(v>g/2)v=g-v;
		}
		// cout<<u<<" "<<v<<"\n";
		if(op1){
			if(u+v>g/2)swap(u,v),u=g/2-u,v=g/2-v;
		}
		if(op0){
			if(u>v)swap(u,v);
		}
		// cout<<u<<" "<<v<<"\n";
		return mkp(u,v);
	};
	while(q--){
		int u=read(),v=read(),x=read(),y=read();
		if(get(u,v)==get(x,y))puts("Yes");
		else puts("No");
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}