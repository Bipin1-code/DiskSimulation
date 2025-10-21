# 📀 DiskSimulation v0.1

[GitHub Repository](https://github.com/Bipin1-code/DiskSimulation)

---

## 📝 Overview

**DiskSimulation** is a simple C-based disk management simulation tool.  
Version `0.1` allows basic operations on a simulated disk:

- Persist files to the simulated disk.
- Read files from the disk.
- Search for files.

This project is ideal for learning and experimenting with file system concepts in memory and on disk.

---

## 🚀 Features (v0.1)

1. **Persist File**  
   Save files into the simulated disk storage so that they remain even after program termination.

2. **Read File**  
   Retrieve and display the contents of stored files.

3. **Search File**  
   Quickly locate files by name.

---

## ⚙️ Usage

### 1. Clone the repository:

```bash
git clone https://github.com/Bipin1-code/DiskSimulation.git
cd DiskSimulation
2. Compile the program:
gcc -o DiskSimulation main.c

3. Run the simulation:
./DiskSimulation

4. Menu Options:
==============Menu==================
=======Press 1. Create File ========
=======Press 2. Search File ========
=====Press 3. Exit Application =====
Enter your choice:

📂 Example: Searching and Opening a File
Enter your choice:
2
Enter the file name:
SecondFile.txt
File name you entered: SecondFile.txt
FileCount 2
FileName: 0 = FirstFile.txt
FileName: 1 = SecondFile.txt
Yes we have SecondFile.txt file.
Do you wanna open it?
For 'Yes'/'No' Press 1 or -1 respectively.
1
Content:
Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget
Disk status or Logs:
Block:0  [1:1:MetaFile:-1]
DiskInfo :
 {7:2}
FileInfo :
 {FirstFile.txt:1:1235}
FileInfo :
 {SecondFile.txt:4:912}
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

🔮 Future Plans

Implement file deletion.

Support updating file content.

Directory and file hierarchy support.

Advanced search with filters.

🤝 Contribution

Feel free to fork the repository and submit pull requests.
Contributions are welcome to enhance the functionality and performance of the simulation.
