project (Barcode LANGUAGES CXX)

#=======================================
# Handle optional dependencies
#=======================================
if (${GNUBARCODE_FOUND})
  add_definitions (-DHAVE_GNU_BARCODE=1)
  set (OPTIONAL_GNUBARCODE GNU::BARCODE)
else ()
  set (OPTIONAL_GNUBARCODE "")
endif ()

if (${LIBQRENCODE_FOUND})
  add_definitions (-DHAVE_QRENCODE=1)
  set (OPTIONAL_QRENCODE QRENCODE::QRENCODE)
else ()
  set (OPTIONAL_QRENCODE "")
endif ()

if (${LIBZINT_FOUND})
  add_definitions (-DHAVE_ZINT=1)
  set (OPTIONAL_ZINT ZINT::ZINT)
else ()
  set (OPTIONAL_ZINT "")
endif ()

if (${PNG_FOUND})
  add_definitions (-DHAVE_PNG=1)
  set (OPTIONAL_PNG PNG::PNG)
else ()
  set (OPTIONAL_PNG "")
endif ()

#=======================================
# Sources
#=======================================
set (barcode_sources
  Backends.cpp
  Style.cpp
  GnuBarcode.cpp
  QrEncode.cpp
  Zint.cpp
)

set (barcode_qobject_headers
  Backends.h
)

qt5_wrap_cpp (barcode_moc_sources ${barcode_qobject_headers})

#=====================================
# Target
#=====================================
add_library (Barcode STATIC
  ${barcode_sources}
  ${barcode_moc_sources}
)

#target_compile_features (Barcode
#  PUBLIC cxx_std_11
#)
set_property (TARGET Barcode PROPERTY CXX_STANDARD 11)

target_include_directories (Barcode
  PUBLIC ..
)

target_link_libraries (Barcode
  glbarcode
  Qt5::Core
  ${OPTIONAL_GNUBARCODE}
  ${OPTIONAL_PNG}
  ${OPTIONAL_ZINT}
  ${OPTIONAL_QRENCODE}
)
