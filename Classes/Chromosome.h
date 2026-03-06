#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

class Chromosome
{
public:
    ~Chromosome();
    Chromosome(double x, double y);

    double X() const { return x; }
    double Y() const { return y; }

private:
    double x;
    double y;
};

#endif /* CHROMOSOME_H_ */
