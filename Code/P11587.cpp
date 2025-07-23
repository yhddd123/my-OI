#include<bits/stdc++.h>
#define ll long long
#define pii pair<ll,ll>
#define fi first
#define se second
using namespace std;
const int maxn=100010;
const int B=300;
const int maxm=maxn/B+5;
const int inf=1e9;

int n,q;
ll a[maxn],b[maxn];
pii qq[maxn];int h,t;
int f[maxm][maxn];
bool chk(pii u,pii v,pii w){return (__int128)(w.fi-u.fi)*(w.se-v.se)<(__int128)(w.fi-v.fi)*(w.se-u.se);}
void ins(pii p){while(h<t&&chk(qq[t-1],qq[t],p))t--;qq[++t]=p;}
int ask(pii p){if(h>t)return inf;while(h<t&&chk(qq[h+1],qq[h],p))h++;return (p.fi-qq[h].fi)/(p.se-qq[h].se);}
int que(int l,int r){
    int res=inf;
    if(l/B==r/B){
        h=1,t=0;ins({b[l],l});
        for(int i=l+1;i<=r;i++)res=min(res,ask({a[i],i})),ins({b[i],i});
    }
    else{
        res=min(f[l/B+1][r],f[r/B][l]);
        h=1,t=0;
        for(int i=l;i<=(l/B+1)*B-1;i++)ins({b[i],i});
        for(int i=r/B*B;i<=r;i++)res=min(res,ask({a[i],i}));
    }
    return res;
}
vector<int> testset(vector<int> A, vector<int> _B, vector<int> L, vector<int> U){
    n=A.size();q=L.size();
    for(int i=1;i<=n;i++)a[i]=a[i-1]+A[i-1]+_B[i-1];
    for(int i=1;i<n;i++)b[i]=a[i]-_B[i-1];
    for(int i=0;i<=n;i+=B){
        f[i/B][i]=inf;
        h=1,t=0;ins({b[i],i});
        for(int j=i+1;j<=n;j++)f[i/B][j]=min(f[i/B][j-1],ask({a[j],j})),ins({b[j],j});
        h=1,t=0;ins({-a[i],-i});
        for(int j=i-1;j>=0;j--)f[i/B][j]=min(f[i/B][j+1],ask({-b[j],-j})),ins({-a[j],-j});
    }
    vector<int> ans(q);
    for(int i=0;i<q;i++)ans[i]=que(L[i],U[i]+1);
    return ans;
}

// void my_assert (bool x) {
// 	if (!x) {
// 		puts("Wrong input");
// 		exit(0);
// 	}
// }

// int main()
// {
//     freopen("A.in","r",stdin);
//     freopen("A.out","w",stdout);
// 	int N, M;

// 	my_assert(scanf("%d %d", &N, &M) == 2);
// 	std::vector<int> A(N), B(N - 1), L(M), U(M);

// 	for (int i = 0; i < N; i++) my_assert(scanf("%d", &A[i]) == 1);
// 	for (int j = 0; j < N-1; j++) my_assert(scanf("%d", &B[j]) == 1);
// 	for (int i = 0; i < M; i++) my_assert(scanf ("%d %d", &L[i], &U[i]) == 2);

// 	std::vector<int> S = testset(A, B, L, U);
// 	if ((int)S.size() != M) {
// 		printf("Size of S should be %d, but it is %d\n", M, (int)S.size());
// 		return 0;
// 	}

// 	for (int& s : S) printf ("%d\n",s);

// 	return 0;
// }
