// Problem: P9165 「INOH」Round 1 - 意外
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9165
// Memory Limit: 2 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-05-08 17:37:47
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
vector<int> Encode(vector<int> a){
	vector<int> ans(750);
	for(int i=0;i<150;i++){
		ll v=0;for(int j=99;~j;j--)v=(v*(i+1)+a[j])%mod;
		for(int j=0;j<5;j++)ans[i*5+j]=v;
	}
	return ans;
}
inline ll ksm(ll a,int b=mod-2){
	a=(a%mod+mod)%mod;
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
vector<int> Decode(vector<int> a){
	vector<ll> ans(100),f(101),ni(151);
	vector<pii> p;
	for(int i=0;i<150;i++){
		int v=-1;
		for(int j=0;j<5;j++){
			for(int k=j+1;k<5;k++)if(a[i*5+j]==a[i*5+k])v=a[i*5+j];
		}
		if(v>=0)p.pb({i+1,v});
	}
	p.resize(100);
	f[0]=1;
	for(int i=0;i<100;i++){
		for(int j=i+1;j;j--)f[j]=(f[j-1]+f[j]*(mod-p[i].fi))%mod;
		f[0]=f[0]*(mod-p[i].fi)%mod;
	}
	ni[0]=ni[1]=1;for(int i=2;i<=150;i++)ni[i]=ni[mod%i]*(mod-mod/i)%mod;
	for(int i=0;i<100;i++){
		ll val=p[i].se;
		for(int j=0;j<i;j++)val=val*ni[p[i].fi-p[j].fi]%mod;
		for(int j=i+1;j<100;j++)val=val*(mod-ni[p[j].fi-p[i].fi])%mod;
		f[0]=f[0]*(mod-ni[p[i].fi])%mod;
		for(int j=1;j<=100;j++)f[j]=(f[j]+mod-f[j-1])*(mod-ni[p[i].fi])%mod;
		for(int j=0;j<100;j++)(ans[j]+=val*f[j])%=mod;
		for(int j=100;j;j--)f[j]=(f[j-1]+f[j]*(mod-p[i].fi))%mod;
		f[0]=f[0]*(mod-p[i].fi)%mod;
	}
	vector<int> res(100);
	for(int i=0;i<100;i++)res[i]=ans[i];
	return res;
}
#undef mod

// const int mod = 998244353;
// const int test_time = 10000;
// mt19937 rndint(0);
// vector<int> in, out, tmp;
// int getmark(int);
// void wa(int);
// int main(){
	// int x, sum = 100;
	// in.resize(100);
	// for (int i = 0; i < test_time; ++i){
		// // cout<<i<<"\n";
		// for (int j = 0; j < 100; ++j)in[j] = rndint() % mod;
		// tmp = Encode(in);
		// for (int j : tmp)if (j < 0 || j >= mod)wa(-1);
		// for (int j = 0; j < tmp.size(); ++j)if (rndint() & 1)tmp[j] = rndint() % mod;
		// out = Decode(tmp);
		// if (out.size() != 100)wa(-2);
		// // for(int j=0;j<100;j++)cout<<in[j]<<" ";cout<<"\n";
		// // for(int j=0;j<100;j++)cout<<out[j]<<" ";cout<<"\n";
		// // for(int j=0;j<100;j++)cout<<tmp[j]<<" ";cout<<"\n";
		// for (int j = 0; j < 100; ++j)if (in[j] != out[j])wa(i);
		// sum = min(sum, getmark(tmp.size()));
	// }
	// printf ("%d\n", sum);
	// return 0;
// }
// int getmark(int a){
	// if (!a)return 0;
	// return min(100, int(1500 / ceil(a * 0.02)));
// }
// void wa(int op){
	// cout<<op<<"\n";
	// puts("Illegaled operation");
	// exit(0);
// }