#include "include/HiRACalibratedRootEvent.h"

//________________________________________________
HiRACalibratedData::HiRACalibratedData(int num_bars) :
fmulti(0)
{
  fnumtel=           new  Int_t    [fmulti];
  fnumstripf=        new  Int_t    [fmulti];
  fEnergySifHi=      new  UShort_t [fmulti];
  fEnergySifLo=      new  UShort_t [fmulti];
  fTimeSif=          new  UShort_t [fmulti];
  fnumstripb=        new  Int_t    [fmulti];
  fEnergySibHi=      new  UShort_t [fmulti];
  fEnergySibLo=      new  UShort_t [fmulti];
  fTimeSib=          new  UShort_t [fmulti];
  fnumcsi=           new  Int_t    [fmulti];
  fEnergycsi=        new  UShort_t [fmulti];
  fTimecsi=          new  Double_t [fmulti];

  fEnergySifMatched= new  Double_t [fmulti];
  fEnergySibMatched= new  Double_t [fmulti];
  fEnergySifCal=     new  Double_t [fmulti];
  fEnergySibCal=     new  Double_t [fmulti];
  fEnergycsiCal=     new  Double_t [fmulti];

  fTheta=	           new  Double_t [fmulti];
  fPhi= 	           new  Double_t [fmulti];
  fZ=		             new  Int_t    [fmulti];
  fA=		             new  Int_t    [fmulti];
  fIdCode=	         new  Int_t    [fmulti];
}

//________________________________________________
HiRACalibratedData::HiRACalibratedData() :
fmulti(0)
{
  fnumtel=           new  Int_t    [12*NUM_MAX_PARTICLES_PER_TEL];
  fnumstripf=        new  Int_t    [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergySifHi=      new  UShort_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergySifLo=      new  UShort_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fTimeSif=          new  UShort_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fnumstripb=        new  Int_t    [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergySibHi=      new  UShort_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergySibLo=      new  UShort_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fTimeSib=          new  UShort_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fnumcsi=           new  Int_t    [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergycsi=        new  UShort_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fTimecsi=          new  Double_t [12*NUM_MAX_PARTICLES_PER_TEL];

  fEnergySifMatched= new  Double_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergySibMatched= new  Double_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergySifCal=     new  Double_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergySibCal=     new  Double_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fEnergycsiCal=     new  Double_t [12*NUM_MAX_PARTICLES_PER_TEL];

  fTheta=	           new  Double_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fPhi= 	           new  Double_t [12*NUM_MAX_PARTICLES_PER_TEL];
  fZ=		             new  Int_t    [12*NUM_MAX_PARTICLES_PER_TEL];
  fA=		             new  Int_t    [12*NUM_MAX_PARTICLES_PER_TEL];
  fIdCode=	         new  Int_t    [12*NUM_MAX_PARTICLES_PER_TEL];
}

//________________________________________________
HiRACalibratedData::~HiRACalibratedData()
{
  delete []  fnumtel;
  delete []  fnumstripf;
  delete []  fEnergySifHi;
  delete []  fEnergySifLo;
  delete []  fTimeSif ;
  delete []  fnumstripb;
  delete []  fEnergySibHi;
  delete []  fEnergySibLo;
  delete []  fTimeSib;
  delete []  fnumcsi;
  delete []  fEnergycsi;
  delete []  fTimecsi;

  delete []  fEnergySifMatched;
  delete []  fEnergySibMatched;
  delete []  fEnergySifCal;
  delete []  fEnergySibCal;
  delete []  fEnergycsiCal;

  delete []  fTheta;
  delete []  fPhi;
  delete []  fZ;
  delete []  fA;
  delete []  fIdCode;
}
