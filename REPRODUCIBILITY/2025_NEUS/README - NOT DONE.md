This README is meant to provide information about reproducing results used in NEUS 2025. However, it can also be used as a more general installation guide for BehaVerify, though eventually it may be inadequate for this purpose as it will not be updated along with BehaVerify, in order to ensure it remains useful for its primary purpose, reproduction of results for NEUS 2025.

version\_info\_pip.txt contains all python package information for BehaVerify. verion\_info\_pip\_graphs\_only.txt contains all python package information for amking necessary graphs and the like. version\_info\_apt.txt contains all other version information.

In case you are reading this somewhere outside of the repository, our repository is at https://github.com/verivital/behaverify .

# About this File and its Layout

1. Prerequisites and Information -> this section will explain what you need and what assumptions we make.
2. Running Tests using Docker -> this section will explain how to run the tests using Docker.
3. Interpreting and Comparing Results -> this section will explain how to interpret the generated results and what they correspond to in the paper.
4. Potential Errors and Workarounds -> this section will explain how to deal with some of the potential errors encountered.
5. Docker Tests with Details -> this section will explain how to run the tests using Docker.
6. Running Tests Locally (verbose) -> this section will explain how to run tests locally. It also explains why each step of the installation is necessary.
7. Running Tests Locally (concise) -> this section will explain how to run tests locally. It does not provide explanations.

Finally, note that this is a .md file, and as such, we escape various characters. If you are reading this using a text editor, please make sure to keep this in mind.

# Prerequisites and Information

1. docker with the ability to run commands as a regular user (see https://docs.docker.com/engine/install/linux-postinstall/ ). Additionally, we will be using Ubuntu 24.10 inside docker. Some users appear to have issues with running commands like update or upgrade in docker when using Ubuntu; we do not have a workaround for this.
2. nuXmv (see  https://nuxmv.fbk.eu/download.html or https://nuxmv.fbk.eu/theme/download.php?file=nuXmv-2.1.0-linux64.tar.xz ). Our script can automatically download nuXmv for you from an appropriate URL. Should an error arise, you will need to download nuXmv. There should be no installation. Please ensure you download the Linux 64-bit x86 version 2.1.0 (November 29, 2024). The executable will be located in **nuXmv-2.1.0-linux64/nuXmv-2.1.0-Linux/bin/nuXmv**. There should be **NO FILE EXTENSION**. Note that we are **ONLY** interested in the binary; you do not need the other files or the folder structure, so long as you have the binary.
3. If you choose to use Docker, we assume you have access to Python3 and docker-py (see below).
4. If you choose to run locally, we assume you are able to run bash scripts. These have **only been tested on Linux**. If you cannot run the scripts, please run the commands present in the bash scripts manually. Note that this will require arguments to replaced. Specifically, $1 means the first argument provided to the bash script, $2 means the second argument provided to the bash script, etc.

Note, we require docker py for use with python3 if using docker. It can be installed using
```
python3 -m pip install docker
```

## nuXmv

Per the licensing agreement of nuXmv (see https://nuxmv.fbk.eu/downloads/LICENSE.txt ), we may not re-distribute the software in any form for any purpose. As such, the best we can do is download it from a provided URL.

---

# Running Tests With Docker

The tests can be run using docker.

Build Script:
```
python3 build_and_run.py /path/to/Dockerfile/Folder/ /path/to/output NUXMV_URL
```
	
Build Example:
```
python3 ./python_script/build_and_run.py ./ ./MyOutput 'https://nuxmv.fbk.eu/theme/download.php?file=nuXmv-2.1.0-linux64.tar.xz'
```

Alternatively, if you have downloaded nuXmv and placed in the same folder:
```
python3 ./python_script/build_and_run.py ./ ./MyOutput nuXmv --local
```

---

# Interpreting and Comparing Results

Suppose you ran
```
python3 ./python_script/build_and_run.py ./ ./MyOutput 'https://nuxmv.fbk.eu/theme/download.php?file=nuXmv-2.1.0-linux64.tar.xz'
```

Then the results will be in **./MyOutput.tar.xz**. There should be 5 folders within this, named **AcasXu**, **AcasXu\_closed\_loop**, **grid\_world**, and **grid\_world\_big**. The other files may safely be ignored.

- **2025\_NEUS\_BT2BIP**
    - **results**
	    - **INVAR\_full\_opt\_MarsRover\_0.txt** -> counterexample for the specification in Section 4 (Comparisons and Results) Subsection C (BT2BIP) for MarsRover.
	    - **INVAR\_full\_opt\_TrainControl\_0.txt** -> counterexample for the specification in Section 4 (Comparisons and Results) Subsection C (BT2BIP) for Train Controller.
	    - **SILENT\_INVAR\_full\_opt\_MarsRover\_0.txt** -> Timing for specification checking for mars rover
	    - **SILENT\_INVAR\_full\_opt\_TrainControl\_0.txt** -> Timing for specification checking for train control
- **2025\_NEUS\_BT2Fiacre**
	- **processed\_data** -> This will contain three images showing a counterexample. These were referred to in Section 3 (Tool Description) Subsection D (Additional Features) and in Section 4 (Comparisons and Results) Subsection B (BT2Fiacre).
	- **smv/full\_opt\_drone3\_0.txt** -> This has the .smv file for use for the drone3 example. Search this file for MODULE define\_nodes. This will have a list of nodes numbered from 0 to 35, showing there are 36 nodes total.
	- **results**
	    - **INVAR\_full\_opt\_drone3_0.txt** -> Proof the height on our drone3 does not exceed 60.
	    - **SILENT\_INVAR\_full\_opt\_drone3_0.txt** -> Timing result for Table 2, Check Height, B-Drone3.
	    - **INVAR\_full\_opt\_drone3_3.txt** -> Proof the height on our droneNew does not exceed 60.
	    - **SILENT\_INVAR\_full\_opt\_drone3_3.txt** -> Timing result for Table 2, Check Height, B-DroneNew.
		- **translation\_drone3\_0.txt** -> Timing result for Table 2, Prep., B-Drone3.
		- **translation\_drone3\_3.txt** -> Timing result for Table 2, Prep., B-DroneNew.
	    - **INVAR\_full\_opt\_drone3_2.txt** -> Counterexample trace used to generate the images in processed\_data.
- **2025\_NEUS\_MoVe4BT**
    - **smv/full\_opt\_binary\_tree\_1.smv** -> This has the .smv file for use for the binary tree example. Search this file for MODULE define\_nodes. This will have a list of nodes numbered from 0 to 10, showing there are 11 nodes total.
    - **smv/full\_opt\_binary\_tree\_10.smv** -> This has the .smv file for use for the binary tree example. Search this file for MODULE define\_nodes. This will have a list of nodes numbered from 0 to 2054, showing there are 2055 nodes total.
    - **CTL-BehaVerify-Concise**, **LTL-BehaVerify-Concise**, **LTL-MoVe4BT-Concise** -> These files contain manually copied timing results that are then used by graph\_result.py to create the image in **processed\_data**. See below for how to check each of them against your current run.
	- **results**
	    - **SILENT\_LTL\_full\_opt\_binary\_tree\_*.txt** -> Timing result for BehaVerify LTL; goes from 1 to 10.
	    - **SILENT\_CTL\_full\_opt\_binary\_tree\_*.txt** -> Timing result for BehaVerify LTL; goes from 1 to 10.
		- The MoVe4BT results must be run separately, because it doesn't have a CLI. See earlier for how to run MoVe4BT.
- **NetworkExample**
    - **results**
	    - **translation\_network\_0.txt** -> Timing result for Table 3, Trans., 1.0000 Acc.
	    - **translation\_network\_1.txt** -> Timing result for Table 3, Trans., 0.9995 Acc.
	    - **SILENT\_CTL\_full\_opt\_network\_0.txt** -> Timing result for Table 3, CTL, 1.0000 Acc.
	    - **SILENT\_CTL\_full\_opt\_network\_1.txt** -> Timing result for Table 3, CTL, 0.9995 Acc.
	    - **SILENT\_INVAR\_full\_opt\_network\_0.txt** -> Timing result for Table 3, Invar, 1.0000 Acc.
	    - **SILENT\_INVAR\_full\_opt\_network\_1.txt** -> Timing result for Table 3, Invar, 0.9995 Acc.
		- **INVAR\_full\_opt\_network\_0.txt** -> Proof the 1.0000 Acc satisfies the Invar Specification.
		- **INVAR\_full\_opt\_network\_1.txt** -> Proof the 0.9995 Acc satisfies the Invar Specification.
		- **CTL\_full\_opt\_network\_0.txt** -> Proof the 1.0000 Acc satisfies the CTL Specification.
		- **CTL\_full\_opt\_network\_1.txt** -> Proof the 0.9995 Acc does not satisfy the CTL Specification.

---

# Potential Errors and Workarounds

1. If a script fails because permission has been denied, please run the script without sudo (running docker without sudo requires some configuration). If the problem persists, please try a different location, as occasionally docker cannot write to secondary disks.
2. Turn off your VPN, if possible.
3. If everything runs to completion, but there are no images in the copied directory, please confirm if there are files in the results folders. If there are, then most likely you encountered errors similar to the following during execution:
   ```
   OpenBLAS blas_thread_init: pthread_create failed for thread 1 of 16: Operation not permitted
   ```
   Note that this error would not prevent the scripts from completing; it would only prevent the generation of graphs and tables. The internet suggests upgrading your docker version (we tested using docker version 20.10.24, build 297e128).

---
# Step by Step Docker instructions

This section will explain how to utilize either the provided docker image or Dockerfile to recreate the tests using docker in more detail.

### 1. Creation of the Docker Image and Container

```
python3 reinstall.py /path/to/Dockerfile/folder NUXMV_URL
```

Example:
```
python3 ./python_script/reinstall.py ./ 'https://nuxmv.fbk.eu/theme/download.php?file=nuXmv-2.1.0-linux64.tar.xz'
```

Alternatively, if you have downloaded nuXmv and placed in the same folder:
```
python3 ./python_script/reinstall.py ./ nuXmv --local
```

This will create a docker image named behaverify\_2025\_fmcad\_img with the tag latest. It will then also create a container named behaverify\_2025\_fmcad from that image. It will also either download nuXmv from the URL or copy it in.

### 2. Reproducing Results

```
python3 generate.py /path/to/output
```

Example:
```
python3 ./python_script/generate.py ./MyOutput
```

---

# Verbose Installation for Running tests locally without docker.

The instructions are for Linux (and more specifically Ubuntu). We have not tested this on any other systems. Some of the scripts are likely to break on other systems. For instance, the scripts assume that nuXmv will be named nuXmv, and not nuXmv.exe. However, our code itself should still work (though we have not tested this).

This section is intentionally lengthy. If you are not interested in the details and just want the commands, please scroll down further


1. nuXmv<br />Please download nuXmv (see  https://nuxmv.fbk.eu/ ). You only need to download nuXmv. There should be no installation. Download the relevant version for your system. It should be version 2.0.0. The download will include many files. You only need the executable (no file extension). See above for more information.
2. Updating<br /> We suggest running the following commands.

		sudo apt update
		sudo apt upgrade
3. Python3<br />Python3 is used to run BehaVerify. As such, it is necessary. If you already have python3 installed, skip the following step. If not, run
	
		sudo apt install python3
4. pip<br />pip is used to install other python packages. If you already have pip installed (for python3), skip the following step. If not, run

		sudo apt install pip
5. PyTrees<br />PyTrees is used in the generated python code. It is necessary for the differential testing experiments, or for using generated python code in general.

		python3 -m pip install py_trees
6. pandas<br />pandas is used for data gathering and displaying. It is necessary for graph and table creation.

		python3 -m pip install pandas
7. jinja2<br />jinja2 is used by something for graph/table creations.

		python3 -m pip install jinja2
8. textX<br />textX is used by BehaVerify for parsing. It is necessary for BehaVerify to run in any capacity

		python3 -m pip install textX
9. matplotlib<br />matplotlib is used for generating graphs and plots.

		python3 -m pip install matplotlib
10. graphviz<br />graphviz is used to generate graphs and plots.

		sudo apt install graphviz
11. git<br />git is used to download our repository. If you would prefer to manually download our repository, you can skip this step.

		sudo apt install git
12. (OPTIONAL) Haskell prerequisites<br />These are prerequisites required by Haskell. **THESE STEPS ARE UNNECESSARY FOR FMAS RESULTS**

		sudo apt install build-essential curl libffi-dev libffi8ubuntu1 libgmp-dev libgmp10 libncurses-dev libncurses5 libtinfo5
13. (OPTIONAL) Additional Haskell prerequisite<br />

		sudo apt install libgmp3-dev
14. (OPTIONAL) GHCUP<br />Please follow the instructions at https://www.haskell.org/ghcup/ to install GHCUP, Haskell, and cabal. These are used to run generated Haskell code. Please preappend (or append) your path when asked.
15. (OPTIONAL) GHCUP upgrade<br />This will upgrade GHCUP.

		ghcup upgrade
16. (OPTIONAL) Cabal<br />This will install and set the specific version of cabal we used. Most likely, everything will work with a different version.

		ghcup install cabal 3.6.2.0
		ghcup set cabal 3.6.2.0
17. (OPTIONAL) GHC<br />This will install and set the specific version of ghc we used. Most likely, everything will work with a different version.

		ghcup install ghc 9.2.8
		ghcup set ghc 9.2.8
18. BehaVerify<br />Download our repository. If you did not install git, please download manually. If you installed git

		git clone https://github.com/verivital/behaverify
19. Enable scripts<br />This will allow all the necessary scripts to run. Please navigate to the top level of our repository and run the following

		sudo chmod -R +x ./REPRODUCIBILITY/2025_NEUS/*.sh
20. Move nuXmv<br />You downloaded nuXmv in step 1. Please place it in behaverify/REPRODUCIBILITY/2025\_NEUS/
21. Enable nuXmv<br />Please navigate to the top level of our repository and run the following

		sudo chmod +x ./REPRODUCIBILITY/2025_NEUS/nuXmv


You are now ready to run the scripts locally. Scroll past the concise installation instructions to see the scripts explanation.

---

# Concise Installation for Running the tests locally without docker.

The instructions are for Linux (and more specifically Ubuntu). We have not tested this on any other systems. Some of the scripts are likely to break on other systems. For instance, the scripts assume that nuXmv will be named nuXmv, and not nuXmv.exe. However, our code itself should still work (though we have not tested this).


Please download nuXmv (see  https://nuxmv.fbk.eu/ ). You only need to download nuXmv. There should be no installation. Download the relevant version for your system. It should be version 2.0.0.
```
sudo apt update
sudo apt upgrade
sudo apt install python3
sudo apt install pip
```
	
(OPTIONAL) PyTrees is required to use the python code generated by BehaVerify. However, this is not used in the FMAS tests
```
python3 -m pip install py_trees
```
	
Below we have more mandatory requirements
```
python3 -m pip install pandas
python3 -m pip install jinja2
python3 -m pip install textX
python3 -m pip install matplotlib
sudo apt install graphviz
sudo apt install git
```
	
(OPTIONAL) These are prerequisites for Haskell, which is not used in the FMAS tests.
```
sudo apt install build-essential curl libffi-dev libffi8ubuntu1 libgmp-dev libgmp10 libncurses-dev libncurses5 libtinfo5
sudo apt install libgmp3-dev
```

(OPTIONAL) Please follow the instructions at https://www.haskell.org/ghcup/ to install ghcup, Haskell, and cabal. These are used to run generated Haskell code. Please preappend (or append) your path when asked.
```
ghcup upgrade
ghcup install cabal 3.6.2.0
ghcup set cabal 3.6.2.0
ghcup install ghc 9.2.8
ghcup set ghc 9.2.8
```
	
You may clone or download the repository
```
git clone https://github.com/verivital/behaverify
```

Please navigate to the top level of our repository and run the following
```
sudo chmod -R +x ./REPRODUCIBILITY/2025_NEUS/*.sh
```

You downloaded nuXmv earlier. Please place it in behaverify/REPRODUCIBILITY/2025\_NEUS/

Please navigate to the top level of our repository and run the following
```
sudo chmod +x ./REPRODUCIBILITY/2025_NEUS/nuXmv
```

You are now ready to run the scripts locally. 


---

# Running Tests Locally without docker (requires installation, see above).

Note that each script will erase all the relevant results before running, to ensure that the results which exist after the script runs are accurate to that script. Thus if you wish to save the results, please move them before running another script.

```
./BehaVerify_2025_NEUS ./
```

