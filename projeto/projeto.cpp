#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> read_file(std::string file_path) {
    std::vector<std::string> lines;
    std::ifstream ficheiro(file_path);
    if(!ficheiro.is_open()){
        std::cerr << "Erro" << std::endl;
        return lines;
    }    
    std::string linha;
    int line_number = 0;
    while(std::getline(ficheiro, linha)){
        lines[line_number++] = linha;
    }
    ficheiro.close();
    return lines;
}

int main(int argc , char** argv){
    std::vector<std::string> lines= read_file(argv[1]);
    return 0;
}