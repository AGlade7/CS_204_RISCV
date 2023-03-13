
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>RISCV</title>
</head>
<body>
    <br />
<p align="center">
    <img src="logo.png" alt="Logo" width="580" height="200">

  <h3 align="center">RISC-V Simulator</h3>

  <p align="center">
    A C++ and python implementation of RISC-V Simulation.
    <br />
    <a href="https://github.com/anushthaPrakash/CS_204_RISCV/tree/main/src"><strong>Explore the docs »</strong></a>
    
  </p>
</p>
    <h1  style="color:blue;text-align:center" ><strong>CS204 Project:RISC-V Assembler</strong></h1>
    <p>The aim of this project is to simulate the machine level execution of RISC V as well as the execution of RISC-V 32-bit instructions using a high level language.. The Project also aims to give updates to the user regarding each step of the execution of the program. It also returns the final status of the memory and registers as output for the user to analyse the working of their programs thoroughly. The Project currently allows the user to use 26 different instructions and can be extended to allow the use of any number of instructions by editing the .csv files as long as the instructions are supported by 32-bit RISC V ISA. For each instruction the program gives various updates like IR, PC, decoded instruction, temporary registers like RA, RB, RZ, RY, etc. during each cycle and prints the number of cycles. The program executes each instruction using five stages as described in the RISC V architecture.The instruction memory size is upto 1000 instructions</p>
    <br/>
    <h2>Table of Contents</h2>
<ul>
  <li><a href="#getting-started">Getting Started:Installation and running</a></li>
  <li><a href="#about">About</a></li>
  <li><a href="#usage">Implementation</a></li>
  <li><a href="#contributors">Contributors</a></li>
</ul>
<h2 id="getting-started">Getting Started: Installation and running</h2>
<h3>Running the GUI version</h3>
<ul>
  <li>Your computer should have Python3, G++ and Makefile installed.You can check if they are installed or not by using the following commands</li>
  <pre><code>
    python3 --version
    g++ --version 
    make --version
 </code></pre>
  <li>Download the zip file of the repository</li>
  <li>cd into the CS_204_RISCV then to src</li>
  <pre><code>
   cd CS_204_RISCV/src
 </code></pre>
  <li>Now run the following command in terminal </li>
  <pre><code>
    make
  </code></pre>
</ul>
<br>
<ul>
  <li>The above commands will open the GUI and you ahve to press RUN</li>
  <li>This will print the output log , upadte the resistors and data memory</li>
  <li>You can see the values in the output windows</li>
</ul>
<h3>Running the Basic version without GUI</h3>
<ul>
  <li>Type the following command after cd into the src folder</li>
  <pre><code>
    g++ main.cpp myRISCVSim.cpp -I ../include
  </code></pre>
  <li>This will run the progame and output the output log in data_out.mem,D_memory.mem and resistor.mem</li>
</ul>

</body>
</html>