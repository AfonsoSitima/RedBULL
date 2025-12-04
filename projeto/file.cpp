#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <climits>

struct Aminoacid {
    char type;
    unsigned long long energy;
    int index;
};


int affinity(char a, char b) {
    if (a == 'T' || b == 'T') return 1;

    auto val = [](char c) {
        switch (c) {
            case 'P': return 0;
            case 'N': return 1;
            case 'A': return 2;
            case 'B': return 3;
            default:  return -1;
        }
    };

    static const int table[4][4] = {
        {1, 3, 1, 3},
        {5, 1, 0, 1},
        {0, 1, 0, 4},
        {1, 3, 2, 3}
    };

    int i = val(a);
    int j = val(b);
    if (i < 0 || j < 0) return 0;
    return table[i][j];
}



unsigned long long removal_energy(Aminoacid aa1, Aminoacid aa2, Aminoacid aa3){
    return aa1.energy *affinity(aa1.type,aa2.type)*aa2.energy + aa2.energy * affinity(aa2.type,aa3.type)*aa3.energy;
}



void build_order(int i, int j, std::vector<std::vector<int>> &choice, std::vector<int> &order) {
    if (i > j) return;
    int k = choice[i][j];
    build_order(i, k - 1, choice, order); 
    build_order(k + 1, j, choice, order); 
    order.push_back(k);
}




int main(){
    int n;
    scanf("%d", &n);

    std::vector<Aminoacid> chain(n + 2);
    std::vector<char> chain_types(n + 2);

    chain[0].type = 'T';
    chain[0].energy = 1;
    chain[n + 1].type = 'T';
    chain[n + 1].energy = 1;
    
    for (int i = 1; i < n + 1; i++)
        scanf("%llu", &chain[i].energy);

    scanf("%s", chain_types.data());
    for (int i = 0; i < n; i++)
        chain[i + 1].type = chain_types[i];

    std::vector<std::vector<unsigned long long>> best(n + 2, std::vector<unsigned long long>(n + 2, 0));
    std::vector<std::vector<int>> choice(n + 2, std::vector<int>(n + 2, 0));
    for (int len = 1; len <= n; len++) {
        

        for(int i = 1; i + len - 1 <= n; i++) { 
            int j = len + i - 1;
            unsigned long long best_val = 0;
            int best_k = 0;
            

            for(int k = i; k <= j; k++) {            
                unsigned long long sub1 = (k > i) ? best[i][k - 1] : 0;
                unsigned long long sub2 = (k < j) ? best[k + 1][j] : 0;

                unsigned long long curr = sub1 + sub2 + removal_energy(chain[i - 1], chain[k], chain[j + 1]);

                if (curr > best_val) {
                    best_val = curr;
                    best_k = k; 
                }
                else if (curr == best_val && best_k < k){ 
                    best_k = k;
                }
            }
            best[i][j] = best_val;
            choice[i][j] = best_k;

        }
    }

    std::vector<int> result;
    build_order(1, n, choice, result);
    printf("%llu\n", best[1][n]);
    for (int i = 0; i < (int)result.size(); ++i) {
        if (i) printf(" ");
        printf("%d", result[i]);
    }

    printf("\n");
    return 0;
}

