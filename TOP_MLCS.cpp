#include "TOP_MLCS.h"

TOP_MLCS::TOP_MLCS(vector<string>& seqs, string& alphabets){

	unordered_map<char, int> cmap = build_alphabet_map(alphabets);
	phash_init(seqs.size());
	SucTabs = cal_suc_tabs(seqs, cmap);
	this->seqs = seqs;

}

int TOP_MLCS::construct_ICSG(){

    Point<CordType> *p0 = new Point<CordType>(SucTabs.size(), false, 0);
    queue< Point<CordType>* > Q;
    int index = 0;
	
    Q.push(p0);
    DM.insert(p0);
    ID.push_back(0);

    while(!Q.empty()){
        Point<CordType> *p = Q.front();
        for(int i = 0; i < SucTabs[0].size(); ++i){
            Point<CordType> *suc = successor(p, SucTabs, i);
            if(suc){
                if(DM.insert(suc)){
                    Q.push(suc);
                    ID.push_back(1);
                }
                else{
                    int index_t = DM.at(suc);
                    ID[index_t] = ID[index_t] + 1;
					delete suc;
                }
            }
        }
        Q.pop();
        index++;
    }

    Point<CordType> *pinf = new Point<CordType>(SucTabs.size(), false, -1);
    DM.insert(pinf);

    return DM.size();

}

int TOP_MLCS::ForwardTopSort(int maxIndex){

    vector<int> D{0};
    tlevel = vector<int>(maxIndex, 0);
    precursor = vector< list<int> >(maxIndex, list<int>());

    int k = 0;

    while(D.size()){
        vector<int> Dt;
        for(auto index : D){
            bool hasSuccessor = false;
			Point<CordType> *p = DM.at(index);
			for(int i = 0; i < SucTabs[0].size(); ++i){
				Point<CordType> *suc = successor(p, SucTabs, i);
                if(suc){
                    int index_t = DM.at(suc);
                    hasSuccessor = true;
                    tlevel[index_t] = k + 1;
                    if(is_immediate_successor(suc, p, SucTabs)){
                        precursor[index_t].push_back(index);
                    }
                    ID[index_t] = ID[index_t] - 1;
                    if(ID[index_t] == 0){
                        Dt.push_back(index_t);
                    }
					delete suc;
                }
            }
            if(!hasSuccessor){
                precursor[maxIndex - 1].push_back(index);
            }
        }
        k = k + 1;
        D = Dt;
    }
    tlevel[maxIndex - 1] = k;

    return k - 1;

}



void TOP_MLCS::BackwardTopSort(int maxlevel, int pinf_index){

    vector<int> D{pinf_index};
    int k = 0;

    while(D.size() != 0){
        vector<int> Dt;
        for(auto q : D){
            for(auto p = precursor[q].begin(); p != precursor[q].end();){
                if(tlevel[*p] + k != maxlevel){
                    p = precursor[q].erase(p);
                }
                else{
                    Dt.push_back(*p);
                    p++;
                }
            }
        }
        D = Dt;
        k = k + 1;
    }

}

void TOP_MLCS::run(){
	
	int maxIndex, maxlevel;
	string LCSRecord;
	
	maxIndex = construct_ICSG();
    cout << "The number of points Generated is " << maxIndex << " ." << endl;
    maxlevel = ForwardTopSort(maxIndex);
    cout << "The maximal level of points is " << maxlevel << " ." << endl;
    BackwardTopSort(maxlevel, maxIndex - 1);
	cout << "Generating MLCS..." << endl;
	GetMLCS(LCSRecord, maxIndex - 1);
	for(string& lcs : mlcs){
        reverse(lcs.begin(), lcs.end());
    }
	
}

void TOP_MLCS::GetMLCS(string& LCSRecord, int index){

    if(index == 0){
        mlcs.push_back(LCSRecord.substr(0, LCSRecord.length() - 1));
        return;
    }

    for(auto p : precursor[index]){
        Point<CordType> *q = DM.at(p);
        LCSRecord += seqs[0][q->cord[0] - 1];
        GetMLCS(LCSRecord, p);
        LCSRecord = LCSRecord.substr(0, LCSRecord.length() - 1);
    }

}

TOP_MLCS::~TOP_MLCS(){
	
	
}