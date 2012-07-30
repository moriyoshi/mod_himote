/*
  +----------------------------------------------------------------------+
  | HIMOTE Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The HIMOTE Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the HIMOTE license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.himote.net/license/3_01.txt                                  |
  | If you did not receive a copy of the HIMOTE license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_COMPAT_H
#define HIMOTE_COMPAT_H

#ifdef HIMOTE_WIN32
#include "config.w32.h"
#else
#include <himote_config.h>
#endif

#if defined(HAVE_BUNDLED_PCRE) || !defined(HIMOTE_VERSION)
#define pcre_compile			himote_pcre_compile
#define pcre_compile2			himote_pcre_compile2
#define pcre_copy_substring		himote_pcre_copy_substring
#define pcre_exec			himote_pcre_exec
#define pcre_get_substring		himote_pcre_get_substring
#define pcre_get_substring_list		himote_pcre_get_substring_list
#define pcre_maketables			himote_pcre_maketables
#define pcre_study			himote_pcre_study
#define pcre_version			himote_pcre_version
#define pcre_fullinfo			himote_pcre_fullinfo
#define pcre_free			himote_pcre_free
#define pcre_malloc			himote_pcre_malloc
#define pcre_config			himote_pcre_config
#define pcre_copy_named_substring	himote_pcre_copy_named_substring
#define pcre_free_substring		himote_pcre_free_substring
#define pcre_free_substring_list	himote_pcre_free_substring_list
#define pcre_get_named_substring	himote_pcre_get_named_substring
#define pcre_get_stringnumber		himote_pcre_get_stringnumber
#define pcre_refcount			himote_pcre_refcount
#define _pcre_ord2utf8			himote__pcre_ord2utf8
#define _pcre_try_flipped		himote__pcre_try_flipped
#define _pcre_valid_utf8		himote__pcre_valid_utf8
#define _pcre_xclass			himote__pcre_xclass
#define pcre_callout			himote_pcre_callout
#define _pcre_OP_lengths		himote__pcre_OP_lengths
#define _pcre_utt_names			himote__pcre_utt_names
#define _pcre_default_tables		himote__pcre_default_tables
#define pcre_get_stringtable_entries	himote_pcre_get_stringtable_entries
#define _pcre_is_newline		himote__pcre_is_newline
#define pcre_stack_free			himote_pcre_stack_free
#define pcre_stack_malloc		himote_pcre_stack_malloc
#define _pcre_utf8_table1		himote__pcre_utf8_table1
#define _pcre_utf8_table1_size		himote__pcre_utf8_table1_size
#define _pcre_utf8_table2		himote__pcre_utf8_table2
#define _pcre_utf8_table3		himote__pcre_utf8_table3
#define _pcre_utf8_table4		himote__pcre_utf8_table4
#define _pcre_utt			himote__pcre_utt
#define _pcre_utt_size			himote__pcre_utt_size
#define _pcre_was_newline		himote__pcre_was_newline
#define _pcre_ucd_records		himote__pcre_ucd_records
#define _pcre_ucd_stage1		himote__pcre_ucd_stage1
#define _pcre_ucd_stage2		himote__pcre_ucd_stage2
#define _pcre_ucp_gentype		himote__pcre_ucp_gentype
#endif

#define lookup				himote_lookup
#define hashTableInit		himote_hashTableInit
#define hashTableDestroy	himote_hashTableDestroy
#define hashTableIterInit	himote_hashTableIterInit
#define hashTableIterNext	himote_hashTableIterNext

#if defined(HAVE_LIBXML) && (defined(HAVE_XML) || defined(HAVE_XMLRPC)) && !defined(HAVE_LIBEXPAT)
#define XML_DefaultCurrent himote_XML_DefaultCurrent
#define XML_ErrorString himote_XML_ErrorString
#define XML_ExpatVersion himote_XML_ExpatVersion
#define XML_ExpatVersionInfo himote_XML_ExpatVersionInfo
#define XML_ExternalEntityParserCreate himote_XML_ExternalEntityParserCreate
#define XML_GetBase himote_XML_GetBase
#define XML_GetBuffer himote_XML_GetBuffer
#define XML_GetCurrentByteCount himote_XML_GetCurrentByteCount
#define XML_GetCurrentByteIndex himote_XML_GetCurrentByteIndex
#define XML_GetCurrentColumnNumber himote_XML_GetCurrentColumnNumber
#define XML_GetCurrentLineNumber himote_XML_GetCurrentLineNumber
#define XML_GetErrorCode himote_XML_GetErrorCode
#define XML_GetIdAttributeIndex himote_XML_GetIdAttributeIndex
#define XML_GetInputContext himote_XML_GetInputContext
#define XML_GetSpecifiedAttributeCount himote_XML_GetSpecifiedAttributeCount
#define XmlGetUtf16InternalEncodingNS himote_XmlGetUtf16InternalEncodingNS
#define XmlGetUtf16InternalEncoding himote_XmlGetUtf16InternalEncoding
#define XmlGetUtf8InternalEncodingNS himote_XmlGetUtf8InternalEncodingNS
#define XmlGetUtf8InternalEncoding himote_XmlGetUtf8InternalEncoding
#define XmlInitEncoding himote_XmlInitEncoding
#define XmlInitEncodingNS himote_XmlInitEncodingNS
#define XmlInitUnknownEncoding himote_XmlInitUnknownEncoding
#define XmlInitUnknownEncodingNS himote_XmlInitUnknownEncodingNS
#define XML_ParseBuffer himote_XML_ParseBuffer
#define XML_Parse himote_XML_Parse
#define XML_ParserCreate_MM himote_XML_ParserCreate_MM
#define XML_ParserCreateNS himote_XML_ParserCreateNS
#define XML_ParserCreate himote_XML_ParserCreate
#define XML_ParserFree himote_XML_ParserFree
#define XmlParseXmlDecl himote_XmlParseXmlDecl
#define XmlParseXmlDeclNS himote_XmlParseXmlDeclNS
#define XmlPrologStateInitExternalEntity himote_XmlPrologStateInitExternalEntity
#define XmlPrologStateInit himote_XmlPrologStateInit
#define XML_SetAttlistDeclHandler himote_XML_SetAttlistDeclHandler
#define XML_SetBase himote_XML_SetBase
#define XML_SetCdataSectionHandler himote_XML_SetCdataSectionHandler
#define XML_SetCharacterDataHandler himote_XML_SetCharacterDataHandler
#define XML_SetCommentHandler himote_XML_SetCommentHandler
#define XML_SetDefaultHandlerExpand himote_XML_SetDefaultHandlerExpand
#define XML_SetDefaultHandler himote_XML_SetDefaultHandler
#define XML_SetDoctypeDeclHandler himote_XML_SetDoctypeDeclHandler
#define XML_SetElementDeclHandler himote_XML_SetElementDeclHandler
#define XML_SetElementHandler himote_XML_SetElementHandler
#define XML_SetEncoding himote_XML_SetEncoding
#define XML_SetEndCdataSectionHandler himote_XML_SetEndCdataSectionHandler
#define XML_SetEndDoctypeDeclHandler himote_XML_SetEndDoctypeDeclHandler
#define XML_SetEndElementHandler himote_XML_SetEndElementHandler
#define XML_SetEndNamespaceDeclHandler himote_XML_SetEndNamespaceDeclHandler
#define XML_SetEntityDeclHandler himote_XML_SetEntityDeclHandler
#define XML_SetExternalEntityRefHandlerArg himote_XML_SetExternalEntityRefHandlerArg
#define XML_SetExternalEntityRefHandler himote_XML_SetExternalEntityRefHandler
#define XML_SetNamespaceDeclHandler himote_XML_SetNamespaceDeclHandler
#define XML_SetNotationDeclHandler himote_XML_SetNotationDeclHandler
#define XML_SetNotStandaloneHandler himote_XML_SetNotStandaloneHandler
#define XML_SetParamEntityParsing himote_XML_SetParamEntityParsing
#define XML_SetProcessingInstructionHandler himote_XML_SetProcessingInstructionHandler
#define XML_SetReturnNSTriplet himote_XML_SetReturnNSTriplet
#define XML_SetStartCdataSectionHandler himote_XML_SetStartCdataSectionHandler
#define XML_SetStartDoctypeDeclHandler himote_XML_SetStartDoctypeDeclHandler
#define XML_SetStartElementHandler himote_XML_SetStartElementHandler
#define XML_SetStartNamespaceDeclHandler himote_XML_SetStartNamespaceDeclHandler
#define XML_SetUnknownEncodingHandler himote_XML_SetUnknownEncodingHandler
#define XML_SetUnparsedEntityDeclHandler himote_XML_SetUnparsedEntityDeclHandler
#define XML_SetUserData himote_XML_SetUserData
#define XML_SetXmlDeclHandler himote_XML_SetXmlDeclHandler
#define XmlSizeOfUnknownEncoding himote_XmlSizeOfUnknownEncoding
#define XML_UseParserAsHandlerArg himote_XML_UseParserAsHandlerArg
#define XmlUtf16Encode himote_XmlUtf16Encode
#define XmlUtf8Encode himote_XmlUtf8Encode
#define XML_FreeContentModel himote_XML_FreeContentModel
#define XML_MemMalloc himote_XML_MemMalloc
#define XML_MemRealloc himote_XML_MemRealloc
#define XML_MemFree himote_XML_MemFree
#define XML_UseForeignDTD himote_XML_UseForeignDTD
#define XML_GetFeatureList himote_XML_GetFeatureList
#define XML_ParserReset himote_XML_ParserReset

#ifdef HAVE_GD_BUNDLED
#define any2eucjp himote_gd_any2eucjp
#define createwbmp himote_gd_createwbmp
#define empty_output_buffer himote_gd_empty_output_buffer
#define fill_input_buffer himote_gd_fill_input_buffer
#define freewbmp himote_gd_freewbmp
#define gdAlphaBlend himote_gd_gdAlphaBlend
#define gdCompareInt himote_gd_gdCompareInt
#define gdCosT himote_gd_gdCosT
#define gdCtxPrintf himote_gd_gdCtxPrintf
#define gdDPExtractData himote_gd_gdDPExtractData
#define gdFontGetGiant himote_gd_gdFontGetGiant
#define gdFontGetLarge himote_gd_gdFontGetLarge
#define gdFontGetMediumBold himote_gd_gdFontGetMediumBold
#define gdFontGetSmall himote_gd_gdFontGetSmall
#define gdFontGetTiny himote_gd_gdFontGetTiny
#define gdFontGiant himote_gd_gdFontGiant
#define gdFontGiantData himote_gd_gdFontGiantData
#define gdFontGiantRep himote_gd_gdFontGiantRep
#define gdFontLarge himote_gd_gdFontLarge
#define gdFontLargeData himote_gd_gdFontLargeData
#define gdFontLargeRep himote_gd_gdFontLargeRep
#define gdFontMediumBold himote_gd_gdFontMediumBold
#define gdFontMediumBoldData himote_gd_gdFontMediumBoldData
#define gdFontMediumBoldRep himote_gd_gdFontMediumBoldRep
#define gdFontSmall himote_gd_gdFontSmall
#define gdFontSmallData himote_gd_gdFontSmallData
#define gdFontSmallRep himote_gd_gdFontSmallRep
#define gdFontTiny himote_gd_gdFontTiny
#define gdFontTinyData himote_gd_gdFontTinyData
#define gdFontTinyRep himote_gd_gdFontTinyRep
#define gdGetBuf himote_gd_gdGetBuf
#define gdGetByte himote_gd_gdGetByte
#define gdGetC himote_gd_gdGetC
#define _gdGetColors himote_gd__gdGetColors
#define gd_getin himote_gd_gd_getin
#define gdGetInt himote_gd_gdGetInt
#define gdGetWord himote_gd_gdGetWord
#define gdImageAABlend himote_gd_gdImageAABlend
#define gdImageAALine himote_gd_gdImageAALine
#define gdImageAlphaBlending himote_gd_gdImageAlphaBlending
#define gdImageAntialias himote_gd_gdImageAntialias
#define gdImageArc himote_gd_gdImageArc
#define gdImageBrightness himote_gd_gdImageBrightness
#define gdImageChar himote_gd_gdImageChar
#define gdImageCharUp himote_gd_gdImageCharUp
#define gdImageColor himote_gd_gdImageColor
#define gdImageColorAllocate himote_gd_gdImageColorAllocate
#define gdImageColorAllocateAlpha himote_gd_gdImageColorAllocateAlpha
#define gdImageColorClosest himote_gd_gdImageColorClosest
#define gdImageColorClosestAlpha himote_gd_gdImageColorClosestAlpha
#define gdImageColorClosestHWB himote_gd_gdImageColorClosestHWB
#define gdImageColorDeallocate himote_gd_gdImageColorDeallocate
#define gdImageColorExact himote_gd_gdImageColorExact
#define gdImageColorExactAlpha himote_gd_gdImageColorExactAlpha
#define gdImageColorMatch himote_gd_gdImageColorMatch
#define gdImageColorResolve himote_gd_gdImageColorResolve
#define gdImageColorResolveAlpha himote_gd_gdImageColorResolveAlpha
#define gdImageColorTransparent himote_gd_gdImageColorTransparent
#define gdImageCompare himote_gd_gdImageCompare
#define gdImageContrast himote_gd_gdImageContrast
#define gdImageConvolution himote_gd_gdImageConvolution
#define gdImageCopy himote_gd_gdImageCopy
#define gdImageCopyMerge himote_gd_gdImageCopyMerge
#define gdImageCopyMergeGray himote_gd_gdImageCopyMergeGray
#define gdImageCopyResampled himote_gd_gdImageCopyResampled
#define gdImageCopyResized himote_gd_gdImageCopyResized
#define gdImageCreate himote_gd_gdImageCreate
#define gdImageCreateFromGd himote_gd_gdImageCreateFromGd
#define gdImageCreateFromGd2 himote_gd_gdImageCreateFromGd2
#define gdImageCreateFromGd2Ctx himote_gd_gdImageCreateFromGd2Ctx
#define gdImageCreateFromGd2Part himote_gd_gdImageCreateFromGd2Part
#define gdImageCreateFromGd2PartCtx himote_gd_gdImageCreateFromGd2PartCtx
#define gdImageCreateFromGd2PartPtr himote_gd_gdImageCreateFromGd2PartPtr
#define gdImageCreateFromGd2Ptr himote_gd_gdImageCreateFromGd2Ptr
#define gdImageCreateFromGdCtx himote_gd_gdImageCreateFromGdCtx
#define gdImageCreateFromGdPtr himote_gd_gdImageCreateFromGdPtr
#define gdImageCreateFromGif himote_gd_gdImageCreateFromGif
#define gdImageCreateFromGifCtx himote_gd_gdImageCreateFromGifCtx
#define gdImageCreateFromGifSource himote_gd_gdImageCreateFromGifSource
#define gdImageCreateFromJpeg himote_gd_gdImageCreateFromJpeg
#define gdImageCreateFromJpegCtx himote_gd_gdImageCreateFromJpegCtx
#define gdImageCreateFromJpegPtr himote_gd_gdImageCreateFromJpegPtr
#define gdImageCreateFromPng himote_gd_gdImageCreateFromPng
#define gdImageCreateFromPngCtx himote_gd_gdImageCreateFromPngCtx
#define gdImageCreateFromPngPtr himote_gd_gdImageCreateFromPngPtr
#define gdImageCreateFromPngSource himote_gd_gdImageCreateFromPngSource
#define gdImageCreateFromWBMP himote_gd_gdImageCreateFromWBMP
#define gdImageCreateFromWBMPCtx himote_gd_gdImageCreateFromWBMPCtx
#define gdImageCreateFromWBMPPtr himote_gd_gdImageCreateFromWBMPPtr
#define gdImageCreateFromXbm himote_gd_gdImageCreateFromXbm
#define gdImageCreatePaletteFromTrueColor himote_gd_gdImageCreatePaletteFromTrueColor
#define gdImageCreateTrueColor himote_gd_gdImageCreateTrueColor
#define gdImageDashedLine himote_gd_gdImageDashedLine
#define gdImageDestroy himote_gd_gdImageDestroy
#define gdImageEdgeDetectQuick himote_gd_gdImageEdgeDetectQuick
#define gdImageEllipse himote_gd_gdImageEllipse
#define gdImageEmboss himote_gd_gdImageEmboss
#define gdImageFill himote_gd_gdImageFill
#define gdImageFilledArc himote_gd_gdImageFilledArc
#define gdImageFilledEllipse himote_gd_gdImageFilledEllipse
#define gdImageFilledPolygon himote_gd_gdImageFilledPolygon
#define gdImageFilledRectangle himote_gd_gdImageFilledRectangle
#define _gdImageFillTiled himote_gd__gdImageFillTiled
#define gdImageFillToBorder himote_gd_gdImageFillToBorder
#define gdImageGaussianBlur himote_gd_gdImageGaussianBlur
#define gdImageGd himote_gd_gdImageGd
#define gdImageGd2 himote_gd_gdImageGd2
#define gdImageGd2Ptr himote_gd_gdImageGd2Ptr
#define gdImageGdPtr himote_gd_gdImageGdPtr
#define gdImageGetClip himote_gd_gdImageGetClip
#define gdImageGetPixel himote_gd_gdImageGetPixel
#define gdImageGetTrueColorPixel himote_gd_gdImageGetTrueColorPixel
#define gdImageGif himote_gd_gdImageGif
#define gdImageGifCtx himote_gd_gdImageGifCtx
#define gdImageGifPtr himote_gd_gdImageGifPtr
#define gdImageGrayScale himote_gd_gdImageGrayScale
#define gdImageInterlace himote_gd_gdImageInterlace
#define gdImageJpeg himote_gd_gdImageJpeg
#define gdImageJpegCtx himote_gd_gdImageJpegCtx
#define gdImageJpegPtr himote_gd_gdImageJpegPtr
#define gdImageLine himote_gd_gdImageLine
#define gdImageMeanRemoval himote_gd_gdImageMeanRemoval
#define gdImageNegate himote_gd_gdImageNegate
#define gdImagePaletteCopy himote_gd_gdImagePaletteCopy
#define gdImagePng himote_gd_gdImagePng
#define gdImagePngCtx himote_gd_gdImagePngCtx
#define gdImagePngCtxEx himote_gd_gdImagePngCtxEx
#define gdImagePngEx himote_gd_gdImagePngEx
#define gdImagePngPtr himote_gd_gdImagePngPtr
#define gdImagePngPtrEx himote_gd_gdImagePngPtrEx
#define gdImagePngToSink himote_gd_gdImagePngToSink
#define gdImagePolygon himote_gd_gdImagePolygon
#define gdImageRectangle himote_gd_gdImageRectangle
#define gdImageRotate himote_gd_gdImageRotate
#define gdImageRotate180 himote_gd_gdImageRotate180
#define gdImageRotate270 himote_gd_gdImageRotate270
#define gdImageRotate45 himote_gd_gdImageRotate45
#define gdImageRotate90 himote_gd_gdImageRotate90
#define gdImageSaveAlpha himote_gd_gdImageSaveAlpha
#define gdImageSelectiveBlur himote_gd_gdImageSelectiveBlur
#define gdImageSetAntiAliased himote_gd_gdImageSetAntiAliased
#define gdImageSetAntiAliasedDontBlend himote_gd_gdImageSetAntiAliasedDontBlend
#define gdImageSetBrush himote_gd_gdImageSetBrush
#define gdImageSetClip himote_gd_gdImageSetClip
#define gdImageSetPixel himote_gd_gdImageSetPixel
#define gdImageSetStyle himote_gd_gdImageSetStyle
#define gdImageSetThickness himote_gd_gdImageSetThickness
#define gdImageSetTile himote_gd_gdImageSetTile
#define gdImageSkewX himote_gd_gdImageSkewX
#define gdImageSkewY himote_gd_gdImageSkewY
#define gdImageSmooth himote_gd_gdImageSmooth
#define gdImageString himote_gd_gdImageString
#define gdImageString16 himote_gd_gdImageString16
#define gdImageStringFT himote_gd_gdImageStringFT
#define gdImageStringFTEx himote_gd_gdImageStringFTEx
#define gdImageStringTTF himote_gd_gdImageStringTTF
#define gdImageStringUp himote_gd_gdImageStringUp
#define gdImageStringUp16 himote_gd_gdImageStringUp16
#define gdImageTrueColorToPalette himote_gd_gdImageTrueColorToPalette
#define gdImageWBMP himote_gd_gdImageWBMP
#define gdImageWBMPCtx himote_gd_gdImageWBMPCtx
#define gdImageWBMPPtr himote_gd_gdImageWBMPPtr
#define gdImageXbmCtx himote_gd_gdImageXbmCtx
#define gdNewDynamicCtx himote_gd_gdNewDynamicCtx
#define gdNewDynamicCtxEx himote_gd_gdNewDynamicCtxEx
#define gdNewFileCtx himote_gd_gdNewFileCtx
#define gdNewSSCtx himote_gd_gdNewSSCtx
#define gdPutBuf himote_gd_gdPutBuf
#define gdPutC himote_gd_gdPutC
#define _gdPutColors himote_gd__gdPutColors
#define gdPutInt himote_gd_gdPutInt
#define gd_putout himote_gd_gd_putout
#define gdPutWord himote_gd_gdPutWord
#define gdSeek himote_gd_gdSeek
#define gdSinT himote_gd_gdSinT
#define gd_strtok_r himote_gd_gd_strtok_r
#define gdTell himote_gd_gdTell
#define getmbi himote_gd_getmbi
#define init_destination himote_gd_init_destination
#define init_source himote_gd_init_source
#define jpeg_gdIOCtx_dest himote_gd_jpeg_gdIOCtx_dest
#define jpeg_gdIOCtx_src himote_gd_jpeg_gdIOCtx_src
#define lsqrt himote_gd_lsqrt
#define printwbmp himote_gd_printwbmp
#define Putchar himote_gd_Putchar
#define putmbi himote_gd_putmbi
#define Putword himote_gd_Putword
#define readwbmp himote_gd_readwbmp
#define skipheader himote_gd_skipheader
#define skip_input_data himote_gd_skip_input_data
#define term_destination himote_gd_term_destination
#define term_source himote_gd_term_source
#define writewbmp himote_gd_writewbmp
#define ZeroDataBlock himote_gd_ZeroDataBlock
#define gdCacheCreate himote_gd_gdCacheCreate
#define gdCacheDelete himote_gd_gdCacheDelete
#define gdCacheGet himote_gd_gdCacheGet
#define gdFontCacheSetup himote_gd_gdFontCacheSetup
#define gdFontCacheShutdown himote_gd_gdFontCacheShutdown
#define gdFreeFontCache himote_gd_gdFreeFontCache
#endif /* HAVE_GD_BUNDLED */

/* Define to specify how much context to retain around the current parse
   point. */
#define XML_CONTEXT_BYTES 1024

/* Define to make parameter entity parsing functionality available. */
#define XML_DTD 1

/* Define to make XML Namespaces functionality available. */
#define XML_NS 1
#endif

#ifdef HIMOTE_EXPORTS
#define PCRE_STATIC
#endif

#endif
