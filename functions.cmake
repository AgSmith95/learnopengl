cmake_minimum_required(VERSION 3.13)
function(copyfiles src_dir dst_dir patterns)
    string(REPLACE " " ";" patterns_list ${patterns})
    string(REPLACE "," ";" patterns_list ${patterns})
    foreach(pattern ${patterns_list})
        FILE(
            GLOB
            TMP_FILES
            ${src_dir}/${pattern}
        )
        foreach(f ${TMP_FILES})
#            message(${f})
            file(COPY ${f} DESTINATION ${dst_dir})
        endforeach()
    endforeach()
endfunction(copyfiles)