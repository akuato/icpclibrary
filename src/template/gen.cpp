int main(){cin.tie(0);ios::sync_with_stdio(false);
    // 実行ごとに異なる強力なシードを生成
    random_device rd;
    mt19937 mt(rd());
    
    // 例: 1から100までのランダムな整数
    int T=1;
    uniform_int_distribution<int> randN(1, 5);
    uniform_int_distribution<int> randV(1, 7);
    int K=randV(mt);

    cout<< T << endl;
    cout<< N <<" " << K <<  endl;
    while(1){
        vi a;
        rep(i,N)a.push_back(randV(mt));
        sort(all(a));
        a.erase(unique(all(a)),a.end());
        if(a.size()==N){
            for(auto u:a)cout << u << " ";
            cout << endl;
            break;
        }
    }
}

