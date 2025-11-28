#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

struct Aminoacid {
    char type;
    int energy;
};

int affinity(char aa1, char aa2){
    std::map<std::pair<char, char>, int> affinity_map = {
        {{'P', 'P'},  1}, {{'P', 'N'}, 3}, {{'P', 'A'}, 1}, {{'P', 'B'}, 3},
        {{'N', 'P'}, 5}, {{'N', 'N'},  1}, {{'N', 'A'}, 0}, {{'N', 'B'}, -2},
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

int removal_energy(Aminoacid aa1, Aminoacid aa2, Aminoacid aa3){
    return aa1.energy *affinity(aa1.type,aa2.type)*aa2.energy + aa2.energy * affinity(aa2.type,aa3.type)*aa3.energy;
}

int best_removal_energy(std::vector<Aminoacid> chain, int position, int beg, int end){
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

int main(){
    char 
    return 0;
}