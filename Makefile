CFLAGS    :=`root-config --cflags --libs`
SYSLIB    := -lz -l TreePlayer -lMathMore
ROOTCLINGORCINT   := rootcling

SrcSuf    := cpp
ObjSuf    := o
DepSuf    := h
PcmSuf    := _rdict.pcm
ObjDir    := obj/

OBJS := E15190Reader.$(ObjSuf) E15190ReaderData.$(ObjSuf) E15190ReaderCustomized.$(ObjSuf) shared.$(ObjSuf)
OBJS += HTNeutronWallRootEvent.$(ObjSuf) HTForwardArrayRootEvent.$(ObjSuf) HTVetoWallRootEvent.$(ObjSuf)
OBJS += NWPositionCalibration.$(ObjSuf) NWCosmicRayManager.$(ObjSuf) NWTimeCalibration.$(ObjSuf) NWPulseHeightCalibration.$(ObjSuf) NWGeometry.$(ObjSuf)
OBJS += FATimeCalibration.$(ObjSuf)
OBJS += NWCalibratedRootEvent.$(ObjSuf)
OBJS += HTMicroballRootEvent.$(ObjSuf) MBCalibratedRootEvent.$(ObjSuf)
OBJS += MBDetectorStatus.$(ObjSuf) MBGeometry.$(ObjSuf) MBHitCondition.$(ObjSuf) MBImpactParameter.$(ObjSuf)
OBJS += EnergyLossModule.$(ObjSuf) nuclear_masses.$(ObjSuf) HiRACsICalibration.$(ObjSuf) HiRASiCalibration.$(ObjSuf) HTHiRARootEvent.$(ObjSuf)
OBJS := $(addprefix $(ObjDir), $(OBJS))

DEPS := $(_OBJS:.$(ObjSuf)=.$(DepSuf))

ROOTHTNW_HDRS  := HTNeutronWallRootEvent.h HTNeutronWallLinkDef.h
ROOTHTNW_DICT  := HTNeutronWallDict.$(SrcSuf)
ROOTHTNW_DICTH := $(ROOTHTNW_DICT:.$(SrcSuf)=.h)
ROOTHTNW_DICTO := $(addprefix $(ObjDir), $(ROOTHTNW_DICT:.$(SrcSuf)=.$(ObjSuf)))
ROOTHTNW_PCM   := $(addprefix $(ObjDir), HTNeutronWallDict$(PcmSuf))

ROOTHTVW_HDRS  := HTVetoWallRootEvent.h HTVetoWallLinkDef.h
ROOTHTVW_DICT  := HTVetoWallDict.$(SrcSuf)
ROOTHTVW_DICTH := $(ROOTHTVW_DICT:.$(SrcSuf)=.h)
ROOTHTVW_DICTO := $(addprefix $(ObjDir), $(ROOTHTVW_DICT:.$(SrcSuf)=.$(ObjSuf)))
ROOTHTVW_PCM   := $(addprefix $(ObjDir), HTVetoWallDict$(PcmSuf))

ROOTHTFA_HDRS  := HTForwardArrayRootEvent.h HTForwardArrayLinkDef.h
ROOTHTFA_DICT  := HTForwardArrayDict.$(SrcSuf)
ROOTHTFA_DICTH := $(ROOTHTFA_DICT:.$(SrcSuf)=.h)
ROOTHTFA_DICTO := $(addprefix $(ObjDir), $(ROOTHTFA_DICT:.$(SrcSuf)=.$(ObjSuf)))
ROOTHTFA_PCM   := $(addprefix $(ObjDir), HTForwardArrayDict$(PcmSuf))

ROOTNWCALIBRATED_HDRS  := NWCalibratedRootEvent.h NWCalibratedLinkDef.h
ROOTNWCALIBRATED_DICT  := NWCalibratedDict.$(SrcSuf)
ROOTNWCALIBRATED_DICTH := $(ROOTNWCALIBRATED_DICT:.$(SrcSuf)=.h)
ROOTNWCALIBRATED_DICTO := $(addprefix $(ObjDir), $(ROOTNWCALIBRATED_DICT:.$(SrcSuf)=.$(ObjSuf)))
ROOTNWCALIBRATED_PCM   := $(addprefix $(ObjDir), NWCalibratedDict$(PcmSuf))

ROOTHTMB_HDRS  := HTMicroballRootEvent.h HTMicroballLinkDef.h
ROOTHTMB_DICT  := HTMicroballDict.$(SrcSuf)
ROOTHTMB_DICTH := $(ROOTHTMB_DICT:.$(SrcSuf)=.h)
ROOTHTMB_DICTO := $(addprefix $(ObjDir), $(ROOTHTMB_DICT:.$(SrcSuf)=.$(ObjSuf)))
ROOTHTMB_PCM   := $(addprefix $(ObjDir), HTMicroballDict$(PcmSuf))

ROOTMBCALIBRATED_HDRS  := MBCalibratedRootEvent.h MBCalibratedLinkDef.h
ROOTMBCALIBRATED_DICT  := MBCalibratedDict.$(SrcSuf)
ROOTMBCALIBRATED_DICTH := $(ROOTMBCALIBRATED_DICT:.$(SrcSuf)=.h)
ROOTMBCALIBRATED_DICTO := $(addprefix $(ObjDir), $(ROOTMBCALIBRATED_DICT:.$(SrcSuf)=.$(ObjSuf)))
ROOTMBCALIBRATED_PCM   := $(addprefix $(ObjDir), MBCalibratedDict$(PcmSuf))

ROOTHTHIRA_HDRS  := HTHiRARootEvent.h HTHiRALinkDef.h
ROOTHTHIRA_DICT  := HTHiRADict.$(SrcSuf)
ROOTHTHIRA_DICTH := $(ROOTHTHIRA_DICT:.$(SrcSuf)=.h)
ROOTHTHIRA_DICTO := $(addprefix $(ObjDir), $(ROOTHTHIRA_DICT:.$(SrcSuf)=.$(ObjSuf)))
ROOTHTHIRA_PCM   := $(addprefix $(ObjDir), HTHiRADict$(PcmSuf))

INCLUDES  := -I./include
INCLUDES  += -I./Nuclear_Masses

PROG      := $(wildcard exec_*.$(SrcSuf))
PROG      := $(patsubst %.$(SrcSuf), %, $(PROG))

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3

all: $(PROG)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(PcmSuf)

$(PROG): $(OBJS) $(ROOTHTNW_DICTO) $(ROOTHTVW_DICTO) $(ROOTHTFA_DICTO) $(ROOTNWCALIBRATED_DICTO) $(ROOTHTMB_DICTO) $(ROOTMBCALIBRATED_DICTO) $(ROOTHTHIRA_DICTO)
	$(CXX) $(CXXFLAGS) -o ${@} ${@}.cpp $^ $(SYSLIB) $(CFLAGS) $(RLIBS)

$(ObjDir)%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(CFLAGS)

$(ROOTHTNW_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTHTNW_HDRS)

$(ROOTHTVW_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTHTVW_HDRS)

$(ROOTHTFA_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTHTFA_HDRS)

$(ROOTNWCALIBRATED_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTNWCALIBRATED_HDRS)

$(ROOTHTMB_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTHTMB_HDRS)

$(ROOTMBCALIBRATED_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTMBCALIBRATED_HDRS)

$(ROOTHTHIRA_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTHTHIRA_HDRS)

.PHONY: clean
clean:
	@$(RM) -f $(OBJS) $(ROOTHTNW_DICT) $(ROOTHTNW_PCM) $(ROOTHTNW_DICTO) $(ROOTHTNW_DICTH) $(ROOTHTVW_DICT) $(ROOTHTVW_PCM) $(ROOTHTVW_DICTO) $(ROOTHTVW_DICTH)\
	 $(ROOTHTFA_DICT) $(ROOTHTFA_PCM) $(ROOTHTFA_DICTO) $(ROOTHTFA_DICTH) $(ROOTHTMB_DICT) $(ROOTHTMB_PCM) $(ROOTHTMB_DICTO) $(ROOTHTMB_DICTH)\
	  $(ROOTNWCALIBRATED_DICT) $(ROOTNWCALIBRATED_PCM) $(ROOTNWCALIBRATED_DICTO) $(ROOTNWCALIBRATED_DICTH) $(ROOTMBCALIBRATED_DICT)\
		 $(ROOTMBCALIBRATED_PCM) $(ROOTMBCALIBRATED_DICTO) $(ROOTMBCALIBRATED_DICTH) $(ROOTHTHIRA_DICT) $(ROOTHTHIRA_PCM) $(ROOTHTHIRA_DICTO) $(ROOTHTHIRA_DICTH)
	@echo "$(RM) -f $(OBJS) $(ROOTHTNW_DICT) $(ROOTHTNW_PCM) $(ROOTHTNW_DICTO) $(ROOTHTNW_DICTH) $(ROOTHTVW_DICT) $(ROOTHTVW_PCM) $(ROOTHTVW_DICTO) $(ROOTHTVW_DICTH)\
	 $(ROOTHTFA_DICT) $(ROOTHTFA_PCM) $(ROOTHTFA_DICTO) $(ROOTHTFA_DICTH) $(ROOTHTMB_DICT) $(ROOTHTMB_PCM) $(ROOTHTMB_DICTO) $(ROOTHTMB_DICTH)\
	  $(ROOTNWCALIBRATED_DICT) $(ROOTNWCALIBRATED_PCM) $(ROOTNWCALIBRATED_DICTO) $(ROOTNWCALIBRATED_DICTH) $(ROOTMBCALIBRATED_DICT)\
		 $(ROOTMBCALIBRATED_PCM) $(ROOTMBCALIBRATED_DICTO) $(ROOTMBCALIBRATED_DICTH) $(ROOTHTHIRA_DICT) $(ROOTHTHIRA_PCM) $(ROOTHTHIRA_DICTO) $(ROOTHTHIRA_DICTH)"
