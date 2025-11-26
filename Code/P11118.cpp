#include<bits/stdc++.h>
#define ll long long
#define pii pair<ll,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=150010;

int n,m;
int a[maxn],b[maxn],c[maxn];
int id[maxn],rnk[maxn];
int lim[maxn][550];
const int B=400;
ll s1[maxn],s2[maxn/B+5];
void upd1(int p,int w){
	int pl=p,pr=min((p/B+1)*B-1,n);
	for(int i=pl;i<=pr;i++)s1[i]+=w;
	pl=p/B,pr=n/B;
	for(int i=pl;i<=pr;i++)s2[i]+=w;
}
ll que1(int p){
	return ((p/B)?s2[p/B-1]:0)+s1[p];
}
ll s3[maxn],s4[maxn/B+5];
void upd2(int p,int w){
	s3[p]+=w,s4[p/B]+=w;
}
ll que2(int p){
	ll res=0;
	int pl=p,pr=min((p/B+1)*B-1,n);
	for(int i=pl;i<=pr;i++)res+=s3[i];
	pl=p/B+1,pr=n/B;
	for(int i=pl;i<=pr;i++)res+=s4[i];
	return res;
}
ll ans;
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),id[i]=i;
	stable_sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	for(int i=1;i<=n;i++)rnk[id[i]]=i;
	int mm=0;
	for(int i=1,lst=0;i<=m;i++){
		int p=read(),l=p-lst;lst=p;
		if(l<=b[mm])c[mm]++;
		else b[++mm]=l,c[mm]=1;
	}swap(m,mm);
	for(int j=1;j<=m;j++){
		for(int i=1,k=0;i<=n;i++){
			while(k+1<=n&&make_pair(1ll*a[id[k+1]]*b[j],id[k+1])<=make_pair(1ll*a[id[i]]*b[m],id[i]))k++;
			lim[id[i]][j]=k;
		}
	}
	// for(int i=1;i<=n;i++){
		// cout<<i<<" "<<rnk[i]<<"\n";
		// for(int j=1;j<=m;j++)cout<<lim[i][j]<<" ";cout<<"\n";
	// }
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)ans+=que1(lim[i][j])*c[j];
		upd1(rnk[i],1);
		for(int j=1;j<=m;j++)upd2(lim[i][j],c[j]);
		ans+=que2(rnk[i]);
		ans-=mm;
		printf("%lld\n",ans);
	}
}

int T;
signed main(){
	T=1;
	while(T--)work();
}