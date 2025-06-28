#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=2e9;
bool mbe;

int n,u,v,d;
int id(int u){
	if(u<=0)u+=n;
	if(u>n)u-=n;
	return u;
}
int ask(int u,int v){
	u=id(u),v=id(v);
	if(u==v)return 0;
	printf("? %lld %lld\n",u,v);fflush(stdout);
	return read();
}
int dis(int u,int v){
	u=id(u),v=id(v);
	if(u>v)swap(u,v);
	return min(v-u,n-(v-u));
}
bool chk(int u,int v){return ask(u,v)==dis(u,v);}
void work(){
	n=read();
	u=v=0;
	if(n&1){
		if(!chk(1,(n+1)/2))u=1,v=(n+1)/2;
		else if(!chk(1,(n+1)/2+1))u=1,v=(n+1)/2+1;
		else if(!chk(2,(n+1)/2+1))u=2,v=(n+1)/2+1;
		else if(!chk(2,(n+1)/2+2))u=2,v=(n+1)/2+2;
		else if(!chk(3,(n+1)/2+2))u=3,v=(n+1)/2+2;
	}
	else{
		if(!chk(1,n/2+1))u=1,v=n/2+1;
		else if(!chk(2,n/2+2))u=2,v=n/2+2;
		else if(!chk(3,n/2+3))u=3,v=n/2+3;
	}
	assert(u&&v);
	// cout<<u<<" "<<v<<"\n";
	d=ask(u,v);
	if(ask(u-1,v)==d-1){
		u+=n;
		int l=v,r=u,res=u;
		while(l<=r){
			int mid=l+r>>1;
			if(ask(v,mid)+dis(u,mid)==d)res=mid,r=mid-1;
			else l=mid+1;
		}
		d-=dis(u,res)+1,u=res;
		if(ask(v+d,u)==1)v=v+d;
		else v=v-d;
	}
	else if(ask(u+1,v)==d-1){
		int l=u,r=v,res=u;
		while(l<=r){
			int mid=l+r>>1;
			if(ask(v,mid)+dis(u,mid)==d)res=mid,l=mid+1;
			else r=mid-1;
		}
		d-=dis(u,res)+1,u=res;
		if(ask(v+d,u)==1)v=v+d;
		else v=v-d;
	}
	else{
		d--;
		if(ask(v+d,u)==1)v=v+d;
		else v=v-d;
	}
	u=id(u),v=id(v);
	printf("! %lld %lld\n",u,v);fflush(stdout);
	int op=read();
	if(op==-1)exit(0);
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