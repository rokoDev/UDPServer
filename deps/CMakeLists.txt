include(FetchContent)

# Setup directory to which dependencies will be downloaded
get_filename_component(deps_content "../deps_content"
                       REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
set(FETCHCONTENT_BASE_DIR ${deps_content})

# set(FETCHCONTENT_SOURCE_DIR_NDT "path/to/alternative/version/of/ndt")

# If ndt, fmt or VersionHelper not available then download it and make available
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG 9cb347b4b2e80fc9fbf57b8621746663c3f870f6
	)

FetchContent_Declare(
	VersionHelper
    GIT_REPOSITORY https://github.com/rokoDev/VersionHelper.git
    GIT_TAG        c50c9f6743f8791439313246c56f476a7b1e0b84
)

FetchContent_Declare(
	ndt
	GIT_REPOSITORY https://github.com/rokoDev/ndt.git
	GIT_TAG abdef32f2b6b67f8cda3d95e3206829e044191fc)

FetchContent_MakeAvailable(fmt VersionHelper ndt)

# If use IDE add fmt and ndt targets into deps source group
set_target_properties(fmt ndt PROPERTIES FOLDER deps)

# Generate sources with information about udpserver version
list(APPEND CMAKE_MODULE_PATH "${versionhelper_SOURCE_DIR}")
include(VersionInfoUtils)
m_generate_version_info(PROJECT_NAME ${ProjectName}
	                    CPP_NAMESPACE "server"
	                    BUILD_TYPES Debug Release
	                    IDE_SRC_GROUP "generated"
	                    TARGET_NAME "udpserver")