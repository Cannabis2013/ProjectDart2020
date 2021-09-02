#ifndef IDCINPUTMODEL_H
#define IDCINPUTMODEL_H

namespace DCContext {
    class IDCInputModel
    {
    public:
        virtual int point() const = 0;
        virtual int modKeyCode() const = 0;
        virtual int score() const = 0;
    };
}

#endif // IDCINPUTMODEL_H
