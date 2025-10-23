#include<bits/stdc++.h>
#define int long long
#define mod 1000003
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
const int maxn=450010;
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
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,m;
char s[maxn];
int t[26];
int val[110][110],f[110][110],g[110][110];
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	m=0;for(int l=1,r=1;l<=n;l=r){
		while(r<=n&&s[l]==s[r])r++;
		++m;
	}
	for(int i=0;i<26;i++)t[i]=0;
	for(int i=1;i<=n;i++)t[s[i]-'a']++;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=m;j++)f[i][j]=0;
	}
	f[0][0]=1;
	for(int i=0;i<26;i++)if(t[i]){
		for(int j=1;j<=t[i]&&j<=m;j++){
			for(int k=1;k<=j&&k<=m;k++){
				val[j][k]=((((j-k)&1)?mod-1:1)*inv[k]%mod*C(j-1,k-1)%mod*C(t[i]-1,j-1))%mod;
				// cout<<j<<" "<<k<<" "<<val[j][k]<<"\n";
			}
		}
		for(int j=0;j<=m;j++){
			for(int k=0;k<=j;k++)if(f[j][k]){
				// cout<<i<<" "<<j<<" "<<k<<" "<<f[j][k]<<"\n";
				for(int jj=1;jj<=t[i]&&j+jj<=m;jj++){
					for(int kk=1;kk<=jj;kk++){
						(g[j+jj][k+kk]+=f[j][k]*val[jj][kk]%mod)%=mod;
					}
				}
			}
		}
		for(int j=0;j<=m;j++){
			for(int k=0;k<=j;k++)f[j][k]=g[j][k],g[j][k]=0;
		}
	}
	// for(int i=1;i<=m;i++)cout<<f[m][i]<<" ";cout<<"\n";
	int ans=0;for(int i=1;i<=m;i++)(ans+=f[m][i]*fac[i])%=mod;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("runs.in","r",stdin);
	// freopen("runs.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();init(maxn-10);
	for(int t=1;t<=T;t++){
		printf("Case #%lld: ",t);
		work();
	}
}