#include "include/E15190Reader.h"

//____________________________________________________
void E15190Reader::CreateUsefulVetoWallHistograms(const char * file_name, Long64_t evt_amount)
{
  // this method constructs some useful VetoWall histograms

  if(!fIsNWB || !fIsFA || !fIsVW) return;

  TFile * FileOut = new TFile(file_name, "RECREATE");
  if(FileOut->IsZombie()) {
    printf("Error: Cannot create file %s\n", file_name);
    return;
  }

  // Initializing output histograms
  TH2D * VWDETOF[NUM_BARS_VW];
  TH2D * VWDETOFMatched[NUM_BARS_VW];
  for(int i=0; i<NUM_BARS_VW; i++) {
    VWDETOF[i] = new TH2D (Form("VWDETOF%02d",i), Form("VWDETOF%02d",i), 600,0,300,1024,0,4096);
    VWDETOFMatched[i] = new TH2D (Form("VWDETOF%02dMatched",i), Form("VWDETOF%02dMatched",i), 600,0,300,1024,0,4096);
  }

  Long64_t nentries=fChain->GetEntries();
  if(evt_amount!=0) {
    nentries=evt_amount;
  }
  Long64_t jentry=0;
  std::cout << "found " << nentries << " entries\n";
  for(;fE15190Reader->Next() && jentry<nentries; jentry++)
  {
    if(jentry%100000==0) {
      PrintPercentage(jentry,nentries);
    }

    NeutronWallCalibratedData * NWB = fNWBCal->Get();
    ForwardArrayCalibratedData * ForwardArray = fForwardArrayCal->Get();
    VetoWallCalibratedData * VetoWall = fVetoWallCal->Get();

    for(int i=0; i<NWB->fmulti; i++) {
      double TOF = NWB->fTimeMean[i]-ForwardArray->fTimeMin;
      for(int j=0; j<VetoWall->fmulti; j++) {
        VWDETOF[VetoWall->fnumbar[j]]->Fill(TOF,VetoWall->fGeoMean[j]);
        VWDETOFMatched[VetoWall->fnumbar[j]]->Fill(TOF,VetoWall->fGeoMeanMatched[j]);
      }
    }
  }

  //Writing histograms to file
  for(int i=0; i<NUM_BARS_VW; i++) {
    FileOut->WriteTObject(VWDETOF[i], VWDETOF[i]->GetName());
    FileOut->WriteTObject(VWDETOFMatched[i], VWDETOFMatched[i]->GetName());
  }

  // closing output file
  FileOut->Close();
}

//____________________________________________________
void E15190Reader::CreateUsefulForwardArrayHistograms(const char * file_name, Long64_t evt_amount)
{
  // this method constructs some useful VetoWall histograms

  if(!fIsNWB || !fIsFA) return;

  TFile * FileOut = new TFile(file_name, "RECREATE");
  if(FileOut->IsZombie()) {
    printf("Error: Cannot create file %s\n", file_name);
    return;
  }

  // Initializing output histograms
  TH1D * FANWBToF[NUM_DETECTORS_FA];
  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FANWBToF[i] = new TH1D(Form("FA%02dNWBToF", i+1),Form("FA%02dNWBToF", i+1),600,-150,150);
  }

  Long64_t nentries=fChain->GetEntries();
  if(evt_amount!=0) {
    nentries=evt_amount;
  }
  Long64_t jentry=0;
  std::cout << "found " << nentries << " entries\n";
  for(;fE15190Reader->Next() && jentry<nentries; jentry++)
  {
    if(jentry%100000==0) {
      PrintPercentage(jentry,nentries);
    }

    NeutronWallCalibratedData * NWB = fNWBCal->Get();
    ForwardArrayCalibratedData * ForwardArray = fForwardArrayCal->Get();

    for(int FAhit=0; FAhit<ForwardArray->fmulti; FAhit++)
    {
      for(int NWhit=0; NWhit<NWB->fmulti; NWhit++) {
        // I record the ToF spectrum only if the FA element has a significant energy (more than 300)
        if(ForwardArray->fE[FAhit]>300) FANWBToF[ForwardArray->fnumdet[FAhit]-1]->Fill(NWB->fTimeMean[NWhit]-ForwardArray->fTime[FAhit]);
      }
    }

  }

  //Writing histograms to file
  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FileOut->WriteTObject(FANWBToF[i], FANWBToF[i]->GetName());
  }

  // closing output file
  FileOut->Close();
}
