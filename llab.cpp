#include <iostream>
#include <cassert>


template<typename T, size_t dim = 2>        
class Grid final {
    using SGrid = Grid<T, dim - 1>;         
public:
    Grid() : data(nullptr), ax_size(0) {}   

    ~Grid() {
        delete[] data;                      
    }

    template<class ... sizes>
    Grid(const T& val, size_t ax_size, sizes ... args) : ax_size(ax_size) {         
        data = new SGrid[ax_size];                  
        for (int i = 0; i < ax_size; i++)           
            data[i] = SGrid(val, args...);          
    }

    Grid(const Grid<T, dim>& cpy) : ax_size(cpy.ax_size) {  
        data = new SGrid[ax_size];
        for (int i = 0; i < ax_size; i++)
            data[i] = cpy.data[i];
    }

    Grid(Grid<T, dim>&& cpy) : ax_size(cpy.ax_size) { 
        data = cpy.data;
        cpy.data = nullptr;
        cpy.ax_size = 0;
    }

    Grid<T, dim>& operator=(const Grid<T, dim>& rha) {   
        if (&rha == this)
            return *this;
        if (ax_size != rha.ax_size) {
            ax_size = rha.ax_size;
            delete[] data;
            data = new SGrid[ax_size];
        }
        for (int i = 0; i < ax_size; i++)
            data[i] = rha.data[i];
        return *this;
    }

    Grid<T, dim>& operator=(Grid<T, dim>&& rha) { 
        if (&rha == this)
            return *this;
        ax_size = rha.ax_size;
        delete[] data;
        data = rha.data;
        rha.data = nullptr;
        rha.ax_size = 0;
        return *this;
    }

    const SGrid& operator[](size_t i) const {
        return data[i];
    }

    SGrid& operator[](size_t i) {
        return data[i];
    }

    template<class ... indexes>
    const T& operator()(size_t i, indexes ... args) const {
        return data[i](args...);            
    }

    template<class ... indexes>
    T& operator()(size_t i, indexes ... args) {
        return data[i](args...);
    }

private:
    SGrid* data;                           
    size_t ax_size;                         
};

template <typename T>
class Grid<T, 2> final {

private:
    size_t y_size, x_size;
    T* data;
public:
    Grid() : data(nullptr), x_size(0), y_size(0) {}  

    ~Grid() {
        delete[] data;         
    }

    Grid(T* data, size_t y_size, size_t x_size) :    
        data(data), y_size(y_size), x_size(x_size) { }

    Grid(const Grid<T>& rha) : y_size(rha.y_size), x_size(rha.x_size) {      
        data = new T[x_size * y_size];
        for (int i = 0; i < x_size * y_size; i++)
            data[i] = rha.data[i];
    }

    Grid(Grid<T>&& rha) : y_size(rha.y_size), x_size(rha.x_size) {   
        data = rha.data;
        rha.data = nullptr;
        rha.x_size = 0;
        rha.y_size = 0;
    }

    Grid(const T& t) : x_size(1), y_size(1) {        
        data = new T[1];
        *data = t;
    }

    Grid(size_t y_size, size_t x_size) : y_size(y_size), x_size(x_size) {            
        data = new T[y_size * x_size]();
    }

    Grid(const T& t, size_t y_size, size_t x_size) : y_size(y_size), x_size(x_size) {    
        data = new T[y_size * x_size];
        for (int i = 0; i < x_size * y_size; i++)
            data[i] = t;
    }

    Grid<T>& operator=(const Grid<T>& rha) {   
        if (&rha == this)
            return *this;
        delete data;
        x_size = rha.x_size;
        y_size = rha.y_size;
        data = new T[x_size * y_size];
        for (int i = 0; i < x_size * y_size; i++)
            data[i] = rha.data[i];
        return *this;
    }

    Grid<T>& operator=(Grid<T>&& rha) {    
        if (&rha == this)
            return *this;
        delete data;
        x_size = rha.x_size;
        y_size = rha.y_size;
        data = rha.data;
        rha.data = nullptr;
        rha.x_size = 0;
        rha.y_size = 0;
        return *this;
    }

    T operator()(size_t y, size_t x) const {
        return data[y * x_size + x];
    }

    T& operator()(size_t y, size_t x) {
        return data[y * x_size + x];
    }

    Grid<T>& operator=(const T& t) {   
        for (auto it = data, end = data + x_size * y_size; it != end; it++)
            *it = t;
        return *this;
    }

    T* operator[](size_t y) {
        return data + x_size * y;           
    }

    const T* operator[](size_t y) const {
        return data + x_size * y;
    }

    size_t get_y_size() const { return y_size; }
    size_t get_x_size() const { return x_size; }

};


int main() {

    Grid<float> g(0.0f, 3, 2);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    for (size_t y = 0; y != g.get_y_size(); y++)
        for (size_t x = 0; x != g.get_x_size(); x++)
            assert(0.0f == g[y][x]);

    for (size_t y = 0; y != g.get_y_size(); y++)
        for (size_t x = 0; x != g.get_x_size(); x++)
            g[y][x] = 1.0f;

    for (size_t y = 0; y != g.get_y_size(); y++)
        for (size_t x = 0; x != g.get_x_size(); x++)
            assert(1.0f == g[y][x]);

    Grid<float, 3> const g3(1.0f, 2, 3, 4);
    assert(1.0f == g3(1, 1, 1));

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));

    g2 = g3[1];
    assert(1.0f == g2(1, 1));

    return 0;
}
