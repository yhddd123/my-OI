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
const int maxn=5000010;
const int inf=1e9;
bool mbe;

int op,l,r,ans;
pii sovle(int l,int r){
	if(l==r)return {1,0};
	int k=__lg(l^r);
	if(l+(1ll<<k+1)-1==r)return {1ll<<k,1ll<<k};
	int p=((l&r)>>k<<k)|(1ll<<k);
	// cout<<l<<" "<<p<<" "<<r<<"\n";
	auto[l1,l2]=sovle(l,p-1);
	auto[r1,r2]=sovle(p,r);
	if(__builtin_parityll(l&((1ll<<k)-1))==__builtin_parityll(p&((1ll<<k)-1)))return {l1+r2,l2+r1};
	else return {l1+r1,l2+r2};
}
void merge(vector<int> &a,vector<int> &b){
	int n=a.size(),m=b.size();
	a.resize(n+m);
	for(int i=0;i<m;i++)a[i+n]=b[i];
}
pair<vector<int>,vector<int>> sovle1(int l,int r){
	if(l==r)return {{l},{}};
	int k=__lg(l^r);
	if(l+(1ll<<k+1)-1==r){
		vector<int> al,ar;
		int o=__builtin_parityll(l);
		for(int s=l;s<=r;s++)(__builtin_parityll(s)==o?al:ar).pb(s);
		return {al,ar};
	}
	int p=((l&r)>>k<<k)|(1ll<<k);
	auto[l1,l2]=sovle1(l,p-1);
	auto[r1,r2]=sovle1(p,r);
	vector<int> vl,vr;
	if(__builtin_parityll(l&((1ll<<k)-1))==__builtin_parityll(p&((1ll<<k)-1))){
		merge(l1,r2),merge(l2,r1);
		return {l1,l2};
	}
	else{
		merge(l1,r1),merge(l2,r2);
		return {l1,l2};
	}
}
bool vis[maxn];
void work(){
	op=read(),l=read(),r=read();ans=0;
	if(l==r){puts("1");return ;}
	if(!op){
		int k=__lg(l^r);
		if(l<=r-(1ll<<k)){
			auto[ans1,ans2]=sovle(l,r);
			printf("%lld\n",max(ans1,ans2));
		}
		else{
			int p=((l&r)>>k<<k)|(1ll<<k);
			// cout<<l<<" "<<p<<" "<<r<<"\n";
			auto[ans1,ans2]=sovle(l,p-1);
			auto[ans3,ans4]=sovle(p,r);
			printf("%lld\n",max(ans1,ans2)+max(ans3,ans4));
		}
	}
	else{
		for(int i=0;i<=r-l+1;i++)vis[i]=0;
		int k=__lg(l^r);
		if(l<=r-(1ll<<k)){
			auto[ans1,ans2]=sovle1(l,r);
			if(ans2.size()>ans1.size())swap(ans1,ans2);
			for(int u:ans1)vis[u-l]=1;
		}
		else{
			int p=((l&r)>>k<<k)|(1ll<<k);
			// cout<<l<<" "<<p<<" "<<r<<"\n";
			auto[ans1,ans2]=sovle1(l,p-1);
			auto[ans3,ans4]=sovle1(p,r);
			if(ans2.size()>ans1.size())swap(ans1,ans2);
			for(int u:ans1)vis[u-l]=1;
			if(ans4.size()>ans3.size())swap(ans3,ans4);
			for(int u:ans3)vis[u-l]=1;
		}
		for(int i=0;i<=r-l;i++)putchar(vis[i]?'1':'0');puts("");
		// int num=0;for(int i=0;i<=r-l;i++)num+=vis[i];
		// cout<<num<<"\n";
		// for(int i=l;i<=r;i++)if(vis[i-l]){
			// for(int j=i+1;j<=r;j++)if(vis[j-l]){
				// if(__builtin_popcountll(i^j)==1){
					// cout<<"err\n";
					// cout<<i<<" "<<j<<"\n";
					// return ;
				// }
			// }
		// }
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}