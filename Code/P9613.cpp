#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=110;
const int inf=1e9;

int n,p,ans;
char c[maxn];
int tree[maxn][26],fail[maxn],idx;
bool vis[maxn];
void insert(char *c,int len){
	int nd=0;
	for(int i=1;i<=len;i++){
		if(!tree[nd][c[i]-'a'])tree[nd][c[i]-'a']=++idx;
		nd=tree[nd][c[i]-'a'];
	}
	vis[nd]=1;
}
queue<int> q;
void build(){
	int nd=0;
	for(int i=0;i<26;i++)if(tree[nd][i])q.push(tree[nd][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(tree[u][i]){
				fail[tree[u][i]]=tree[fail[u]][i];
				vis[tree[u][i]]|=vis[fail[tree[u][i]]];
				q.push(tree[u][i]);
			}
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
struct nd{
	int e[maxn][maxn];
	nd(){memset(e,0,sizeof(e));}
	nd operator *(const nd&tmp)const{
		nd ans;
		for(int i=0;i<=100;i++){
			for(int j=0;j<=100;j++){
				for(int k=0;k<=100;k++){
					ans.e[i][k]+=e[i][j]*tmp.e[j][k]%mod;
					ans.e[i][k]%=mod;
				}
			}
		}
		return ans;
	}
}bas;
nd ksm(nd a,int b){
	nd ans;
	for(int i=0;i<=100;i++)ans.e[i][i]=1;
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	scanf("%lld%lld",&n,&p);
	while(p--){
		int len;
		scanf("%lld%s",&len,c+1);
		insert(c,len);
	}
	build();
	for(int i=0;i<=idx;i++){
		for(int j=0;j<26;j++)if(!vis[tree[i][j]])bas.e[i][tree[i][j]]++;
	}
	bas=ksm(bas,n);
	for(int i=0;i<=idx;i++)ans+=bas.e[0][i],ans%=mod;
	printf("%lld\n",ans);
}
