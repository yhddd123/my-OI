#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=210;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,l;
char c[maxn][maxn],s[maxn];
int len[maxn];
int tree[maxn][26],idx,fail[maxn];
bool ed[maxn];
void insert(){
	int len=strlen(s+1);
	int nd=0;
	for(int i=1;i<=len;i++){
		if(!tree[nd][s[i]-'a'])tree[nd][s[i]-'a']=++idx;
		nd=tree[nd][s[i]-'a'];
	}
	ed[nd]=true;
}
queue<int> q;
void build(){
	for(int i=0;i<26;i++){
		if(tree[0][i])q.push(tree[0][i]);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(tree[u][i]){
				q.push(tree[u][i]);
				fail[tree[u][i]]=tree[fail[u]][i];
				ed[tree[u][i]]|=ed[fail[tree[u][i]]];
			}
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
int dp[maxn][maxn],res;
struct mat{
	int e[maxn][maxn];
	mat(){memset(e,0,sizeof(e));}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<=2*idx+2;i++){
			for(int j=0;j<=2*idx+2;j++){
				for(int k=0;k<=2*idx+2;k++)res.e[i][j]+=e[i][k]*tmp.e[k][j]%mod;
				res.e[i][j]%=mod;
			}
		}
		return res;
	}
}bas,a;
mat ksm(mat a,int b){
	mat ans;
	for(int i=0;i<=2*idx+2;i++)ans.e[i][i]=1;
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
void sovle(){
	n=read();m=read();l=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c[i]+1);
		len[i]=strlen(c[i]+1);
	}
	for(int i=1;i<=m;i++){
		scanf("%s",s+1);
		insert();
	}
	build();
	if(l<=100){
		dp[0][0]=1;
		for(int i=0;i<=l;i++){
			for(int j=0;j<=idx;j++){
				if(!dp[i][j])continue;
				for(int k=1;k<=n;k++){
					if(i+len[k]>l)continue;
					int nd=j;
					for(int l=1;l<=len[k]&&nd!=-1;l++){
						nd=tree[nd][c[k][l]-'a'];
						if(ed[nd])nd=-1;
					}
					if(nd!=-1)dp[i+len[k]][nd]+=dp[i][j],dp[i+len[k]][nd]%=mod;
				}
			}
		}
		for(int i=0;i<=idx;i++)res+=dp[l][i],res%=mod;
		printf("%lld\n",res);
	}
	else{
		for(int i=0;i<=idx;i++)bas.e[i+idx+1][i]=1;
		for(int i=0;i<=idx;i++){
			for(int j=1;j<=n;j++){
				if(len[j]==1){
					int nd=i;
					if(ed[nd])continue;
					nd=tree[nd][c[j][1]-'a'];
					if(ed[nd])continue;
					bas.e[i+idx+1][nd+idx+1]++;
				}
				else{
					int nd=i;
					if(ed[nd])continue;
					nd=tree[nd][c[j][1]-'a'];
					if(ed[nd])continue;
					nd=tree[nd][c[j][2]-'a'];
					if(ed[nd])continue;
					bas.e[i][nd+idx+1]++;
				}
			}
		}
		a.e[0][0+idx+1]=1;
		a=a*ksm(bas,l);
		for(int i=0;i<=idx;i++){
			res+=a.e[0][i+idx+1],res%=mod;
		}
		printf("%lld\n",res);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
