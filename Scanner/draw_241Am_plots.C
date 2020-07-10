{

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  int angle[3]={90, 45, 30};
  TString fName;
  
  fName.Form("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/%ddeg/processed/scanner_241Am_%ddeg_0p5mm10mmEA18_realisticSource_*_processed.root", angle[0], angle[0]);
  TChain* ch_90 = new TChain("procTree");
  ch_90->Add(fName);
  TH1D* hE_0 = new TH1D("hE_0", "Energy", 700, 0 , 7);
  hE_0->SetLineColor(kBlue);
  hE_0->SetXTitle("energy [MeV]");
  hE_0->SetYTitle("Events/10 keV");


  fName.Form("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/%ddeg/processed/scanner_241Am_%ddeg_0p5mm10mmEA18_realisticSource_*_processed.root", angle[1], angle[1]);
  TChain* ch_45 = new TChain("procTree");
  ch_45->Add(fName);
  TH1D* hE_1 = new TH1D("hE_1", "Energy", 700, 0 , 7);
  hE_1->SetLineColor(kViolet);
  hE_1->SetXTitle("energy [MeV]");
  
  fName.Form("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/%ddeg/processed/scanner_241Am_%ddeg_0p5mm10mmEA18_realisticSource_*_processed.root", angle[2], angle[2]);
  TChain* ch_30 = new TChain("procTree");
  ch_30->Add(fName);
  TH1D* hE_2 = new TH1D("hE_2", "Energy", 700, 0 , 7);
  hE_2->SetLineColor(kRed);
  hE_2->SetXTitle("energy [MeV]");
  
  ch_90->Draw("energy >> hE_0", "tDrift < 300 && !isMulti");
  hE_0->GetXaxis()->SetRangeUser(5, 7);
  ch_45->Draw("energy >> hE_1", "tDrift < 300 && !isMulti");
  ch_30->Draw("energy >> hE_2", "tDrift < 300 && !isMulti");
  hE_0->Draw("HIST");
  hE_1->Draw("HIST SAME");
  hE_2->Draw("HIST SAME");
  hE_0->SetMinimum(0.1);

  TLegend* legend = new TLegend(0.15, 0.7, 0.3, 0.85);
  legend->SetBorderSize(0);
  legend->AddEntry(hE_0, "90 deg", "L");
  legend->AddEntry(hE_1, "45 deg", "L");
  legend->AddEntry(hE_2, "30 deg", "L");
  legend->Draw();

  fName = "/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/241Am_spectrum_wPSA.pdf";
  c1->SaveAs(fName);

  TH1D* hZ_0 = new TH1D("hZ_0", "Z Depth, #alpha peak", 50, 34.95 , 35);
  hZ_0->SetLineColor(kBlue);
  hZ_0->SetXTitle("Z (mm)");
  hZ_0->SetYTitle("Events/um");
  ch_90->Draw("z>>hZ_0", "energy>5.476 && energy<5.494", "tDrift < 300 && !isMulti");
  
  TH1D* hZ_1 = new TH1D("hZ_1", "Z Depth, #alpha peak", 50, 34.95 , 35);
  hZ_1->SetLineColor(kViolet);
  ch_45->Draw("z>>hZ_1", "energy>5.476 && energy<5.494", "tDrift < 300 && !isMulti");
  
  TH1D* hZ_2 = new TH1D("hZ_2", "Z Depth, #alpha peak", 50, 34.95 , 35);
  hZ_2->SetLineColor(kRed);
  ch_30->Draw("z>>hZ_2", "energy>5.476 && energy<5.494", "tDrift < 300 && !isMulti");
 
  hZ_0->Draw("HIST");
  hZ_1->Draw("HIST SAME");
  hZ_2->Draw("HIST SAME");
  legend->Draw();

  fName = "/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/241Am_z_alpha_wPSA.pdf";
  c1->SaveAs(fName);

  double runTime = 135.0;
  ofstream fOut;
  fOut.open("/Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/241Am_counts.txt", std::ofstream::app);
  
  fOut<<std::setw(10)<<"90deg "<<std::setw(20)<<"energy>10keV "<<std::setw(10)<<ch_90->GetEntries("energy>0.01")/runTime<<"Hz"<<endl;
  fOut<<std::setw(10)<<"90deg "<<std::setw(20)<<"energy>5.476MeV && energy<5.494MeV && tDrift<300 && !isMulti"<<std::setw(10)<<ch_90->GetEntries("energy>5.476 && energy<5.494 && tDrift < 300 && !isMulti")/runTime<<" Hz"<<endl;
  fOut<<std::setw(10)<<"45deg "<<std::setw(20)<<"energy>10keV "<<std::setw(10)<<ch_45->GetEntries("energy>0.01")/runTime<<" Hz"<<endl;
  fOut<<std::setw(10)<<"45deg "<<std::setw(20)<<"energy>5.476MeV && energy<5.494MeV && tDrift<300 && !isMulti"<<std::setw(10)<<ch_45->GetEntries("energy>5.476 && energy<5.494 &&tDrift < 300 && !isMulti ")/runTime<<" Hz"<<endl;
  fOut<<std::setw(10)<<"30deg "<<std::setw(20)<<"energy>10keV "<<std::setw(10)<<ch_30->GetEntries("energy>0.01")/runTime<<" Hz"<<endl;
  fOut<<std::setw(10)<<"30deg "<<std::setw(20)<<"energy>5.476MeV && energy<5.494MeV && tDrift<300 && !isMulti"<<std::setw(10)<<ch_30->GetEntries("energy>5.476 && energy<5.494 &&tDrift < 300 && !isMulti ")/runTime<<" Hz"<<endl;
  fOut<<std::setw(10)<<"30deg "<<std::setw(20)<<"energy>5.476MeV && energy<5.494MeV && tDrift<300 && !isMulti"<<std::setw(10)<<ch_30->GetEntries("energy>5.476 && energy<5.494 &&tDrift < 300 && !isMulti ")<<endl;
}
