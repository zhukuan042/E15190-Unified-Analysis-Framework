#include "include/E15190Reader.h"

//____________________________________________________
E15190Reader::E15190Reader(TChain * Chain, const char * DataType, bool IsDataCalibrated) :
fHiRA(new TTreeReaderValue<HTHiRAData> *[NUM_TEL]),
fChain(Chain),
fDegToRad(TMath::Pi()/180.),
fRadToDeg(180./TMath::Pi()),
fSpeedOfLight(29.9792),
fNWBarLength(200),
fNWBarHigh(7.62),
fNWBarThickness(6.35),
fIsNWA(false),
fIsNWB(false),
fIsFA(false),
fIsVW(false),
fIsMB(false),
fIsHiRA(false),
fIsDataCalibrated(IsDataCalibrated),
fNWAPositionCalibrated(false),
fNWBPositionCalibrated(false),
fNWTimeCalibrated(false),
fNWPulseHeightCalibrated(false),
fNWACosmicRayPositionLoaded(false),
fNWBCosmicRayPositionLoaded(false),
fNWATimeCalibrated(false),
fNWBTimeCalibrated(false),
fNWAGeometryCalibrated(false),
fNWBGeometryCalibrated(false),
fNWAPulseHeightMatched(false),
fNWBPulseHeightMatched(false),
fNWAPulseHeightCalibrated(false),
fNWBPulseHeightCalibrated(false),
fFATimeCalibrated(false),
fMBGeometryLoaded(false),
fMBStatusLoaded(false),
fMBHitConditionLoaded(false),
fMBCentralityLoaded(false),
fHiRACsICalibrated(false),
fHiRASiCalibrated(false),
fHiRAGeometryCalibrated(false),
fHiRAStripBadLoaded(false),
fHiRASiHiLowMatched(false),
fNWAPositionCalibration(new NWPositionCalibration(NUM_BARS_NWA)),
fNWBPositionCalibration(new NWPositionCalibration(NUM_BARS_NWB)),
fNWACosmicRayInfo(new NWCosmicRayManager(NUM_BARS_NWA)),
fNWBCosmicRayInfo(new NWCosmicRayManager(NUM_BARS_NWB)),
fNWATimeCalibration(new NWTimeCalibration(NUM_BARS_NWA)),
fNWBTimeCalibration(new NWTimeCalibration(NUM_BARS_NWB)),
fNWAGeometry(new NWGeometry(NUM_BARS_NWA)),
fNWBGeometry(new NWGeometry(NUM_BARS_NWB)),
fNWAPulseHeightCalibrationTools(new NWPulseHeightCalibration(NUM_BARS_NWA)),
fNWBPulseHeightCalibrationTools(new NWPulseHeightCalibration(NUM_BARS_NWB)),
fFATimeCalibration(new FATimeCalibration(NUM_DETECTORS_FA)),
fMicroballStatus(new MBDetectorStatus()),
fMicroballGeometry(new MBGeometry()),
fMicroballHitCondition(new MBHitCondition()),
fMicroballCentrality(new MBImpactParameter()),
fGeometryTab(new HiRAGeometry[NUM_TEL*NUM_STRIP_F*NUM_STRIP_B]),
fSiCalibrationTools(new HiRASiCalibration(NUM_TEL,NUM_STRIP_F,NUM_STRIP_B)),
fSiHiLowMatching(new HiRASiHiLowMatching[NUM_TEL*NUM_STRIP_F+NUM_TEL*NUM_STRIP_B]),
fCsICalibrationModule(new HiRACsICalibrationManager()),
fTelSiThickness(new double[NUM_TEL]),
fStripfBad(new bool*[NUM_TEL]),
fStripbBad(new bool*[NUM_TEL])
{
  //Parsing DataType string to allocate specific detectors
  std::string DetectorsIncluded(DataType);
  std::istringstream StreamDetectorsIncluded(DetectorsIncluded);
  std::string DetectorToAdd;
  while (StreamDetectorsIncluded>>DetectorToAdd) {
    if(DetectorToAdd.compare("NWA")==0) fIsNWA=true;
    if(DetectorToAdd.compare("NWB")==0) fIsNWB=true;
    if(DetectorToAdd.compare("FA")==0) fIsFA=true;
    if(DetectorToAdd.compare("VW")==0) fIsVW=true;
    if(DetectorToAdd.compare("MB")==0) fIsMB=true;
    if(DetectorToAdd.compare("HiRA")==0) fIsHiRA=true;
  }

  if(fChain!=0) {
    fE15190Reader = new TTreeReader(fChain);
    if(!fIsDataCalibrated) {
      if(fIsNWA) fNWA = new TTreeReaderValue<HTNeutronWallData>(*fE15190Reader, "NWA.");
      if(fIsNWB) fNWB = new TTreeReaderValue<HTNeutronWallData>(*fE15190Reader, "NWB.");
      if(fIsFA) fForwardArray = new TTreeReaderValue<HTForwardArrayData>(*fE15190Reader, "ForwardArray.");
      if(fIsVW) fVetoWall = new TTreeReaderValue<HTVetoWallData>(*fE15190Reader, "VetoWall.");
      if(fIsMB) fMicroball = new TTreeReaderValue<HTMicroballData>(*fE15190Reader, "uBall.");
      if(fIsHiRA) {
        for(int i=0; i<NUM_TEL; i++) fHiRA[i] = new TTreeReaderValue<HTHiRAData>(*fE15190Reader, Form("HiRA.tele%d.",i));
      }
    } else {
      if(fIsNWA) fNWACal = new TTreeReaderValue<NeutronWallCalibratedData>(*fE15190Reader, "NWA.");
      if(fIsNWB) fNWBCal = new TTreeReaderValue<NeutronWallCalibratedData>(*fE15190Reader, "NWB.");
      if(fIsFA) fForwardArrayCal = new TTreeReaderValue<ForwardArrayCalibratedData>(*fE15190Reader, "ForwardArray.");
      if(fIsVW) fVetoWallCal = new TTreeReaderValue<VetoWallCalibratedData>(*fE15190Reader, "VetoWall.");
      if(fIsMB) fMicroballCal = new TTreeReaderValue<MicroballCalibratedData>(*fE15190Reader, "uBall.");
      if(fIsHiRA) {
        for(int i=0; i<NUM_TEL; i++) {}
      }
    }
  }
  for(int TelNum=0; TelNum<NUM_TEL; TelNum++) {
  fStripfBad[TelNum]= new bool[NUM_STRIP_F];
  fStripbBad[TelNum]= new bool[NUM_STRIP_B];
  }
  fTelSiThickness[0]=1537; fTelSiThickness[1]=1521; fTelSiThickness[2] =1500; fTelSiThickness [3]=1496;
  fTelSiThickness[4]=1517; fTelSiThickness[5]=1512; fTelSiThickness[6] =1491; fTelSiThickness [7]=1460;
  fTelSiThickness[8]=1537; fTelSiThickness[9]=1536; fTelSiThickness[10]=1471; fTelSiThickness[11]=1491;
  fCsIMylarThickness=2.076;
  fCsIlenght=100000;
}

//____________________________________________________
E15190Reader::~E15190Reader()
{
  if(fChain!=0) {
    delete fE15190Reader;
    if(!fIsDataCalibrated) {
      if (fIsNWA) delete fNWA;
      if (fIsNWB) delete fNWB;
      if (fIsFA) delete fForwardArray;
      if (fIsVW) delete fVetoWall;
      if (fIsMB) delete fMicroball;
      if (fIsHiRA) {
        for(int i=0; i<NUM_TEL; i++) delete fHiRA[i];
      }
    } else {
      if (fIsNWA) delete fNWACal;
      if (fIsNWB) delete fNWBCal;
      if (fIsFA) delete fForwardArrayCal;
      if (fIsVW) delete fVetoWallCal;
      if (fIsMB) delete fMicroballCal;
      if (fIsHiRA) {
        for(int i=0; i<NUM_TEL; i++) {}
      }
    }
  }

  if(fHiRA) delete [] fHiRA;
  if(fNWAPositionCalibration) delete fNWAPositionCalibration;
  if(fNWBPositionCalibration) delete fNWBPositionCalibration;
  if(fNWACosmicRayInfo) delete fNWACosmicRayInfo;
  if(fNWBCosmicRayInfo) delete fNWBCosmicRayInfo;
  if(fNWATimeCalibration) delete fNWATimeCalibration;
  if(fNWBTimeCalibration) delete fNWBTimeCalibration;
  if(fFATimeCalibration) delete fFATimeCalibration;
  if(fNWAGeometry) delete fNWAGeometry;
  if(fNWBGeometry) delete fNWBGeometry;
}

//____________________________________________________
int E15190Reader::LoadNWPositionCalibration(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWAPositionCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWAPositionCalibrated=true;
      printf("Loaded position calibration for NWA %s\n", file_name);
      return NLines;
    }
    fNWAPositionCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBPositionCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWBPositionCalibrated=true;
      printf("Loaded position calibration for NWB %s\n", file_name);
      return NLines;
    }
    fNWBPositionCalibrated=false;
  }

  printf("Error: Error while loading NW Position calibration file %s\n", file_name);
  return -1;
}

//____________________________________________________
int E15190Reader::LoadNWCosmicRayPosition(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWACosmicRayInfo->LoadPeakPositions(file_name);
    if(NLines>0) {
      fNWACosmicRayPositionLoaded=true;
      printf("Loaded cosmics calibration for NWA %s\n", file_name);
      return NLines;
    }
    fNWACosmicRayPositionLoaded=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBCosmicRayInfo->LoadPeakPositions(file_name);
    if(NLines>0) {
      fNWBCosmicRayPositionLoaded=true;
      printf("Loaded cosmics calibration for NWB %s\n", file_name);
      return NLines;
    }
    fNWBCosmicRayPositionLoaded=false;
  }

  printf("Error: Error while loading NW cosmic ray positions %s\n", file_name);
  return -1;
}

//____________________________________________________
int E15190Reader::LoadNWTimeCalibration(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWATimeCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWATimeCalibrated=true;
      printf("Loaded time calibration for NWA %s\n", file_name);
      return NLines;
    }
    fNWATimeCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBTimeCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWBTimeCalibrated=true;
      printf("Loaded time calibration for NWB %s\n", file_name);
      return NLines;
    }
    fNWBTimeCalibrated=false;
  }

  printf("Error: Error while loading NW time calibration %s\n", file_name);
  return -1;
}

//____________________________________________________
int E15190Reader::LoadNWGeometryFiducialPoints(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWAGeometry->LoadFiducialPoints(file_name);
    if(NLines>0) {
      fNWAGeometryCalibrated=true;
      printf("Loaded geometry fiducial points for NWA %s\n", file_name);
      return NLines;
    }
    fNWAGeometryCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBGeometry->LoadFiducialPoints(file_name);
    if(NLines>0) {
      fNWBGeometryCalibrated=true;
      printf("Loaded geometry fiducial points for NWB %s\n", file_name);
      return NLines;
    }
    fNWBGeometryCalibrated=false;
  }

  printf("Error: Error while loading NW geometry fiducial points %s\n", file_name);
  return -1;
}

//____________________________________________________
int E15190Reader::LoadNWPulseHeightMatching(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWAPulseHeightCalibrationTools->LoadMatching(file_name);
    if(NLines>0) {
      fNWAPulseHeightMatched=true;
      printf("Loaded gain matching for NWA %s\n", file_name);
      return NLines;
    }
    fNWAPulseHeightMatched=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBPulseHeightCalibrationTools->LoadMatching(file_name);
    if(NLines>0) {
      fNWBPulseHeightMatched=true;
      printf("Loaded gain matching for NWB %s\n", file_name);
      return NLines;
    }
    fNWBPulseHeightMatched=false;
  }

  printf("Error: Error while loading NW gain matching %s\n", file_name);
  return -1;
}

//____________________________________________________
int E15190Reader::LoadFATimeCalibration(const char * file_name)
{
  int NLines=fFATimeCalibration->LoadCalibration(file_name);
  if(NLines>0) {
    fFATimeCalibrated=true;
    printf("Loaded time calibration for FA %s\n", file_name);
    return NLines;
  } else {
    fFATimeCalibrated=false;
    printf("Error: Error while loading FA time calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadFATimePulseHeightCorrection(const char * file_name)
{
  int NLines=fFATimeCalibration->LoadPulseHeightCorrection(file_name);
  if(NLines>0) {
    fFATimeCalibrated=true;
    printf("Loaded time pulse height correction for FA %s\n", file_name);
    return NLines;
  } else {
    fFATimeCalibrated=false;
    printf("Error: Error while loading FA time calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
double E15190Reader::GetNWAXcm(int num_bar, double tleft, double tright) const
{
  return fNWAPositionCalibrated ? fNWAPositionCalibration->GetPosition(num_bar, tleft, tright) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBXcm(int num_bar, double tleft, double tright) const
{
  return fNWBPositionCalibrated ? fNWBPositionCalibration->GetPosition(num_bar, tleft, tright) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWACosmicCenter(int num_bar) const
{
  return fNWACosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayCenter(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWACosmicStartingPoint(int num_bar) const
{
  return fNWACosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayStartingPoint(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBCosmicCenter(int num_bar) const
{
  return fNWBCosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayCenter(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBCosmicStartingPoint(int num_bar) const
{
  return fNWBCosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayStartingPoint(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWATimeMean(int num_bar, double tleft, double tright) const
{
  return fNWATimeCalibrated ? 0.5*(tleft+tright)-fNWATimeCalibration->GetTimeOffset(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBTimeMean(int num_bar, double tleft, double tright) const
{
  return fNWBTimeCalibrated ? 0.5*(tleft+tright)-fNWBTimeCalibration->GetTimeOffset(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetFATimeOffset(int num_det) const
{
  return fFATimeCalibrated ? fFATimeCalibration->GetTimeOffset(num_det) : 0;
}

//____________________________________________________
double E15190Reader::GetNWATheta(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetTheta(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWAPhi(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetPhi(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWAThetaRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetThetaRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWAPhiRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetPhiRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWADistance(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetR(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWADistanceRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetRRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBTheta(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetTheta(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBPhi(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetPhi(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBThetaRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetThetaRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBPhiRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetPhiRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBDistance(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetR(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBDistanceRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetRRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetFATimePulseHeightCorrection(int num_det, double pulse_height) const
{
  return fFATimeCalibrated ? fFATimeCalibration->GetTimePulseHeightCorrection(num_det, pulse_height) : 0;
}

//____________________________________________________
int E15190Reader::LoadMBGeometry(const char * file_name)
{
  int NLines=fMicroballGeometry->LoadGeometry(file_name);
  if(NLines>0) {
    fMBGeometryLoaded=true;
    printf("Loaded Microball geometry from file %s\n", file_name);
    return NLines;
  } else {
    fMBGeometryLoaded=false;
    printf("Error: Error while loading Microball geometry %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadMBDetectorStatus(const char * file_name)
{
  int NLines=fMicroballStatus->LoadBadDetectors(file_name);
  if(NLines>0) {
    fMBStatusLoaded=true;
    printf("Loaded Microball status from file %s\n", file_name);
    return NLines;
  } else {
    fMBStatusLoaded=false;
    printf("Error: Error while loading Microball status %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadMBFastSlowHitCondition(const char * file_name)
{
  int NLines=fMicroballHitCondition->LoadFastSlowCuts(file_name);
  if(NLines>0) {
    fMBHitConditionLoaded=true;
    printf("Loaded Microball Fast Slow Hit conditions from file %s\n", file_name);
    return NLines;
  } else {
    fMBHitConditionLoaded=false;
    printf("Error: Error while loading Microball Fast Slow Hit conditions %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadMBCentrality(const char * file_name)
{
  int NLines=fMicroballCentrality->LoadImpactParameter(file_name);
  if(NLines>0) {
    fMBCentralityLoaded=true;
    printf("Loaded Microball centrality conditions from file %s\n", file_name);
    return NLines;
  } else {
    fMBCentralityLoaded=false;
    printf("Error: Error while loading Microball centrality conditions %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
double E15190Reader::GetTheta(int num_ring, int num_det) const
{
  return fMBGeometryLoaded ? fMicroballGeometry->GetTheta(num_ring, num_det) : -9999;
}

//____________________________________________________
double E15190Reader::GetPhi(int num_ring, int num_det) const
{
  return fMBGeometryLoaded ? fMicroballGeometry->GetPhi(num_ring, num_det) : -9999;
}

//____________________________________________________
double E15190Reader::GetThetaRandom(int num_ring, int num_det) const
{
  return fMBGeometryLoaded ? fMicroballGeometry->GetThetaRandom(num_ring, num_det) : -9999;
}

//____________________________________________________
double E15190Reader::GetPhiRandom(int num_ring, int num_det) const
{
  return fMBGeometryLoaded ? fMicroballGeometry->GetPhiRandom(num_ring, num_det) : -9999;
}

//____________________________________________________
double E15190Reader::GetImpactParameter(int multiplicity) const
{
  return fMBCentralityLoaded ? fMicroballCentrality->GetImpactParameter(multiplicity) : -9999;
}

//____________________________________________________
double E15190Reader::Getbhat(int multiplicity) const
{
  return fMBCentralityLoaded ? fMicroballCentrality->Getbhat(multiplicity) : -9999;
}

//____________________________________________________
bool E15190Reader::IsMBDetectorBad (int num_ring, int num_det) const
{
  return fMBStatusLoaded ? fMicroballStatus->IsBad(num_ring,num_det) : false;
}

//____________________________________________________
bool E15190Reader::IsMBHit (int num_ring, int num_det, double fast, double tail, double time) const
{
  return fMBHitConditionLoaded ? fMicroballHitCondition->IsHit(num_ring,num_det,fast,tail,time) : false;
}

//____________________________________________________
int E15190Reader::LoadHiRAGeometry(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    printf("Error: error while opening geometry file\n");
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int numstripf;
    int numstripb;
    double theta;
    double phi;

    LineStream >> numtel >> numstripf >> numstripb >> theta >> phi;

    // Phi Corretions // TEMPORARY
    if(phi<0) {
      phi=-phi-180;
    } else {
      phi=-phi+180;
    }

    // Strip order corrections // TEMPORARY
    numstripf=31-numstripf;

    HiRAGeometry newGeom;
    newGeom.numtel=numtel;
    newGeom.stripf=numstripf;

    newGeom.stripb=numstripb;
    newGeom.thetadeg=theta;
    newGeom.phideg=phi;
    newGeom.theta=theta*fDegToRad;
    newGeom.phi=phi*fDegToRad;

    fGeometryTab[numtel*NUM_STRIP_F*NUM_STRIP_B+numstripf*NUM_STRIP_B+numstripb]=newGeom;
    NRead++;
  }

  fHiRAGeometryCalibrated=true;
  return NRead;
}

//____________________________________________________
int E15190Reader::LoadHiRAStripBad(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    printf("Error: error while opening strip bad file\n");
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int striptype;
    int numstrip;
    int isbad;

    LineStream >> striptype >> numtel >> numstrip >> isbad;

    if(striptype==0) {
      fStripbBad[numtel][numstrip]=bool(isbad);
    } else if(striptype==1) {
      fStripfBad[numtel][numstrip]=bool(isbad);
    }

    NRead++;
  }

  fHiRAStripBadLoaded=true;
  return NRead;
}

//____________________________________________________
int E15190Reader::LoadHiRASiCalibration(const char * file_name)
{
  int NLines=fSiCalibrationTools->LoadCalibration(file_name);
  if(NLines>0) {
    fHiRASiCalibrated=true;
    printf("Loaded HiRA Silicon calibration from file %s\n", file_name);
    return NLines;
  } else {
    fHiRASiCalibrated=false;
    printf("Error: Error while loading HiRA Silicon calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadHiRACsICalibration(const char * file_name, int Z, int A)
{
  int NLines=fCsICalibrationModule->LoadEnergyCalibration(file_name, Z, A);
  if(NLines>0) {
    fHiRACsICalibrated=true;
    printf("Loaded HiRA CsI calibration for Z=%d A=%d from file %s\n", Z, A, file_name);
    return NLines;
  } else {
    fHiRACsICalibrated=false;
    printf("Error: Error while loading HiRA CsI calibration for Z=%d A=%d from file %s\n", Z, A, file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadHiRASiHiLowMatching(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    printf("Error: error while opening Si matching file\n");
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int numstrip;
    bool FB;
    double intercept;
    double slope;
    double saturationpoint;

    LineStream >> numtel >> numstrip >> FB >> intercept >> slope >> saturationpoint;

    HiRASiHiLowMatching newMatching;
    newMatching.numtel=numtel;
    newMatching.FB=FB;
    newMatching.numstrip=numstrip;
    newMatching.intercept=intercept;
    newMatching.slope=slope;
    newMatching.saturationpoint=saturationpoint;

    if(FB==0) {
      fSiHiLowMatching[numtel*NUM_STRIP_B+numstrip]=newMatching;
    } else if (FB==1) {
      fSiHiLowMatching[NUM_TEL*NUM_STRIP_B+numtel*NUM_STRIP_F+numstrip]=newMatching;
    }
    NRead++;
  }

  fHiRASiHiLowMatched=true;
  return NRead;
}

//____________________________________________________
int E15190Reader::LoadHiRACsIPulserInfo(const char * file_name)
{
  return fCsICalibrationModule->LoadPulserInfo(file_name);
}

//____________________________________________________
bool E15190Reader::IsStripfBad(int telescope, int strip_front)
{
  return fHiRAStripBadLoaded ? fStripfBad[telescope][strip_front] : false;
}

//____________________________________________________
bool E15190Reader::IsStripbBad(int telescope, int strip_back)
{
  return fHiRAStripBadLoaded ? fStripbBad[telescope][strip_back] : false;
}

//____________________________________________________
double E15190Reader::GetThetaPixel(int telescope, int strip_front, int strip_back)
{
  return fHiRAGeometryCalibrated ? fGeometryTab[telescope*NUM_STRIP_F*NUM_STRIP_B+strip_front*NUM_STRIP_B+strip_back].theta : -9999;
}

//____________________________________________________
double E15190Reader::GetPhiPixel(int telescope, int strip_front, int strip_back)
{
  return fHiRAGeometryCalibrated ? fGeometryTab[telescope*NUM_STRIP_F*NUM_STRIP_B+strip_front*NUM_STRIP_B+strip_back].phi : -9999;
}

//____________________________________________________
double E15190Reader::GetThetaPixelDeg(int telescope, int strip_front, int strip_back)
{
  return fHiRAGeometryCalibrated ? fGeometryTab[telescope*NUM_STRIP_F*NUM_STRIP_B+strip_front*NUM_STRIP_B+strip_back].thetadeg : -9999;
}

//____________________________________________________
double E15190Reader::GetPhiPixelDeg(int telescope, int strip_front, int strip_back)
{
  return fHiRAGeometryCalibrated ? fGeometryTab[telescope*NUM_STRIP_F*NUM_STRIP_B+strip_front*NUM_STRIP_B+strip_back].phideg : -9999;
}

//____________________________________________________
double E15190Reader::GetSifIntercept(int telescope, int numstrip)
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetIntercept(telescope,numstrip,0) : -9999;
}

//____________________________________________________
double E15190Reader::GetSibIntercept(int telescope, int numstrip)
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetIntercept(telescope,numstrip,1) : -9999;
}

//____________________________________________________
double E15190Reader::GetSifSlope(int telescope, int numstrip)
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetSlope(telescope,numstrip,0) : -9999;
}

//____________________________________________________
double E15190Reader::GetSibSlope(int telescope, int numstrip)
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetSlope(telescope,numstrip,0) : -9999;
}

//____________________________________________________
double E15190Reader::GetSifHiLowMatched(int chHi, int chLow, int telescope, int numstrip)
{
  if(!fHiRASiHiLowMatched) return -9999;
  if(chLow<fSiHiLowMatching[NUM_TEL*NUM_STRIP_B+telescope*NUM_STRIP_F+numstrip].saturationpoint) {
    return chHi;
  }
  else {
    return chLow*fSiHiLowMatching[NUM_TEL*NUM_STRIP_B+telescope*NUM_STRIP_F+numstrip].slope+fSiHiLowMatching[NUM_TEL*NUM_STRIP_B+telescope*NUM_STRIP_F+numstrip].intercept;
  }
}

//____________________________________________________
double E15190Reader::GetSibHiLowMatched(int chHi, int chLow, int telescope, int numstrip)
{
  if(!fHiRASiHiLowMatched) return -9999;
  if(chLow<fSiHiLowMatching[telescope*NUM_STRIP_B+numstrip].saturationpoint) {
    return chHi;
  }
  else {
    return chLow*fSiHiLowMatching[telescope*NUM_STRIP_B+numstrip].slope+fSiHiLowMatching[telescope*NUM_STRIP_B+numstrip].intercept;
  }
}

//____________________________________________________
double E15190Reader::GetCsIEMeV(int ch, int telescope, int numcsi, int Z, int A)
{
  return fHiRACsICalibrated ? fCsICalibrationModule->GetEnergyValue(gRandom->Uniform(ch-0.5,ch+0.5), telescope, numcsi, Z, A) : -9999;
}

//____________________________________________________
double E15190Reader::GetSifEMeV(int ch, int telescope, int numstripf)
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetEnergy(gRandom->Uniform(ch-0.5,ch+0.5),telescope,numstripf,0) : -9999;
}

//____________________________________________________
double E15190Reader::GetSibEMeV(int ch, int telescope, int numstripb)
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetEnergy(gRandom->Uniform(ch-0.5,ch+0.5),telescope,numstripb,1) : -9999;
}

//____________________________________________________
void E15190Reader::Loop(const char * file_name, Long64_t evt_amount)
{
  // this method loops on the first "evt_amount" data entries
  // and creates a ROOT otput file named "file_name"
  // where the user can write some ROOT output
  TFile * FileOut = new TFile(file_name, "RECREATE");

  Long64_t nentries=fChain->GetEntries();
  if(evt_amount!=0) {
    nentries=evt_amount;
  }
  Long64_t jentry=0;
  std::cout << "found " << nentries << " entries\n";
  for(;fE15190Reader->Next() && jentry<nentries; jentry++)
  {
    if(jentry%100000==0) {
      printf("Percentage = %.2f %%\n", 100*double(jentry)/nentries);
    }

    if (fIsNWA) {
      HTNeutronWallData * NWA = fNWA->Get();
      //Insert NWA code here
    }
    if (fIsNWB) {
      HTNeutronWallData * NWB = fNWB->Get();
      //Insert NWB code here
    }
    if (fIsFA) {
      HTForwardArrayData * ForwardArray = fForwardArray->Get();
      //Insert ForwardArray code here
    }
    if (fIsVW) {
      HTVetoWallData * VetoWall = fVetoWall->Get();
      //Insert VetoWall code here
    }
    if (fIsMB) {
      HTMicroballData * Microball = fMicroball->Get();
      //Insert Microball code here
    }
    if (fIsHiRA) {
      HTHiRAData * HiRATel[NUM_TEL];
      for(int i=0; i<NUM_TEL; i++) {
        HiRATel[i] = fHiRA[i]->Get();
      }
      //Insert HiRA code here
    }

    jentry++;
  }

  // closing output file
  FileOut->Close();
}

//____________________________________________________
void E15190Reader::LoopOnCalibratedData(const char * file_name, Long64_t evt_amount)
{
  // this method loops on the first "evt_amount" data entries
  // and creates a ROOT otput file named "file_name"
  // where the user can write some ROOT output
  TFile * FileOut = new TFile(file_name, "RECREATE");

  Long64_t nentries=fChain->GetEntries();
  if(evt_amount!=0) {
    nentries=evt_amount;
  }
  Long64_t jentry=0;
  std::cout << "found " << nentries << " entries\n";
  for(;fE15190Reader->Next() && jentry<nentries; jentry++)
  {
    if(jentry%100000==0) {
      printf("Percentage = %.2f %%\n", 100*double(jentry)/nentries);
    }

    if (fIsNWA) {
      NeutronWallCalibratedData * NWA = fNWACal->Get();
      //Insert NWA code here
    }
    if (fIsNWB) {
      NeutronWallCalibratedData * NWB = fNWBCal->Get();
      //Insert NWB code here
    }
    if (fIsFA) {
      ForwardArrayCalibratedData * ForwardArray = fForwardArrayCal->Get();
      //Insert ForwardArray code here
    }
    if (fIsVW) {
      VetoWallCalibratedData * VetoWall = fVetoWallCal->Get();
      //Insert VetoWall code here
    }
    if (fIsMB) {
      MicroballCalibratedData * Microball = fMicroballCal->Get();
      //Insert Microball code here
    }
    if (fIsHiRA) {
      for(int i=0; i<NUM_TEL; i++) {}
      //Insert HiRA code here
    }

    jentry++;
  }

  // closing output file
  FileOut->Close();
}
