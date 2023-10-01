#ifndef CEIL_H_
#define CEIL_H_

  class Ceil {
    public:
      int step = 0;
      bool visited = false;

      Ceil() : r_wall{true}, d_wall{true} {}

      bool IsRight() const noexcept { return r_wall; }
      bool IsDown() const noexcept { return d_wall; }

      bool& GetRight() noexcept { return r_wall; }
      bool& GetDown() noexcept { return d_wall; }

    private:
      bool r_wall;
      bool d_wall;
  };

#endif // CEIL_H_
