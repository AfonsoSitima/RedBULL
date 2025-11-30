#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

struct Aminoacid {
    char type;
    long long energy;
    int index;
};

struct KeepTrack {
    std::string numList;
    std::string allTypes;
    long long totalEnergy = 0;
};

int affinity(char aa1, char aa2){
    static std::map<std::pair<char, char>, int> affinity_map = {
        {{'P', 'P'},  1}, {{'P', 'N'}, 3}, {{'P', 'A'}, 1}, {{'P', 'B'}, 3},
        {{'N', 'P'}, 5}, {{'N', 'N'},  1}, {{'N', 'A'}, 0}, {{'N', 'B'}, 1},
        {{'A', 'P'}, 0}, {{'A', 'N'}, 1}, {{'A', 'A'},  0}, {{'A', 'B'},  4},
        {{'B', 'P'}, 1}, {{'B', 'N'}, 3}, {{'B', 'A'},  2}, {{'B', 'B'},  3}
    };
    if (aa1 == 'T' || aa2 == 'T') {
        return 1; // Retorna 1 se qualquer aminoácido for 'T'
    }
    else if (affinity_map.find({aa1, aa2}) == affinity_map.end()) {
        return 0; // Retorna 0 se a combinação não for encontrada
    }
    return affinity_map[{aa1, aa2}];
}

long long removal_energy(Aminoacid aa1, Aminoacid aa2, Aminoacid aa3){
    return aa1.energy *affinity(aa1.type,aa2.type)*aa2.energy + aa2.energy * affinity(aa2.type,aa3.type)*aa3.energy;
}

/*int best_removal_energy(std::vector<Aminoacid> chain, int position, int beg, int end){
    Aminoacid terminal;
    terminal.type = 'T';
    terminal.energy = 1;
    if(position - beg<=1){
        return removal_energy(chain[beg], chain[position], chain[position+1]);
    }
    else if (end- position<= 1){
        return removal_energy(chain[position-1], chain[position], chain[end]);
 
    }
    return max(best_removal_energy(chain,,beg,position))
}

*/
std::string mergeLexico(const std::string &a, const std::string &b) {
    std::string res;
    size_t i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        // comparamos os sufixos a partir de i e j
        if (a.compare(i, std::string::npos, b, j, std::string::npos) <= 0) {
            res.push_back(a[i]);
            i++;
        } else {
            res.push_back(b[j]);
            j++;
        }
    }

    // copia o que sobrar de uma das duas
    res.append(a.begin() + i, a.end());
    res.append(b.begin() + j, b.end());

    return res;
}

void changeMax(KeepTrack* n1, KeepTrack* max) {
    if (n1->totalEnergy > max->totalEnergy) *max = *n1;
    else if (n1->totalEnergy == max->totalEnergy &&   n1->allTypes < max->allTypes)  *max = *n1; //se não passar a testes mudar isto O(n)
    return;
}


bool ab_less_ba(std::string &a, std::string &b) {
    size_t n = a.size();
    size_t m = b.size();
    size_t total = n + m;
    for (size_t k = 0; k < total; ++k) {
        char c1 = (k < n) ? a[k] : b[k - n];
        char c2 = (k < m) ? b[k] : a[k - m];
        if (c1 < c2) return true; //(a + b) < (b + a)
        if (c1 > c2) return false; //(a + b) > (b + a)
    }
    return false; // (a+b) == (b+a)
}

void addSubProblems(KeepTrack* n1, KeepTrack* n2, Aminoacid aa, KeepTrack* result) {
    result->totalEnergy = n1->totalEnergy + n2->totalEnergy + aa.energy;
    if(n1->allTypes + n2->allTypes <= n2->allTypes + n1->allTypes) {   //caso for lento trocar
        result->allTypes = n1->allTypes + n2->allTypes;   
        result->numList = n1->numList + n2->numList;
    }
    else{
        result->allTypes = n2->allTypes + n1->allTypes;
        result->numList = n2->numList + n1->numList;
    }
    result->allTypes += aa.type;
    result->numList += std::to_string(aa.index) + " ";
    return; 
}




int main(){
    int n;
    scanf("%d", &n);

    std::vector<std::vector<KeepTrack>> max_energy(n + 2, std::vector<KeepTrack>(n + 2));
    std::vector<Aminoacid> chain(n + 2);
    std::vector<char> chain_types(n + 2);

    chain[0].type = 'T';
    chain[0].energy = 1;
    chain[n + 1].type = 'T';
    chain[n + 1].energy = 1;
    
    for (int i = 1; i < n + 1; i++)
        scanf("%lld", &chain[i].energy);

    scanf("%s", chain_types.data());
    for (int i = 0; i < n; i++)
        chain[i + 1].type = chain_types[i];

    //isto está a fazer o tamanho da diagonal
    for (int len = 1; len <= n; len++) {  //tamanho da diagonal
        

        for(int i = 1; i + len - 1 <= n; i++) {  //i é o index horizontal e j index vertical
            int j = len + i - 1;   //mexer na diagonal  j - i + 1 = len
            

            for(int k = i; k <= j; k++) {  //mexe na horizontal (escolhe qual é o ultimo a sair)
                Aminoacid aa;
                KeepTrack subComplete;
                aa.energy = removal_energy(chain[i - 1], chain[k], chain[j + 1]); //k é a ultima energia a ser removida
                aa.type = chain[k].type;
                aa.index = k;
                
                KeepTrack sub1 = max_energy[i][k - 1];  //temos que ver qual é lexicalmente menor entre estas duas
                KeepTrack sub2 = max_energy[k + 1][j];

                addSubProblems(&sub1, &sub2, aa, &subComplete);
                changeMax(&subComplete, &max_energy[i][j]);
            }
        }
    }

    printf("%lld\n", max_energy[1][n].totalEnergy);
    printf("%s\n", max_energy[1][n].numList.c_str());
    return 0;
}