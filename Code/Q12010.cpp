#include<bits/stdc++.h>
// #define int long long
#define mod 1000000007ll
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,f[maxn][55],ans;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int op[8];
char s[maxn];
struct automation{
	int f[110][110][6];
	bool check(int n,int s){
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				for(int o=0;o<6;o++)f[i][j][o]=0;
			}
		}
		for(int i=1;i<=n;i++)f[i][i][(s>>i-1)&1]=1;
		for(int len=2;len<=n;len++){
			for(int i=1,j=len;j<=n;i++,j++){
				for(int k=i;k<j;k++){
					for(int o1=0;o1<6;o1++)if(f[i][k][o1]){
						for(int o2=0;o2<6;o2++)if(f[k+1][j][o2]){
							if(o1<2&&o2<2)f[i][j][(o1|(o2<<1))+2]=1;
							else if(o1<2)f[i][j][op[o1|((o2-2)<<1)]]=1;
							else if(o2<2)f[i][j][op[(o1-2)|(o2<<2)]]=1;
							else{
								f[i][j][(((o1-2)&1)|(op[((o1-2)>>1)|((o2-2)<<1)]<<1))+2]=1;
								f[i][j][(op[(o1-2)|(((o2-2)&1)<<2)]|((o2-2)&2))+2]=1;
							}
						}
					}
				}
			}
		}
		// cout<<n<<" "<<s<<" "<<f[1][n][to]<<"\n";
		return f[1][n][1];
	}
	struct node{
		int len,sta;
		int son[2];
		bool ok;
		__int128 nxt;
	}dfa[55];int idx;
	node init(int l,int s){
		node res; 
		res.len=l,res.sta=s;
		res.son[0]=res.son[1]=0;
		res.ok=check(l,s);
		res.nxt=0;
		for(int i=0,cnt=0;i<=6;i++){
			for(int t=0;t<(1<<i);t++){
				if(check(l+i,s|(t<<l)))res.nxt|=(__int128)1<<cnt;
				cnt++;
			}
		}
		return res;
	}
	void init(){
		dfa[idx=0]=init(0,0);
		for(int id=0;id<=idx;id++){
			for(int c=0;c<2;c++){
				int l=dfa[id].len+1,s=dfa[id].sta|(c<<l-1);
				node nw=init(l,s);
				int p=-1;for(int j=0;j<=idx;j++)if(nw.nxt==dfa[j].nxt)p=j;
				if(p==-1)dfa[++idx]=nw,p=idx;
				dfa[id].son[c]=p;
			}
			// cout<<dfa[id].len<<" "<<dfa[id].sta<<" "<<dfa[id].son[0]<<" "<<dfa[id].son[1]<<" a\n";
		}
		// cout<<idx<<"\n";
	}
}a;
void work(){
	scanf("%s",s);
	for(int i=0;i<8;i++)op[i]=s[i]-'0';a.init();
	scanf("%s",s+1);n=strlen(s+1);
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=a.idx;j++)f[i][j]=0;
		for(int j=0;j<=a.idx;j++)if(f[i-1][j]){
			for(int c=0;c<2;c++)if(s[i]-'0'!=(c^1))inc(f[i][a.dfa[j].son[c]],f[i-1][j]);
		}
	}
	ans=0;for(int i=0;i<=a.idx;i++)if(a.dfa[i].ok)inc(ans,f[n][i]);
	printf("%d\n",ans);
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