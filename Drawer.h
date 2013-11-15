/**
 * @brief Drawer
 */
#pragma once

#include <SDL/SDL.h>
#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SYNTHESIS_H

#include <cmath>
#include <map>
#include <iostream>

typedef   std::map<std::string,FT_Face> FacesMap;

enum StyleFT{
   Regular,
   Italic,
   Bold,
   BoldItalic,
   Light,
   LightItalic,
   Medium,
   MediumItalic
};

struct Point{
   double X;
   double Y;

   Point(double aX, double aY)
   {
      X = aX;
      Y = aY;
   }

   bool operator != (const Point& aPoint) const
   {
      return ((X != aPoint.X) || (Y != aPoint.Y));
   }
};

struct SFreetypeFamilyData
{
   FT_Face mFTFontRegular;    ///< Fonte Freetype Regular
   FT_Face mFTFontBold;       ///< Fonte Freetype Bold
   FT_Face mFTFontItalic;     ///< Fonte Freetype Italic
   FT_Face mFTFontBoldItalic; ///< Fonte Freetype Bold Italic
};

class Drawer
{

public:
   // Constructeur, et destructeur virtuel
   Drawer (void);
   virtual ~Drawer (void);

   void Init (SDL_Surface* aSource);
   void LoadFonts(void);
   void UnLoadFonts(void);
   void Blit (cairo_surface_t* apDest);
   void BlitConvert (SDL_Surface* apDest);
   void Clear (void);
   void ClearRotate (void);

   void DrawRepere (double aR, double aG, double aB);

   void SetColor(double aR, double aG, double aB);

   void MoveTo (const Point& aPoint);
   void DrawPoint(const Point& aPoint, double aRadius=5);
   void DrawLine(const Point& aEndPoint, double aWidth=5);
   void DrawArc(const Point& aPoint, double aRadius, double aRadian, double aWidth=10);
   void DrawCurve(const Point& aTangPoint1, const Point& aTangPoint2, const Point& aEndPoint);
   void DrawCurve(const Point& aPrevPoint, const Point& aStartPoint, const Point& aEndPoint, const Point& aNextPoint, double& aCoef);
   void DrawCurveDebug(const Point& aPrevPoint, const Point& aStartPoint, const Point& aEndPoint, const Point& aNextPoint, double& aCoef);
   void DrawCurve2(const Point& aPrevPoint, const Point& aStartPoint, const Point& aEndPoint, const Point& aNextPoint, double& aCoef);
   void DrawEllipse (double aWidth, double aHeight);
   void DrawText(std::string& aTexte);
   void DrawTriangle (double aWidth, double aHeight);
   void Rotation(double aAngle);
   void RotationOLD(double aAngle);

   void TestCurve(const Point& aPoint1, const Point& aPoint2, const Point& aPoint3, const Point& aPoint4, const Point& aPoint5, const Point& aPoint6, double& aCoef);

private:
   cairo_surface_t*  mCairoSurface;
   cairo_t*          mCairoDC;

   FT_Library mLibrary;
   FT_Face mFontSystem;
   FT_Face mFontTest;

   double mAngle;

   FacesMap mFacesMap;
};

