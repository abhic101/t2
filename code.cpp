#include <iostream>
#include <zlib.h>
#include <minizip/unzip.h>

int main()
{
   // Open the zip file
   unzFile zipFile = unzOpen("file.zip");
   if (zipFile == NULL) {
       std::cout << "Error opening zip file!" << std::endl;
       return 1;
   }

   // Read and print the contents of the zip file
   int result = unzGoToFirstFile(zipFile);
   while (result == UNZ_OK) {
       // Get the file info
       unz_file_info fileInfo;
       result = unzGetCurrentFileInfo(zipFile, &fileInfo, NULL, 0, NULL, 0, NULL, 0);
       if (result != UNZ_OK) {
           std::cout << "Error getting file info!" << std::endl;
           return 1;
       }

       // Get the file name
       char fileName[256];
       result = unzGetCurrentFileInfo(zipFile, NULL, fileName, sizeof(fileName), NULL, 0, NULL, 0);
       if (result != UNZ_OK) {
           std::cout << "Error getting file name!" << std::endl;
           return 1;
       }

       // Open the current file
       result = unzOpenCurrentFile(zipFile);
       if (result != UNZ_OK) {
           std::cout << "Error opening file!" << std::endl;
           return 1;
       }

       // Read the file
       int bufferSize = fileInfo.uncompressed_size;
       char* buffer = new char[bufferSize];
       result = unzReadCurrentFile(zipFile, buffer, bufferSize);
       if (result != UNZ_OK) {
           std::cout << "Error reading file!" << std::endl;
           return 1;
       }

       // Print the contents of the file
       std::cout << "File Name: " << fileName << std::endl;
       std::cout << "File Contents:" << std::endl;
       std::cout << buffer << std::endl;

       // Close the current file
       result = unzCloseCurrentFile(zipFile);
       if (result != UNZ_OK) {
           std::cout << "Error closing file!" << std::endl;
           return 1;
       }

       // Go to the next file
       result = unzGoToNextFile(zipFile);
   }

   // Close the zip file
   result = unzClose(zipFile);
   if (result != UNZ_OK) {
       std::cout << "Error closing zip file!" << std::endl;
       return 1;
   }

   return 0;
}
