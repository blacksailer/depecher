#include "SearchChatMessagesModel.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"

namespace tdlibQt {

SearchChatMessagesModel::SearchChatMessagesModel(QObject *parent) : QAbstractListModel(parent)
{
    m_tdlibJson = TdlibJsonWrapper::instance();
}
} // namespace tdlibQt
