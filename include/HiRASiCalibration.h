#ifndef HIRASICALIBRATION_h
#define HIRASICALIBRATION_h

#include <fstream>
#include <sstream>
#include <string>

class HiRASiCalibration
{
public :
  HiRASiCalibration(int TotNumTel, int TotNumStripf, int TotNumStripb);
  ~HiRASiCalibration();

  int LoadCalibration(const char *);

  double GetEnergy(double ch, int num_tel, int num_strip, bool FrontBack) const;
  double GetSlope(int num_tel, int num_strip, bool FrontBack) const;
  double GetIntercept(int num_tel, int num_strip, bool FrontBack) const;

private :
  int fNumTel;
  int fNumStripf;
  int fNumStripb;

  double *fIntercept;
  double *fSlope;

  bool fCalibrationLoaded;

};

#endif
