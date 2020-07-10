#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TRandom.h"
#include "TMath.h"

using namespace std;

map<pair<int,int>,double> driftMap;

int loadDriftTimes(string fName)
{
   ifstream mapFile;
   mapFile.open(fName);
   if(!mapFile.is_open()){
     cout<<"Failed to open "<<fName<<endl;
     return 0;
   }
   string line;
   std::getline(mapFile, line);
   int rVal, zVal;
   double tDrift;
   while(std::getline(mapFile, line)){
     istringstream row(line);
     while(row>> rVal >> zVal >> tDrift) driftMap[pair<int,int>(rVal,(-1*zVal)+40)] = tDrift;
   }
   return 1;
}
int main(int argc, char** argv)
{
  double dTthresh = 16.;
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
  int failCode = loadDriftTimes("/Users/jgruszko/Documents/LEGEND/SurfaceScanner/c3f_map.txt");
  if(failCode == 0) return 1;

  TTreeReader treeReader(tree);
  TTreeReaderValue< vector<double> > Edep(treeReader, "Edep");
  TTreeReaderValue< vector<double> > xIn(treeReader, "x");
  TTreeReaderValue< vector<double> > yIn(treeReader, "y");
  TTreeReaderValue< vector<double> > zIn(treeReader, "z");
  TTreeReaderValue< vector<int> > volID(treeReader, "volID");
  TTreeReaderValue< vector<int> > iRep(treeReader, "iRep");
  TTreeReaderValue< int > eventIn(treeReader, "event");

  cout<<inName<<endl;
  cout<<inName.Last('.')<<endl;
  TString outName(inName(0, inName.Last('.'))); 
  outName += "_processed_wPSA.root";
  TFile* outFile = TFile::Open(outName, "recreate");
  TTree* outTree = new TTree("procTree", "procTree");

  vector<double> energy;
  outTree->Branch("energy", &energy);
  vector<double> rOut;
  outTree->Branch("r", &rOut);
  vector<double> xOut;
  outTree->Branch("x", &xOut);
  vector<double> yOut;
  outTree->Branch("y", &yOut);
  vector<double> zOut;
  outTree->Branch("z", &zOut);
  vector<double> tOut;
  outTree->Branch("tDrift", &tOut);
  vector<double> dTHeuristic;
  outTree->Branch("dTHeuristic", &dTHeuristic);
  vector<bool> isMulti;
  outTree->Branch("isMulti", &isMulti);
  vector<int> detID;
  outTree->Branch("detID", &detID);
  vector<int> volIDOut;
  outTree->Branch("volID", &volIDOut);
  int event;
  outTree->Branch("event", &event, "event/I");
 
  double radius = 0;
  double deadR = 36;
  double passR = 13;
  double deadZ = 39;

  double xVal, yVal, zVal, rVal, tVal;
  while(treeReader.Next()) {
    energy.clear();
    xOut.clear();
    yOut.clear();
    zOut.clear();
    tOut.clear();
    rOut.clear();
    detID.clear();
    volIDOut.clear();
    dTHeuristic.clear();
    isMulti.clear();
    map<pair<int,int>,double> hits;
    map<pair<int,int>,double> hitsX;
    map<pair<int,int>,double> hitsY;
    map<pair<int,int>,double> hitsZ;
    map<pair<int, int>, double> maxE;
    map<pair<int, int>, double> maxX;
    map<pair<int, int>, double> maxY;
    map<pair<int, int>, double> maxZ;
    map<pair<int, int>, double> secondE;
    map<pair<int, int>, double> secondX;
    map<pair<int, int>, double> secondY;
    map<pair<int, int>, double> secondZ;
    map<pair<int, int>, double> dT;
    map<pair<int, int>, bool> multiTag;

    for(size_t i=0; i < Edep->size(); i++) {
      if(volID->at(i) != 1) continue;
      radius = TMath::Sqrt(xIn->at(i)*xIn->at(i) + yIn->at(i)*yIn->at(i));
      if(radius>deadR) continue; //cut outside deadlayer 
      if(zIn->at(i)<-1*deadZ) continue; //cut bottom deadlayer (non-p+ side)
      if(zIn->at(i)>deadZ && radius > passR) continue; //cut wrap-around
      hits[pair<int,int>(volID->at(i),iRep->at(i))] += Edep->at(i);
      hitsX[pair<int,int>(volID->at(i),iRep->at(i))] += Edep->at(i)*xIn->at(i);
      hitsY[pair<int,int>(volID->at(i),iRep->at(i))] += Edep->at(i)*yIn->at(i);
      hitsZ[pair<int,int>(volID->at(i),iRep->at(i))] += Edep->at(i)*zIn->at(i);
      
      if (Edep->at(i) > maxE[pair<int, int>(volID->at(i), iRep->at(i))]){
        maxE[pair<int, int>(volID->at(i), iRep->at(i))] = Edep->at(i);
        maxX[pair<int, int>(volID->at(i), iRep->at(i))] = xIn->at(i);
        maxY[pair<int, int>(volID->at(i), iRep->at(i))] = yIn->at(i);
        maxZ[pair<int, int>(volID->at(i), iRep->at(i))] = zIn->at(i);
      }
      else if (Edep->at(i) > secondE[pair<int, int>(volID->at(i), iRep->at(i))]){
        secondE[pair<int, int>(volID->at(i), iRep->at(i))] = Edep->at(i);
        secondX[pair<int, int>(volID->at(i), iRep->at(i))] = xIn->at(i);
        secondY[pair<int, int>(volID->at(i), iRep->at(i))] = yIn->at(i);
        secondZ[pair<int, int>(volID->at(i), iRep->at(i))] = zIn->at(i);
      }
    }
    for(auto& hit : maxE) {
      if(hit.second == 0) continue; //if there's no max Edep, skip this event
      else if (secondE.find(hit.first)->second == 0){
        isMulti.push_back(false); 
	continue; //if the second-largest eDep is 0, event is single-site
      }
      double e1 = hit.second;
      double x1 = maxX.find(hit.first)->second;
      double y1 = maxY.find(hit.first)->second;
      double z1 = maxZ.find(hit.first)->second;
      double r1 = TMath::Sqrt(x1*x1+y1*y1);
      double t1 = driftMap.find(pair<int, int>((int)round(r1), (int)round(z1)))->second;
     
      double e2 = secondE.find(hit.first)->second;
      double x2 = secondX.find(hit.first)->second;
      double y2 = secondY.find(hit.first)->second;
      double z2 = secondZ.find(hit.first)->second;
      double r2 = TMath::Sqrt(x2*x2+y2*y2);
      double t2 = driftMap.find(pair<int, int>((int)round(r2), (int)round(z2)))->second;

      dT[hit.first] = TMath::Sqrt((t1-t2)*(t1-t2))*TMath::Sqrt(e1*e2);
      if(dT.find(hit.first)->second > dTthresh) multiTag[hit.first]= true;
      else multiTag[hit.first]= false;
    }
    for(auto& hit : hits) {
      if(hit.second == 0) continue;
      double e0 = hit.second;
      double sigma = pctResAt1MeV/100.*sqrt(e0);
      xVal = hitsX.find(hit.first)->second/e0;
      yVal = hitsY.find(hit.first)->second/e0;
      zVal = hitsZ.find(hit.first)->second/e0;
      rVal = TMath::Sqrt(xVal*xVal+yVal*yVal);
      //tVal = driftMap.find(pair<int, int>((int)round(rVal), (int)round(zVal)))->second;
      //interpolating drift times:
      tVal = driftMap.find(pair<int, int>((int)round(rVal), (int)round(zVal)))->second;
      if(tVal == 0) continue;
      
      energy.push_back(gRandom->Gaus(e0, sigma));
      volIDOut.push_back(hit.first.first);
      detID.push_back(hit.first.second);
      xOut.push_back(xVal);
      yOut.push_back(yVal);
      zOut.push_back(zVal);
      rOut.push_back(rVal);
      tOut.push_back(tVal);
      dTHeuristic.push_back(dT.find(hit.first)->second);
      isMulti.push_back(multiTag.find(hit.first)->second);
    }
    event = int(*eventIn);
    if(energy.size() > 0) outTree->Fill();
  }

  outTree->Write();
  outFile->Close();

  return 0;
}
