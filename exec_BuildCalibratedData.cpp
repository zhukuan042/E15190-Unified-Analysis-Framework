#include <E15190Reader.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TChain.h>
#include <TH2.h>
#include <iostream>

#include <HTExperimentInfo.h>
#include <HTRunInfo.h>

int main (int argc, char ** argv)
{
  if(argc<=1) return -1;
  std::string data_path("/mnt/analysis/e15190/HiRAEVTMapper_rootfiles/");
  TChain *dataChain = (TChain*) new TChain("E15190");
  std::string first_run_name(argv[1]);
  int first_run = atoi(first_run_name.c_str());
  int last_run=first_run;
  Long64_t evt_amount=0;
  if(argc==4) {
    evt_amount=atoi(argv[3]);
  }
  if(argc>2) {
    std::string last_run_name(argv[2]);
    last_run = atoi(last_run_name.c_str());
  }

  // Building Epxeriment Info class
  HTExperimentInfo * ExpInfo = new HTExperimentInfo();
  ExpInfo->InitClass("config/HiRAEVT.conf");

  // Run by Run loop ////////////////////////
  for(int cur_run=first_run; cur_run<=last_run; cur_run++)
  {
    char file_evt[100];
    sprintf (file_evt,"run-%04d*.root",cur_run);
    std::string file_evt_string(file_evt);
    std::string path_to_evt_file(data_path+file_evt_string);
    int n_files = dataChain->Add((data_path+file_evt).c_str());
    printf("%d Root files added to chain for run %d\n", n_files, cur_run);


    //Building framework /////////////////

    E15190Reader E15190Analyzer(dataChain, "NWB NWA VW FA");

    //Building HTRunInfo class ///////////
    HTRunInfo * CurrRunInfo = ExpInfo->GetRunInfo(cur_run);

    //Loading calibration files //////////
    E15190Analyzer.LoadNWPositionCalibration(CurrRunInfo->GetNWBPositionCalibrationFileName(), "NWB");
    E15190Analyzer.LoadNWPositionCalibration(CurrRunInfo->GetNWAPositionCalibrationFileName(), "NWA");
    E15190Analyzer.LoadNWGeometryFiducialPoints(CurrRunInfo->GetNWBGeometryCalibrationFileName(), "NWB");
    E15190Analyzer.LoadNWTimeCalibration(CurrRunInfo->GetNWBTimeOffsetCalibrationFileName(), "NWB");
    E15190Analyzer.LoadNWPulseHeightMatching(CurrRunInfo->GetNWBGainMatchingCalibrationFileName(), "NWB");
    E15190Analyzer.LoadNWPulseHeightMatching(CurrRunInfo->GetNWAGainMatchingCalibrationFileName(), "NWA");
    E15190Analyzer.LoadFATimeCalibration(CurrRunInfo->GetFATimeCalibrationFileName());
    E15190Analyzer.LoadFATimePulseHeightCorrection(CurrRunInfo->GetFAPulseHeightCorrectionFileName());
    E15190Analyzer.LoadMBGeometry(CurrRunInfo->GetMBGeometryFileName());
    E15190Analyzer.LoadMBDetectorStatus(CurrRunInfo->GerMBDetectorStatusFileName());
    E15190Analyzer.LoadMBFastSlowHitCondition(CurrRunInfo->GetMBHitConditionFileName());
    E15190Analyzer.LoadMBCentrality(CurrRunInfo->GetMBImpactParameterFileName());
    E15190Analyzer.LoadHiRAGeometry(CurrRunInfo->GetHiRAGeometryFileName());
    E15190Analyzer.LoadHiRASiCalibration(CurrRunInfo->GetHiRASiEnergyCalibrationFileName());
    E15190Analyzer.LoadHiRAStripBad(CurrRunInfo->GetHiRADetectorStatusFileName());
    E15190Analyzer.LoadHiRACsIPulserInfo(CurrRunInfo->GetHiRACsIPulserFileName());
    E15190Analyzer.LoadHiRASiHiLowMatching(CurrRunInfo->GetHiRASiHiLowMatchingFileName());
    E15190Analyzer.LoadHiRACsICalibration(CurrRunInfo->GetNWBGeometryCalibrationFileName(), 1, 1);


    //Definition of the output file //////

    std::string FileOutName(Form("outputNW/CalibratedData_%04d.root", cur_run));


    //Run the required method(s) /////////

    E15190Analyzer.BuildCalibratedTree(FileOutName.c_str(), evt_amount);

  }
  // End of the main loop //////////////////

  printf("\nData Analyzed, Bye!\n");
  return 0;
}
