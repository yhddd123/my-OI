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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int s,q;
map<tuple<int,int,int,int>,bool> mp;
bool sovle(int a1,int b1,int a2,int b2){
	// cout<<a1<<" "<<b1<<" "<<a2<<" "<<b2<<"\n";
	if(a1+b1*s<=0)return 0;
	if(a2>=s){
		if(a1<=0)return 0;
		return !sovle(a2-a1,b2,a1,b1);
	}
	if(a1>=s&&a2<=s)return 1;
	if(a1<=0){
		if(a2<=0){
			int k=max(1ll,min({b1,b2,(-a1)/s,(-a2)/s}));
			return sovle(a1+k*s,b1-k,a2+k*s,b2-k);
		}
		return !sovle(a2,b2,a1+s,b1-1);
	}
	if(a2<=0){
		if(b1)return !sovle(a2,b2,a1+s,b1-1);
		int k=(-a2)/(s-a1)+1;
		if(k>b2)return 1;
		return sovle(a1,b1,a2+k*(s-a1),b2-k);
	}
	if(a1+b1*(s-a2)>=s)return 1;
	if(mp.find({a1,b1,a2,b2})!=mp.end())return mp[{a1,b1,a2,b2}];
	if(b1){
		int k=max(1ll,min(b1,(a2-a1+b2*s-b2*a1-s)/((b2+1)*(s-a1))));
		if(sovle(a1+k*(s-a2),b1-k,a2,b2))return mp[{a1,b1,a2,b2}]=1;
	}
	return mp[{a1,b1,a2,b2}]=!sovle(a2-a1,b2,a1,b1);
}
void work(){
	s=read();q=read();
	while(q--){
		int c1=read(),f1=read(),c2=read(),f2=read();
		puts(sovle(c1-f2*s,f2,c2-f1*s,f1)?"YES":"NO");
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}