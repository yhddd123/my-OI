#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=400010;
const int inf=5e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,k;
int ans[maxn],tp;
struct nd{
	int l,r,id;
	bool operator<(const nd&tmp)const{return r<tmp.l;}
}a[maxn];
int b[maxn],l;
bool cmp(nd u,nd v){return u.l<v.l;}
bool cmp1(nd u,nd v){return u.id<v.id;}
int to[maxn][21];
int mn[maxn],id[maxn];
int get(int l,int r){
	int res=0;
	for(int i=20;i>=0;i--){
		if(a[to[l][i]].r<=r)res+=(1<<i),l=to[l][i];
	}
	return res;
}
set<nd> s;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();k=read();
	for(int i=1;i<=n;i++){
		a[i].l=read()*4+1;a[i].r=read()*4-1;a[i].id=i;
		b[++l]=a[i].l;b[++l]=a[i].r;
	}
	sort(b+1,b+l+1);l=unique(b+1,b+l+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i].l=lower_bound(b+1,b+l+1,a[i].l)-b;
		a[i].r=lower_bound(b+1,b+l+1,a[i].r)-b;
	}
	sort(a+1,a+n+1,cmp);
	a[0]={-inf,-inf,0};a[n+1]={inf,inf,n+1};
	memset(mn,0x3f,sizeof(mn));
	mn[l+1]=l+1;id[l+1]=n+1;
	for(int i=n;i>=1;i--){
		if(mn[a[i].l]>a[i].r){
			mn[a[i].l]=a[i].r;
			id[a[i].l]=a[i].id;
		}
	}
	for(int i=l;i>=1;i--){
		if(mn[i]>mn[i+1]){
			mn[i]=mn[i+1];	
			id[i]=id[i+1];
		}
	}
	to[n+1][0]=n+1;
	for(int i=1;i<=n;i++)to[a[i].id][0]=id[a[i].r+1];
	int st=n+1;for(int i=1;i<=n;i++)if(a[i].r<a[st].r)st=i;
	to[0][0]=a[st].id;
	for(int j=1;j<=20;j++){
		for(int i=0;i<=n+1;i++)to[i][j]=to[to[i][j-1]][j-1];
	}
	sort(a+1,a+n+1,cmp1);
	s.insert(a[0]);s.insert(a[n+1]);
	if(get(0,inf-1)<k){printf("-1\n");return 0;}
	int num=get(0,inf-1)-k;
	// cout<<a[1].l<<" "<<a[1].r<<" "<<a[2].l<<" "<<a[2].r<<"\n";
	for(int i=1;i<=n;i++){
		if(s.find(a[i])!=s.end())continue;
		auto it=s.upper_bound(a[i]);nd r=*it;
		it--;nd l=*it;
		// if(i==89998){cout<<i<<" "<<l.id<<" "<<r.id<<" "<<a[89912].r<<" "<<a[89998].l<<"\n";return 0;}
		if(get(l.id,a[i].l-1)+get(i,r.l-1)+1+num>=get(l.id,r.l-1)){
			num-=get(l.id,r.l-1)-(get(l.id,a[i].l-1)+get(i,r.l-1)+1);
			s.insert(a[i]);
			k--;printf("%lld\n",i);
			if(!k)return 0;
		}
		// cout<<k<<" "<<tp<<"\n";
	}
}