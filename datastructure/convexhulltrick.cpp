#include<bits/stdc++.h>
using namespace std;
using Int = long long;
//BEGIN CUT HERE
template <typename T,bool isMin>
struct ConvexHullTrick {
  #define F first
  #define S second
  using P = pair<T, T>;
  deque<P> H;
  bool empty()const{return H.empty();}
  void clear(){H.clear();}

  inline int sgn(T x){return x==0?0:(x<0?-1:1);}
  
  using D = long double;
  inline bool check(const P &a,const P &b,const P &c){
    if(b.S==a.S||c.S==b.S)
      return sgn(b.F-a.F)*sgn(c.S-b.S) >= sgn(c.F-b.F)*sgn(b.S-a.S);
    
    //return (b.F-a.F)*(c.S-b.S) >= (b.S-a.S)*(c.F-b.F);
    return
      D(b.F-a.F)*sgn(c.S-b.S)/D(abs(b.S-a.S)) >=
      D(c.F-b.F)*sgn(b.S-a.S)/D(abs(c.S-b.S));
  }  
  
  void addLine(T m,T b){
    if(!isMin) m*=-1,b*=-1;
    P line(m,b);
    if(empty()||H.front().F<=m){
      while(H.size()>=2&&check(line,H.front(),H[1])) H.pop_front();
      H.emplace_front(line);
    }else{
      assert(m<=H.back().F);      
      while(H.size()>=2&&check(H[H.size()-2],H.back(),line)) H.pop_back();
      H.emplace_back(line);
    } 
  }
  
  inline T getY(const P &a,const T &x){
    return a.F*x+a.S; 
  }

  T query(T x){
    assert(!empty());
    int l=-1,r=H.size()-1;
    while(l+1<r){
      int m=(l+r)>>1;
      if(getY(H[m],x)>=getY(H[m+1],x)) l=m;
      else r=m;
    }
    if(!isMin) return -getY(H[r],x);
    return getY(H[r],x);
  }

  T queryMonotoneFromLeft(T x){
    assert(!empty()); 
    while(H.size()>=2&&getY(H.front(),x)>=getY(H[1],x)) H.pop_front();
    if(!isMin) return -getY(H.front(),x);
    return getY(H.front(),x);
  }
  
  T queryMonotoneFromRight(T x){
    assert(!empty());
    while(H.size()>=2&&getY(H.back(),x)>=getY(H[H.size()-2],x)) H.pop_back();
    if(!isMin) return -getY(H.back(),x);
    return getY(H.back(),x);
  }
  
  T queryMonotoneInc(T x){
    if(!isMin) return queryMonotoneFromRight(x);
    return queryMonotoneFromLeft(x);
  }
  
  T queryMonotoneDec(T x){    
    if(!isMin) return queryMonotoneFromLeft(x);
    return queryMonotoneFromRight(x);
  }
  #undef F
  #undef S
};
//END CUT HERE
template<typename T1,typename T2> void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> void chmax(T1 &a,T2 b){if(a<b) a=b;}

//INSERT ABOVE HERE
signed TENKA12016FINAL_E(){
  int n,l;
  scanf("%d %d",&n,&l);
  vector<vector<int> > a(n,vector<int>(l));
  for(int i=0;i<n;i++)
    for(int j=0;j<l;j++)
      scanf("%d",&a[i][j]);
  
  vector<Int> dp(l,0);
  
  for(int i=0;i<n;i++){
    ConvexHullTrick<Int, true> cht;
    for(Int j=0;j<l;j++)
      cht.addLine(-2*j,a[i][j]+j*j);
    for(Int j=0;j<l;j++)
      dp[j]+=j*j+cht.queryMonotoneInc(j);
  }
  
  printf("%lld\n",*min_element(dp.begin(),dp.end()));
  return 0;
}

/*
  verified on 2019/03/11
  https://beta.atcoder.jp/contests/tenka1-2016-final/tasks/tenka1_2016_final_e
*/

signed COLOPL2018FINAL_C(){
  int n;
  scanf("%d",&n);
  vector<Int> a(n);
  for(int i=0;i<n;i++) scanf("%lld",&a[i]);
  ConvexHullTrick<Int, true> cht;
  for(Int i=0;i<n;i++) cht.addLine(-2*i,a[i]+i*i);
  for(Int i=0;i<n;i++) printf("%lld\n",cht.queryMonotoneInc(i)+i*i);
  return 0;
}

/*
  verified on 2019/03/11
  https://beta.atcoder.jp/contests/colopl2018-final-open/tasks/colopl2018_final_c
*/

signed AOJ_2725(){
  int n,x;
  scanf("%d %d",&n,&x);
  vector<Int> t(n),p(n),f(n);
  for(Int i=0;i<n;i++) scanf("%lld %lld %lld",&t[i],&p[i],&f[i]);

  using T = tuple<Int, Int, Int>;
  vector<T> vt(n);
  for(Int i=0;i<n;i++) vt[i]=T(f[i],p[i],t[i]);
  sort(vt.begin(),vt.end());
  for(Int i=0;i<n;i++) tie(f[i],p[i],t[i])=vt[i];
  
  vector<ConvexHullTrick<Int, false> > vh(x+1);
  
  Int ans=0;
  for(Int i=0;i<n;i++){
    for(Int j=x;j>t[i];j--){
      if(vh[j-t[i]].empty()) continue;
      Int val=vh[j-t[i]].queryMonotoneInc(f[i])+p[i]-f[i]*f[i];
      vh[j].addLine(2*f[i],val-f[i]*f[i]);      
      chmax(ans,val);
    }
    vh[t[i]].addLine(2*f[i],p[i]-f[i]*f[i]);
    chmax(ans,p[i]); 
  }
  
  printf("%lld\n",ans);
  return 0;
}
/*
  verified on 2019/03/11
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2725
*/


signed main(){
  //TENKA12016FINAL_E();
  //COLOPL2018FINAL_C();
  //AOJ_2725();
  return 0;
}
