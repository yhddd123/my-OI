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
const int maxn=20;
const int maxm=1000010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,m,a[maxn],S,T;
int e[maxn],t[1<<maxn],num[1<<maxn];
char s[1000010];
int f[1<<maxn];
void work(){
	n=read();m=read();init(n);
	for(int i=0;i<m;i++)e[i]=a[i]=read();
	for(int i=m;i<n;i++)t[a[i]=read()]++;
	scanf("%s",s);
	for(int i=0;i<m;i++)if(s[i]=='1')S|=1<<i;T=1<<m-1-S;
	for(int s=0;s<(1<<m);s++)num[s]=t[s];
	for(int i=0;i<m;i++){
		if(S&(1<<i)){
			for(int s=0;s<(1<<m);s++)if(s&(1<<i))num[s^(1<<i)]+=num[s];
		}
		else{
			for(int s=0;s<(1<<m);s++)if(s&(1<<i))num[s]+=num[s^(1<<i)];
		}
	}
	for(int i=0;i<n;i++){
		if(s[i]=='1'){
			if(S&a[i]){puts("0");return ;}
		}
		else{
			if(T&a[i]){puts("0");return ;}
		}
	}
	for(int s=0;s<(1<<m);s++)num[s]+=__builtin_popcount(s);
	f[0]=1;
	for(int s=0;s<(1<<n);s++){
		int s1=s&S,t1=s&T;
		for(int s2=s1;;s2=(s2-1)&s1){
			for(int t2=t1;;t2=T^(((T^t2)-1)&(T^t1))){
				inc(f[s1|t2],1ll*f[s]*t[s2|t2]%mod*C(num[s1|t2]-num[s]-1,num))
				if(t2==T)break;
			}
			if(!s2)break;
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