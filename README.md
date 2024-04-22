# FPGA Based Linear Regression Acceleration for ECE 465 Srping 2024
This is the github repository for Adam Ross and Abhiishek Muralidhar's final project for ECE 465 during the spring semester of 2024 at the University of Illinois in Chicago.
Our project goal was to expose ourselves to FPGA development tools and techniques by replicating an accelerator found in existing literature.
In the end we decided to replicate a linear regression accelerator found in the paper [FPGA hardware linear regression implementation using fixed-point arithmetic](https://ieeexplore.ieee.org/document/8862300) by Willian de Assis Pedrobon Ferreira, Ian Grout, and Alexandre César Rodrigues da Silva.

This repository includes C++ HLS code, as well corresponding .bit, .hwh, and .tcl files implemented in Vivado for the [PYNQ-Z2](https://www.amd.com/en/corporate/university-program/aup-boards/pynq-z2.html) board.
It also includes jupyter notebooks used for interfacing with and benchmarking the resulting accelerator, and tar distributions of the python [fixedpoint package](https://pypi.org/project/fixedpoint/) used for data conversion in and out of the accelerator.

## Results
We were able to successfully create a module that accelerated linear regression on an FPGA. Due to hardware access differences between ourselves and the original authors, our design had to be altered from the original paper's.
Ours is done in multiple cycles compared to their singular cycle, and thus uses more memory elements than the original paper's.
This does also however mean that ours uses less logic elements and multipliers as some can be reused.

Below are some slides created to summarize the major results and differences.
![image](https://github.com/aross50/465LinRegression/assets/149820800/ec126bbf-5fed-4384-9e52-ae5575af2713)
![image](https://github.com/aross50/465LinRegression/assets/149820800/1887db19-00e8-45a4-b68e-6cd0f2261aef)

We note that this module is only accurate for inputs within a certain range, as the Q16.16 format for signed fixed point numbers has a maximum value of 32768, which can quickly be overflowed during the calculations necessary for this linear regression algorithm.
Further explanation of how this happens and possible means of adressing this can be found at the bottom of the jupyter notebook [`linRegDriver.ipynb`](https://github.com/aross50/465LinRegression/blob/main/PYNQ%20Files/Jupyter%20Notebooks/linRegDriver.ipynb).

## Replication
#### On PYNQ-Z2:
To use this IP on a PYNQ-Z2 board, start by setting up the board as described [here](https://pynq.readthedocs.io/en/latest/getting_started/pynq_z2_setup.html) with an imaged micro-SD card as described [here](https://pynq.readthedocs.io/en/latest/pynq_sd_card.html#prepare-the-building-environment).

Once the board has been set up and you have a proper connection with it, samba can be used to copy files over onto the board and the jupyter notebook server can be accessed over a browser as described in the tutorials above.

A new folder was created in `/home/xilinx/pynq/overlays` called `linRegOverlays`. Once this folder is created, the contents of [`PYNQ Files/Overlays Folder/linRegOverlays`](https://github.com/aross50/465LinRegression/tree/main/PYNQ%20Files/Overlays%20Folder/linRegOverlays) can be copied over to that new folder.
Only the bitstreams and associated files with v3 and v4 in the name are used in [`linRegDriver.ipynb`](https://github.com/aross50/465LinRegression/blob/main/PYNQ%20Files/Jupyter%20Notebooks/linRegDriver.ipynb), and are the only fully funtional ones.
Thus it is recomended that only v3 and v4 files are copied over for use. The difference in these versions is discussed in the linRegDriver notebook.

The main notebook file [linRegDriver.ipynb](https://github.com/aross50/465LinRegression/blob/main/PYNQ%20Files/Jupyter%20Notebooks/linRegDriver.ipynb) can be copied directly into `/home/xilinx/jupyter_notebooks`.

The notebook uses the python [fixedpoint](https://pypi.org/project/fixedpoint/) package to convert input floating point numbers into fixed point numbers for the FPGA and vice versa when reading results. This package is non standard and thus needs to be installed before use of this driver.

If your PYNQ-Z2 board was set up to be connected directly to the internet this is as simple as creating a new cell in a notebook and running
```
%pip install fixedpoint
```
If your board is instead set up with a direct connection to your primary computer (i.e., connected directly over ethernet), you can instead copy the [`extraPackages`](https://github.com/aross50/465LinRegression/tree/main/PYNQ%20Files/extraPackages) folder into `/home/xilinx/jupyter_notebooks`, and then creating a new cell in a notebook and running
```
%pip install extraPackages/fixedpoint-1.0.1-py3-none-any.whl
```
You can now use 'lin

#### On other Xilinx Boards:
To use this IP on other Xilinx boards than the PYNQ-Z2, the c++ file [`calcXtX.cpp`](https://github.com/aross50/465LinRegression/blob/main/calcXtX.cpp) can be used in Vitis HLS to syntehesize the module for your target board, which can then be used in Vivado to create a bitstream compatable with that board.

If your board is also pynq enabled with a [PYNQ Image](https://www.pynq.io/boards.html), the jupyter notebook files/drivers created should also be usable on your board in a manner similar to that described in the section above, though this has not been attempted or verified.
