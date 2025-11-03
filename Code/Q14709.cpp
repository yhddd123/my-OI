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
const int maxn=210;
const int inf=1e9;
bool mbe;

int a,b,n,p;
bool f[maxn][maxn][25][2][3];
tuple<int,int,int,int,int> pre[maxn][maxn][25][2][3];
int v[maxn][maxn][25][2][3];
void work(){
	a=read();b=read();n=read();p=read();
	vector<int> ans;
	if(f[a][b][n][p][0]||f[a][b][n][p][1]||f[a][b][n][p][2]){
		int fl=0;
		if(f[a][b][n][p][1])fl=1;
		else if(f[a][b][n][p][2])fl=2;
		while(a||b||n!=21||p||fl){
			// assert(f[a][b][n][p][fl]);
			ans.pb(v[a][b][n][p][fl]);
			auto[_a,_b,_n,_p,_fl]=pre[a][b][n][p][fl];
			a=_a,b=_b,n=_n,p=_p,fl=_fl;
		}
		reverse(ans.begin(),ans.end());
		for(int v:ans)printf("%c",(v==-1)?'/':(char)(v+'0'));
		puts("");
	}
	else puts("NA");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	f[0][0][21][0][0]=1;
	for(int a=0;a<=200;a++){
		for(int b=0;b<=200;b++){
			for(int n=21;n;n--){
				for(int p=0;p<2;p++){
					for(int fl=0;fl<3;fl++)if(f[a][b][n][p][fl]){
						if(!f[a][b][n][p^1][n<=6?2:0]){
							f[a][b][n][p^1][n<=6?2:0]=1;
							pre[a][b][n][p^1][n<=6?2:0]={a,b,n,p,fl};
							v[a][b][n][p^1][n<=6?2:0]=-1;
						}
					}
				}
				for(int p=0;p<2;p++){
					for(int fl=0;fl<3;fl++)if(f[a][b][n][p][fl]){
						if(!f[a][b][n][p^1][n<=6?2:0]){
							f[a][b][n][p^1][n<=6?2:0]=1;
							pre[a][b][n][p^1][n<=6?2:0]={a,b,n,p,fl};
							v[a][b][n][p^1][n<=6?2:0]=-1;
						}
					}
				}
				for(int p=0;p<2;p++){
					for(int fl=0;fl<3;fl++)if(f[a][b][n][p][fl]){
						if(!fl){
							if(!f[a+(p==0)][b+(p==1)][n-1][p][1]){
								f[a+(p==0)][b+(p==1)][n-1][p][1]=1;
								pre[a+(p==0)][b+(p==1)][n-1][p][1]={a,b,n,p,fl};
								v[a+(p==0)][b+(p==1)][n-1][p][1]=1;
							}
						}
						else{
							if(fl==2){
								int c=6-n+2;
								if(!f[a+(p==0)*c][b+(p==1)*c][n-1][p][2]){
									f[a+(p==0)*c][b+(p==1)*c][n-1][p][2]=1;
									pre[a+(p==0)*c][b+(p==1)*c][n-1][p][2]={a,b,n,p,fl};
									v[a+(p==0)*c][b+(p==1)*c][n-1][p][2]=c;
								}
							}
							else{
								for(int c=2;c<=7;c++){
									if(!f[a+(p==0)*c][b+(p==1)*c][n][p][n<=6?2:0]){
										f[a+(p==0)*c][b+(p==1)*c][n][p][n<=6?2:0]=1;
										pre[a+(p==0)*c][b+(p==1)*c][n][p][n<=6?2:0]={a,b,n,p,fl};
										v[a+(p==0)*c][b+(p==1)*c][n][p][n<=6?2:0]=c;
									}
								}
							}
						}
					}
				}
			}
		}
	}
		
	T=read();
	while(T--)work();
}