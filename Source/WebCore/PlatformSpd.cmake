LIST(APPEND WebCore_LINK_FLAGS
    ${ECORE_X_LDFLAGS}
    ${SPDDEPS_LDFLAGS}
)

LIST(APPEND WebCore_INCLUDE_DIRECTORIES
  "${JAVASCRIPTCORE_DIR}/wtf/gobject"
#  "${WEBCORE_DIR}/accessibility/efl"
  "${WEBCORE_DIR}/page/spd"
#  "${WEBCORE_DIR}/platform/efl"
  "${WEBCORE_DIR}/platform/graphics/spd"
#  "${WEBCORE_DIR}/platform/network/soup"
  "${WEBCORE_DIR}/platform/network/curl"
  "${WEBCORE_DIR}/platform/text/spd"
#  "${WEBCORE_DIR}/plugins/efl"
#  "${WEBKIT_DIR}/efl/WebCoreSupport"
#  "${WEBKIT_DIR}/efl/ewk"
)

LIST(APPEND WebCore_SOURCES
#  accessibility/efl/AccessibilityObjectEfl.cpp
  bindings/js/ScriptControllerEfl.cpp
  page/spd/DragControllerSpd.cpp
  page/spd/EventHandlerSpd.cpp
  platform/Cursor.cpp
  platform/graphics/ImageSource.cpp
  platform/spd/RenderThemeSpd.cpp
  platform/spd/CursorSpd.cpp
  platform/spd/ClipboardSpd.cpp
  platform/spd/DragDataSpd.cpp
  platform/spd/EditorSpd.cpp
  platform/spd/KURLSpd.cpp
  platform/spd/MIMETypeRegistrySpd.cpp
  platform/spd/PasteboardSpd.cpp
  platform/spd/PlatformKeyboardEventSpd.cpp
  platform/spd/ScrollbarThemeSpd.cpp
  platform/spd/SharedBufferSpd.cpp
  platform/spd/WidgetSpd.cpp
  platform/spd/LocalizedStringsSpd.cpp
  platform/spd/DragImageSpd.cpp
  platform/spd/FileSystemSpd.cpp
  platform/spd/SSLKeyGeneratorSpd.cpp
  platform/spd/LanguageSpd.cpp
  platform/spd/PlatformScreenSpd.cpp
  platform/spd/SharedTimerSpd.cpp
  platform/spd/SoundSpd.cpp
  platform/spd/SystemTimeSpd.cpp
  #platform/spd/VirtualUser.cpp
  #platform/spd/EventLoopSpd.cpp
  platform/spd/SEvent.cpp
  platform/graphics/spd/GraphicsContextSpd.cpp
  platform/graphics/spd/ImageBufferSpd.cpp
  platform/graphics/spd/BitmapImageSpd.cpp
  platform/graphics/spd/PathSpd.cpp
  platform/graphics/spd/FontSpd.cpp
  platform/graphics/spd/FontCacheSpd.cpp
  platform/graphics/spd/FontPlatformDataSpd.cpp
  platform/graphics/spd/FontCustomPlatformData.cpp
  platform/graphics/spd/GlyphPageSpd.cpp
  platform/graphics/spd/GradientSpd.cpp
  platform/graphics/spd/IconSpd.cpp
  platform/graphics/spd/ImageSpd.cpp
  platform/graphics/spd/SimpleFontDataSpd.cpp
  platform/image-decoders/ImageDecoder.cpp
  platform/image-decoders/bmp/BMPImageDecoder.cpp
  platform/image-decoders/bmp/BMPImageReader.cpp
  platform/image-decoders/gif/GIFImageDecoder.cpp
  platform/image-decoders/gif/GIFImageReader.cpp
  platform/image-decoders/ico/ICOImageDecoder.cpp
  platform/image-decoders/jpeg/JPEGImageDecoder.cpp
  platform/image-decoders/png/PNGImageDecoder.cpp
  platform/image-decoders/webp/WEBPImageDecoder.cpp
  platform/network/curl/CookieJarCurl.cpp
  platform/network/curl/CredentialStorageCurl.cpp
  platform/network/curl/DNSCurl.cpp
  platform/network/curl/FormDataStreamCurl.cpp
  platform/network/curl/ProxyServerCurl.cpp
  platform/network/curl/ResourceHandleCurl.cpp
  platform/network/curl/ResourceHandleManager.cpp
  platform/network/curl/SocketStreamHandleCurl.cpp
  platform/posix/FileSystemPOSIX.cpp
  platform/text/spd/TextBreakIteratorInternalICUSpd.cpp
)

IF (ENABLE_NETSCAPE_PLUGIN_API)
  LIST(APPEND WebCore_SOURCES
    plugins/PluginDatabase.cpp
    plugins/PluginDebug.cpp
    plugins/PluginPackage.cpp
    plugins/PluginStream.cpp
    plugins/PluginView.cpp

    plugins/efl/PluginDataEfl.cpp
    plugins/efl/PluginPackageEfl.cpp
    plugins/efl/PluginViewEfl.cpp
  )
ELSE ()
  LIST(APPEND WebCore_SOURCES
    plugins/PluginDataNone.cpp
    plugins/PluginPackageNone.cpp
    plugins/PluginViewNone.cpp
  )
ENDIF ()

LIST(APPEND WebCore_USER_AGENT_STYLE_SHEETS
    ${WEBCORE_DIR}/css/mediaControlsEfl.css
)

IF (WTF_USE_CAIRO)
  LIST(APPEND WebCore_INCLUDE_DIRECTORIES
    "${WEBCORE_DIR}/platform/cairo"
    "${WEBCORE_DIR}/platform/graphics/cairo"
  )
  LIST(APPEND WebCore_SOURCES
    platform/cairo/WidgetBackingStoreCairo.cpp
    platform/graphics/cairo/CairoUtilities.cpp
    platform/graphics/cairo/FontCairo.cpp
    platform/graphics/cairo/GradientCairo.cpp
    platform/graphics/cairo/GraphicsContextCairo.cpp
    platform/graphics/cairo/ImageBufferCairo.cpp
    platform/graphics/cairo/ImageCairo.cpp
    platform/graphics/cairo/OwnPtrCairo.cpp
    platform/graphics/cairo/PathCairo.cpp
    platform/graphics/cairo/PatternCairo.cpp
    platform/graphics/cairo/PlatformContextCairo.cpp
    platform/graphics/cairo/PlatformPathCairo.cpp
    platform/graphics/cairo/RefPtrCairo.cpp
    platform/graphics/cairo/TransformationMatrixCairo.cpp

    platform/image-decoders/cairo/ImageDecoderCairo.cpp
  )

  IF (WTF_USE_FREETYPE)
    LIST(APPEND WebCore_INCLUDE_DIRECTORIES
      "${WEBCORE_DIR}/platform/graphics/freetype"
    )
    LIST(APPEND WebCore_SOURCES
      platform/graphics/WOFFFileFormat.cpp
      platform/graphics/efl/FontEfl.cpp
      platform/graphics/freetype/FontCacheFreeType.cpp
      platform/graphics/freetype/FontCustomPlatformDataFreeType.cpp
      platform/graphics/freetype/FontPlatformDataFreeType.cpp
      platform/graphics/freetype/GlyphPageTreeNodeFreeType.cpp
      platform/graphics/freetype/SimpleFontDataFreeType.cpp
    )
    LIST(APPEND WebCore_LIBRARIES
      ${ZLIB_LIBRARIES}
    )
  ENDIF ()

  IF (WTF_USE_PANGO)
    LIST(APPEND WebCore_INCLUDE_DIRECTORIES
      "${WEBCORE_DIR}/platform/graphics/pango"
      ${Pango_INCLUDE_DIRS}
    )
    LIST(APPEND WebCore_SOURCES
      platform/graphics/pango/FontPango.cpp
      platform/graphics/pango/FontCachePango.cpp
      platform/graphics/pango/FontCustomPlatformDataPango.cpp
      platform/graphics/pango/FontPlatformDataPango.cpp
      platform/graphics/pango/GlyphPageTreeNodePango.cpp
      platform/graphics/pango/SimpleFontDataPango.cpp
      platform/graphics/pango/PangoUtilities.cpp
    )
    LIST(APPEND WebCore_LIBRARIES
      ${Pango_LIBRARY}
      ${Pango_Cairo_LIBRARY}
    )
  ENDIF ()
ENDIF ()

IF (WTF_USE_ICU_UNICODE)
  LIST(APPEND WebCore_SOURCES
    editing/SmartReplaceICU.cpp
    platform/text/TextEncodingDetectorICU.cpp
    platform/text/TextBreakIteratorICU.cpp
    platform/text/TextCodecICU.cpp
  )
ENDIF ()

IF (ENABLE_GEOLOCATION)
  LIST(APPEND WebCore_SOURCES
    platform/efl/GeolocationServiceEfl.cpp
  )
ENDIF()

IF (ENABLE_VIDEO)
  LIST(APPEND WebCore_INCLUDE_DIRECTORIES
    "${WEBCORE_DIR}/platform/graphics/gstreamer"
  )
  LIST(APPEND WebCore_SOURCES
    platform/graphics/gstreamer/GRefPtrGStreamer.cpp
    platform/graphics/gstreamer/GStreamerGWorld.cpp
    platform/graphics/gstreamer/ImageGStreamerCairo.cpp
    platform/graphics/gstreamer/MediaPlayerPrivateGStreamer.cpp
    platform/graphics/gstreamer/PlatformVideoWindowEfl.cpp
    platform/graphics/gstreamer/VideoSinkGStreamer.cpp
    platform/graphics/gstreamer/WebKitWebSourceGStreamer.cpp
  )
ENDIF ()

LIST(APPEND WebCore_LIBRARIES
#  ${Cairo_LIBRARIES}
  ${ECORE_X_LIBRARIES}
  ${SPDDEPS_LIBRARIES}
#  ${EVAS_LIBRARIES}
  ${FREETYPE_LIBRARIES}
  ${ICU_LIBRARIES}
  ${LIBXML2_LIBRARIES}
#  ${LIBXSLT_LIBRARIES}
  ${SQLITE_LIBRARIES}
  ${Glib_LIBRARIES}
#  ${LIBSOUP24_LIBRARIES}
)

IF (ENABLE_VIDEO)
  LIST(APPEND WebCore_LIBRARIES
    ${GStreamer-App_LIBRARIES}
    ${GStreamer-Interfaces_LIBRARIES}
    ${GStreamer-Pbutils_LIBRARIES}
    ${GStreamer-Video_LIBRARIES}
  )
ENDIF ()

LIST(APPEND WebCore_INCLUDE_DIRECTORIES
#  ${Cairo_INCLUDE_DIRS}
  ${ECORE_X_INCLUDE_DIRS}
  ${SPDDEPS_INCLUDE_DIRS}
#  ${EVAS_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS}
  ${ICU_INCLUDE_DIRS}
  ${LIBXML2_INCLUDE_DIR}
#  ${LIBXSLT_INCLUDE_DIR}
  ${SQLITE_INCLUDE_DIR}
  ${Glib_INCLUDE_DIRS}
#  ${LIBSOUP24_INCLUDE_DIRS}
)

IF (ENABLE_VIDEO)
  LIST(APPEND WebCore_INCLUDE_DIRECTORIES
    ${GStreamer-App_INCLUDE_DIRS}
    ${GStreamer-Interfaces_INCLUDE_DIRS}
    ${GStreamer-Pbutils_INCLUDE_DIRS}
    ${GStreamer-Video_INCLUDE_DIRS}
  )
ENDIF ()

IF (ENABLE_WEBGL)
  LIST(APPEND WebCore_INCLUDE_DIRECTORIES
    ${OPENGL_INCLUDE_DIR}
    "${WEBCORE_DIR}/platform/graphics/cairo"
    "${WEBCORE_DIR}/platform/graphics/glx"
    "${WEBCORE_DIR}/platform/graphics/opengl"
  )
  LIST(APPEND WebCore_LIBRARIES
    ${OPENGL_gl_LIBRARY}
  )
  LIST(APPEND WebCore_SOURCES
    platform/graphics/cairo/DrawingBufferCairo.cpp
    platform/graphics/cairo/GraphicsContext3DCairo.cpp
    platform/graphics/glx/GraphicsContext3DPrivate.cpp
    platform/graphics/OpenGLShims.cpp
    platform/graphics/opengl/Extensions3DOpenGL.cpp
    platform/graphics/opengl/GraphicsContext3DOpenGL.cpp
    platform/graphics/opengl/GraphicsContext3DOpenGLCommon.cpp
  )
ENDIF ()

ADD_DEFINITIONS(-DWTF_USE_CROSS_PLATFORM_CONTEXT_MENUS=1
                -DDATA_DIR="${CMAKE_INSTALL_PREFIX}/${DATA_INSTALL_DIR}")
