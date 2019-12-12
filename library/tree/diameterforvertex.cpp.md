---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: tree/diameterforvertex.cpp
<a href="../../index.html">Back to top page</a>

* category: tree
* <a href="{{ site.github.repository_url }}/blob/master/tree/diameterforvertex.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-12 19:01:48 +0900




## Verified With
* :heavy_check_mark: <a href="../../verify/test/aoj/0415.test.cpp.html">test/aoj/0415.test.cpp</a>


## Code
{% raw %}
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename T>
struct DiameterForVertex{
  vector<T> vs,dp;
  vector<vector<int> > G;
  DiameterForVertex(int n):dp(n),G(n){}
  DiameterForVertex(vector<T> vs):vs(vs),dp(vs.size()),G(vs.size()){}

  void add_edge(int u,int v){
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  void dfs(int v,int p,int &s){
    if(p<0) dp[v]=T(0);
    dp[v]+=vs[v];
    if(dp[s]<dp[v]) s=v;
    for(int u:G[v]){
      if(u==p) continue;
      dp[u]=dp[v];
      dfs(u,v,s);
    }
  }

  T build(){
    assert(!vs.empty());
    int s=0;
    dfs(s,-1,s);
    dfs(s,-1,s);
    return dp[s];
  }

  T build(vector<T> us){
    assert(us.size()==dp.size());
    vs=us;
    return build();
  }
};
//END CUT HERE
#ifndef call_from_test

struct FastIO{
  FastIO(){
    cin.tie(0);
    ios::sync_with_stdio(0);
  }
}fastio_beet;

//INSERT ABOVE HERE

signed AGC033_C(){
  int n;
  cin>>n;
  vector<int> vs(n,1);
  DiameterForVertex<int> G(vs);
  for(int i=1;i<n;i++){
    int x,y;
    cin>>x>>y;
    x--;y--;
    G.add_edge(x,y);
  }
  int ans=G.build();
  cout<<((ans%3!=2)?"First":"Second")<<endl;
  return 0;
}
/*
  verified on 2019/11/12
  https://atcoder.jp/contests/agc033/tasks/agc033_c
*/

signed ARC097_F(){
  int n;
  cin>>n;
  DiameterForVertex<int> G(n);
  vector<int> deg(n,0);
  for(int i=1;i<n;i++){
    int x,y;
    cin>>x>>y;
    x--;y--;
    G.add_edge(x,y);
    deg[x]++;
    deg[y]++;
  }

  string s;
  cin>>s;

  int cnt=(n-1)*2,num=0;
  queue<int> que;
  vector<int> dead(n,0);
  for(int i=0;i<n;i++){
    num+=(s[i]=='W');
    if((deg[i]==1)&&(s[i]=='B')){
      dead[i]=1;
      que.emplace(i);
    }
  }

  while(!que.empty()){
    int v=que.front();que.pop();
    cnt-=2;
    for(int u:G.G[v]){
      if(dead[u]) continue;
      deg[u]--;
      if(deg[u]==1&&(s[u]=='B')){
        dead[u]=1;
        que.emplace(u);
      }
    }
  }

  if(num<=1){
    cout<<num<<endl;
    return 0;
  }

  vector<int> vs(n,0);
  for(int i=0;i<n;i++){
    if(dead[i]) continue;
    vs[i]=deg[i]+(s[i]=='W');
    vs[i]%=2;
    cnt+=vs[i];
  }

  cout<<cnt-G.build(vs)*2<<endl;
  return 0;
}
/*
  verified on 2019/11/12
  https://atcoder.jp/contests/arc097/tasks/arc097_d
*/

signed main(){
  //AGC033_C();
  //ARC097_F();
  return 0;
}
#endif

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
