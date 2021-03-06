enum SelectionBit {
     kLoose       =(1<<0),
     kFake        =(1<<1),
     kMedium      =(1<<2),
     kTight       =(1<<3),
     kDxyz        =(1<<4),
     kTrigger     =(1<<5),
     kFakeTrigger =(1<<6)
};

enum TriggerBits {
        kMETTrig       =(1<<0),
        kSinglePhoTrig =(1<<1),
        kMuEGTrig      =(1<<2),
        kMuMuTrig      =(1<<3),
        kMuTrig        =(1<<4),
        kEGEGTrig      =(1<<5),
        kEGTrig        =(1<<6),
        kMuTagTrig     =(1<<7),
        kEGTagTrig     =(1<<8),
        kMuFakeTrig    =(1<<9),
        kEGFakeTrig    =(1<<10)
};

const double mass_el = 0.000510998928;
const double mass_mu = 0.10566;

double fakeRateFactor(double pt, double eta, int pdgId, bool applyTight, TH2D *histoFakeEffSelMediumEtaPt_m, TH2D *histoFakeEffSelMediumEtaPt_e, TH2D *histoFakeEffSelTightEtaPt_m, TH2D *histoFakeEffSelTightEtaPt_e){
  double etal = eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
  int binXT = histoFakeEffSelMediumEtaPt_m->GetXaxis()->FindFixBin(etal);
  int binYT = histoFakeEffSelMediumEtaPt_m->GetYaxis()->FindFixBin(pt);
  
  double rate = 1.0;
  if     (TMath::Abs(pdgId) == 13 && applyTight == false) rate = TMath::Min(histoFakeEffSelMediumEtaPt_m->GetBinContent(binXT,binYT),0.999);
  else if(TMath::Abs(pdgId) == 13 && applyTight == true)  rate = TMath::Min(histoFakeEffSelTightEtaPt_m ->GetBinContent(binXT,binYT),0.999);
  else if(TMath::Abs(pdgId) == 11 && applyTight == false) rate = TMath::Min(histoFakeEffSelMediumEtaPt_e->GetBinContent(binXT,binYT),0.999);
  else if(TMath::Abs(pdgId) == 11 && applyTight == true)  rate = TMath::Min(histoFakeEffSelTightEtaPt_e ->GetBinContent(binXT,binYT),0.999);
  else printf("IMPOSSIBLE COMPUTING FAKE RATES\n");

  if(pt<20 && applyTight == true) rate = 2*rate/(1+rate);

  return rate/(1-rate);
}

double nPUScaleFactor(TH1D *fhDPU, float npu){
  double mynpu = TMath::Min(npu,(float)99.999);
  Int_t npuxbin = fhDPU->GetXaxis()->FindBin(mynpu);
  return fhDPU->GetBinContent(npuxbin);
}
