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

# cloning dependencies
find_package(Git REQUIRED)
function(clone_git dst_dir repo branch commit)
    message(
        "CHECKING OUT
        to dir:${dst_dir}
        repo:'${repo}'
        branch:'${branch}'
        commit:'${commit}'"
    )

    if("${branch}" STREQUAL "")
        message("# clone repo")
        # clone repo
        execute_process(
            COMMAND ${GIT_EXECUTABLE} clone ${repo} ${dst_dir}
            RESULT_VARIABLE git_result
            OUTPUT_VARIABLE git_ver
        )
    else()
        message("# clone specific branch of the repo")
        # clone specific branch of the repo
        execute_process(
            COMMAND ${GIT_EXECUTABLE} clone -b ${branch} ${repo} ${dst_dir}
            RESULT_VARIABLE git_result
            OUTPUT_VARIABLE git_ver
        )
    endif()

    if("${commit}" STREQUAL "")
    else()
        message("# git reset to correct commit")
        # git reset to correct commit
        execute_process(
            WORKING_DIRECTORY ${dst_dir}
            COMMAND ${GIT_EXECUTABLE} reset --hard ${commit}
        )
    endif()
endfunction()
