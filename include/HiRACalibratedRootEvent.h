#ifndef HIRACALIBRATEDROOTEVENT_H
#define HIRACALIBRATEDROOTEVENT_H

#include <TROOT.h>

#include "shared.h"

class HiRACalibratedData
{
public:
  Int_t    fmulti;
  Int_t    *fnumtel;       //[fmulti]
  Int_t    *fnumstripf;    //[fmulti]
  UShort_t *fEnergySifHi;  //[fmulti]
  UShort_t *fEnergySifLo;  //[fmulti]
  UShort_t *fTimeSif;      //[fmulti]
  Int_t    *fnumstripb;    //[fmulti]
  UShort_t *fEnergySibHi;  //[fmulti]
  UShort_t *fEnergySibLo;  //[fmulti]
  UShort_t *fTimeSib;      //[fmulti]
  Int_t    *fnumcsi;       //[fmulti]
  UShort_t *fEnergycsi;    //[fmulti]
  Double_t *fTimecsi;      //[fmulti]

  Double_t *fEnergySifMatched; //[fmulti]
  Double_t *fEnergySibMatched; //[fmulti]
  Double_t *fEnergySifCal;     //[fmulti]
  Double_t *fEnergySibCal;     //[fmulti]
  Double_t *fEnergycsiCal;     //[fmulti]

  Double_t *fTheta;            //[fmulti]
  Double_t *fPhi;              //[fmulti]
  Int_t    *fZ;                //[fmulti]
  Int_t    *fA;                //[fmulti]
  Int_t    *fIdCode;           //[fmulti]

  HiRACalibratedData(int);
  HiRACalibratedData();
  virtual ~HiRACalibratedData();

  ClassDef(HiRACalibratedData,1);
};

#endif
