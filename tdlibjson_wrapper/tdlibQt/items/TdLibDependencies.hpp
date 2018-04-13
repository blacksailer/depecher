#ifndef TDLIBDEPENDENCIES_HPP
#define TDLIBDEPENDENCIES_HPP
/*** Slice ***/
#include <QtCore>
#include <QVariantMap>
namespace tdlibQt {
using int32 = qint32;
using int64 = qint64;

template <size_t size>
struct UInt {
    static_assert(size % 8 == 0, "size should be divisible by 8");
    quint8 raw[size / 8];
};

template <size_t size>
inline bool operator==(const UInt<size> &a, const UInt<size> &b)
{
    return memcmp(a.raw, b.raw, sizeof(a.raw)) == 0;
}

template <size_t size>
inline bool operator!=(const UInt<size> &a, const UInt<size> &b)
{
    return !(a == b);
}

using UInt128 = UInt<128>;
using UInt256 = UInt<256>;


class Slice
{
    const char *s_;
    size_t len_;

    struct private_tag {};

public:
    Slice();
    Slice(const char *s, size_t len);
    Slice(const unsigned char *s, size_t len);
    Slice(const std::string &s);
    Slice(const char *s, const char *t);
    Slice(const unsigned char *s, const unsigned char *t);

    template <size_t N>
    constexpr Slice(char (&a)[N]) = delete;

    template <size_t N>
    constexpr Slice(const char (&a)[N]) : s_(a), len_(N - 1)
    {
    }

    bool empty() const;
    size_t size() const;

    Slice &remove_prefix(size_t prefix_len);
    Slice &remove_suffix(size_t suffix_len);
    Slice &truncate(size_t size);

    Slice copy() const;

    const char *data() const;
    const char *begin() const;
    const unsigned char *ubegin() const;
    const char *end() const;
    const unsigned char *uend() const;

    std::string str() const;
    Slice substr(size_t from) const;
    Slice substr(size_t from, size_t size) const;
    size_t find(char c) const;
    size_t rfind(char c) const;

    char back() const;
    char operator[](size_t i) const;
};

bool operator==(const Slice &a, const Slice &b);
bool operator!=(const Slice &a, const Slice &b);


inline Slice::Slice() : Slice("", static_cast<size_t>(0))
{
}

inline Slice::Slice(const char *s, size_t len) : s_(s), len_(len)
{
}

inline Slice::Slice(const unsigned char *s, size_t len) : s_(reinterpret_cast<const char *>(s)),
    len_(len)
{
}

inline Slice::Slice(const std::string &s) : Slice(s.c_str(), s.size())
{
}

inline Slice::Slice(const char *s, const char *t) : Slice(s, t - s)
{
}

inline Slice::Slice(const unsigned char *s, const unsigned char *t) : Slice(s, t - s)
{
}

inline size_t Slice::size() const
{
    return len_;
}

inline Slice &Slice::remove_prefix(size_t prefix_len)
{
//    CHECK(prefix_len <= len_);
    s_ += prefix_len;
    len_ -= prefix_len;
    return *this;
}

inline Slice &Slice::remove_suffix(size_t suffix_len)
{
//    CHECK(suffix_len <= len_);
    len_ -= suffix_len;
    return *this;
}

inline Slice &Slice::truncate(size_t size)
{
    if (len_ > size) {
        len_ = size;
    }
    return *this;
}

inline Slice Slice::copy() const
{
    return *this;
}

inline bool Slice::empty() const
{
    return len_ == 0;
}

inline const char *Slice::data() const
{
    return s_;
}

inline const char *Slice::begin() const
{
    return s_;
}

inline const unsigned char *Slice::ubegin() const
{
    return reinterpret_cast<const unsigned char *>(s_);
}

inline const char *Slice::end() const
{
    return s_ + len_;
}

inline const unsigned char *Slice::uend() const
{
    return reinterpret_cast<const unsigned char *>(s_) + len_;
}

inline std::string Slice::str() const
{
    return std::string(begin(), size());
}

inline Slice Slice::substr(size_t from) const
{
    return Slice(s_ + from, len_ - from);
}
inline Slice Slice::substr(size_t from, size_t size) const
{
    return Slice(s_ + from, std::min(size, len_ - from));
}

inline size_t Slice::find(char c) const
{
    for (size_t pos = 0; pos < len_; pos++) {
        if (s_[pos] == c) {
            return pos;
        }
    }
    return static_cast<size_t>(-1);
}

inline size_t Slice::rfind(char c) const
{
    for (size_t pos = len_; pos-- > 0;) {
        if (s_[pos] == c) {
            return pos;
        }
    }
    return static_cast<size_t>(-1);
}

inline char Slice::back() const
{
    return s_[len_ - 1];
}

inline char Slice::operator[](size_t i) const
{
    return s_[i];
}

inline bool operator==(const Slice &a, const Slice &b)
{
    return a.size() == b.size() && memcmp(a.data(), b.data(), a.size()) == 0;
}

inline bool operator!=(const Slice &a, const Slice &b)
{
    return !(a == b);
}

class TlStorerToString
{
    std::string result;
    int shift = 0;

    void store_field_begin(const char *name)
    {
        for (int i = 0; i < shift; i++) {
            result += ' ';
        }
        if (name && name[0]) {
            result += "\"";
            result += name;
            result += "\":";
        }
    }
    void store_field_end()
    {
        result += ",\n";
    }
    void store_long(qint64 value)
    {
        result += QString::number(value).toStdString();
    }
    void store_binary(Slice data)
    {
        static const char *hex = "0123456789ABCDEF";
        std::string bytes = "";

        result.append("{ ");
        for (auto c : data) {
            unsigned char byte = c;
            bytes += hex[byte >> 4];
            bytes += hex[byte & 15];
            bytes += ' ';
        }
        result.append(bytes);
        result.append("}");
    }

    template<class T>
    void insert_to_map(const char *name, const T &value)
    {
//        if (sizeof(name) == 0)
//            root->value("vector").toList().append(value);
//        else
        root->insert(name, value);
    }
public:
    TlStorerToString() = default;
    TlStorerToString(const TlStorerToString &other) = delete;
    TlStorerToString &operator=(const TlStorerToString &other) = delete;
    QQueue<QPair<QString, QVariantMap>> queue_ptrs;
    QVariantMap *root;
    QVariantMap doc;

    void store_field(const char *name, bool value)
    {
        store_field_begin(name);
        result += (value ? "true" : "false");
        insert_to_map(name, value);
        store_field_end();
    }

    void store_field(const char *name, qint32 value)
    {
        store_field(name, static_cast<int64>(value));
        insert_to_map(name, value);
    }

    void store_field(const char *name, qint64 value)
    {
        store_field_begin(name);
        store_long(value);
        store_field_end();
        insert_to_map(name, value);
    }

    void store_field(const char *name, double value)
    {
        store_field_begin(name);
        result += QString::number(value).toStdString();
        store_field_end();
        insert_to_map(name, value);
    }

    void store_field(const char *name, const char *value)
    {
        store_field_begin(name);
        result += "\"";
        result += value;
        result += "\"";
        store_field_end();
        insert_to_map(name, value);
    }

    void store_field(const char *name, const std::string &value)
    {
        store_field_begin(name);
        result += '"';
        result.append(value.data(), value.size());
        result += '"';
        store_field_end();
        insert_to_map(name, QString::fromStdString(value));
    }

    template <class T>
    void store_field(const char *name, const T &value)
    {
        store_field_begin(name);
        result.append(value.data(), value.size());
        store_field_end();
        insert_to_map(name, QString::fromRawData(value.data(), value.size()));
    }

    template <class BytesT>
    void store_bytes_field(const char *name, const BytesT &value)
    {
        static const char *hex = "0123456789ABCDEF";
        std::string bytes = "";
        store_field_begin(name);
        result.append("bytes { ");
        for (size_t i = 0; i < value.size(); i++) {
            int b = value[static_cast<int>(i)] & 0xff;
            bytes += hex[b >> 4];
            bytes += hex[b & 15];
            bytes += ' ';
        }
        result.append(bytes);
        result.append("}");
        store_field_end();
        insert_to_map(name, QString::fromStdString(bytes));
    }

    void store_field(const char *name, const UInt128 &value)
    {
        store_field_begin(name);
        auto sliceObj = Slice(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
        store_binary(sliceObj);
        store_field_end();

        static const char *hex = "0123456789ABCDEF";
        std::string bytes = "";
        for (auto c : sliceObj) {
            unsigned char byte = c;
            bytes += hex[byte >> 4];
            bytes += hex[byte & 15];
            bytes += ' ';
        }

        insert_to_map(name, QString::fromStdString(bytes));

    }

    void store_field(const char *name, const UInt256 &value)
    {
        store_field_begin(name);
        auto sliceObj = Slice(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
        store_binary(sliceObj);
        store_field_end();

        static const char *hex = "0123456789ABCDEF";
        std::string bytes = "";
        for (auto c : sliceObj) {
            unsigned char byte = c;
            bytes += hex[byte >> 4];
            bytes += hex[byte & 15];
            bytes += ' ';
        }
        insert_to_map(name, QString::fromStdString(bytes));
    }

    void store_class_begin(const char *field_name, const char *class_name)
    {
        queue_ptrs.push_front(QPair<QString, QVariantMap>(field_name, QVariantMap()));
        root = &queue_ptrs.first().second;
        if (!QString::fromLatin1(class_name).contains("vector"))
            insert_to_map("@type", class_name);
        else
            insert_to_map("vector", QVariantList());

        store_field_begin(field_name);
        result += " {\n\"@type\":\"";
        result += class_name;
        result += "\",";
        shift += 2;
    }

    void store_class_end()
    {
        auto value = queue_ptrs.takeFirst();
        if (queue_ptrs.size() > 0) {
            root = &queue_ptrs.first().second;
            if (value.second.contains("vector"))
                queue_ptrs.first().second[value.first] = value.second["vector"];
            else
                queue_ptrs.first().second[value.first] = value.second;
        } else {
            root = &doc;
            if (value.second.contains("vector"))
                doc[value.first] = value.second["vector"];
            else
                doc[value.first] = value.second;
        }
        shift -= 2;
        for (int i = 0; i < shift; i++) {
            result += ' ';
        }
        result += "}\n";
//        CHECK(shift >= 0);
    }

    std::string str() const
    {
        return result;
    }
};


} //namespace tdlibQt
#endif // TDLIBDEPENDENCIES_HPP
