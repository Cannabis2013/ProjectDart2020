#ifndef IDARTSSTATISTICS_H
#define IDARTSSTATISTICS_H

class IDartsStatistics{
public:
        virtual double average() = 0;
        virtual int lowest() = 0;
        virtual int highest() = 0;
};

#endif // IDARTSSTATISTICS_H
