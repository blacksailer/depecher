#ifndef STICKERMODEL_HPP
#define STICKERMODEL_HPP

#include <QAbstractListModel>

namespace tdlibQt {

class StickerModel : public QAbstractListModel
{
public:
    StickerModel(QObject *parent = 0);
};
} //tdlibQt
#endif // STICKERMODEL_HPP
