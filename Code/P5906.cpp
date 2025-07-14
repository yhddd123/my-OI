// Problem: P5906 【模板】回滚莫队&不删除莫队
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5906
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-05-30 09:52:19
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],m,B;
struct ask{
	int l,r,id;
}que[maxn];int ans[maxn];
int lsh[maxn],len;
int pl[maxn],pr[maxn];
int calc(int l,int r){
	int res=0;for(int i=l;i<=r;i++)pl[a[i]]=0;
	for(int i=l;i<=r;i++){
		if(!pl[a[i]])pl[a[i]]=i;
		else res=max(res,i-pl[a[i]]);
	}
	for(int i=l;i<=r;i++)pl[a[i]]=0;
	return res;
}
void work(){
	n=read();B=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=lsh[i]=read();
	sort(lsh+1,lsh+n+1);len=unique(lsh+1,lsh+n+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	m=read();
	for(int i=1;i<=m;i++)que[i]={read(),read(),i};
	sort(que+1,que+m+1,[&](ask u,ask v){
		if(u.l/B==v.l/B)return u.r<v.r;
		return u.l<v.l;
	});
	for(int i=0,j=1;i<=n/B;i++){
		int l=min(n,(i+1)*B-1)+1,r=l-1,res=0;
		vector<int> id;
		while(j<=m&&que[j].l/B==i){
			if(que[j].r/B==i)ans[que[j].id]=calc(que[j].l,que[j].r);
			else{
				while(r<que[j].r){
					++r;pr[a[r]]=r;
					if(!pl[a[r]])pl[a[r]]=r,id.push_back(a[r]);
					res=max(res,r-pl[a[r]]);
				}
				int nw=res;
				while(l>que[j].l){
					--l;
					if(pr[a[l]])res=max(res,pr[a[l]]-l);
					else pr[a[l]]=l;
				}
				// cout<<l<<" "<<r<<" "<<res<<"\n";
				ans[que[j].id]=res;
				while(l<min(n,(i+1)*B-1)+1){
					if(pr[a[l]]==l)pr[a[l]]=0;
					l++;
				}
				res=nw;
			}
			j++;
		}
		for(int k:id)pl[k]=pr[k]=0;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
