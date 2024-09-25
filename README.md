# A DIBSection wrapper for Win32 and WinCE

A class that makes using DIBSections as simple as using a CBitmap





![Sample Image](https://raw.githubusercontent.com/ChrisMaunder/dibsection/master/docs/assets/dibsection.jpg)

<!-- Article Starts -->

## Preface

The sample demo workspace includes two projects: DIBSectionTest for Win32 
environments, and DIBSectionTestCE for CE environments that demonstrate the ` DIBSection` wrapper. You will need the CE SDKs from Microsoft to be installed before you can build DIBSectionTestCE.dsw.

There is also a version of the DIBSection wrapper, ported by Kenny Goers, with no dependancies on MFC. This version is currently slightly out of sync with the MFC version, and is provided as a convenience only.

## Introduction

Device Independant Bitmaps (DIBs) offer a means to manipulate and display
bitmaps in a form that is independant of the current display setting of your
computer. They are also the format of the standard windows .BMP file, and so
having a means to load, display and modify DIBs is very handy.

Win32 offers many different ways of dealing with DIBs, including the standard
DIB functions such as `SetDIBitsToDevice`, `GetDIBits` etc, 
the `DrawDib` functions, and the GDI functions such as `BitBlt` 
for use with DIBsections.

However, when working in a CE environment, many of the usual functions we
know and love have been discarded in an effort to reduce the size of the overall
OS, and as such we are only left with the possibility of using DDB's (via `CBitmap`)
or DIBSections. This is not too much of a handycap though since DIBSections are,
in a way, superior to plain DIBs in that they have an associated `HBITMAP` handle,
and hence can be manipulated via the GDI functions such as `BitBlt` and `StretchBlt`.
Furthermore, the handle to a DIBSection can be selected into a memory DC and then
drawn to directly using the `TextOut`, `Line` etc GDI functions. 
This is far easier than accessing the bits of a DIB yourself and plotting the pixels 
one by one.

The only problem with DIBsections, from an MFC programmers point of view, is
that there is no DIBSection wrapper. Jeff Prosise, in his book *Programming Windows 95 with MFC* discusses DIBSections and how great they are, but states that because
the next version of MFC will have a DIBSection wrapper class, there is no
point in him supplying one in his book. Oops! Several updates to MFC have come and gone
since that book was written and still there is no sign of a DIBSection wrapper
class. 

With the advent of CE, DIBSections have become even more important. Here I
present the `CDIBSectionLite` class - a DIBSection wrapper class for Win32 
and WinCE platforms. This class provides a simple interface to DIBSections including 
loading, saving and displaying DIBSections. Full palette support is provided for Win32 
and CE 2.11 and above. 

Note that CE introduces a new bitmap depth, namely 2 bits per pixel. This is for
older 4-level grey scale devices. `CDIBSectionLite` supports this pixel
depth in CE builds only.

## Creating and displaying DIBSections

The first step in creating a DIBSection is to fill out a `BITMAPINFOHEADER`
structure. If you are creating a DIBSection from scratch then just fill in 
these values with whatever you like. If, on the other hand, you wish to
convert a DDB to a DIBSection then your best friend is the GetDIBits function.
It fills in the `BITMAPINFOHEADER` structure for you by querying the values of
the supplied bitmap. 

Unfortunately CE does not support this function and so you must do this yourself. 
While this is no great drama it does make it a little  more difficult to get the 
colour table info from the supplied bitmap. Microsoft have kindly helped us programmers
along by writing the KB article *HOWTO: Get the Color Table of a DIBSection in Windows CE*. One limitation of the code in the KB article is that it only extracts color
table info for bitmaps that are DIBSections themselves. `CDIBSectionLite`
gets around this by synthesizing a half-tone color table for DDB's without color 
table info.

Once you have the `BITMAPINFOHEADER` structure, including the color table entries
filled in, simply call `CreateDIBSection`. This funtion will return a `HBITMAP`
 handle plus a pointer to the actual image bits. What more could you ask for!

To actually display the DIBSections you simply use the tried and true windows
GDI functions (BitBlt etc). Some functionality is lost in CE, such as GDIFlush
and SetStretchBltMode, but on the whole a HBITMAP created as a DIBSection is no
different to use than a HBITMAP from a DDB.

The `CDIBSectionLite` class includes support for the DrawDib functions. These provide
high speed display as well as dithering, but unfortunately are not available on CE.
To toggle between using the windows GDI and the DrawDib routines, use the 
`CDIBSectionLite::SetDither(...)` function.

## Using CDIBSectionLite

This class is very simple to use and wraps all the messy plumbing from view. 
The bitmap can be set using either `SetBitmap()` (which accepts either a Device 
dependant or device independant bitmap, or a resource ID) or by using `Load()`, 
which allows an image to be loaded from disk. To display the bitmap simply use 
Draw or Stretch.

eg. 

```cpp
      CDIBsectionLite dibsection;
      dibsection.Load(_T("image.bmp"));
      dibsection.Draw(pDC, CPoint(0,0));  // pDC is of type CDC*

      CDIBsectionLite dibsection;
      dibsection.SetBitmap(IDB_BITMAP); 
      dibsection.Draw(pDC, CPoint(0,0));  // pDC is of type CDC*
```

## CDIBsectionLite API

 The `CDIBSectionLite` API includes methods for loading and 
displaying images, methods to extract information about the image, as well as 
palette options for getting and setting the current palette. Note that the 
palette methods are only available in Win32 or in CE 2.11 or later.

```cpp
    // Attributes
    HBITMAP      GetSafeHandle() const  // Gets a HBITMAP handle to the image
    operator     HBITMAP() const        // Gets a HBITMAP handle to the image
    CSize        GetSize() const        // Gets the size of the image in pixels
    int          GetHeight() const      // Gets the height of the image in pixels
    int          GetWidth() const       // Gets the width of the image in pixels
    int          GetPlanes() const      // Gets the number of colour planes in the image 
    int          GetBitCount() const    // Gets the bits per pixel for the image 
    LPVOID       GetDIBits()            // Returns a pointer to the image bits
    LPBITMAPINFO GetBitmapInfo()        // Returns a pointer a BITMAPINFO structure for the image
    DWORD        GetImageSize() const   // Returns the size of the image (in bytes)
    LPBITMAPINFOHEADER GetBitmapInfoHeader() // Returns a pointer to a BITMAPINFOHEADER structure
    LPRGBQUAD    GetColorTable()        // Returns a pointer to the RGBQUAD data in the DIB color table

    // Operations (Palette)
    LPRGBQUAD GetColorTable() 
    BOOL      SetColorTable(UINT nNumColors, RGBQUAD *pColors);
    int       GetColorTableSize() 
    // these only available if DIBSECTION_NO_PALETTE not defined
    CPalette *GetPalette();            
    BOOL      SetPalette(CPalette* pPalette);
    BOOL      SetLogPalette(LOGPALETTE* pLogPalette);

    // Operations (Bitmap)
    // Loads an image into the object.
    //   nIDResource   - Bitmap resource ID 
    //   lpszResourceName  - Bitmap resource ID
    //   hBitmap       - existing image handle
    //   palette       - palette to be used for image construction (Win32 or CE 2.11 only)
    //   lpBitmapInfo  - pointer to BITMAPINFO structure
    //   lpBits        - pointer to image bits
    BOOL SetBitmap(UINT nIDResource);
    BOOL SetBitmap(LPCTSTR lpszResourceName);
    BOOL SetBitmap(HBITMAP hBitmap, CPalette* pPalette = NULL);
    BOOL SetBitmap(LPBITMAPINFO lpBitmapInfo, LPVOID lpBits);   

    BOOL Load(LPCTSTR lpszFileName);            // Load form disk
    BOOL Save(LPCTSTR lpszFileName);            // Save to disk
    BOOL Copy(CDIBSectionLite& Bitmap);         // make a copy

    // Operations (Display)
    BOOL Draw(CDC* pDC, CPoint ptDest, BOOL bForceBackground = FALSE);
    BOOL Stretch(CDC* pDC, CPoint ptDest, CSize size, BOOL bForceBackground = FALSE);

    // Only available in Win32
    BOOL SetDither(BOOL bDither);               // Set whether or not dithering is on
    BOOL GetDither();

    void DeleteObject()                         // Deletes the image and frees all memory
```

## Latest Updates

- 4 May 2000 - The class was updated with corrections from [Jim Miller](mailto:jam@3dfx.com)
of 3DFX to correct a bug with compressed bitmaps.
- 20 Sep 2000 - Fixed Bug fix in Save() (saving 4 bytes too many - Tadeusz Dracz)

    Allowed lpBits to be NULL in SetBitmap - Don Grasberger

    Fixed NumColorEntries bug - Itay Szekely

    Fixed buffer overrun bug in Load() - Itay Szekely
- 5 Apr 2001 - Fix for 16/32 bpp bitmaps for PocketPC's (Dan Robbins)

            Non-MFC port (Kenny Goers)
- 22 May 2001 - Fix for missing break in 24bpp case of NumColorEntries (Steve Kramp)
