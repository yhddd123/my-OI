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

int n;
map<int,int> mp;
void work(){
	n=read();mp.clear();
	for(int i=1;i<=2*n;i++){
		int x=read();
		mp[x]++;
	}
	int cnt=0,ss=0;
	int x1=-1,x2=-1;
	for(auto[v,t]:mp){
		ss^=((t/2)&1)*v;
		if(t&1){
			cnt+=(t&1);
			if(x1==-1)x1=v;
			else if(x2==-1)x2=v;
		}
	}
	puts(((cnt==0&&ss==0)||(cnt==2&&(x1==ss||x2==ss)))?"Menji":"Bot");
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