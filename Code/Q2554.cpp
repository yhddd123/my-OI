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

int n,a[1<<20];
void work(){
	n=read();
	for(int i=0;i<(1<<n);i++)a[i]=read();
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++)if(!(s&(1<<i))){
			for(int j=i+1;j<n;j++)if(!(s&(1<<j))){
				if(a[s|(1<<i)]+a[s|(1<<j)]<a[s]+a[s|(1<<i)|(1<<j)]){
					printf("%d %d\n",s|(1<<i),s|(1<<j));
					return ;
				}
			}
		}
	}
	puts("-1");
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