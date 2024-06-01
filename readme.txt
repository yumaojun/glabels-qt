1. update D:\Projects\GitHub\glabels-qt\model\StrUtil.cpp
2. 引入第三方头文件和库
 include_directories ("/dir/..") # 引入头文件目录
 link_directories ("/../..") # 引入库目录
 link_libraries ("/../../xxx.so")
3. 指定项目，引入第三方头文件和库
 target_link_directoryes (指定项目 ...)
 target_link_libraries (指定项目 库文件 ...)
4. mark_as_advanced表示把变量标记为高级选项，使得在CMake GUI中默认隐藏
 mark_as_advanced(LIBZINT_INCLUDE_DIR LIBZINT_LIBRARY)

引入一个第三方库的步骤：
1. 需要有一个FindXXX.cmake文件
 FindPNG.cmake、FindZLIB.cmake
 其中会设置变量
 PNG::PNG
 ZLIB::ZLIB
2. 然后在主文件CMakeLists.txt
 find_package (ZLIB)
3. 在对应项目Model的cmake文件中：
 if (${ZLIB_FOUND})
  add_definitions (-DHAVE_ZLIB=1)
  set (OPTIONAL_ZLIB ZLIB::ZLIB)
else ()
  set (OPTIONAL_ZLIB "")
endif ()
4. 然后引入库
target_link_libraries (Model
  Barcode
  Merge
  Qt5::Core
  Qt5::PrintSupport
  Qt5::Xml
  Qt5::Svg
  ${OPTIONAL_ZLIB}
)
