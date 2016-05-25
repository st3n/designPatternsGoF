/* Draw triangle, circle and polygon with diferent graphics library */

#include <iostream>
#include<string>
using namespace std;

class Triangle
{
   public:
      virtual void draw() = 0;
};

class Circle
{
   public:
      virtual void draw() = 0;
};

class Polygon
{
   public:
      virtual void draw() = 0;
};

class DirectXTriangle : public Triangle
{
   public:
      void draw() { cout << "Draw triangle with directX graphics" << endl; };
};

class DirectXCircle : public Circle
{
   public:
      void draw() { cout << "Draw circle with directX graphics" << endl; };
};

class DirectXPolygon : public Polygon
{
   public:
      void draw() { cout << "Draw polygon with directX graphics" << endl; };
};

class OpenGLTriangle : public Triangle
{
   public:
      void draw() { cout << "Draw triangle with openGL graphics" << endl; };
};

class OpenGLCircle : public Circle
{
   public:
      void draw() { cout << "Draw circle with openGL graphics" << endl; };
};

class OpenGLPolygon : public Polygon
{
   public:
      void draw() { cout << "Draw polygon with openGL graphics" << endl; };
};

class FiguresFactory
{
   public:
      virtual Triangle* createTriangle() = 0;
      virtual Circle* createCircle() = 0;
      virtual Polygon* createPolygon() = 0;
};

class DirectXFiguresFactory : public FiguresFactory
{
   public:
      Triangle* createTriangle() { return new DirectXTriangle(); }
      Circle* createCircle() { return new DirectXCircle(); }
      Polygon* createPolygon() { return new DirectXPolygon(); }
};

class OpenGLFiguresFactory : public FiguresFactory
{
   public:
      Triangle* createTriangle() { return new OpenGLTriangle(); }
      Circle* createCircle() { return new OpenGLCircle(); }
      Polygon* createPolygon() { return new OpenGLPolygon(); }
};

int main ()
{
   FiguresFactory* factory = NULL;

   string s;
   cout << "What library do you use?" << endl;
   cin >> s;

   if (s == "OpenGL")
      factory = new OpenGLFiguresFactory;
   else
      factory = new DirectXFiguresFactory;

   factory->createTriangle()->draw();
   factory->createCircle()->draw();
   factory->createPolygon()->draw();

   return 0;
}
