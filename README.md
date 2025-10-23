# 🖴 DiskSimulation

## Overview
`DiskSimulation` simulates how a real disk works using a file as virtual storage.  
It demonstrates **block allocation, reading, writing, and file management**, mimicking real disk behavior.

---
## Version
- Available :
  -  [* ## https://github.com/Bipin1-code/DiskSimulation/tree/DkS_v0.1*](https://github.com/Bipin1-code/DiskSimulation/tree/DkS_v0.1) 
---
## Features
- 🗂 Virtual disk using a file  
- 📦 Fixed-size block allocation  
- 📤 Block-level read/write operations  
- 📝 File metadata tracking  
- 🎓 Educational tool for understanding disk internals  

---

## Disk Parameters
- **Disk Size:** Configurable (e.g., 4 KB)  
- **Block Size:** Configurable (e.g., 512 bytes)  
- **Block Count:** Calculated automatically  

---

## Sample Output
```
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
```
> ⚠️ Currently stores files in memory. Persistence and operations like search, read, update, delete will be added soon.

---

## 🧩 Disk Layout Example
```
🔹 [Block0: MetaFile] ──> Tracks all file info
🔹 [Block1: FirstFile.txt] ──> Data chunk 1
🔹 [Block2: FirstFile.txt] ──> Data chunk 2
🔹 [Block3: FirstFile.txt] ──> Data chunk 3
🔹 [Block4: SecondFile.txt] ──> Data chunk 1
🔹 [Block5: SecondFile.txt] ──> Data chunk 2
🔹 [Block6: SecondFile.txt] ──> Data chunk 3
🔹 [Block7: Free/Unused] ➖ Empty block
```
> Visual representation of how files are split across disk blocks.

---

### Compilation
```bash
gcc larnFileInAdv.c -o diskSim
```

### Execution
```bash
./diskSim
```
> Modify disk parameters in the code to experiment with different configurations.

---

## 🎯 Learning Goals
- Understand **how disks store and manage data**  
- Learn **block-level I/O operations**  
- Explore **file-based disk simulation**  
- Gain insights into **file systems**

---

## 🔮 Future Improvements
- Persist disk data to a file 💾  
- Implement **file search, read, update, delete** 🔍  
- Fully simulate a **real disk with block management** 🖴  
- Add **metadata and allocation table structures** 📑  

---

