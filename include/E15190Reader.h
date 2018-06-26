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

#include "NWPositionCalibration.h"
#include "NWCosmicRayManager.h"
#include "NWCalibratedRootEvent.h"
#include "NWTimeCalibration.h"
#include "NWGeometry.h"
#include "FATimeCalibration.h"

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
  E15190Reader(const char * opt="HiRA NWA NWB VW FA uBall", bool IsDataCalibrated=0);
  ~E15190Reader();



private :

};

#endif
