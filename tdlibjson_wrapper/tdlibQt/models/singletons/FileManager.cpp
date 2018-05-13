#include "FileManager.hpp"
namespace tdlibQt {

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}

FileManager *FileManager::instance()
{
    static FileManager instance;
    return &instance;
}
} //tdlibQt
