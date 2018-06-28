#ifndef E15190READER_H
#define E15190READER_H

#include <string.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <TChain.h>
#include <TMath.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <TCutG.h>
#include <TMultiGraph.h>
#include <TLatex.h>
#include <TCanvas.h>

#include "HTNeutronWallRootEvent.h"
#include "HTForwardArrayRootEvent.h"
#include "HTVetoWallRootEvent.h"
#include "HTMicroballRootEvent.h"
#include "HTHiRARootEvent.h"

#include "NWPositionCalibration.h"
#include "NWCosmicRayManager.h"
#include "NWCalibratedRootEvent.h"
#include "NWTimeCalibration.h"
#include "NWGeometry.h"
#include "FATimeCalibration.h"
#include "NWPulseHeightCalibration.h"

#include "MBCalibratedRootEvent.h"
#include "MBDetectorStatus.h"
#include "MBGeometry.h"
#include "MBHitCondition.h"
#include "MBImpactParameter.h"

#include <HiRAGeometry.h>
#include <HiRASiCalibration.h>
#include <HiRACsICalibration.h>
#include <HiRASiHiLowMatching.h>



#include "shared.h"

/**************************************
E15190Reader class
created by Daniele Dell'Aquila - v1.0 06/22/2018
(dellaqui@nscl.msu.edu)
This class is the core of a unified framework to analyze data of E15190 NSCL Experiment
This framework provides basic tools to loop on raw HiRAEVT data and Calibrated data
by selectively enabling the detector(s) of interest
This class provides methods to get calibrated quantities from raw data structures
A general method to calibrate the whole experiment producing a new tree is provided within the framework (BuildCalibratedTree)
To get calibrated data structure for the current event use the method BuildCalibratedEvent()

*/

class E15190Reader
{
public :
  E15190Reader(TChain *, const char * opt="HiRA NWA NWB VW FA uBall", bool IsDataCalibrated=0);
  ~E15190Reader();

  int LoadNWPositionCalibration(const char * file_name, const char * WallToCalibrate);
  int LoadNWTimeCalibration(const char * file_name, const char * WallToCalibrate);
  int LoadNWCosmicRayPosition(const char *, const char * WallToCalibrate);
  int LoadNWGeometryFiducialPoints(const char *, const char * WallToCalibrate);
  int LoadNWPulseHeightMatching(const char *, const char * WallToCalibrate);
  int LoadNWPulseHeightCalibration(const char *, const char * WallToCalibrate);
  int LoadFATimeCalibration(const char * file_name);
  int LoadFATimePulseHeightCorrection(const char * file_name);
  int LoadMBGeometry(const char * file_name);
  int LoadMBDetectorStatus(const char * file_name);
  int LoadMBFastSlowHitCondition(const char * file_name);
  int LoadMBCentrality(const char * file_name);
  int LoadHiRAGeometry(const char *);
  int LoadHiRACsICalibration(const char *, int Z=1, int A=1);
  int LoadHiRASiCalibration(const char *);
  int LoadHiRAStripBad(const char *);
  int LoadHiRASiHiLowMatching(const char *);
  int LoadHiRACsIPulserInfo(const char *);

  // NW/VW/FA methods
  double GetNWAXcm(int num_bar, double tleft, double tright) const;
  double GetNWBXcm(int num_bar, double tleft, double tright) const;
  double GetNWACosmicCenter(int num_bar) const;
  double GetNWACosmicStartingPoint(int num_bar) const;
  double GetNWBCosmicCenter(int num_bar) const;
  double GetNWBCosmicStartingPoint(int num_bar) const;
  double GetNWATimeMean(int num_bar, double tleft, double tright) const;
  double GetNWBTimeMean(int num_bar, double tleft, double tright) const;
  double GetNWATheta(int num_bar, double Xcm) const;
  double GetNWAPhi(int num_bar, double Xcm) const;
  double GetNWAThetaRan(int num_bar, double Xcm) const;
  double GetNWAPhiRan(int num_bar, double Xcm) const;
  double GetNWADistance(int num_bar, double Xcm) const;
  double GetNWADistanceRan(int num_bar, double Xcm) const;
  double GetNWBTheta(int num_bar, double Xcm) const;
  double GetNWBPhi(int num_bar, double Xcm) const;
  double GetNWBThetaRan(int num_bar, double Xcm) const;
  double GetNWBPhiRan(int num_bar, double Xcm) const;
  double GetNWBDistance(int num_bar, double Xcm) const;
  double GetNWBDistanceRan(int num_bar, double Xcm) const;
  double GetNWALeftCorrected(double ch, int num_bar, double Xcm) const;
  double GetNWARightCorrected(double ch, int num_bar, double Xcm) const;
  double GetFATimeOffset(int num_det) const;
  double GetFATimePulseHeightCorrection(int num_det, double pulse_height) const;
  // Microball methods
  double GetTheta(int num_ring, int num_det) const;
  double GetPhi(int num_ring, int num_det) const;
  double GetThetaRandom(int num_ring, int num_det) const;
  double GetPhiRandom(int num_ring, int num_det) const;
  double GetImpactParameter(int multiplicity) const;
  double Getbhat(int multiplicity) const;
  bool IsMBDetectorBad(int num_ring, int num_det) const;
  bool IsMBHit (int num_ring, int num_det, double fast, double tail, double time) const;
  //HiRA methods
  bool IsStripfBad(int telescope, int strip_front);
  bool IsStripbBad(int telescope, int strip_back);
  double GetThetaPixel(int telescope, int strip_front, int strip_back);
  double GetPhiPixel(int telescope, int strip_front, int strip_back);
  double GetThetaPixelDeg(int telescope, int strip_front, int strip_back);
  double GetPhiPixelDeg(int telescope, int strip_front, int strip_back);
  double GetSifIntercept(int telescope, int numstrip);
  double GetSibIntercept(int telescope, int numstrip);
  double GetSifSlope(int telescope, int numstrip);
  double GetSibSlope(int telescope, int numstrip);
  double GetCsIIntercept(int telescope, int numcsi);
  double GetCsISlope(int telescope, int numcsi);
  double GetSifHiLowMatched(int chHi, int chLow, int telescope, int numstrip);
  double GetSibHiLowMatched(int chHi, int chLow, int telescope, int numstrip);
  double GetCsIEMeV(int ch, int telescope, int numcsi, int Z=1, int A=1);
  double GetSifEMeV(int ch, int telescope, int numstripf);
  double GetSibEMeV(int ch, int telescope, int numstripb);

  // Examples
  void   Loop(const char *, Long64_t evt_amount=0);
  void   LoopOnCalibratedData(const char *, Long64_t evt_amount=0);

  // Output data methods
  void   BuildCosmicRayData(const char *, Long64_t evt_amount=0);
  void   BuildCalibratedTree(const char *, Long64_t evt_amount=0);
  void   BuildCalibratedEvent();

  //Customized methods
  // input here customized methods

private :
  //The TTreeReader
  TTreeReader * fE15190Reader;
  //TTreeReaderValue for non-calibrated classes
  TTreeReaderValue<HTNeutronWallData> *fNWA;
  TTreeReaderValue<HTNeutronWallData> *fNWB;
  TTreeReaderValue<HTVetoWallData> *fVetoWall;
  TTreeReaderValue<HTForwardArrayData> *fForwardArray;
  TTreeReaderValue<HTMicroballData> *fMicroball;
  TTreeReaderValue<HTHiRAData> **fHiRA;
  //TTreeReaderValue for calibrated classes
  TTreeReaderValue<NeutronWallCalibratedData> *fNWACal;
  TTreeReaderValue<NeutronWallCalibratedData> *fNWBCal;
  TTreeReaderValue<VetoWallCalibratedData> *fVetoWallCal;
  TTreeReaderValue<ForwardArrayCalibratedData> *fForwardArrayCal;
  TTreeReaderValue<MicroballCalibratedData> *fMicroballCal;

  //Calibrated objects for event building
  NeutronWallCalibratedData fNWACalibratedData;
  NeutronWallCalibratedData fNWBCalibratedData;
  VetoWallCalibratedData fVetoWallCalibratedData;
  ForwardArrayCalibratedData fForwardArrayCalibratedData;
  MicroballCalibratedData fMicroballCalibratedData;

  TChain      * fChain;

  double fDegToRad;
  double fRadToDeg;
  double fSpeedOfLight;    //cm/ns
  double fNWBarLength;     //cm
  double fNWBarHigh;       //cm
  double fNWBarThickness;  //cm

  bool fIsNWA;
  bool fIsNWB;
  bool fIsFA;
  bool fIsVW;
  bool fIsMB;
  bool fIsHiRA;
  bool fIsDataCalibrated;
  bool fNWAPositionCalibrated;
  bool fNWBPositionCalibrated;
  bool fNWTimeCalibrated;
  bool fNWPulseHeightCalibrated;
  bool fNWACosmicRayPositionLoaded;
  bool fNWBCosmicRayPositionLoaded;
  bool fNWATimeCalibrated;
  bool fNWBTimeCalibrated;
  bool fNWAGeometryCalibrated;
  bool fNWBGeometryCalibrated;
  bool fNWAPulseHeightMatched;
  bool fNWBPulseHeightMatched;
  bool fNWAPulseHeightCalibrated;
  bool fNWBPulseHeightCalibrated;
  bool fFATimeCalibrated;
  bool fMBGeometryLoaded;
  bool fMBStatusLoaded;
  bool fMBHitConditionLoaded;
  bool fMBCentralityLoaded;
  bool fHiRACsICalibrated;
  bool fHiRASiCalibrated;
  bool fHiRAGeometryCalibrated;
  bool fHiRAStripBadLoaded;
  bool fHiRASiHiLowMatched;

  NWPositionCalibration * fNWBPositionCalibration;
  NWPositionCalibration * fNWAPositionCalibration;
  NWCosmicRayManager    * fNWACosmicRayInfo;
  NWCosmicRayManager    * fNWBCosmicRayInfo;
  NWTimeCalibration     * fNWATimeCalibration;
  NWTimeCalibration     * fNWBTimeCalibration;
  NWGeometry            * fNWAGeometry;
  NWGeometry            * fNWBGeometry;
  NWPulseHeightCalibration * fNWAPulseHeightCalibrationTools;
  NWPulseHeightCalibration * fNWBPulseHeightCalibrationTools;
  FATimeCalibration     * fFATimeCalibration;

  MBDetectorStatus      * fMicroballStatus;
  MBGeometry            * fMicroballGeometry;
  MBHitCondition        * fMicroballHitCondition;
  MBImpactParameter     * fMicroballCentrality;

  HiRAGeometry *fGeometryTab;
  HiRASiCalibration *fSiCalibrationTools;
  HiRASiHiLowMatching *fSiHiLowMatching;
  HiRACsICalibrationManager *fCsICalibrationModule;
  double * fTelSiThickness;
  double   fCsIMylarThickness;
  double   fCsIlenght;
  bool   **fStripfBad;
  bool   **fStripbBad;

};

#endif
