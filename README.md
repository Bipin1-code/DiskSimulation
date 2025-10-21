# 📀 DiskSimulation v0.1

**DiskSimulation** is a C-based disk management simulation tool designed for learning and experimenting with file system concepts. Version 0.1 allows you to perform basic operations on a simulated disk: persist files, read files, and search files by name. This project is ideal for students, hobbyists, or anyone interested in understanding how file systems work in memory and on disk.

## 🚀 Features (v0.1)

- **Persist File**: Save files to the simulated disk storage. Files remain available even after program termination.  
- **Read File**: Retrieve and display the contents of stored files.  
- **Search File**: Quickly locate files by name.

## 📥 Repository
```
git clone https://github.com/Bipin1-code/DiskSimulation.git
```

## ⚙️ Usage

1. **Clone the repository:**
```
git clone https://github.com/Bipin1-code/DiskSimulation.git
cd DiskSimulation
```
2. **Compile the program:**
```
gcc -o disksim main.c
```
3. **Run the simulation:**
```
./disksim
```

## 📋 Available Operations

Once running, the program provides a menu with these options:
1. **Create File** - Save a new file to disk
2. **Search File** - Find and read files by name
3. **Exit Application** - Quit the program

## 🖥️ Sample Output
```
File testBinary.bin open successfully.
==============Menu==================
=======Press 1. Create File ========
=======Press 2. Search File ========
=====Press 3. Exit Appication ======
Enter your choice: 2
Enter the file name: SecondFile.txt
File name you entered: SecondFile.txt
FileCount 2
FileName: 0 = FirstFile.txt
FileName: 1 = SecondFile.txt
Yes we have SecondFile.txt file.
Do you wanna open it?
For 'Yes'/'No' Press 1 or -1 respectively.
1
Content:
Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. 
Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, 
pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, 
vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede 
mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. 
Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, 
feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam 
```
Disk status or Logs:
```
Block:0  [1:1:MetaFile:-1]
DiskInfo : {7:2}
FileInfo : {FirstFile.txt:1:1235}
FileInfo : {SecondFile.txt:4:912}
Block:1  [1:0:FirstFile.txt:2]
Content: Lorem ipsum dolor si
Block:2  [1:0:FirstFile.txt:3]
Content: to. Nullam dictum fe
Block:3  [1:0:FirstFile.txt:-1]
Content: cies nisi. Nam eget
Block:4  [1:0:SecondFile.txt:5]
Content: Lorem ipsum dolor si
Block:5  [1:0:SecondFile.txt:6]
Content: to. Nullam dictum fe
Block:6  [1:0:SecondFile.txt:-1]
Content: cies nisi. Nam eget
Block:7  [0:0::-1]
Content:
```
## 🛠️ Technical Details

- **Language**: C
- **Storage**: Simulated disk using file I/O operations
- **Persistence**: Data remains available between program executions
- **Platform**: Cross-platform (any system with a C compiler)

## 🎯 Learning Objectives

This simulation helps understand:
- Basic file system operations
- Disk storage concepts
- File persistence mechanisms
- Memory management in C

## 🤝 Contributing

Contributions are welcome! Feel free to fork this repository and submit pull requests for any improvements.

---

**Note**: This is an educational tool. For production file systems, use established solutions like ext4, NTFS, or FAT32.
