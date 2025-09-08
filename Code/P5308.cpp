#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=200010;
const int inf=1e9;
const db eps=1e-12;
bool mbe;

int n,k;
db f[maxn];int g[maxn];
int q[maxn],h,t;
int check(db x){
	q[h=t=1]=f[0];
	for(int i=1;i<=n;i++){
		while(h<t&&(f[q[h+1]]-f[q[h]])/(q[h+1]-q[h])>1.0/i+eps)h++;
		f[i]=f[q[h]]+1.0*(i-q[h])/i-x,g[i]=g[q[h]]+1;
		while(h<t&&(f[q[t]]-f[q[t-1]])/(q[t]-q[t-1])+eps<(f[i]-f[q[t]])/(i-q[t]))t--;
		q[++t]=i;
	}
	// cout<<x<<" "<<f[n]<<" "<<g[n]<<" "<<f[n]+k*x<<"\n";
	return g[n];
}
void work(){
    n=read();k=read();
    db l=0,r=1;
    for(int t=1;t<=100;t++){
    	db mid=(l+r)/2.0;
    	if(check(mid)<=k)r=mid;
    	else l=mid;
    }
    check(l);
    printf("%.9Lf\n",f[n]+k*l);
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