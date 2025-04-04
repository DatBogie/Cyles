include("/home/dat-bogie/Cyles/build/Desktop-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Cyles-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/dat-bogie/Cyles/build/Desktop-Debug/Cyles
    GENERATE_QT_CONF
)
