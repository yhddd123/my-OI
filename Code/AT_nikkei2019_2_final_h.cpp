// Problem: AT_nikkei2019_2_final_h 逆にする関数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_nikkei2019_2_final_h
// Memory Limit: 1 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2025-06-02 13:56:33
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
const int maxn=600010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],ans;
int pw[maxn];
int pre[maxn],suf[maxn],pos[maxn];
int len[maxn],f[maxn],cnt[maxn];
bool check(int l,int r){
	if(l<1||r>n)return 0;
	if(pre[r]<l&&suf[l]>r)return 1;
	if(pre[r]>=l)return a[l+r-pre[r]]==a[l];
	if(suf[l]<=r)return a[l+r-suf[l]]==a[r];
	return 0;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i*2]=read();n=2*n+1;
	pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*m%mod;
	for(int i=1;i<=n;i++)pre[i]=pos[a[i]],pos[a[i]]=i;
	for(int i=0;i<=m;i++)pos[i]=n+1;
	for(int i=n;i;i--)suf[i]=pos[a[i]],pos[a[i]]=i;
	int mid=0,l=0,r=0;
	for(int i=1;i<=n;i++){
		int j=2*mid-i;
		if(i<=r){
			len[i]=len[j],f[i]=f[j],cnt[i]=cnt[j];
			if(i+len[i]>r){
				for(int k=j-len[j];k<=l-1;k++){
					if(a[k])(f[i]+=mod-pw[m-cnt[i]+1])%=mod;
					if(suf[k]>2*j-k)cnt[i]--;
					if(pre[2*j-k]<=k)cnt[i]--;
				}
				for(int k=r+1;k<=i+len[i];k++){
					if(!check(2*i-k,k)){len[i]=k-i-1;break;}
					if(pre[k]<=2*i-k)cnt[i]++;
					if(suf[2*i-k]>k)cnt[i]++;
					if(a[k])(f[i]+=pw[m-cnt[i]+1])%=mod;
				}
			}
		}
		else f[i]=pw[m-1]*(a[i]!=0),cnt[i]=1;
		while(check(i-len[i]-1,i+len[i]+1)){
			len[i]++;
			if(pre[i+len[i]]<=i-len[i])cnt[i]++;
			if(suf[i-len[i]]>i+len[i])cnt[i]++;
			if(a[i+len[i]])(f[i]+=pw[m-cnt[i]+1])%=mod;
		}
		if(i+len[i]>=r)mid=i,l=i-len[i],r=i+len[i];
		(ans+=f[i])%=mod;
	}
	printf("%lld\n",ans);
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