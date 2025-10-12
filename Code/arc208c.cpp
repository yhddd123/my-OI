// Problem: C - Mod of XOR
// Contest: AtCoder - AtCoder Regular Contest 208 (Div. 2)
// URL: https://atcoder.jp/contests/arc208/tasks/arc208_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-12 20:19:41
// 
// Powered by CP Editor (https://cpeditor.org)

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

int n,c,x;
int v1[40],v2[40];
void work(){
	c=read();x=read();
	if((c^x)>x){
		n=c^x;
		cout<<n<<"\n";
	}
	else{
		// assert(__lg(c)<=__lg(x));
		int pp=__lg(x);
		n=1ll<<(pp+1);
		for(int i=0;i<=30;i++)v1[i]=(c>>i)&1,v2[i]=(x>>i)&1;
		for(int i=0;i<pp;i++)if(v1[i]&&v2[i]){
			int p=i;
			for(int j=i+1;j<=pp;j++){
				if(v1[j]&&v2[j])break;
				if(!v1[j]&&!v2[j])break;
				p=j;
			}
			if(i<p){
				if(v1[p]&&!v2[p]){
					n|=1<<i;
					for(int j=i+1;j<p;j++){
						if(v1[j]&&!v2[j])n|=1<<j;
					}
				}
			}
		}
		if((n^c)%n!=x){
			// for(int v=1;v<=2*n;v++)if((v^c)%v==x){
				// cout<<c<<" "<<x<<" "<<v<<endl;
				// assert(0);
			// }
			puts("-1");}
		else printf("%lld\n",n);
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