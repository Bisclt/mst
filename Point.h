#ifndef _SIMPLE_POINT_H_
#define _SIMPLE_POINT_H_

class SimplePoint {
 private:
  double x_, y_;

 public:
  SimplePoint() = delete;
  SimplePoint(double x, double y) : x_(x), y_(y) {}
  double x() const { return x_; }
  double y() const { return y_; }
  ~SimplePoint() {}
};

#endif