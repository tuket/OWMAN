FILE(REMOVE_RECURSE
  "CMakeFiles/HelloWorld.dir/HelloWorld.cpp.o"
  "HelloWorld.pdb"
  "HelloWorld"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/HelloWorld.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
