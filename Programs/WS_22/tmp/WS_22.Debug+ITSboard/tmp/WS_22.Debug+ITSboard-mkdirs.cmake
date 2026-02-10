# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/WS_22.Debug+ITSboard"
  "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/1"
  "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/WS_22.Debug+ITSboard"
  "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/WS_22.Debug+ITSboard/tmp"
  "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/WS_22.Debug+ITSboard/src/WS_22.Debug+ITSboard-stamp"
  "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/WS_22.Debug+ITSboard/src"
  "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/WS_22.Debug+ITSboard/src/WS_22.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/WS_22.Debug+ITSboard/src/WS_22.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/sawil/Uni_Programme/Repositorys/ML_GSP_VSC_KRF/Programs/WS_22/tmp/WS_22.Debug+ITSboard/src/WS_22.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
