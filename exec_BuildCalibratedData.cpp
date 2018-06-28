#include <E15190Reader.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TChain.h>
#include <TH2.h>
#include <iostream>

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

    //Loading calibration files //////////
    E15190Analyzer.LoadNWPositionCalibration("calibrations/NWB_Position_Calibration_run3014.dat", "NWB");
    E15190Analyzer.LoadNWPositionCalibration("calibrations/NWA_Position_Calibration_run3014.dat", "NWA");
    E15190Analyzer.LoadNWGeometryFiducialPoints("calibrations/NWB_Geometry.dat", "NWB");
    E15190Analyzer.LoadNWTimeCalibration("calibrations/NWB_Time_Offset_run3013.dat", "NWB");
    E15190Analyzer.LoadFATimeCalibration("calibrations/FA_Time_Offset_run4557.dat");
    //E15190Analyzer.LoadFATimeCalibration("calibrations/FA_Time_Offset_run2523.dat");
    E15190Analyzer.LoadFATimePulseHeightCorrection("calibrations/FA_PulseHeightCorrection_run4543.dat");
    //E15190Analyzer.LoadFATimePulseHeightCorrection("calibrations/FA_PulseHeightCorrection_run2523.dat");
    E15190Analyzer.LoadMBGeometry("calibrations/MB_Geometry.dat");
    E15190Analyzer.LoadMBDetectorStatus("calibrations/MB_BadOrMissingDetectors.dat");
    E15190Analyzer.LoadMBFastSlowHitCondition("calibrations/MB_FastSlowCuts_2626.root");
    E15190Analyzer.LoadMBCentrality("calibrations/MB_ImpactParameter_48Ca_64Ni_140AMeV.dat");
    E15190Analyzer.LoadHiRAGeometry("calibrations/PixelLocation_RomerArm.dat");
    E15190Analyzer.LoadHiRASiCalibration("calibrations/HiRA_Si_Calibration_run4761.dat");
    //E15190Analyzer.LoadHiRASiCalibration("calibrations/HiRA_Si_Calibration_run2873.dat");
    E15190Analyzer.LoadHiRAStripBad("calibrations/HiRA_StripBad.dat");
    E15190Analyzer.LoadHiRACsIPulserInfo("calibrations/HiRA_CsI_Pulser_170setting.dat");
    //E15190Analyzer.LoadHiRACsIPulserInfo("calibrations/HiRA_CsI_Pulser_200setting.dat");
    E15190Analyzer.LoadHiRACsICalibration("calibrations/HiRA_CsI_LightVsEnergy_Z01_A01.dat", 1, 1);


    //Definition of the output file //////

    std::string FileOutName(Form("outputNW/CalibratedData_%04d.root", cur_run));


    //Run the required method(s) /////////

    E15190Analyzer.BuildCalibratedTree(FileOutName.c_str(), evt_amount);

  }
  // End of the main loop //////////////////

  printf("\nData Analyzed, Bye!\n");
  return 0;
}
