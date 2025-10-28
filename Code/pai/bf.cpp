#include<bits/stdc++.h>
#define int unsigned
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline unsigned read(){
	unsigned x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,q,m,a[maxn];
void work(){
	n=read();q=read();m=read();m=(m==32?-1:(1<<m)-1);
	for(int i=0;i<n;i++)a[i]=read();
	while(q--){
		int op=read();
		if(op==0){
			int l=read(),r=read(),w=read();
			for(int i=l;i<r;i++)a[i]=(a[i]+w)&m;
		}
		else{
			int l=read(),r=read(),ans=m;
			for(int i=l;i<r;i++)ans&=a[i];
			printf("%u\n",ans);
		}
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