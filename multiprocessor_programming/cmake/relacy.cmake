if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject/DownloadProject)

download_project(
    PROJ relacy
    GIT_REPOSITORY https://github.com/dvyukov/relacy.git
    GIT_TAG master
    ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

include_directories("${relacy_SOURCE_DIR}")
