#include<bits/stdc++.h>
// #define int long long
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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn];
int pa[maxn],pb[maxn];
pii mx[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),pa[a[i]]=i;
	for(int i=1;i<=n;i++)b[i]=read(),pb[b[i]]=i;
	vector<pii> ans;
	for(int i=n;i;i--){
		if(pa[i]<pb[i]){puts("NO");return ;}
		mx[pb[i]-1]={0,0};for(int j=pb[i];j<=pa[i];j++){
			if(a[j]<=i)mx[j]=max(mx[j-1],{a[j],j});
			else mx[j]=mx[j-1];
		}
		int p=pa[i];
		while(p>pb[i]){
			auto[v,q]=mx[p-1];
			ans.pb({q,p});
			swap(a[p],a[q]);
			swap(pa[a[p]],pa[a[q]]);
			p=q;
		}
	}
	puts("YES");
	printf("%d\n",ans.size());
	for(auto[i,j]:ans)printf("%d %d\n",i,j);
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