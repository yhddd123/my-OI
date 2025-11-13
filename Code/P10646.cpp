#include<bits/stdc++.h>
#define int long long
#define mod1 998244353ll
#define mod2 1000000009ll
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,k,q,a[maxn],p[maxn];
char s[maxn][15],op[15];
mt19937 rnd(0);
int bas01,val01[26],bas02,val02[26],lsh[maxn],len;
int bas11,val11[maxn],bas12,val12[maxn],lsh1[maxn],len1;
vector<tuple<int,int,int>> edge[maxn];
vector<pii> e[maxn];
pii que[maxn];
vector<int> ans[maxn];
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct,rnk[maxn],fl[maxn];
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(auto[v,fr]:e[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(lw[u]==dfn[u]){
		scc[st[tp]]=++scct,fl[scct]=0;rnk[scct]=st[tp];
		while(st[tp--]!=u){
			scc[st[tp]]=scct;fl[scct]=1;
		}
	}
}
int d[maxn],mxd[maxn];
pii to[maxn];
vector<tuple<int,int,int>> h[maxn];
void dfs(int u,int id){
	if(!que[id].fi)return ;
	// cout<<u<<" "<<id<<" "<<to[u].fi<<" "<<to[u].se<<"\n";
	auto[v,fr]=to[u];
	if(v){
		que[id].fi--;ans[id].pb(fr);
		return dfs(v,id);
	}
}
bool bk[maxn];
void work(){
	n=read();k=read();
	bas01=rnd();for(int i=0;i<26;i++)val01[i]=rnd();
	bas02=rnd();for(int i=0;i<26;i++)val02[i]=rnd();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);int l=strlen(s[i]+1);
		int h1=0;for(int j=1;j<=l;j++)h1=(h1*bas01+val01[s[i][j]-'a'])%mod1;
		int h2=0;for(int j=1;j<=l;j++)h2=(h2*bas02+val02[s[i][j]-'a'])%mod2;
		lsh[++len]=h1*mod2+h2;
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++){
		int l=strlen(s[i]+1);
		int h1=0;for(int j=1;j<=l;j++)h1=(h1*bas01+val01[s[i][j]-'a'])%mod1;
		int h2=0;for(int j=1;j<=l;j++)h2=(h2*bas02+val02[s[i][j]-'a'])%mod2;
		a[i]=lower_bound(lsh+1,lsh+len+1,h1*mod2+h2)-lsh;p[a[i]]=i;
	}
	bas11=rnd();for(int i=1;i<=len;i++)val11[i]=rnd();
	bas12=rnd();for(int i=1;i<=len;i++)val12[i]=rnd();
	for(int i=1;i+k-1<=n;i++){
		int h1=0;for(int j=i;j<=i+k-1;j++)h1=(h1*bas11+val11[a[j]])%mod1;
		int h2=0;for(int j=i;j<=i+k-1;j++)h2=(h2*bas12+val12[a[j]])%mod2;
		lsh1[++len1]=h1*mod2+h2;
	}
	sort(lsh1+1,lsh1+len1+1),len1=unique(lsh1+1,lsh1+len1+1)-lsh1-1;
	unordered_map<int,int> mp;
	for(int i=1;i+k<=n;i++){
		int h1=0;for(int j=i;j<=i+k;j++)h1=(h1*bas11+val11[a[j]])%mod1;
		int h2=0;for(int j=i;j<=i+k;j++)h2=(h2*bas12+val12[a[j]])%mod2;
		mp[h1*mod2+h2]++;
	}
	unordered_map<int,bool> vis;
	for(int i=1;i+k<=n;i++){
		int h11=0;for(int j=i;j<=i+k-1;j++)h11=(h11*bas11+val11[a[j]])%mod1;
		int h12=0;for(int j=i;j<=i+k-1;j++)h12=(h12*bas12+val12[a[j]])%mod2;
		int h21=0;for(int j=i+1;j<=i+k;j++)h21=(h21*bas11+val11[a[j]])%mod1;
		int h22=0;for(int j=i+1;j<=i+k;j++)h22=(h22*bas12+val12[a[j]])%mod2;
		int hh1=(h11*bas11+val11[a[i+k]])%mod1,hh2=(h12*bas12+val12[a[i+k]])%mod2;
		int h1=lower_bound(lsh1+1,lsh1+len1+1,h11*mod2+h12)-lsh1,h2=lower_bound(lsh1+1,lsh1+len1+1,h21*mod2+h22)-lsh1;
		if(!vis[h1*mod2+h2])vis[h1*mod2+h2]=1,edge[mp[hh1*mod2+hh2]].pb({h1,h2,a[i+k]});
	}
	q=read();
	for(int i=1;i<=q;i++){
		int m=read();
		int hh1=0,hh2=0;for(int i=1;i<=k;i++){
			scanf("%s",op+1);int l=strlen(op+1);
			int h1=0;for(int j=1;j<=l;j++)h1=(h1*bas01+val01[op[j]-'a'])%mod1;
			int h2=0;for(int j=1;j<=l;j++)h2=(h2*bas02+val02[op[j]-'a'])%mod2;
			int hh=lower_bound(lsh+1,lsh+len+1,h1*mod2+h2)-lsh;
			hh1=(hh1*bas11+val11[hh])%mod1,hh2=(hh2*bas12+val12[hh])%mod2;
		}
		int hsh=lower_bound(lsh1+1,lsh1+len1+1,hh1*mod2+hh2)-lsh1;
		que[i]={m,hsh};
	}
	vector<int> id;
	for(int w=n;w;w--)if(edge[w].size()){
		for(auto[u,v,fr]:edge[w]){
			// if(w>=3)cout<<w<<" "<<u<<" "<<v<<" "<<fr<<"\n";
			e[u].pb({v,fr});
			if(!bk[u])bk[u]=1,id.pb(u);
			if(!bk[v])bk[v]=1,id.pb(v);
		}
		for(int i:id)dfn[i]=scc[i]=0;idx=scct=0;
		for(int i:id)if(!dfn[i])tar(i);
		for(int i=1;i<=scct;i++)d[i]=mxd[i]=0,h[i].clear();
		// cout<<w<<"\n";
		for(int i:id)to[i]={0,0};
		for(int u:id){
			for(auto[v,fr]:e[u]){
				if(scc[u]!=scc[v])h[scc[v]].pb({u,v,fr}),d[scc[u]]++;
				else fl[scc[u]]=1,to[u]={v,fr};
			}
		}
		queue<int> qq;
		for(int i=1;i<=scct;i++)if(!d[i])qq.push(i);
		while(!qq.empty()){
			int p=qq.front();qq.pop();
			for(auto[u,v,fr]:h[p]){
				int q=scc[u];
				if(!fl[q]){
					if(fl[p])to[u]={v,fr};
					else{
						mxd[q]=max(mxd[q],mxd[p]+1);
						if(mxd[q]==mxd[p]+1)to[u]={v,fr};
					}
				}
				fl[q]|=fl[p];
				d[q]--;
				if(!d[q])qq.push(q);
			}
		}
		// cout<<w<<" "<<id.size()<<" "<<scct<<endl;
		for(int i=1;i<=q;i++)if(que[i].fi){
			auto[m,u]=que[i];
			// cout<<i<<" "<<u<<" "<<scc[u]<<" "<<fl[scc[u]]<<" "<<mxd[scc[u]]<<"\n";
			if(fl[scc[u]]||mxd[scc[u]]>=m)dfs(u,i);
		}
	}
	for(int i=1;i<=q;i++){
		if(!ans[i].size()){
			for(int j=1;j<=que[i].fi;j++)ans[i].pb(1);
		}
		for(int j:ans[i]){
			int l=strlen(s[p[j]]+1);
			for(int k=1;k<=l;k++)putchar(s[p[j]][k]);
			putchar(' ');
		}
		puts("");
	}
}

bool med;
int T;
signed main(){
	 // freopen("break.in","r",stdin);
	 // freopen("break.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}