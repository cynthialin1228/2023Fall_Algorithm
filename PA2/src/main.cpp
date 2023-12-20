#include <cstring>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
using namespace std;

void help_message() {
    cout << "usage: ./mps <input file name> <output file name>" << endl;
}

int MPS(const int* data, int** table,  int i, int j) {
    if(i>=j){
        table[i][j]=0;
        return 0;
    }
    if(table[i][j] >= 0) {
        return table[i][j];
    }
    if(data[i] == j && i+1 == j){
        table[i][j] = 1;
        return table[i][j];
    }
    if(data[i] == j){
        table[i][j] = 1 + MPS(data, table, i+1, j-1);
        return table[i][j];
    }
    if(data[i] == i+1 && data[i]<j){
        table[i][j] = 1 + MPS(data, table, i+2, j);
        return table[i][j];
    }
    if(data[i] > i+1 && data[i]<j){
        int chooseChord = 1 + MPS(data, table, i+1, data[i]-1) + MPS(data, table, data[i]+1, j);
        int notChooseChord = MPS(data, table, i+1, j);
        table[i][j] = max(chooseChord, notChooseChord);
        return table[i][j];
    }
    table[i][j] = MPS(data, table, i+1, j);
    return table[i][j];
}

void get_MPS(const int* data, const int* const* table, vector<int> &chord_list, int i, int j){
    if(i>=j){
        return;
    }
    if(data[i] == j && i+1 == j){
        chord_list.push_back(i);
        return;
    }
    if(data[i] == j){
        chord_list.push_back(i);
        get_MPS(data, table, chord_list, i+1, j-1);
        return;
    }
    if(data[i] == i+1 && data[i]<j){
        chord_list.push_back(i);
        get_MPS(data, table, chord_list, i+2, j);
        return;
    }
    if(data[i] > i+1 && data[i]<j){
        int chooseChord = 1 + table[i+1][data[i]-1] + table[data[i]+1][j];
        int notChooseChord = table[i+1][j];
        if(chooseChord>notChooseChord){
            chord_list.push_back(i);
            get_MPS(data, table, chord_list, i+1, data[i]-1);
            get_MPS(data, table, chord_list, data[i]+1, j);
            return;
        }else{
            get_MPS(data, table, chord_list, i+1, j);
            return;
        }
    }
    get_MPS(data, table, chord_list, i+1, j);
    return;
}
int main(int argc, char* argv[]){
    if(argc != 3) {
       help_message();
       return 1;
    }
// read the input file
    char buffer[200];
    fstream fin(argv[1], ios::in);
    fstream fout;
    fout.open(argv[2],ios::out);
    int ver_num;
    if (!(fin >> ver_num)) { // Check for successful read
        cerr << "Error reading the number of vertices!" << endl;
        return -1;
    }
    int junk,num;
    int data[ver_num];
    for (int i=0; i<ver_num/2; i++){
        fin >> junk >> num;
        data[junk] = num;
        data[num] = junk;
    }

    fin.getline(buffer,200);
    while(fin >> junk) {
        continue;
    }

// main part of MPS
    int mps_chord;
    int **mps_table = new int*[ver_num];
    for (int i = 0; i < ver_num; i++) {
        mps_table[i] = new int[ver_num];
        for (int j = 0; j < ver_num; j++) {
            mps_table[i][j] = -1;
        }
    }
    // draw the dp table
    mps_chord = MPS(data, mps_table, 0, ver_num-1);
    vector<int> chord_list;
    // get the optimized path
    get_MPS(data, mps_table, chord_list, 0, ver_num-1);

    fout << mps_chord << endl;
    for(int i=0; i<chord_list.size(); i++){
        fout<<chord_list[i]<<" "<<data[chord_list[i]]<<endl;
    }
    for (int i = 0; i < ver_num; i++) {
        delete[] mps_table[i];
    }
    delete[] mps_table;
    fin.close();
    fout.close();
    return 0;
}