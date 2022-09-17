# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (DCSS_project)

# Create a sources variable with a link to all cpp files to compile
set (dcss_capture_sou 
        src/main/main_DCSS_capture.cpp
        src/PckCap/CPckCap.cpp
        src/other/bit_conversion.cpp
)

set (dcss_pcap_Sou
    src/main/main_DCSS_pcap.cpp
    src/other/bit_conversion.cpp
)

set (mix_pcap_sou 
    src/tools/MixPcaps.cpp
    src/tools/PcapFile.cpp
    src/tools/main_MixPcap.cpp
)

set (split_sequ_pcap_sou 
    src/tools/main_SplitSquPcap.cpp
)
# Add an executable with the above sources
add_executable(DCSS_pcap ${dcss_pcap_Sou})
add_executable(tools.mix_pcap ${mix_pcap_sou})
add_executable(tools.split_sequ_pcap ${split_sequ_pcap_sou})

target_include_directories(DCSS_pcap PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(tools.mix_pcap PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(tools.split_sequ_pcap PRIVATE ${PROJECT_SOURCE_DIR}/include)

IF (WIN32)
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_win/libCsvStorage.a)
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_win/liblibconfig++.dll.a )
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_win/libSketchPoolSE.a ) 
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_win/libPcapSE.a)
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_win/libPacketSE.a)
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_win/libHashSE.a)
    
        target_link_libraries(tools.mix_pcap ${PROJECT_SOURCE_DIR}/lib_win/liblibconfig++.dll.a )
        target_link_libraries(tools.mix_pcap ${PROJECT_SOURCE_DIR}/lib_win/libPcapSE.a )
        target_link_libraries(tools.mix_pcap ${PROJECT_SOURCE_DIR}/lib_win/libPacketSE.a )

        target_link_libraries(tools.split_sequ_pcap ${PROJECT_SOURCE_DIR}/lib_win/liblibconfig++.dll.a )
        target_link_libraries(tools.split_sequ_pcap ${PROJECT_SOURCE_DIR}/lib_win/libPcapSE.a )
        target_link_libraries(tools.split_sequ_pcap ${PROJECT_SOURCE_DIR}/lib_win/libPacketSE.a )
ELSEIF (UNIX)
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libCsvStorage.a)
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libconfig++.so )
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libSketchPoolSE.a ) 
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libPcapSE.a)
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libPacketSE.a)
        target_link_libraries(DCSS_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libHashSE.a)

        target_link_libraries(tools.mix_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libconfig++.so )
        target_link_libraries(tools.mix_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libPcapSE.a )
        target_link_libraries(tools.mix_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libPacketSE.a )

        target_link_libraries(tools.split_sequ_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libconfig++.so )
        target_link_libraries(tools.split_sequ_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libPcapSE.a )
        target_link_libraries(tools.split_sequ_pcap ${PROJECT_SOURCE_DIR}/lib_linux/libPacketSE.a ) 

        # Add an executable with the above sources
        add_executable(DCSS_capture ${dcss_capture_sou}) 

        target_include_directories(DCSS_capture PRIVATE ${PROJECT_SOURCE_DIR}/include)

        target_link_libraries(DCSS_capture libpcap.a)
        target_link_libraries(DCSS_capture ${PROJECT_SOURCE_DIR}/lib_linux/libSketchPoolSE.a)
        target_link_libraries(DCSS_capture ${PROJECT_SOURCE_DIR}/lib_linux/libPacketSE.a)
        target_link_libraries(DCSS_capture ${PROJECT_SOURCE_DIR}/lib_linux/libHashSE.a)
        target_link_libraries(DCSS_capture ${PROJECT_SOURCE_DIR}/lib_linux/libCsvStorage.a)
        target_link_libraries(DCSS_capture ${PROJECT_SOURCE_DIR}/lib_linux/libconfig++.so )
        # target_link_libraries(DCSS_capture ${PROJECT_SOURCE_DIR}/lib/libRedisStorage.a)
ELSEIF ()
ENDIF ()
