// Problem: P10217 [省选联考 2024] 季风
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10217
// Memory Limit:  MB
// Time Limit:  ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl;
}
const int maxn=100010;
const int inf=2e18;

int n,k,x,y;
int a[maxn],b[maxn];
void work(){
	n=read();k=read();x=read();y=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read(),b[i]=b[i-1]+read();
	int ans=inf;
	for(int i=0;i<n;i++){
		int l=0,r=inf;
		int nx=x+y-a[i]-b[i],ny=x-y-a[i]+b[i];
//		cout<<nx<<" "<<ny<<"\n";
		if(!(a[n]+b[n]+n*k)){
			if(nx-i*k>0)continue;
		}                               
		else{
			int val=a[n]+b[n]+n*k,v=nx-i*k;
			if(val>0)l=max(l,(v+val-1)/val);
			else{
				if(v*val<0)continue;
				v=-v,val=-val,r=min(r,v/val);
			} 
		} 
//		cout<<l<<" "<<r<<"\n";
		if(!(a[n]+b[n]-n*k)){
			if(nx+i*k<0)continue;
		}
		else{
			int val=a[n]+b[n]-n*k,v=nx+i*k;
			if(val>0){
				if(v*val<0)continue;
				r=min(r,v/val);
			} 
			else v=-v,val=-val,l=max(l,(v+val-1)/val);
		} 
//		cout<<l<<" "<<r<<"\n";
		if(!(a[n]-b[n]+n*k)){
			if(ny-i*k>0)continue;
		}
		else{
			int val=a[n]-b[n]+n*k,v=ny-i*k;
			if(val>0)l=max(l,(v+val-1)/val);
			else{
				if(v*val<0)continue;
				v=-v,val=-val,r=min(r,v/val);
			} 
		} 
//		cout<<l<<" "<<r<<"\n";
		if(!(a[n]-b[n]-n*k)){
			if(ny+i*k<0)continue;
		}
		else{
			int val=a[n]-b[n]-n*k,v=ny+i*k;
			if(val>0){
				if(v*val<0)continue;
				r=min(r,v/val);
			} 
			else v=-v,val=-val,l=max(l,(v+val-1)/val);
//			cout<<ny+i*k<<" "<<val<<"\n";
		} 
//		cout<<l<<" "<<r<<"\n";
		if(l>r)continue;
		else ans=min(ans,l*n+i);
//		cout<<l<<" "<<r<<" "<<ans<<"\n";
	}
	if(ans==inf)ans=-1;
	printf("%lld\n",ans);
}

int T;
signed main(){
	T=read();
	while(T--)work();
} 

