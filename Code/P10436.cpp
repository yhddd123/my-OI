// Problem: P10436 [JOIST 2024] 卡牌收集 / Card Collection
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10436
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-01-27 20:35:10
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=200010;
const int inf=1e9;
bool mbe;

namespace automation{
	bool f[110][110][9];
	map<vector<int>,bool> mp;
	int op1(int o1,int o2){
		int a=o1/3-1,b=o1%3-1,c=o2/3-1,d=o2%3-1;
		return (min(a,c)+1)*3+min(b,d)+1;
	}
	int op2(int o1,int o2){
		int a=o1/3-1,b=o1%3-1,c=o2/3-1,d=o2%3-1;
		return (max(a,c)+1)*3+max(b,d)+1;
	}
	bool calc(vector<int> &a){
		if(mp.find(a)!=mp.end())return mp[a];
		int n=a.size();
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				for(int o=0;o<9;o++)f[i][j][o]=0;
			}
			f[i][i][a[i-1]]=1;
		}
		for(int len=2;len<=n;len++){
			for(int i=1,j=len;j<=n;i++,j++){
				for(int k=i;k<j;k++){
					for(int o1=0;o1<9;o1++)if(f[i][k][o1]){
						for(int o2=0;o2<9;o2++)if(f[k+1][j][o2]){
							f[i][j][op1(o1,o2)]=1;
							f[i][j][op2(o1,o2)]=1;
						}
					}
				}
			}
		}
		return mp[a]=f[1][n][4];
	}
	struct node{
		vector<int> sta;
		vector<int> nxt;
	}dft[55];int idx;
	int to[55][9];
	bool ok[55];
	int pw[5]={1,9,81,729,6561};
	node init(vector<int> a,int lim){
		node res;
		res.sta=a;
		for(int i=0;i<=lim;i++){
			for(int s=0;s<pw[i];s++){
				vector<int> b=a;
				for(int j=0;j<i;j++)b.pb((s/pw[j])%9);
				res.nxt.pb(calc(b));
			}
		}
		return res;
	}
	void init(int lim){
		dft[0]=init({},lim);
		queue<int> q;q.push(0);
		for(int id=0;id<=idx;id++){
			// cout<<id<<"\n";
			ok[id]=calc(dft[id].sta);
			for(int c=0;c<9;c++){
				vector<int> b=dft[id].sta;b.pb(c);
				node nw=init(b,lim);
				int p=-1;for(int j=0;j<=idx;j++)if(dft[j].nxt==nw.nxt){p=j;break;}
				if(p==-1)dft[++idx]=nw,p=idx;
				to[id][c]=p;
				cout<<p<<" ";
			}
			cout<<"\n";
		}
		// cout<<idx<<"\n";
	}
}
using automation::to;
using automation::ok;
int n,q;
int a[maxn],b[maxn];
struct node{
	int x,y,id;
}que[maxn];
int pos[maxn],sta[maxn];
void work(){
	automation::init(2);
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=q;i++){
		int x=read(),y=read(),p=0;
		for(int i=1;i<=n;i++){
			int o=((a[i]>x)-(a[i]<x)+1)*3+((b[i]>y)-(b[i]<y)+1);
			p=to[p][o];
		}
		if(ok[p])printf("%d ",i);
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