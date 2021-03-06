#ifndef IO_H
#define IO_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "point.h"
// This part will be automatically generated by updateAlgo.sh 
// alg program header start
#include "topmlcs.h"
#include "quickdp.h"
#include "promlcs.h"
#include "mlcsapp.h"
#include "hasmlcs.h"
// alg program header end

using namespace std;

class MLCSIO{
    
public:
    MLCSIO(){}
    MLCSIO(vector<string>& seqs):seqs(seqs){}
    MLCSIO(string filename);
    ~MLCSIO(){}
    
    vector<string> getSeqs() const {return seqs;}
    void output(ostream& os, string algo, string alphasets, string params);
    
private:
    vector<string> seqs;
    string filename;

};

#endif // IO_H