{

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  int angles[3]={90, 45, 30};
  ofstream fOut;
  fOut.open("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/1mm15mmEA18/Cs137_counts.txt", ios::app);
  TCanvas* c1 = new TCanvas();
  TH1D* hZ[3];
  TString hName;
  TH1D* hZ30 = new TH1D("h30Z", "Z Depth", 8000, -40, 40);
  
  TLegend* legend2 = new TLegend(0.15, 0.7, 0.3, 0.85);
  legend2->SetBorderSize(0);
  for(int i = 0; i<1; i++){
    int angle = angles[i];
    TString fName;
    fName.Form("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/1mm15mmEA18/137Cs/%ddeg/processed/scanner_137Cs_%ddeg_1mm15mmEA18_realisticSource_*_processed.root", angle, angle);
    TChain* ch = new TChain("procTree");
    ch->Add(fName);
    cout<<ch->GetEntries()<<" entries"<<endl;

    hName.Form("hZ%d", angle);
    hZ[i] = new TH1D(hName, "Z Depth", 8000, -40, 40);
    
    TH1D* hE_0 = new TH1D("hE_0", "Energy", 1000, 0 , 1);
    hE_0->SetLineColor(kBlue);
    hE_0->SetXTitle("energy [MeV]");
    TH1D* hE_1 = new TH1D("hE_1", "Energy", 1000, 0 , 1);
    hE_1->SetLineColor(kViolet);
    hE_1->SetXTitle("energy [MeV]");
    TH1D* hE_2 = new TH1D("hE_2", "Energy", 1000, 0 , 1);
    hE_2->SetLineColor(kRed);
    hE_2->SetXTitle("energy [MeV]");
    
    ch->Draw("energy >> hE_0");
    ch->Draw("energy >> hE_1", "tDrift < 300");
    ch->Draw("energy >> hE_2", "tDrift < 300 && !isMulti");
    hE_0->GetXaxis()->SetRangeUser(0, .7);
    hE_0->Draw("HIST");
    hE_1->Draw("HIST SAME");
    hE_2->Draw("HIST SAME");
    hE_0->SetMinimum(0.1);
    c1->SetLogy();

    TLegend* legend = new TLegend(0.15, 0.7, 0.3, 0.85);
    legend->SetBorderSize(0);
    legend->AddEntry(hE_0, "All events", "L");
    legend->AddEntry(hE_1, "tDrift < 300ns", "L");
    legend->AddEntry(hE_2, "tDrift < 300ns, 'single-site'", "L");
    legend->Draw();

    fName.Form("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/1mm15mmEA18/137Cs/137Cs_%ddeg_spectrum_1mmby15mm_realisticSource.pdf", angle);
    c1->SaveAs(fName);
    hE_0->GetXaxis()->SetRangeUser(.6, .7);
    hE_0->Draw("HIST");
    hE_1->Draw("HIST SAME");
    hE_2->Draw("HIST SAME");
    legend->Draw();
    fName.Form("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/1mm15mmEA18/137Cs/137Cs_%ddeg_spectrum_1mmby15mm_realisticSource_zoom.pdf", angle);
    c1->SaveAs(fName);

    
    fOut<<std::setw(10)<<angle<<std::setw(30)<<"No cut"<<std::setw(10)<<ch->GetEntries("energy>.622 && energy<.626")<<endl;
    fOut<<std::setw(10)<<angle<<std::setw(30)<<"tDrift<300ns"<<std::setw(10)<<ch->GetEntries("energy>.622 && energy<.626 && tDrift<300")<<endl;
    fOut<<std::setw(10)<<angle<<std::setw(30)<<"tDrift<300ns and !isMulti"<<std::setw(10)<<ch->GetEntries("energy>.622 && energy<.626 && tDrift<300 && !isMulti")<<endl;
    fOut<<std::setw(10)<<angle<<std::setw(30)<<"r<5 and z>34.5"<<std::setw(10)<<ch->GetEntries("energy>.622 && energy<.626 && TMath::Sqrt(x*x+y*y)<5 && z > 34.5")<<endl;
    
    hName.Form("z >> hZ%d", angle);
    ch->Draw(hName, "energy>0.622 && energy<0.626");
    hZ[i]->SetLineColor(i+1);
    hZ[i]->SetXTitle("z (mm)");
    hName.Form("%d deg", angle);
    legend2->AddEntry(hZ[i], hName, "L");

  }
  hZ[0]->GetXaxis()->SetRangeUser(34, 35);
  hZ[0]->GetYaxis()->SetRangeUser(0.1, 500);
  //hZ[1]->GetXaxis()->SetRangeUser(34, 35);
  //hZ[1]->GetYaxis()->SetRangeUser(0.1, 500);
  //hZ[2]->GetXaxis()->SetRangeUser(34, 35);
  //hZ[2]->GetYaxis()->SetRangeUser(0.1, 500);
  hZ[0]->Draw("HIST");
  //hZ[1]->Draw("HIST SAME");
  //hZ[2]->Draw("HIST SAME");
  legend2->Draw();
  c1->SaveAs("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/1mm15mmEA18/137Cs/137Cs_z_1mmby15mm_realisticSource_zoom.pdf");
  for(int i = 0; i < 1; i++){
     hZ[i]->GetXaxis()->SetRangeUser(-40, 40);
     hZ[i]->Rebin(10);
  }
  hZ[0]->Draw("HIST");
  //hZ[1]->Draw("HIST SAME");
  //hZ[2]->Draw("HIST SAME");
  legend2->Draw();
  c1->SaveAs("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/1mm15mmEA18/137Cs/137Cs_z_1mmby15mm_realisticSource.pdf");
}
