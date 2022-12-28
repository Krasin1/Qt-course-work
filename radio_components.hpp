#ifndef RADIO_HPP
#define RADIO_HPP

#include <QString>

class Radio {
   public:
    Radio() : type(""), cost{}, specifications(""){};

    Radio(QString &t, int c, QString &s)
        : type(t), cost(c), specifications(s){};

    Radio(const Radio &other)
        : type(other.type),
          cost(other.cost),
          specifications(other.specifications){};

    Radio &operator=(const Radio &other) {
        type = other.type;
        cost = other.cost;
        specifications = other.specifications;
        return *this;
    }

    QString type;
    int cost;
    QString specifications;
};

#endif
