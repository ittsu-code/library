#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}

//BEGIN CUT HERE
template<size_t N,typename R,typename Add,typename Mul>
struct SquareMatrix{
  typedef array<R, N> arr;
  typedef array<arr, N> mat;
  mat dat;
  Add add;
  Mul mul;
  R r0,r1;
  
  SquareMatrix(Add add,Mul mul,R r0,R r1):
    add(add),mul(mul),r0(r0),r1(r1){
    for(size_t i=0;i<N;i++)
      for(size_t j=0;j<N;j++)
        dat[i][j]=r0;
  }
  
  SquareMatrix& operator=(const SquareMatrix& a){
    dat=a.dat;
    return (*this);
  }
  
  size_t size() const{return N;};
  arr& operator[](size_t k){return dat[k];};
  const arr& operator[](size_t k) const {return dat[k];};
  
  SquareMatrix cross(const SquareMatrix &A,const SquareMatrix &B) const{
    SquareMatrix res(add,mul,r0,r1);
    for(size_t i=0;i<N;i++)
      for(size_t j=0;j<N;j++)
        for(size_t k=0;k<N;k++)
          res[i][j]=add(res[i][j],mul(A[i][k],B[k][j]));
    return res;
  }
  
  SquareMatrix identity() const{
    SquareMatrix res(add,mul,r0,r1);   
    for(size_t i=0;i<N;i++) res[i][i]=r1;
    return res;
  }
  
  SquareMatrix pow(long long n) const{
    SquareMatrix a=*this,res=identity();    
    while(n){
      if(n&1) res=res.cross(res,a);      
      a=a.cross(a,a);      
      n>>=1;
    }
    return res;
  }
};
//END CUT HERE

template<typename T,T MOD = 1000000007>
struct Mint{
  T v;
  Mint():v(0){}
  Mint(signed v):v(v){}
  Mint(long long t){v=t%MOD;if(v<0) v+=MOD;}

  Mint pow(long long k){
    Mint res(1),tmp(v);
    while(k){
      if(k&1) res*=tmp;
      tmp*=tmp;
      k>>=1;
    }
    return res;
  }
  
  Mint inv(){return pow(MOD-2);}
  
  Mint& operator+=(Mint a){v+=a.v;if(v>=MOD)v-=MOD;return *this;}
  Mint& operator-=(Mint a){v+=MOD-a.v;if(v>=MOD)v-=MOD;return *this;}
  Mint& operator*=(Mint a){v=1LL*v*a.v%MOD;return *this;}
  Mint& operator/=(Mint a){return (*this)*=a.inv();}
  
  Mint operator+(Mint a) const{return Mint(v)+=a;};
  Mint operator-(Mint a) const{return Mint(v)-=a;};
  Mint operator*(Mint a) const{return Mint(v)*=a;};
  Mint operator/(Mint a) const{return Mint(v)/=a;};

  Mint operator-(){return v?MOD-v:v;}

  bool operator==(const Mint a)const{return v==a.v;}
  bool operator!=(const Mint a)const{return v!=a.v;}
  bool operator <(const Mint a)const{return v <a.v;}
};


struct FastIO{
  FastIO(){
    cin.tie(0);
    ios::sync_with_stdio(0);
  }
}fastio_beet;


template<typename T>
vector<T> compress(vector<T> v){
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  return v;
}

template<typename T>
map<T, Int> dict(const vector<T> &v){
  map<T, Int> res;
  for(Int i=0;i<(Int)v.size();i++)
    res[v[i]]=i;
  return res;
}

template <typename T, typename F>
struct SegmentTree{
  Int n;
  F f;
  T ti;
  vector<T> dat;
  SegmentTree(){};
  SegmentTree(F f,T ti):f(f),ti(ti){}
  void init(Int n_){    
    n=1;
    while(n<n_) n<<=1;
    dat.assign(n<<1,ti);
  }
  void build(const vector<T> &v){
    Int n_=v.size();
    init(n_);
    for(Int i=0;i<n_;i++) dat[n+i]=v[i];
    for(Int i=n-1;i;i--)
      dat[i]=f(dat[(i<<1)|0],dat[(i<<1)|1]);
  }
  void set_val(Int k,T x){
    dat[k+=n]=x;
    while(k>>=1)
      dat[k]=f(dat[(k<<1)|0],dat[(k<<1)|1]);    
  }
  T query(Int a,Int b){
    T vl=ti,vr=ti;
    for(Int l=a+n,r=b+n;l<r;l>>=1,r>>=1) {
      if(l&1) vl=f(vl,dat[l++]);
      if(r&1) vr=f(dat[--r],vr);
    }
    return f(vl,vr);
  }
};

//INSERT ABOVE HERE
signed YAHOO2019_FINAL_D(){
  using M = Mint<Int>;  
  auto add=[](M a,M b)->M{return a+b;};
  auto mul=[](M a,M b)->M{return a*b;};
  using MM = SquareMatrix<2, M, decltype(add), decltype(mul)>;

  Int n,q;
  cin>>n>>q;
  vector<Int> ts(q),ls(q),rs(q),ps(q);
  for(Int i=0;i<q;i++){
    cin>>ts[i];
    if(ts[i]==1) cin>>ps[i];
    if(ts[i]==2) cin>>ls[i]>>rs[i];
  }
  vector<Int> vs;
  for(Int i=0;i<q;i++){
    if(ts[i]==1){
      vs.emplace_back(ps[i]);
      vs.emplace_back(ps[i]+1);  
      vs.emplace_back(ps[i]+2);   
      vs.emplace_back(ps[i]+3);      
    }
    if(ts[i]==2){
      vs.emplace_back(ls[i]);
      vs.emplace_back(ls[i]+1);
      vs.emplace_back(rs[i]);
      vs.emplace_back(rs[i]+1);
    }
  }
  vs.emplace_back(0);
  vs.emplace_back(n+1);
  vs=compress(vs);
  auto ms=dict(vs);
  
  MM A(add,mul,M(0),M(1));
  A[0][0]=M(1);A[0][1]=M(1);
  A[1][0]=M(1);A[1][1]=M(0);

  vector<MM> vt(vs.size()-1,A);
  for(Int i=0;i+1<(Int)vs.size();i++){
    vt[i]=A.pow(vs[i+1]-vs[i]);
  }

  MM I=A.identity();
  auto f=[&](MM a,MM b){return a.cross(b,a);};
  SegmentTree<MM, decltype(f)> seg(f,I);
  seg.build(vt);
  
  vector<Int> used(vs.size(),0);  
  for(Int i=0;i<q;i++){
    if(ts[i]==1){
      Int k=ms[ps[i]];
      used[k]^=1;
      MM B(add,mul,M(0),M(1));
      for(Int j=k;j<=k+2;j++){
        if(used[j]){
          B[0][0]=M(0);B[0][1]=M(0);
          B[1][0]=M(1);B[1][1]=M(0);        
        }else{
          B[0][0]=M(!used[j-1]);B[0][1]=M(!used[j-2]);
          B[1][0]=M(1);B[1][1]=M(0);
        }
        seg.set_val(j,B);   
      }
    }
    if(ts[i]==2){    
      Int l=ms[ls[i]],r=ms[rs[i]];
      if(used[l]){
        cout<<0<<"\n";
        continue;
      }
      auto B=seg.query(l+1,r+1);
      cout<<B[0][0].v<<"\n";
    }
  }
  cout<<flush;
  return 0;
}
/*
  verified on 2019/02/23
  https://atcoder.jp/contests/yahoo-procon2019-final/tasks/yahoo_procon2019_final_d
*/

signed DDCC2019_FINAL_D(){
  string s;
  cin>>s;
  
  auto add=[](unsigned a,unsigned b)->unsigned{return a+b;};
  auto mul=[](unsigned a,unsigned b)->unsigned{return a*b;};
  using M = SquareMatrix<6, unsigned, decltype(add), decltype(mul)>;
 
  auto f=[](M a,M b){return a.cross(a,b);};
  M ti=M(add,mul,0,1).identity();
  SegmentTree<M, decltype(f)> seg(f,ti);
  vector<M> vt(s.size(),ti);
  for(int i=0;i<(int)s.size();i++){
    if(s[i]=='D') vt[i][0][1]=1;
    if(s[i]=='I') vt[i][1][2]=1;
    if(s[i]=='S') vt[i][2][3]=1;
    if(s[i]=='C') vt[i][3][4]=1;
    if(s[i]=='O') vt[i][4][5]=1;
  }
  seg.build(vt);
  
  int q;
  cin>>q;
  for(int i=0;i<q;i++){
    int l,r;
    cin>>l>>r;
    l--;
    cout<<seg.query(l,r)[0][5]<<"\n";
  }
  cout<<flush;
  return 0;
}
/*
  verified on 2019/02/23
  https://atcoder.jp/contests/ddcc2019-final/tasks/ddcc2019_final_d
*/

signed AOJ_2397(){
  const int MAX = 80;
  const int MOD = 1e9+9;
  using M = Mint<int, MOD>;
  auto add=[](M a,M b)->M{return a+b;};
  auto mul=[](M a,M b)->M{return a*b;};
  
  using SM = SquareMatrix<MAX, M, decltype(add), decltype(mul)>;

  using ll = long long;
  ll w,h,n;
  ll cnt=0;
  while(cin>>w>>h>>n,w){
    vector<ll> x(n),y(n);
    for(int i=0;i<n;i++) cin>>x[i]>>y[i];
    {
      using P = pair<ll, ll>;
      vector<P> vp;
      for(int i=0;i<n;i++) vp.emplace_back(y[i],x[i]);
      sort(vp.begin(),vp.end());
      for(int i=0;i<n;i++) tie(y[i],x[i])=vp[i];
    }
    SM b(add,mul,M(0),M(1));
    for(int i=0;i<w;i++){
      b[i][i]=M(1);
      if(i-1>=0) b[i][i-1]=M(1);
      if(i+1<w)  b[i][i+1]=M(1);
    }
    ll d=1;
    SM res=b.identity();    
    for(int k=0;k<n;k++){
      if(y[k]==d) continue;
      res=res.cross(b.pow(y[k]-d-1),res);
      int j=k;
      SM c(b);
      while(j<n&&y[k]==y[j]){
        for(int i=0;i<w;i++) c[x[j]-1][i]=0;
        j++;
      }
      res=res.cross(c,res);
      d=y[k];
    }
    res=res.cross(b.pow(h-d),res);
    cout<<"Case "<<++cnt<<": "<<res[w-1][0].v<<endl;
  }
  return 0;
}
/*
  verified on 2019/04/11
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2397
*/

signed AOJ_2432(){  
  const int MAX = 160;
  const int INF = 1e8;

  auto add=[](int a,int b)->int{return max(a,b);};
  auto mul=[](int a,int b)->int{return a+b;};
  
  using SM = SquareMatrix<MAX, int, decltype(add), decltype(mul)>;

  int n,m,k;
  cin>>n>>m>>k;
  vector<SM> vs,ws;
  vs.emplace_back(add,mul,-INF,0);
  ws.emplace_back(add,mul,-INF,0);
  
  for(int i=0;i<n;i++){
    vs[0][i][i]=0;
    ws[0][i][i]=0;
  }
  
  for(int i=0;i<m;i++){
    int a,b,c;
    cin>>a>>b>>c;
    chmax(vs[0][a][b],c);
  }
  
  for(int t=0;t<20;t++){
    SM tv=vs[t].cross(vs[t],vs[t]);
    SM tw=vs[t].cross(vs[t],ws[t]);
    vs.emplace_back(tv);    
    ws.emplace_back(tw); 
  }
  
  auto len=[&](SM &sm)->int{
             int res=0;
             for(int i=0;i<n;i++)
               for(int j=0;j<n;j++)
                 chmax(res,sm[i][j]);
             return res;
           };

  if(len(vs.back())<k){
    cout<<-1<<endl;
    return 0;
  }

  int ans=0;
  SM res(ws[0]);
  for(int t=20;t>=0;t--){
    SM tmp=res.cross(res,ws[t]);
    SM nxt=res.cross(res,vs[t]);
    if(len(tmp)<k){
      res.dat=nxt.dat;
      ans+=1<<t;
    }
  }
  cout<<ans<<endl;
  if(ans>100) return 0;

  int dp[MAX][MAX];
  int pr[MAX][MAX];
  for(int i=0;i<MAX;i++){
    for(int j=0;j<MAX;j++){
      dp[i][j]=-INF;
      pr[i][j]=-1;
    }
  }
  for(int v=0;v<n;v++) dp[0][v]=0;
  for(int i=0;i<ans;i++){
    for(int v=0;v<n;v++){
      for(int u=0;u<n;u++){
        if(dp[i+1][u]<dp[i][v]+vs[0][v][u]){
          dp[i+1][u]=dp[i][v]+vs[0][v][u];
          pr[i+1][u]=v;
        }
      }
    }
  }
  int pos=0;
  for(int v=0;v<n;v++)
    if(dp[ans][v]>dp[ans][pos]) pos=v;

  vector<int> vx;
  for(int i=ans;i>=0;i--){
    vx.emplace_back(pos);
    pos=pr[i][pos];    
  }
  reverse(vx.begin(),vx.end());
  for(int i=0;i<=ans;i++){
    if(i) cout<<" ";
    cout<<vx[i];
  }
  cout<<endl;
  return 0;
}
/*
  verified on 2019/04/11
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2432
*/

signed main(){  
  //YAHOO2019_FINAL_D();
  //DDCC2019_FINAL_D();
  //AOJ_2397();
  //AOJ_2432();
  return 0;
}
