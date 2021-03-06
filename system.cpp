//****************************************************************************************************
//???????????? ??????????
//****************************************************************************************************
#include "system.h"

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <unistd.h>

//****************************************************************************************************
//?????????? ???????
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//??????? ?????? ?????? ??????????
//----------------------------------------------------------------------------------------------------
void CreateFileList(const std::string &path,std::vector<std::string> &vector_file_name)
{
 vector_file_name.clear();
 //????????? ????? ????????
 DIR *dir;
 dirent *d_ptr;
 dir=opendir(path.c_str());
 if (dir!=NULL)
 {
  while(1)
  {
   d_ptr=readdir(dir);
   if (d_ptr==NULL) break;
   long len=strlen(d_ptr->d_name);
   if (len==1)
   {
    if (d_ptr->d_name[len-1]=='.') continue;
   }
   if (len==2)
   {
    if (d_ptr->d_name[len-1]=='.' && d_ptr->d_name[len-2]=='.') continue;
   }
   std::string filename=path;
   filename+=GetPathDivider();
   filename+=d_ptr->d_name;

   DIR *dir_tmp;
   dirent *d_tmp_ptr;
   dir_tmp=opendir(filename.c_str());
   if (dir_tmp!=NULL)//??? ???????, ? ?? ????
   {
    closedir(dir_tmp);
    continue;
   }
   //vector_file_name.push_back(filename);
   vector_file_name.push_back(d_ptr->d_name);
  }
  closedir(dir);
 }
}

//----------------------------------------------------------------------------------------------------
//??????? ?????? ????????? ??????????
//----------------------------------------------------------------------------------------------------
void CreateDirectoryList(const std::string &path,std::vector<std::string> &vector_directory_name)
{
 vector_directory_name.clear();
 //????????? ?????????? ????????
 DIR *dir;
 dirent *d_ptr;
 dir=opendir(path.c_str());
 if (dir!=NULL)
 {
  while(1)
  {
   d_ptr=readdir(dir);
   if (d_ptr==NULL) break;
   long len=strlen(d_ptr->d_name);
   if (len==1)
   {
    if (d_ptr->d_name[len-1]=='.') continue;
   }
   if (len==2)
   {
    if (d_ptr->d_name[len-1]=='.' && d_ptr->d_name[len-2]=='.') continue;
   }
   std::string filename=path;
   filename+=GetPathDivider();
   filename+=d_ptr->d_name;

   DIR *dir_tmp;
   dirent *d_tmp_ptr;
   dir_tmp=opendir(filename.c_str());
   if (dir_tmp==NULL) continue;//??? ????,? ?? ???????
   closedir(dir_tmp);
   //vector_directory_name.push_back(filename);
   vector_directory_name.push_back(d_ptr->d_name);
  }
  closedir(dir);
 }
}

//----------------------------------------------------------------------------------------------------
//??????? ???????
//----------------------------------------------------------------------------------------------------
void MakeDirectory(const std::string &directory_name)
{
 mkdir(directory_name.c_str(),S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH |S_IXOTH);
}

//----------------------------------------------------------------------------------------------------
//???????? ????????? ????? ? ????????
//----------------------------------------------------------------------------------------------------
long double GetSecondCounter(void)
{
 return(0);
}
//----------------------------------------------------------------------------------------------------
//????? ? ?????????????
//----------------------------------------------------------------------------------------------------
void PauseInMs(size_t ms)
{
}
//----------------------------------------------------------------------------------------------------
//????? ? ?????????????
//----------------------------------------------------------------------------------------------------
void PauseInUs(size_t us)
{
}
//----------------------------------------------------------------------------------------------------
//???????? ??????? ??????????
//----------------------------------------------------------------------------------------------------
std::string GetCurrentPath(void)
{
 return(std::string("."));
}
//----------------------------------------------------------------------------------------------------
//???????? ??????????? ????????
//----------------------------------------------------------------------------------------------------
std::string GetPathDivider(void)
{
 return(std::string("/"));
}
//----------------------------------------------------------------------------------------------------
//??????? ?????????
//----------------------------------------------------------------------------------------------------
void PutMessage(const std::string &message)
{
 printf("%s\r\n",message.c_str());
}
//----------------------------------------------------------------------------------------------------
//??????? ????????? ? ???????
//----------------------------------------------------------------------------------------------------
void PutMessageToConsole(const std::string &message)
{
 printf("%s",message.c_str());
}
