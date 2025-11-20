// Problem: P14510 夜里亦始终想念着你 miss
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14510
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-20 20:57:19
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=500010;
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
int fac[maxn],inv[maxn],pw[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
}
int n,q;
char s[maxn];
int m,v,f;
int calc(int mm,int vv){
	while(m>mm){
		(f+=mod-C(v+m-1,m)*pw[n-v-m]%mod)%=mod;
		m--;
	}
	while(m<mm){
		m++;
		(f+=C(v+m-1,m)*pw[n-v-m])%=mod;
	}
	while(v<vv){
		(f+=mod-pw[n-v-m-1]*C(v+m,v)%mod)%=mod;
		v++;
	}
	while(v>vv){
		v--;
		(f+=pw[n-v-m-1]*C(v+m,v))%=mod;
	}
	return f;
}
set<int> ss;
int p,num;
void ins(int i){
	++num;
	auto it=ss.insert(i).fi;
	if(it==--ss.end())p+=1+((i&1)==((*--it)&1));
	else{
		int pl=(*--it)&1;it++;
		int pr=(*++it)&1;
		if(pl==pr)p+=((i&1)==pl)*2;
		else p+=2;
	}
}
void del(int i){
	--num;
	auto it=ss.erase(ss.find(i));
	if(it==ss.end())p-=1+((i&1)==((*--it)&1));
	else{
		int pl=(*--it)&1;it++;
		int pr=(*it)&1;
		if(pl==pr)p-=((i&1)==pl)*2;
		else p-=2;
	}
}
void calc(){
	// int p=0,num=0;
	// for(int i=1,lst=0;i<=n;i++)if(s[i]=='0'){
		// p+=1+((i&1)==lst);
		// lst=i&1;
		// ++num;
	// }
	// if(!num){printf("%lld\n",pw[n]);return ;}
	// int m=(n-p)/2,ans=0;
	// cout<<p<<" "<<num<<"\n";
	// for(int i=0;i<=m;i++)(ans+=pw[n-num-i]*C(num+i-1,i))%=mod;
	printf("%lld\n",calc((n-p)/2,num));
}
void work(){
	n=read();q=read();init(n);
	scanf("%s",s+1);
	ss.insert(0);
	for(int i=1;i<=n;i++)if(s[i]=='0')ins(i);
	m=v=0,f=pw[n];
	calc();
	while(q--){
		int p=read();
		if(s[p]=='0')del(p),s[p]='1';
		else ins(p),s[p]='0';
		calc();
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