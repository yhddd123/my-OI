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
const int maxn=1000010;
const int inf=1e18;
bool mbe;

int n,q,a[maxn];
int mn[20][maxn],mx[20][maxn];
int quemn(int l,int r){
	if(l>r)return inf;
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
int quemx(int l,int r){
	if(l>r)return -inf;
	int k=__lg(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1]);
}
vector<pii> que[maxn];
int ans[maxn];
int st[maxn],tp;
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=n;i++)mn[0][i]=mx[0][i]=a[i];
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
			mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
		}
	}
	for(int i=1;i<=q;i++){
		int op=read(),l=read(),r=read();
		que[r].pb({l,i});
		ans[i]=abs(a[r]-a[l-1]);
		ans[i]=max({ans[i],min(a[l-1],a[r])-quemn(l,r-1),quemx(l,r-1)-max(a[l-1],a[r])});
	}
	auto sovle=[&](){
		tp=0;for(int i=1;i<=n;i++){
			while(tp&&a[st[tp]]<=a[i])tp--;
			st[++tp]=i;
			for(auto[j,id]:que[i]){
				int l=upper_bound(st+1,st+tp+1,j)-st,r=tp,res=l-1;
				while(l<=r){
					int mid=l+r>>1;
					if(a[st[mid]]-a[i]>=a[j-1]-quemn(j,st[mid]-1))res=mid,l=mid+1;
					else r=mid-1;
				}
				if(st[res]>j)ans[id]=max(ans[id],a[j-1]-quemn(j,st[res]-1));
				if(res+1<=tp)ans[id]=max(ans[id],a[st[res+1]]-a[i]);
			}
		}
	};
	sovle();
	for(int i=1;i<=n;i++)a[i]=-a[i];
	for(int j=0;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mn[j][i]=-mn[j][i],mx[j][i]=-mx[j][i],swap(mn[j][i],mx[j][i]);
	}
	sovle();
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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