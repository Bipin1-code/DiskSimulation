
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>


#define DISK_V 4 * 1024
#define BLOCK_S 512
#define BLOCK_N ((DISK_V + BLOCK_S - 1) / BLOCK_S)

typedef enum{
  DATA_BLOCK = 0,
  META_BLOCK
} BlockType;

typedef struct{
  char openBkt;
  uint8_t statusFlag;
  char colon1;  
  BlockType bType;
  char colon2;
  char fName[64];
  char colon3; 
  int64_t nextBChain;
  char closeBkt;
  char content[423]; 
} Blocks; 

typedef struct{
  Blocks blocks[BLOCK_N];
} VDisk; //1MB

typedef struct{
  char opCrlBkt; //1
  char fileNam[64]; //65
  char colon1; //66
  int64_t initBkIdx; //72+8 =82
  char colon2; //83
  size_t fileSize; //88+ 8 = 96
  char clCrlBkt; //97 
}FileInfo; //104

typedef struct{
  char opCrlBkt; //0 ofs
  size_t bUCt; //8 ofs 7 padding bytes
  char colon; //16 ofs
  size_t fCt; //24 ofs 7 padding bytes
  char clCrlBkt; //32 ofs
}DiskInfo;  // 40 7 padding bytes

//Global Variables:
FileInfo fileInfo;
DiskInfo diskInfo;


void initDisk(VDisk *vd){

  for(int i = 0; i < BLOCK_N; i++){
    vd->blocks[i] = (Blocks){
      .openBkt = '[',
      .statusFlag = 0,
      .colon1 = ':',
      .bType = DATA_BLOCK,
      .colon2 =':',
      .fName = {0}, 
      .colon3 = ':',
      .nextBChain = -1, 
      .closeBkt =']', 
      .content = ""  
    };
  }
  //Update Disk's block present at index 0
  vd->blocks[0].statusFlag = 1;
  vd->blocks[0].bType = META_BLOCK;
  strncpy(vd->blocks[0].fName, "MetaFile", 63);

  //Disk Info compound literal initialization
  diskInfo = (DiskInfo){
    .opCrlBkt = '{',
    .bUCt = 1,
    .colon = ':',
    .fCt = 0,
    .clCrlBkt = '}'
  };
  memcpy(vd->blocks[0].content, &diskInfo, sizeof(DiskInfo));

  //File Info compound literal initialization
  fileInfo = (FileInfo){
    .opCrlBkt = '{',
    .fileNam = "",
    .colon1 = ':',
    .initBkIdx = -1,
    .colon2 = ':',
    .fileSize = 0,  
    .clCrlBkt = '}'   
  };
}

char* takeData(){
  size_t len = 2, clen = 0;
  char ch;
  char *str = (char*)malloc(len * sizeof(char));
  if(!str){
    fprintf(stderr, "ERROR: Memory allocation failed for %s\n", str);
    return NULL;
  }
  while((ch = getchar()) != '~' && ch != EOF){
    if(clen + 1 >= len){
      len += 5;
      char *temp =(char*)realloc(str, len);
      if(!temp){
	fprintf(stderr, "ERROR: Memory allocation failed for %s\n", temp);
	return NULL;
      }
      str = temp;
    }
    str[clen++] = ch;
  }
  if(str){
    str[clen] = '\0';
  }
  return str;
}

void blockAllocator(VDisk *vd, size_t *allocatedBlock, size_t blockNeeded){
  size_t index = 0;
  for(size_t i = 0; i < BLOCK_N && index < blockNeeded; i++){
    if(vd->blocks[i].statusFlag == 0){
      allocatedBlock[index++] = i;
    }
  }
}

size_t findNewBlockForMetaBlock(VDisk *vd){
  //0 is already been used
  /*TODO:
    later I will create a emergency META_block for to handle the case where file
    take all free block and metaBlocks are filled no space for to save that fileInfo
    than emergency MetaBlock handle that scenario.
  */
  size_t idx = 0;
  for(size_t i = 1; i < BLOCK_N; i++){
    if(vd->blocks[i].statusFlag == 0){
      idx = i;
    }
    //else emergency block future addition 
  }
  return idx;
}

void saveFileInfoToMetaBlock(VDisk *vd, const char *fNam, size_t lenOfData, int64_t startIdx){

  /* I found out I can store 3 file Info in a block */
  DiskInfo readDk;
  memcpy(&readDk, vd->blocks[0].content, sizeof(DiskInfo));

  //find the last metaBlock
  size_t i = 0; //zero because 0 is initailize as METABlOCK
  while(vd->blocks[i].nextBChain != -1){
    i = vd->blocks[i].nextBChain;
  }  
  
  if(readDk.fCt != 0 && readDk.fCt % 3 == 0){
    size_t newMBIdx = findNewBlockForMetaBlock(vd);
    vd->blocks[i].nextBChain = newMBIdx;
    
    //update the block we is now being used
    vd->blocks[newMBIdx].statusFlag = 1;
    vd->blocks[newMBIdx].bType = META_BLOCK;
    strncpy(vd->blocks[newMBIdx].fName, "MetaFile", 63); 

    //store the fileInfo in the block
    fileInfo = (FileInfo){
      .opCrlBkt = '{',
      .fileNam = "",
      .colon1 = ':',
      .initBkIdx = startIdx,
      .colon2 = ':',
      .fileSize = lenOfData,  
      .clCrlBkt = '}'   
    };
    strncpy(fileInfo.fileNam, fNam, 63);
    memcpy(vd->blocks[newMBIdx].content, &fileInfo, sizeof(FileInfo));

    diskInfo.bUCt += 1;
  }else{
    //block 0 still have space have for to store the fileInfo
    //store the fileInfo in the block
    // readBk.fCt = 7 % 3 = 1 current index fileC and 7 / 3 = 2 is number of blockUsedC before current
    fileInfo = (FileInfo){
      .opCrlBkt = '{',
      .fileNam = "",
      .colon1 = ':',
      .initBkIdx = startIdx,
      .colon2 = ':',
      .fileSize = lenOfData,  
      .clCrlBkt = '}'   
    };
    strncpy(fileInfo.fileNam, fNam, 63);
    size_t fileIdxInBlock = readDk.fCt % 3;
    size_t idxSet = sizeof(DiskInfo) + fileIdxInBlock * sizeof(FileInfo);
    if (i != 0) {
      idxSet = fileIdxInBlock * sizeof(FileInfo);
    }
    memcpy(vd->blocks[i].content + idxSet, &fileInfo, sizeof(FileInfo));
  }  
}

void assignFileNDataInMemo(VDisk *vd, const char *fNam, const char *fData){
  size_t lenOfData = strlen(fData);
  size_t blockNeeded = (lenOfData + 422) / 423;
  DiskInfo readDk;
  memcpy(&readDk, vd->blocks[0].content, sizeof(DiskInfo));
  size_t freeBlocks = BLOCK_N - (readDk.bUCt);
  if(blockNeeded > BLOCK_N || blockNeeded > freeBlocks){
    fprintf(stderr,
	    "ERROR: Not enought space present for to save the file!\n");
    return;
  }
  size_t *allocatedBlock = (size_t*)malloc(blockNeeded * sizeof(size_t));
  if(!allocatedBlock){
    fprintf(stderr,
	    "ERROR: Something went wrong while doing block allocation!\n");
    return;
  }
  blockAllocator(vd, allocatedBlock, blockNeeded);

  int written = 0;
  for(size_t i = 0; i < blockNeeded; i++){
    size_t curIdx = allocatedBlock[i];

    vd->blocks[curIdx].bType = DATA_BLOCK;
    vd->blocks[curIdx].statusFlag = 1;
    strncpy(vd->blocks[curIdx].fName, fNam, 63);
    vd->blocks[curIdx].nextBChain =
      (i == blockNeeded - 1) ? -1 : (int64_t)allocatedBlock[i+1];
    
    int leftToWrite = lenOfData - written;
    int toWrite = (leftToWrite > 422) ? 422 : leftToWrite;
   
    memcpy(vd->blocks[curIdx].content, fData+written, toWrite);
    
    written += toWrite;
  }

  int64_t startIdx = (int64_t)allocatedBlock[0];
  
  saveFileInfoToMetaBlock(vd, fNam, lenOfData, startIdx);

  /*
    DiskInfo Update (Logic is that we have to update
    the data on a same loction of disk, No need to create a new struct for DiskInfo)
  */
  diskInfo.bUCt += blockNeeded;
  diskInfo.fCt++;
  memcpy(vd->blocks[0].content, &diskInfo, sizeof(DiskInfo)); 
}

void doOperation(VDisk *vd){
  //Now check the in Memory operation first

  //test Insert data or file to the blocks
  char file_Name[64];
  printf("Enter the file name: \n");
  fflush(stdout);
  fgets(file_Name, sizeof(file_Name), stdin);
  file_Name[strcspn(file_Name, "\n")] = '\0';

  printf("Write your file's content below.\n \
(Press '~' for to save file.):\n");
  fflush(stdout);
  char *data = takeData();
  if(data == NULL){
    //To do: I will later improve this case with more conditions
    fprintf(stderr, "You didn't write anything in file %s!\n", file_Name);
    free(data);
    data = NULL; //just for safe with dangling
    return;
  }
  printf("File name: %s \n Data: %s\n", file_Name, data);

  assignFileNDataInMemo(vd, file_Name, data);
  
  free(data);
  data = NULL; 
}
 
void debugDisk(VDisk *vd){
  for(int i = 0; i < BLOCK_N; i++){
    printf("Block:%d  %c%hhu%c%d%c%s%c%" PRId64 "%c\n", i,
	   vd->blocks[i].openBkt,
	   vd->blocks[i].statusFlag,
	   vd->blocks[i].colon1,
	   vd->blocks[i].bType,
	   vd->blocks[i].colon2,
	   vd->blocks[i].fName,
	   vd->blocks[i].colon3,
	   vd->blocks[i].nextBChain,
	   vd->blocks[i].closeBkt
	   );
    if( i != 0)
      printf("Content: %.20s\n",vd->blocks[i].content);
    else{
      DiskInfo readDiskInfo;
      memcpy(&readDiskInfo, vd->blocks[0].content, sizeof(DiskInfo));
      printf("DiskInfo : \n %c%zu%c%zu%c\n",
	     readDiskInfo.opCrlBkt,
	     readDiskInfo.bUCt,
	     readDiskInfo.colon,
	     readDiskInfo.fCt,
	     readDiskInfo.clCrlBkt
	     );
       
      FileInfo *fInfos = (FileInfo *)(vd->blocks[0].content + sizeof(DiskInfo));
      size_t fcount = readDiskInfo.fCt;
      
      for(size_t i = 0; i < fcount; i++){
	printf("FileInfo : \n %c%s%c%" PRId64 "%c%zu%c\n",
	       fInfos[i].opCrlBkt,
	       fInfos[i].fileNam,
	       fInfos[i].colon1,
	       fInfos[i].initBkIdx,
	       fInfos[i].colon2,
	       fInfos[i].fileSize,
	       fInfos[i].clCrlBkt
	       );
      }
    }
  }
}


int main(){

  VDisk vdisk;
  /* FILE *f = NULL; */
  /* const char *fileName = "testBinary.bin"; */

  /* if(access(fileName, F_OK) != 0){ */
  /*   f = fopen(fileName, "wb"); */
  /*   fprintf(stdout, "File %s created successfully.\n", fileName); */
  /* }else{ */
  /*   f = fopen(fileName, "rb+"); */
  /*   fprintf(stdout, "File %s open successfully.\n", fileName); */
  /* } */
  /* if(!f){ */
  /*   fprintf(stderr, "ERROR: file is not created!\n"); */
  /*   return 1; */
  /* } */
  
  /* fclose(f); */

  initDisk(&vdisk);
  
  while(1){
    int choic;
    printf("==============Menu==================\n");
    printf("=======Press 1. Create File ========\n");
    printf("=====Press 2. Exit Appication ======\n");
    printf("Enter your choice: ");
    fflush(stdout);
    scanf("%d", &choic);
    getchar();
    
    switch(choic){
    case 1:
      doOperation(&vdisk);
      break;
    case 2:
      break;
    default:
      printf("Invalid choice! Try again.\n");
    }
    if(choic == 2)
      break;
  }
  
  debugDisk(&vdisk);
  
  return 0;
}
