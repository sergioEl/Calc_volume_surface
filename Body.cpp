#include "../std_lib_facilities.h"

/*
- Seokho Han 201761541
- COMP2510 ass5
- Description :
    Calculating surface and volume of 3D shapes.
    Body is a pure virtual abstract base class.
 */

const double PI = 3.141592653589793; //constant value for PI

class Body //pure virtual abstract base class
{
    public:
        virtual double surface() = 0;
        virtual double volume() = 0;
};

class Sphere : public Body
{
    protected:
        double radius;
    public:
        Sphere(double r)
            : radius(r)
            {}

        double getRadius() const {return radius;}
        
        double surface() override
        {
            return (4 * PI * radius * radius);
        }

        double volume() override
        {
            return ((4.0/3.0) * PI * radius * radius * radius);
        }

};

//Abstract class for calculating 3D shapes//
class Prism : public Body
{
    protected:
        double height;
        double crossSection;
    
    public:
        Prism (double crossSection, double height)
            : crossSection(crossSection), height(height)
            {}
        double getHeight() const {return height;}
        double getCrossSection() const {return crossSection;}
};

class HexagonalPrism : public Prism
{
    private:
        double side;
        // calculating the cross section surface //
        double calCrossSection(double side)
        {
            return (3 * sqrt(3) / 2 * side * side);
        }
    public:
        HexagonalPrism (double h, double s)
            :   Prism(calCrossSection(s), h),
                side(s)
            {
               // crossSection = 3 * sqrt(3) / 2 * side * side;
            } 

        double getSide() const {return side;}
    
        double surface() override
        {
            return (6 * side * height) + (3 * sqrt(3) * side * side);
        }

        double volume() override
        {
          
            return 3 * sqrt(3) / 2 * side * side * height;
        }
};

class TriangularPrism : public Prism
{
    private:
        double a;
        double b;
        double c;
        // calculating the cross section surface //
        double calCrossSection(double a, double b, double c)
        {
            double s = (a+b+c)/2;
            return sqrt(s * (s-a) * (s-b) * (s-c));
        }
    public:

        TriangularPrism (double h, double a, double b, double c)
            :   a(a), b(b), c(c),
                Prism(calCrossSection(a, b, c), h)
            {
//                double s = (a+b+c)/2;
//                crossSection = sqrt(s * (s-a) * (s-b) * (s-c));
            }

        double getA() const {return a;}
        double getB() const {return b;}
        double getC() const {return c;}

        double surface() override
        {
            double s = (a+b+c)/2;
            return (a + b + c) * getHeight() + 2 * sqrt(s * (s-a) * (s-b) * (s-c));
        }
        double volume() override
        {
            return getCrossSection() * getHeight();
        }
};

class Cuboid : public Prism
{
    protected:
        double length;
        double width;
        // calculating the cross section surface //
        double calCrossSection(double length, double width)
        {
            return length * width;
        }
    
    public:
        //constructor//
        Cuboid (double h, double l, double w)
            :   length(l), width(w),
                Prism(calCrossSection(l, w), h)
            {
//                crossSection = length * width;
            }

        double getLength() const {return length;}
        double getWidth() const {return width;}

        double surface() override
        {
            return 2*(getHeight() * length + width * length + width * getHeight());
        }
        double volume() override
        {
            return getCrossSection() * getHeight();
        }
};

class Cube : public Cuboid
{
    public:
        Cube (double h)
            : Cuboid(h, h, h)
        {}
};

void printStats(Body& c) //pass by a reference
{
    cout << "Surface area is: " << c.surface() << "cm^2\n";
    cout << "Volume is: " << c.volume() << "cm^3\n";
    cout << "------------------------\n";
}

int main()
{
    Cube c{5};
    printStats(c);
    TriangularPrism tri{2, 3, 4, 5};
    HexagonalPrism hexa{12, 4};
    Cuboid cub{7, 8, 9};
    Cube cc{5};
    Sphere s{10};

    vector<Body*> bodies; //vector for storing subtypes of body

    TriangularPrism *tPtr = &tri;
    HexagonalPrism *hPtr = &hexa;
    Cuboid *cPtr = &cub;
    Cube *cubePtr = &cc;
    Sphere *sPtr = &s;

    //store all subtypes into a vector//
    bodies.push_back(tPtr);
    bodies.push_back(hPtr);
    bodies.push_back(cPtr);
    bodies.push_back(cubePtr);
    bodies.push_back(sPtr);

    //cout << setprecision(2) << fixed;
    //print surface and volume of each object//
    for (auto& b : bodies)
    {
        cout << "\nSurface area is: " << b->surface() << "cm^2\n";
        cout << "Volume is: " << b->volume() << "cm^3\n";
    }

    return 0;
}
