DiskSimulation
Overview

DiskSimulation is a C project that simulates how a real disk works using a file as the virtual storage medium. It provides low-level disk operations such as block allocation, reading, writing, and managing disk structures. This project aims to closely mimic how data is stored and accessed on a real disk.

Features

Simulates a real disk using a file as storage

Supports fixed-size block allocation and management

Implements reading and writing at the block level

Tracks files and metadata inside blocks

Educational tool for understanding disk internals

Disk Parameters

Disk size: Configurable (example: 4 KB)

Block size: Configurable (example: 512 bytes)

Block count: Calculated based on disk size and block size

Efficient simulation of disk read/write operations using standard file I/O

Sample Output

The current version of the program saves files in memory (soon to be persisted to a file acting as a whole disk):

Block:0  [1:1:MetaFile:-1]
DiskInfo :
 {7:2}
FileInfo :
 {FirstFile.txt:1:1235}
FileInfo :
 {SecondFIle.txt:4:848}
Block:1  [1:0:FirstFile.txt:2]
Content: Lorem ipsum dolor si
Block:2  [1:0:FirstFile.txt:3]
Content: to. Nullam dictum fe
Block:3  [1:0:FirstFile.txt:-1]
Content: cies nisi. Nam eget
Block:4  [1:0:SecondFIle.txt:5]
Content: Lorem ipsum dolor si
Block:5  [1:0:SecondFIle.txt:6]
Content: to. Nullam dictum fe
Block:6  [1:0:SecondFIle.txt:-1]
Content: cies
Block:7  [0:0::-1]
Content: 


This version is currently able to save files in memory. Soon, it will persist data using a file that acts as a whole disk. Additional features such as search, read, update, and delete for files stored in blocks will be implemented to fully simulate disk behavior.

Usage
Prerequisites

GCC or any standard C compiler

Basic knowledge of C and file I/O

Compilation
gcc larnFileInAdv.c -o diskSim

Execution
./diskSim


The program demonstrates block-level file storage and management.

Modify parameters in the code (disk size, block size) to experiment with different configurations.

Learning Goals

Understand how physical disks store and manage data

Learn block-level I/O operations

Practice file-based simulation of low-level storage concepts

Gain insights into the inner workings of file systems

Future Improvements

Persist disk data to a real file acting as a disk

Implement file search, read, update, and delete operations

Fully simulate a real disk with block-based file management

Add support for file metadata and allocation table structures
