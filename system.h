#ifndef SYSTEM_H
#define SYSTEM_H

//****************************************************************************************************
//зависящие от системы функции
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <vector>
#include <string>

//****************************************************************************************************
//прототипы функций
//****************************************************************************************************

void CreateFileList(const std::string &path,std::vector<std::string> &vector_file_name);//создать список файлов директории
void CreateDirectoryList(const std::string &path,std::vector<std::string> &vector_directory_name);//создать список каталогов директории
void MakeDirectory(const std::string &directory_name);//создать каталог
long double GetSecondCounter(void);//получить прошедшее время в секундах
void PauseInMs(size_t ms);//пауза в миллисекундах
void PauseInUs(size_t us);//пауза в микросекундах
std::string GetCurrentPath(void);//получить текущую директорию
std::string GetPathDivider(void);//получить разделитель каталого
void PutMessage(const std::string &message);//вывести сообщение
void PutMessageToConsole(const std::string &message);//вывести сообщение в консоль

#endif

