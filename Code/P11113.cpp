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
const int inf=1e9;
bool mbe;

int n,m,id[maxn];
char a[maxn];
char s[maxn];
int st[maxn],tp;
void trans(int op){
	if(op==0){
	for(int i=1;i<=n*m;i+=m){
		vector<int> id1,id2;
		for(int j=i;j<=i+m-1;j++){
			if(a[id[j]]=='.')id2.pb(id[j]);
			else id1.pb(id[j]);
		}
		for(int j=0;j<id1.size();j++)id[i+j]=id1[j];
		for(int j=0;j<id2.size();j++)id[i+j+id1.size()]=id2[j];
	}
	}
	if(op==1){
	for(int i=1;i<=n*m;i+=m){
		vector<int> id1,id2;
		for(int j=i;j<=i+m-1;j++){
			if(a[id[j]]=='.')id1.pb(id[j]);
			else id2.pb(id[j]);
		}
		for(int j=0;j<id1.size();j++)id[i+j]=id1[j];
		for(int j=0;j<id2.size();j++)id[i+j+id1.size()]=id2[j];
	}
	}
	if(op==2){
	for(int i=1;i<=m;i++){
		vector<int> id1,id2;
		for(int j=i;j<=n*m;j+=m){
			if(a[id[j]]=='.')id2.pb(id[j]);
			else id1.pb(id[j]);
		}
		for(int j=0;j<id1.size();j++)id[i+j*m]=id1[j];
		for(int j=0;j<id2.size();j++)id[i+(j+id1.size())*m]=id2[j];
	}
	}
	if(op==3){
	for(int i=1;i<=m;i++){
		vector<int> id1,id2;
		for(int j=i;j<=n*m;j+=m){
			if(a[id[j]]=='.')id1.pb(id[j]);
			else id2.pb(id[j]);
		}
		for(int j=0;j<id1.size();j++)id[i+j*m]=id1[j];
		for(int j=0;j<id2.size();j++)id[i+(j+id1.size())*m]=id2[j];
	}
	}
}
int tmp[maxn],pos[maxn],to[maxn];
bool vis[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)scanf("%s",a+(i-1)*m+1);
	for(int i=1;i<=n*m;i++)id[i]=i;
	scanf("%s",s+1);int q=strlen(s+1);
	tp=0;for(int i=1;i<=q;i++){
		int op;
		if(s[i]=='L')op=0;
		if(s[i]=='R')op=1;
		if(s[i]=='U')op=2;
		if(s[i]=='D')op=3;
		if(tp&&op==st[tp]){}
		else if(tp&&(op^1)==st[tp])st[tp]=op;
		else st[++tp]=op;
		if(tp>2&&st[tp-2]==op)tp--;
	}
	if(tp<=8){
		for(int i=1;i<=tp;i++){
			trans(st[i]);
		}
	}
	else{
		for(int i=1;i<=4;i++)trans(st[i]);
		for(int i=1;i<=n*m;i++)tmp[i]=id[i];
		for(int i=5;i<=8;i++)trans(st[i]);
		for(int i=1;i<=n*m;i++)pos[id[i]]=i;
		for(int i=1;i<=n*m;i++)to[i]=pos[tmp[i]];
		// for(int j=1;j<=n*m;j++)cout<<to[j]<<" ";cout<<"\n";
		for(int i=1;i<=n*m;i++)vis[i]=0;
		int k=(tp-4)/4-1;
		for(int i=1;i<=n*m;i++)if(!vis[i]){
			vector<int> cyc;
			int x=i;while(!vis[x])vis[x]=1,cyc.pb(x),x=to[x];
			for(int i=0;i<cyc.size();i++)id[cyc[(i+k)%cyc.size()]]=tmp[cyc[i]];
		}
		// cout<<tp<<" "<<k<<" "<<(tp-4)/4*4+1<<"\n";
		for(int i=(tp-4)/4*4+1;i<=tp;i++)trans(st[i]);
		// for(int j=1;j<=n*m;j++)cout<<id[j]<<" ";cout<<"\n";
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)putchar(a[id[(i-1)*m+j]]);puts("");
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