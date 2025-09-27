#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
#define mkp make_pair
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,k,s;
int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
map<pii,int> f;
int go(int s){
	int ss=0;
	for(int i=0;i<9;i++)if(s&(1<<i)){
		int p=i/3,q=i%3;
		for(int j=0;j<4;j++){
			int np=p+fx[j][0],nq=q+fx[j][1];
			if(np<0||nq<0||np>=3||nq>=3)continue;
			ss|=1<<(np*3+nq);
		}
	}
	return ss;
}
int dfs(int s1,int s2){
	if(f.find({s1,s2})!=f.end())return f[{s1,s2}];
	int S=s1|s2;
	int res1=10,res2=10,res=10;
	for(int t=s2;t;t=(t-1)&s2){
		res1=res2=10;
		for(int i=0;i<9;i++)if(S&(1<<i)){
			int SS=S^(1<<i);
			{
				int ss1=S^(t&S),ss2=t&S;
				int to=go(ss2)&S;
				if(!(to&SS))res1=1;
				else res1=min(res1,dfs((S^to)&SS,to&SS)+1);
			}
			{
				int ss1=S^((s2^t)&S),ss2=(s2^t)&S;
				int to=go(ss2)&S;
				if(!(to&SS))res2=1;
				else res2=min(res2,dfs((S^to)&SS,to&SS)+1);
			}
			// cout<<t<<" "<<i<<" "<<res1<<" "<<res2<<"\n";
		}
		res=min(res,max(res1,res2));
	}
	// cout<<s1<<" "<<s2<<" "<<res<<" a\n";
	return f[{s1,s2}]=res;
}
char op[10];
void work(){
	n=read();k=read();s=0;
	for(int i=1;i<=k;i++)s|=1<<(read()-1);
	if(dfs(0,((1<<9)-1)^s)<=n){
		puts("Trapper");fflush(stdout);
		int s1=0,s2=((1<<9)-1)^s;
		while(1){
		// cout<<s1<<" "<<s2<<" "<<f[{s1,s2}]<<" a\n";
			int S=s1|s2;
			// cout<<s1<<" "<<s2<<"\n";
			pii res1={10,0},res2={10,0},res={10,0};
			for(int t=s2;t;t=(t-1)&s2){
				int res1=10,res2=10;
				for(int i=0;i<9;i++)if(S&(1<<i)){
					int SS=S^(1<<i);
					{
						int ss1=S^(t&S),ss2=t&S;
						int to=go(ss2)&S;
						if(!(to&SS))res1=1;
						else res1=min(res1,dfs((S^to)&SS,to&SS)+1);
					}
					{
						int ss1=S^((s2^t)&S),ss2=(s2^t)&S;
						int to=go(ss2)&S;
						if(!(to&SS))res2=1;
						else res2=min(res2,dfs((S^to)&SS,to&SS)+1);
					}
				}
				res=min(res,{max(res1,res2),t});
			}
			int t=res.se;
			printf("%d\n",__builtin_popcount(t));fflush(stdout);
			for(int i=0;i<9;i++)if(t&(1<<i))printf("%d ",i+1);puts("");fflush(stdout);
			scanf("%s",op);
			res={10,0};res1=res2={10,0};
			for(int i=0;i<9;i++)if(S&(1<<i)){
				int SS=S^(1<<i);
				{
					int ss1=S^(t&S),ss2=t&S;
					int to=go(ss2)&S;
					if(!(to&SS))res1={1,i};
					else res1=min(res1,{dfs((S^to)&SS,to&SS)+1,i});
				}
				{
					int ss1=S^((s2^t)&S),ss2=(s2^t)&S;
					int to=go(ss2)&S;
					if(!(to&SS))res2={1,i};
					else res2=min(res2,{dfs((S^to)&SS,to&SS)+1,i});
				}
			}
			if(op[0]=='Y')res=res1;
			else res=res2;
			int i=res.se;
			printf("%d\n",i+1);fflush(stdout);
			int SS=S^(1<<i),ss1,ss2;
			if(op[0]=='Y')ss1=S^(t&S),ss2=t&S;
			else ss1=S^((s2^t)&S),ss2=(s2^t)&S;
			int to=go(ss2)&S;
			s1=(S^to)&SS,s2=to&SS;
			scanf("%s",op);
			if(op[0]=='T')break;
		}
	}
	else{
		puts("Runner");fflush(stdout);
		int s1=0,s2=((1<<9)-1)^s;
		// cout<<f[{s1,s2}]<<"\n";
		vector<pii> tmp(n+1);
		for(int tt=0;tt<n;tt++){
			int k=read(),t=0;
			for(int i=1;i<=k;i++)t|=1<<(read()-1);
			pii res={10,0},res1={10,0},res2={10,0};
			int S=s1|s2;
			// cout<<s1<<" "<<s2<<" "<<t<<"\n";
			t&=s2;
			for(int i=0;i<9;i++)if(S&(1<<i)){
				int SS=S^(1<<i);
				{
					int ss1=S^(t&S),ss2=t&S;
					int to=go(ss2)&S;
					if(!(to&SS))res1={1,i};
					else res1=min(res1,{dfs((S^to)&SS,to&SS)+1,i});
				}
				{
					int ss1=S^((s2^t)&S),ss2=(s2^t)&S;
					int to=go(ss2)&S;
					if(!(to&SS))res2={1,i};
					else res2=min(res2,{dfs((S^to)&SS,to&SS)+1,i});
				}
			}
			res=max(res1,res2);
			if(res==res1){
				printf("Yes\n");fflush(stdout);
			}
			else{
				printf("No\n");fflush(stdout);
			}
			int i=read()-1;
			int SS=S^(1<<i),ss1,ss2;
			if(res==res1)ss1=S^(t&S),ss2=t&S;
			else ss1=S^((s2^t)&S),ss2=(s2^t)&S;
			int to=go(ss2)&S;
			tmp[tt]={res==res1?t:(s2^t),to&SS};
			s1=(S^to)&SS,s2=to&SS;
			printf("Free\n");fflush(stdout);
		}
		// cout<<s1<<" "<<s2<<"\n";
		vector<int> ans;
		int u=0;
		for(int i=0;i<9;i++)if(tmp[n-1].se&(1<<i))u=i;
		for(int i=n-1;~i;i--){
			int s1=tmp[i].fi,s2=tmp[i].se;
			ans.pb(u);
			int p=u/3,q=u%3,v=0;
			for(int j=0;j<4;j++){
				int np=p+fx[j][0],nq=q+fx[j][1];
				if(np<0||nq<0||np>=3||nq>=3)continue;
				int id=np*3+nq;
				if(s1&(1<<id))v=id;
			}
			u=v;
		}
		ans.pb(u);
		reverse(ans.begin(),ans.end());
		for(int u:ans)printf("%d ",u+1);puts("");fflush(stdout);
	}
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