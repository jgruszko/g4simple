#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TRandom.h"
#include "TMath.h"

using namespace std;

int main(int argc, char** argv)
{
  double pctResAt1MeV = 0.15;

  if(argc != 2) {
    cout << "Usage: postprocroot [filename.root]" << endl;
    return 1;
  }
  TString inName(argv[1]);
  TFile* file = TFile::Open(argv[1]);
  if(file == NULL) return 1;

  TTree* tree = (TTree*) file->Get("g4sntuple");
  if(tree == NULL) {
    cout << "Couldn't find g4stree in file" << endl;
    return 1;
  }

  TTreeReader treeReader(tree);
  TTreeReaderValue< vector<double> > Edep(treeReader, "Edep");
  TTreeReaderValue< vector<double> > xIn(treeReader, "x");
  TTreeReaderValue< vector<double> > yIn(treeReader, "y");
  TTreeReaderValue< vector<double> > zIn(treeReader, "z");
  TTreeReaderValue< vector<int> > volID(treeReader, "volID");
  TTreeReaderValue< vector<int> > iRep(treeReader, "iRep");
  TTreeReaderValue< int > eventIn(treeReader, "event");

  TString outName(inName(0, inName.Last('.'))); 
  outName += "_processed.root";
  TFile* outFile = TFile::Open(outName, "recreate");
  TTree* outTree = new TTree("procTree", "procTree");

  vector<double> energy;
  outTree->Branch("energy", &energy);
  vector<double> xOut;
  outTree->Branch("x", &xOut);
  vector<double> yOut;
  outTree->Branch("y", &yOut);
  vector<double> zOut;
  outTree->Branch("z", &zOut);
  vector<int> detID;
  outTree->Branch("detID", &detID);
  vector<int> volIDOut;
  outTree->Branch("volID", &volIDOut);
  int event;
  outTree->Branch("event", &event, "event/I");
 
  double eSum = 0;
  double radius = 0;
  double deadR = 34;
  double passR = 10;
  double deadZ = 34;

  while(treeReader.Next()) {
    energy.clear();
    xOut.clear();
    yOut.clear();
    zOut.clear();
    detID.clear();
    volIDOut.clear();
    eSum = 0;
    map<pair<int,int>,double> hits;
    map<pair<int,int>,double> hitsX;
    map<pair<int,int>,double> hitsY;
    map<pair<int,int>,double> hitsZ;
    for(size_t i=0; i < Edep->size(); i++) {
      if(volID->at(i) != 1) continue;
      radius = TMath::Sqrt(xIn->at(i)*xIn->at(i) + yIn->at(i)*yIn->at(i));
      if(radius>deadR) continue; 
      if(zIn->at(i)<-1*deadZ) continue;
      if(zIn->at(i)>deadZ && radius > passR) continue;
      hits[pair<int,int>(volID->at(i),iRep->at(i))] += Edep->at(i);
      hitsX[pair<int,int>(volID->at(i),iRep->at(i))] += Edep->at(i)*xIn->at(i);
      hitsY[pair<int,int>(volID->at(i),iRep->at(i))] += Edep->at(i)*yIn->at(i);
      hitsZ[pair<int,int>(volID->at(i),iRep->at(i))] += Edep->at(i)*zIn->at(i);
    }
    for(auto& hit : hits) {
      if(hit.second == 0) continue;
      volIDOut.push_back(hit.first.first);
      detID.push_back(hit.first.second);
      double e0 = hit.second;
      double sigma = pctResAt1MeV/100.*sqrt(e0);
      energy.push_back(gRandom->Gaus(e0, sigma));
      xOut.push_back(hitsX.find(hit.first)->second/e0);
      yOut.push_back(hitsY.find(hit.first)->second/e0);
      zOut.push_back(hitsZ.find(hit.first)->second/e0);
    }
    event = int(*eventIn);
    if(energy.size() > 0) outTree->Fill();
  }

  outTree->Write();
  outFile->Close();

  return 0;
}
