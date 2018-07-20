# E15190-Unified-Analysis-Framework
A global unified analysis framework to analyze HiRAEVT raw data structures, produce calibrated data with new data structures and analyze calibrated data.

The framework is designed for E15190 data structures.

Contributors: Daniele Dell'Aquila(1), Kuan Zhu

(1) dellaqui@nscl.msu.edu

Table of contents
=================
<!--ts-->
* [Getting the code](#getting-the-code)
  * [Using git](#using-git)
  * [Downloading from Git Hub](#downloading-from-git-hub)
* [Setup and Configuration](#setup-and-configuration)
  * [Requirements](#requirements)
  * [Compile the Code](#compile-the-code)
  * [Configure the Program](#configure-the-program)
  * [Limitations](#limitations)
* [The E15190Reader Framework](#the-e15190reader-framework)
  * [Framework Description](#framework-description)
  * [Run the Code](#run-the-code)
  * [Run the Code on NSCL ember](#run-the-code-on-nscl-ember)
  * [Calibrated Output Data](#calibrated-output-data)
  * [Customized Methods](#customized-methods)
  * [How to add new features](#how-to-add-new-features)
  * [Extension to future experiments](#extension-to-future-experiments)
  * [Notes for Developers](#notes-for-developers)
<!--te-->

## Getting the code
### Using git
The latest version of the code can be obtained by using the git command. This is possible after installing git on a linux machine (see https://git-scm.com/download/linux for further documentation on how to install git). Use the following command to download the framework:
````
$ git clone https://github.com/nscl-hira/E15190-Unified-Analysis-Framework.git
````
### Downloading from Git Hub
The code can be downloaded also frm the Git Hub web page at the link: https://github.com/dellaquilamaster/HiRAEVT, by
clicking on the "Clone or Download" button on the right side of the page and then "Download ZIP". It is possible to donwload also a previous release of the code. For a complete list of all the releases please visit: https://github.com/nscl-hira/E15190-Unified-Analysis-Framework.git.
## Setup and Configuration
### Requirements
The code is compiled using the g++ compiler.
In order to compile and run the code ROOT 6 is required (the program has been tested with version 6.04.02). Please note that, since the program uses advanced ROOT 6 features, it is not possible to run or compile it by using an installation of ROOT 5. Ensure ROOT 6 environment variables are correctly exported. Usually one can use the command "source /mnt/misc/sw/x86_64/Debian/8/root/gnu/x.xx.xx/bin/thisroot.sh" or type it in the ".bash" file.
### Compile the code
To compile the code by using gcc compiler use the command:
````
$ make -jN
$ make install
````
where, in multi-cpu machines, N can be used to specify the number of core to use in the compilation and significantly speed up the procedure.
To proceed with a clean compilation run before the command:
````
$ make clean
````
or
````
$ make distclean
````
the latter will clear also shared libraries generated by the "install" option and stored in the directory "lib/".
### Configure the Program
To be written.
### Limitations
To be written.
## The E15190Reader Framework
### Framework Description
The framework allows to handle data of the E15190 experiment, with HiRAEVTMapper data structures, by including all the existing calibrations and detector analysis tools. The framework is fully versatile since it allows to include any possible combination of existing detectors in the analysis, and any possible combination of required calibrations. One of the most important features of the framework is the production of new calibrated data structures
