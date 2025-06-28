// Problem: P11346 [KTSC 2023 R2] 会议室 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11346
// Memory Limit: 1000 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-30 09:37:25
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
const int maxn=4010;

ll fac[maxn],inv[maxn];
int lsh[maxn],len;
ll f[maxn][maxn],g[maxn][maxn];
int pl[maxn],pr[maxn];
int cnt[maxn];
ll calc(vector<pii> a){
	int n=a.size();++cnt[n];
	len=0;for(auto[l,r]:a)lsh[++len]=l,lsh[++len]=r;
	sort(lsh+1,lsh+len+1);
	for(int i=1;i<=len;i++)pl[i]=pr[i]=0;
	for(int i=1;i<=len;i++){
		for(int j=1;j<=len;j++)f[i][j]=g[i][j]=0;
		pl[i]=pr[i]=0;
	}
	for(auto&[l,r]:a){
		l=lower_bound(lsh+1,lsh+len+1,l)-lsh;
		r=lower_bound(lsh+1,lsh+len+1,r)-lsh;
		f[l][r]++,g[l][r]++;
		pl[l]=r,pr[r]=l;
	}
	auto calc=[&](int l,int r,int p,int q){
		return (f[l][q]+2*mod-f[r+1][q]-f[l][p-1]+f[r+1][p-1])%mod;
	};
	for(int l=len;l;l--){
		for(int r=l;r<=len;r++){
			if(g[l][r])(f[l][r]+=f[l+1][r]+f[l][r-1]+mod-f[l+1][r-1])%=mod;
			if(pl[l]&&pl[l]<r)(f[l][r]+=calc(l+1,pl[l],r,r))%=mod;
			if(pr[r]&&pr[r]>l)(f[l][r]+=calc(l,l,pr[r],r-1))%=mod;
			(g[l][r]+=g[l+1][r]+g[l][r-1]+mod-g[l+1][r-1])%=mod;
			f[l][r]=f[l][r]*inv[n-g[l][r]]%mod;
			(f[l][r]+=f[l+1][r]+f[l][r-1]+mod-f[l+1][r-1])%=mod;
		}
	}
	// cout<<n<<" "<<f[1][len]<<"\n";
	return calc(1,1,len,len)*fac[n]%mod*inv[n]%mod;
}
int count_removals(std::vector<int> S, std::vector<int> E){
	int n=S.size();ll ans=1;
	vector<pii> a;for(int i=0;i<n;i++)a.pb({S[i],E[i]});
	sort(a.begin(),a.end());
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[0]=inv[1]=1;for(int i=2;i<=n;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=0,j;i<n;i=j+1){
		j=i;int mx=a[i].se;
		while(j+1<n&&mx>=a[j+1].fi){
			j++;
			mx=max(mx,a[j].se);
		}
		vector<pii> b;
		for(int k=i;k<=j;k++)b.pb(a[k]);
		ans=ans*calc(b)%mod;
	}
	for(int i=1;i<=n;i++)ans=ans*fac[cnt[i]]%mod;
	return ans;
}

// void my_assert(bool x){
	// if(!x){
		// puts("Wrong input");
		// exit(0);
	// }
// }
// int main(){
	// int N;
	// my_assert(scanf("%d", &N) == 1);
	// std::vector<int> S(N), E(N);
	// for(int i = 0; i < N; i++){
		// my_assert(scanf("%d %d", &S[i], &E[i]) == 2);
	// }
	// int ans = count_removals(S, E);
	// printf("%d\n", ans);
	// return 0;
// }