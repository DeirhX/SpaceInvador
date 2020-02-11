//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) Microsoft Corporation.  All Rights Reserved.
//
//  File:       d3dx10tex.h
//  Content:    D3DX10 texturing APIs
//
//////////////////////////////////////////////////////////////////////////////

#include "d3dx10.h"

#ifndef __D3DX10TEX_H__
#define __D3DX10TEX_H__


//----------------------------------------------------------------------------
// D3DX10_FILTER flags:
// ------------------
//
// A valid filter must contain one of these values:
//
//  D3DX10_FILTER_NONE
//      No scaling or filtering will take place.  Pixels outside the bounds
//      of the source image are assumed to be transparent black.
//  D3DX10_FILTER_POINT
//      Each destination pixel is computed by sampling the nearest pixel
//      from the source image.
//  D3DX10_FILTER_LINEAR
//      Each destination pixel is computed by linearly interpolating between
//      the nearest pixels in the source image.  This filter works best 
//      when the scale on each axis is less than 2.
//  D3DX10_FILTER_TRIANGLE
//      Every pixel in the source image contributes equally to the
//      destination image.  This is the slowest of all the filters.
//  D3DX10_FILTER_BOX
//      Each pixel is computed by averaging a 2x2(x2) box pixels from 
//      the source image. Only works when the dimensions of the 
//      destination are half those of the source. (as with mip maps)
//
// And can be OR'd with any of these optional flags:
//
//  D3DX10_FILTER_MIRROR_U
//      Indicates that pixels off the edge of the texture on the U-axis
//      should be mirrored, not wraped.
//  D3DX10_FILTER_MIRROR_V
//      Indicates that pixels off the edge of the texture on the V-axis
//      should be mirrored, not wraped.
//  D3DX10_FILTER_MIRROR_W
//      Indicates that pixels off the edge of the texture on the W-axis
//      should be mirrored, not wraped.
//  D3DX10_FILTER_MIRROR
//      Same as specifying D3DX10_FILTER_MIRROR_U | D3DX10_FILTER_MIRROR_V |
//      D3DX10_FILTER_MIRROR_V
//  D3DX10_FILTER_DITHER
//      Dithers the resulting image using a 4x4 order dither pattern.
//  D3DX10_FILTER_SRGB_IN
//      Denotes that the input data is in sRGB (gamma 2.2) colorspace.
//  D3DX10_FILTER_SRGB_OUT
//      Denotes that the output data is in sRGB (gamma 2.2) colorspace.
//  D3DX10_FILTER_SRGB
//      Same as specifying D3DX10_FILTER_SRGB_IN | D3DX10_FILTER_SRGB_OUT
//
//----------------------------------------------------------------------------

typedef enum D3DX10_FILTER_FLAG
{
    D3DX10_FILTER_NONE            =   (1 << 0),
    D3DX10_FILTER_POINT           =   (2 << 0),
    D3DX10_FILTER_LINEAR          =   (3 << 0),
    D3DX10_FILTER_TRIANGLE        =   (4 << 0),
    D3DX10_FILTER_BOX             =   (5 << 0),

    D3DX10_FILTER_MIRROR_U        =   (1 << 16),
    D3DX10_FILTER_MIRROR_V        =   (2 << 16),
    D3DX10_FILTER_MIRROR_W        =   (4 << 16),
    D3DX10_FILTER_MIRROR          =   (7 << 16),

    D3DX10_FILTER_DITHER          =   (1 << 19),
    D3DX10_FILTER_DITHER_DIFFUSION=   (2 << 19),

    D3DX10_FILTER_SRGB_IN         =   (1 << 21),
    D3DX10_FILTER_SRGB_OUT        =   (2 << 21),
    D3DX10_FILTER_SRGB            =   (3 << 21),
} D3DX10_FILTER_FLAG;

//----------------------------------------------------------------------------
// D3DX10_NORMALMAP flags:
// ---------------------
// These flags are used to control how D3DX10ComputeNormalMap generates normal
// maps.  Any number of these flags may be OR'd together in any combination.
//
//  D3DX10_NORMALMAP_MIRROR_U
//      Indicates that pixels off the edge of the texture on the U-axis
//      should be mirrored, not wraped.
//  D3DX10_NORMALMAP_MIRROR_V
//      Indicates that pixels off the edge of the texture on the V-axis
//      should be mirrored, not wraped.
//  D3DX10_NORMALMAP_MIRROR
//      Same as specifying D3DX10_NORMALMAP_MIRROR_U | D3DX10_NORMALMAP_MIRROR_V
//  D3DX10_NORMALMAP_INVERTSIGN
//      Inverts the direction of each normal 
//  D3DX10_NORMALMAP_COMPUTE_OCCLUSION
//      Compute the per pixel Occlusion term and encodes it into the alpha.
//      An Alpha of 1 means that the pixel is not obscured in anyway, and
//      an alpha of 0 would mean that the pixel is completly obscured.
//
//----------------------------------------------------------------------------

typedef enum D3DX10_NORMALMAP_FLAG
{
    D3DX10_NORMALMAP_MIRROR_U          =   (1 << 16),
    D3DX10_NORMALMAP_MIRROR_V          =   (2 << 16),
    D3DX10_NORMALMAP_MIRROR            =   (3 << 16),
    D3DX10_NORMALMAP_INVERTSIGN        =   (8 << 16),
    D3DX10_NORMALMAP_COMPUTE_OCCLUSION =   (16 << 16),
} D3DX10_NORMALMAP_FLAG;

//----------------------------------------------------------------------------
// D3DX10_CHANNEL flags:
// -------------------
// These flags are used by functions which operate on or more channels
// in a texture.
//
// D3DX10_CHANNEL_RED
//     Indicates the red channel should be used
// D3DX10_CHANNEL_BLUE
//     Indicates the blue channel should be used
// D3DX10_CHANNEL_GREEN
//     Indicates the green channel should be used
// D3DX10_CHANNEL_ALPHA
//     Indicates the alpha channel should be used
// D3DX10_CHANNEL_LUMINANCE
//     Indicates the luminaces of the red green and blue channels should be 
//     used.
//
//----------------------------------------------------------------------------

typedef enum D3DX10_CHANNEL_FLAG
{
    D3DX10_CHANNEL_RED           =    (1 << 0),
    D3DX10_CHANNEL_BLUE          =    (1 << 1),
    D3DX10_CHANNEL_GREEN         =    (1 << 2),
    D3DX10_CHANNEL_ALPHA         =    (1 << 3),
    D3DX10_CHANNEL_LUMINANCE     =    (1 << 4),
} D3DX10_CHANNEL_FLAG;



//----------------------------------------------------------------------------
// D3DX10IMAGE_FILEFORMAT:
// ---------------------
// This enum is used to describe supported image file formats.
//
//----------------------------------------------------------------------------

typedef enum _D3DX10IMAGE_FILEFORMAT
{
    D3DX10IFF_BMP         = 0,
    D3DX10IFF_JPG         = 1,
    D3DX10IFF_PNG         = 3,
    D3DX10IFF_DDS         = 4,
    D3DX10IFF_TIFF		  = 10,
    D3DX10IFF_GIF		  = 11,
    D3DX10IFF_FORCE_DWORD = 0x7fffffff

} D3DX10IMAGE_FILEFORMAT;


//----------------------------------------------------------------------------
// D3DX10IMAGE_INFO:
// ---------------
// This structure is used to return a rough description of what the
// the original contents of an image file looked like.
// 
//  Width
//      Width of original image in pixels
//  Height
//      Height of original image in pixels
//  Depth
//      Depth of original image in pixels
//  ArraySize
//      Array size in textures
//  MipLevels
//      Number of mip levels in original image
//  Format
//      D3D format which most closely describes the data in original image
//  ResourceType
//      D3DRESOURCETYPE representing the type of texture stored in the file.
//      D3DRTYPE_TEXTURE, D3DRTYPE_VOLUMETEXTURE, or D3DRTYPE_CUBETEXTURE.
//  ImageFileFormat
//      D3DX10IMAGE_FILEFORMAT representing the format of the image file.
//
//----------------------------------------------------------------------------

typedef struct _D3DX10IMAGE_INFO
{
    UINT                    Width;
    UINT                    Height;
    UINT                    Depth;
    UINT                    ArraySize;
    UINT                    MipLevels;
    DXGI_FORMAT             Format;
    D3D10_RESOURCE          ResourceType;
    D3DX10IMAGE_FILEFORMAT  ImageFileFormat;

} D3DX10IMAGE_INFO;





#ifdef __cplusplus
extern "C" {
#endif //__cplusplus



//////////////////////////////////////////////////////////////////////////////
// Image File APIs ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#define D3DX10_IMAGE_LOAD_VALID_FLAGS       (0)

typedef struct _D3DX10IMAGE_LOAD_INFO
{
    UINT                       Width;
    UINT                       Height;
    UINT                       Depth;
    UINT                       FirstMipLevel;
    UINT                       MipLevels;
    D3D10_USAGE                Usage;
    UINT32                     BindFlags;
    UINT32                     CpuAccessFlags;
    UINT32                     MiscFlags;
    DXGI_FORMAT                Format;
    UINT                       Filter;
    UINT                       MipFilter;
    D3DX10IMAGE_INFO*          pSrcInfo;
    
#ifdef __cplusplus
    _D3DX10IMAGE_LOAD_INFO()
    {
        Width = D3DX10_DEFAULT;
        Height = D3DX10_DEFAULT;
        Depth = D3DX10_DEFAULT;
        FirstMipLevel = D3DX10_DEFAULT;
        MipLevels = D3DX10_DEFAULT;
        Usage = (D3D10_USAGE) D3DX10_DEFAULT;
        BindFlags = D3DX10_DEFAULT;
        CpuAccessFlags = D3DX10_DEFAULT;
        MiscFlags = D3DX10_DEFAULT;
        Format = DXGI_FORMAT_FROM_FILE;
        Filter = D3DX10_DEFAULT;
        MipFilter = D3DX10_DEFAULT;
        pSrcInfo = NULL;
    }  
#endif

} D3DX10IMAGE_LOAD_INFO;

//----------------------------------------------------------------------------
// D3DX10 Asynchronous texture I/O (advanced mode)
//----------------------------------------------------------------------------

HRESULT WINAPI D3DX10CreateAsyncFileLoaderW(LPCWSTR pFileName, ID3DX10DataLoader **ppDataLoader);
HRESULT WINAPI D3DX10CreateAsyncFileLoaderA(LPCSTR pFileName, ID3DX10DataLoader **ppDataLoader);
HRESULT WINAPI D3DX10CreateAsyncMemoryLoader(LPCVOID pData, SIZE_T cbData, ID3DX10DataLoader **ppDataLoader);
HRESULT WINAPI D3DX10CreateAsyncResourceLoaderW(HMODULE hSrcModule, LPCWSTR pSrcResource, ID3DX10DataLoader **ppDataLoader);
HRESULT WINAPI D3DX10CreateAsyncResourceLoaderA(HMODULE hSrcModule, LPCSTR pSrcResource, ID3DX10DataLoader **ppDataLoader);

#ifdef UNICODE
#define D3DX10CreateAsyncFileLoader D3DX10CreateAsyncFileLoaderW
#define D3DX10CreateAsyncResourceLoader D3DX10CreateAsyncResourceLoaderW
#else
#define D3DX10CreateAsyncFileLoader D3DX10CreateAsyncFileLoaderA
#define D3DX10CreateAsyncResourceLoader D3DX10CreateAsyncResourceLoaderA
#endif

HRESULT WINAPI D3DX10CreateAsyncTextureProcessor(ID3D10Device *pDevice, D3DX10IMAGE_LOAD_INFO *pLoadInfo, ID3DX10DataProcessor **ppDataProcessor);
HRESULT WINAPI D3DX10CreateAsyncTextureInfoProcessor(D3DX10IMAGE_INFO *pImageInfo, ID3DX10DataProcessor **ppDataProcessor);

//----------------------------------------------------------------------------
// GetImageInfoFromFile/Resource:
// ------------------------------
// Fills in a D3DX10IMAGE_INFO struct with information about an image file.
//
// Parameters:
//  pSrcFile
//      File name of the source image.
//  pSrcModule
//      Module where resource is located, or NULL for module associated
//      with image the os used to create the current process.
//  pSrcResource
//      Resource name
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  pSrcInfo
//      Pointer to a D3DX10IMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DX10GetImageInfoFromFileA(
        LPCSTR                    pSrcFile,
        ID3DX10ThreadPump*        pPump,
        D3DX10IMAGE_INFO*         pSrcInfo);

HRESULT WINAPI
    D3DX10GetImageInfoFromFileW(
        LPCWSTR                   pSrcFile,
        ID3DX10ThreadPump*        pPump,
        D3DX10IMAGE_INFO*         pSrcInfo);

#ifdef UNICODE
#define D3DX10GetImageInfoFromFile D3DX10GetImageInfoFromFileW
#else
#define D3DX10GetImageInfoFromFile D3DX10GetImageInfoFromFileA
#endif


HRESULT WINAPI
    D3DX10GetImageInfoFromResourceA(
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        ID3DX10ThreadPump*        pPump,
        D3DX10IMAGE_INFO*         pSrcInfo);

HRESULT WINAPI
    D3DX10GetImageInfoFromResourceW(
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        ID3DX10ThreadPump*        pPump,
        D3DX10IMAGE_INFO*         pSrcInfo);

#ifdef UNICODE
#define D3DX10GetImageInfoFromResource D3DX10GetImageInfoFromResourceW
#else
#define D3DX10GetImageInfoFromResource D3DX10GetImageInfoFromResourceA
#endif


HRESULT WINAPI
    D3DX10GetImageInfoFromMemory(
        LPCVOID                   pSrcData,
        SIZE_T                    SrcDataSize,
        ID3DX10ThreadPump*        pPump,
        D3DX10IMAGE_INFO*         pSrcInfo);

//////////////////////////////////////////////////////////////////////////////
// Create/Save Texture APIs //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------
// D3DX10CreateTextureFromFile/Resource:
// D3DX10CreateShaderResourceViewFromFile/Resource:
// -----------------------------------
// Create a texture object from a file or resource.
//
// Parameters:
//
//  pDevice
//      The D3D device with which the texture is going to be used.
//  pSrcFile
//      File name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module
//  pvSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  Width, Height, Depth, Size
//      Size in pixels.  If zero or D3DX10_DEFAULT, the size will be taken from 
//      the file and rounded up to a power of two.  If D3DX10_DEFAULT_NONPOW2, 
//      and the device supports NONPOW2 textures, the size will not be rounded.
//      If D3DX10_FROM_FILE, the size will be taken exactly as it is in the file, 
//      and the call will fail if this violates device capabilities.
//  MipLevels
//      Number of mip levels.  If zero or D3DX10_DEFAULT, a complete mipmap
//      chain will be created.  If D3DX10_FROM_FILE, the size will be taken 
//      exactly as it is in the file, and the call will fail if this violates 
//      device capabilities.
//  Usage
//      Texture usage flags
//  Format
//      Desired pixel format. If DXGI_FORMAT_FROM_FILE, the format will be taken
//      exactly as it is in the file, and the call will fail if the device does
//      not support the given format.
//  Filter
//      D3DX10_FILTER flags controlling how the image is filtered.
//      Or D3DX10_DEFAULT for D3DX10_FILTER_TRIANGLE.
//  MipFilter
//      D3DX10_FILTER flags controlling how each miplevel is filtered.
//      Or D3DX10_DEFAULT for D3DX10_FILTER_BOX,
//  pSrcInfo
//      Pointer to a D3DX10IMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file, or NULL.
//  ppResource
//      Resource object created
//  ppShaderResourceView
//      Shader resource view object created
//
//----------------------------------------------------------------------------


// FromFile

HRESULT WINAPI
    D3DX10CreateShaderResourceViewFromFileA(
        ID3D10Device*               pDevice,
        LPCSTR                      pSrcFile,
        D3DX10IMAGE_LOAD_INFO      *pLoadInfo,
        ID3DX10ThreadPump*          pPump,
        ID3D10ShaderResourceView**  ppTexture);

HRESULT WINAPI
    D3DX10CreateShaderResourceViewFromFileW(
        ID3D10Device*               pDevice,
        LPCWSTR                     pSrcFile,
        D3DX10IMAGE_LOAD_INFO      *pLoadInfo,
        ID3DX10ThreadPump*          pPump,
        ID3D10ShaderResourceView**  ppTexture);

#ifdef UNICODE
#define D3DX10CreateShaderResourceViewFromFile D3DX10CreateShaderResourceViewFromFileW
#else
#define D3DX10CreateShaderResourceViewFromFile D3DX10CreateShaderResourceViewFromFileA
#endif

HRESULT WINAPI
    D3DX10CreateTextureFromFileA(
        ID3D10Device*               pDevice,
        LPCSTR                      pSrcFile,
        D3DX10IMAGE_LOAD_INFO      *pLoadInfo,
        ID3DX10ThreadPump*          pPump,
        ID3D10Resource**            ppTexture);

HRESULT WINAPI
    D3DX10CreateTextureFromFileW(
        ID3D10Device*               pDevice,
        LPCWSTR                     pSrcFile,
        D3DX10IMAGE_LOAD_INFO      *pLoadInfo,
        ID3DX10ThreadPump*          pPump,
        ID3D10Resource**            ppTexture);

#ifdef UNICODE
#define D3DX10CreateTextureFromFile D3DX10CreateTextureFromFileW
#else
#define D3DX10CreateTextureFromFile D3DX10CreateTextureFromFileA
#endif

// FromResource (resources in dll/exes)

HRESULT WINAPI
    D3DX10CreateShaderResourceViewFromResourceA(
        ID3D10Device*              pDevice,
        HMODULE                    hSrcModule,
        LPCSTR                     pSrcResource,
        D3DX10IMAGE_LOAD_INFO     *pLoadInfo,
        ID3DX10ThreadPump*         pPump,
        ID3D10ShaderResourceView** ppShaderResourceView);

HRESULT WINAPI
    D3DX10CreateShaderResourceViewFromResourceW(
        ID3D10Device*             pDevice,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        D3DX10IMAGE_LOAD_INFO    *pLoadInfo,
        ID3DX10ThreadPump*        pPump,
        ID3D10ShaderResourceView** ppShaderResourceView);

#ifdef UNICODE
#define D3DX10CreateShaderResourceViewFromResource D3DX10CreateShaderResourceViewFromResourceW
#else
#define D3DX10CreateShaderResourceViewFromResource D3DX10CreateShaderResourceViewFromResourceA
#endif

HRESULT WINAPI
    D3DX10CreateTextureFromResourceA(
        ID3D10Device*            pDevice,
        HMODULE                  hSrcModule,
        LPCSTR                   pSrcResource,
        D3DX10IMAGE_LOAD_INFO   *pLoadInfo,  
        ID3DX10ThreadPump*       pPump,   
        ID3D10Resource**         ppTexture);

HRESULT WINAPI
    D3DX10CreateTextureFromResourceW(
        ID3D10Device*         pDevice,
        HMODULE               hSrcModule,
        LPCWSTR               pSrcResource,
        D3DX10IMAGE_LOAD_INFO      *pLoadInfo,
        ID3DX10ThreadPump*    pPump,
        ID3D10Resource**      ppTexture);

#ifdef UNICODE
#define D3DX10CreateTextureFromResource D3DX10CreateTextureFromResourceW
#else
#define D3DX10CreateTextureFromResource D3DX10CreateTextureFromResourceA
#endif


// FromFileInMemory

HRESULT WINAPI
    D3DX10CreateShaderResourceViewFromMemory(
        ID3D10Device*             pDevice,
        LPCVOID                   pSrcData,
        SIZE_T                    SrcDataSize,
        D3DX10IMAGE_LOAD_INFO    *pLoadInfo,
        ID3DX10ThreadPump*        pPump,        
        ID3D10ShaderResourceView** ppShaderResourceView);

HRESULT WINAPI
    D3DX10CreateTextureFromMemory(
        ID3D10Device*             pDevice,
        LPCVOID                   pSrcData,
        SIZE_T                    SrcDataSize,
        D3DX10IMAGE_LOAD_INFO    *pLoadInfo,    
        ID3DX10ThreadPump*        pPump,    
        ID3D10Resource**          ppTexture);


//----------------------------------------------------------------------------
// D3DX10SaveTextureToFile:
// ----------------------
// Save a texture to a file.
//
// Parameters:
//  pDestFile
//      File name of the destination file
//  DestFormat
//      D3DX10IMAGE_FILEFORMAT specifying file format to use when saving.
//  pSrcTexture
//      Source texture, containing the image to be saved
//
//----------------------------------------------------------------------------


HRESULT WINAPI
    D3DX10SaveTextureToFileA(
        ID3D10Resource            *pSrcTexture,
        D3DX10IMAGE_FILEFORMAT    DestFormat,
        LPCSTR                    pDestFile);

HRESULT WINAPI
    D3DX10SaveTextureToFileW(
        ID3D10Resource            *pSrcTexture,
        D3DX10IMAGE_FILEFORMAT    DestFormat,
        LPCWSTR                   pDestFile);

#ifdef UNICODE
#define D3DX10SaveTextureToFile D3DX10SaveTextureToFileW
#else
#define D3DX10SaveTextureToFile D3DX10SaveTextureToFileA
#endif

//----------------------------------------------------------------------------
// D3DX10SaveTextureToMemory:
// ----------------------
// Save a texture to a file.
//
// Parameters:
//  ppDestBuf
//      address of a d3dxbuffer pointer to return the image data
//  DestFormat
//      D3DX10IMAGE_FILEFORMAT specifying file format to use when saving.
//  pSrcTexture
//      Source texture, containing the image to be saved
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DX10SaveTextureToMemory(
        ID3D10Resource            *pSrcTexture,
        D3DX10IMAGE_FILEFORMAT      DestFormat,
        LPD3D10BLOB*                ppDestBuf);


//----------------------------------------------------------------------------
// D3DX10ComputeNormalMap:
// ---------------------
// Converts a height map into a normal map.  The (x,y,z) components of each
// normal are mapped to the (r,g,b) channels of the output texture.
//
// Parameters
//  pSrcTexture
//      Pointer to the source heightmap texture 
//  Flags
//      D3DX10_NORMALMAP flags
//  Channel
//      D3DX10_CHANNEL specifying source of height information
//  Amplitude
//      The constant value which the height information is multiplied by.
//  pDestTexture
//      Pointer to the destination texture
//---------------------------------------------------------------------------

HRESULT WINAPI
    D3DX10ComputeNormalMap(
        ID3D10Texture2D		     *pSrcTexture,
        UINT                      Flags,
        UINT                      Channel,
        FLOAT                     Amplitude,
        ID3D10Texture2D		     *pDestTexture);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX10TEX_H__

