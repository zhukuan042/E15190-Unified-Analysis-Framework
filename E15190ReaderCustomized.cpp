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
  for(int i=0; i<NUM_BARS_VW; i++) {
    VWDETOF[i] = new TH2D (Form("VWDETOF%02d",i), Form("VWDETOF%02d",i), 600,0,300,1024,0,4096);
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
      }
    }
  }

  for(int i=0; i<NUM_BARS_VW; i++) {
    FileOut->WriteTObject(VWDETOF[i], VWDETOF[i]->GetName());
  }

  // closing output file
  FileOut->Close();
}
