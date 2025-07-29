#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=2000010;
const int maxm=110;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
inline int C(int m,int n){
	if(m<n||m<0||n<0)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int n,m;
int x[maxm],y[maxm];
int a[maxm][maxm];
int det(int n){
	int ans=1;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)if(a[j][i]){
			while(a[i][i]){
				int d=a[j][i]/a[i][i];
				for(int k=i;k<=n;k++)(a[j][k]+=mod-a[i][k]*d%mod)%=mod;
				swap(a[i],a[j]),ans=mod-ans;
			}
			swap(a[i],a[j]),ans=mod-ans;
		}
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)cout<<a[i][j]<<" ";cout<<"\n";
	// }
	for(int i=1;i<=n;i++)ans=ans*a[i][i]%mod;
	return ans;
}
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++)x[i]=read(),y[i]=read();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++)a[i][j]=C(y[i]-x[j]+n-1,n-1);
    }
    printf("%lld\n",det(m));
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    n=maxn-10;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;

    T=read();
    while(T--)work();
}