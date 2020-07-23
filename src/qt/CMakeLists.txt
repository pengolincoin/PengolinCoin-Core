CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/forms ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/forms)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif ()

find_package(Qrcode)
if (QRCODE_FOUND)
    include_directories ( ${QRCODE_INCLUDE_DIR} )
    link_directories ( ${QRCODE_LIBRARY_DIRS} )
endif()

unset(Qt5Enables)
foreach(comp Widgets Core Gui Network LinguistTools DBus Svg Charts)
    find_package(Qt5${comp})
    set(Qt5Enables "${Qt5Enables};Qt5${comp}_FOUND")
    if(Qt5${comp}_FOUND)
        MESSAGE(STATUS "FOUND QT5${comp}")
        include_directories(${include_directories} ${Qt5${comp}_INCLUDE_DIRS} ${QT_USE_FILE})
        add_definitions(${Qt5${comp}_DEFINITIONS})
        list(APPEND Qt5_LIBRARIES ${Qt5${comp}_LIBRARIES})
    else()
        MESSAGE(WARNING "Cant find Qt5${comp}")
    endif()
endforeach(comp)

if (Qt5DBus_FOUND)
    add_compile_options("-DUSE_DBUS")
endif()

if (Qt5Charts_FOUND)
    add_compile_options("-DUSE_QTCHARTS")
endif()

find_program(MOC_BIN NAMES moc moc-qt5 qt5-moc
        PATHS /usr/lib/qt5/bin /usr/lib/x86_64-linux-gnu/qt5/bin /usr/local/opt/qt/bin /usr/local/opt/qt5/bin
        NO_DEFAULT_PATH
        NO_SYSTEM_ENVIRONMENT_PATH)
if (MOC_BIN)
    MESSAGE(STATUS "FOUND MOC ${MOC_BIN}")

endif ()

# Why isn't this done automatically??
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_AUTOMOC_MOC_OPTIONS "-DQ_OS_MAC")
endif()

file(GLOB LOCAL_QT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("QtHeaders" FILES ${LOCAL_QT_HEADERS})

find_package(Protobuf REQUIRED)
if(Protobuf_FOUND)
    message(STATUS "Found Protobuf compiler: ${Protobuf_PROTOC_EXECUTABLE}")
    message(STATUS "Found Protobuf library: ${Protobuf_LIBRARIES}")
endif()
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/paymentrequest.proto)

SET(QT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/bantablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/blockexplorer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/bitcoinaddressvalidator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/bitcoinamountfield.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/bitcoinunits.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/clientmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/csvmodelwriter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/governancepage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/guiutil.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/intro.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/networkstyle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/notificator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/optionsdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/optionsmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/peertablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/platformstyle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qvalidatedlineedit.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qvaluecombobox.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rpcconsole.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/splashscreen.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/trafficgraphwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utilitydialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/addressbookpage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/addresstablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/askpassphrasedialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/coincontroldialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zpgocontroldialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/coincontroltreewidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/proposalframe.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editaddressdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/openuridialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/paymentrequestplus.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/paymentserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/recentrequeststablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transactiondesc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transactionfilterproxy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transactionrecord.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transactiontablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/walletmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/walletmodeltransaction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zpgocontroldialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/pengolincoingui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/loadingdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/pwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/guitransactionsutils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/snackbar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/navmenuwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/lockunlock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/receivedialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/furabstractlistitemdelegate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/txviewholder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/qtutils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/expandablebutton.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/walletpassworddialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/topbar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/txrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/addressfilterproxymodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/dashboardwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/coincontrolpgowidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/addresslabelrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/contactdropdownrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/contactsdropdown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/optionbutton.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/mninfodialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/coldstakingmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/mnmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/masternodewizarddialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/mnrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/masternodeswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/sendchangeaddressdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/sendconfirmdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/sendcustomfeedialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/sendchangeaddressdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/sendmultirow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/send.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/addnewaddressdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/addnewcontactdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/requestdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/receivewidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/myaddressrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/csrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/addressholder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/tooltipmenu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/addresseswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/defaultdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/denomgenerationdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/privacywidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/coldstakingwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsbackupwallet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsbittoolwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsconsolewidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsdisplayoptionswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsfaqwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsinformationwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsmainoptionswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsmultisenddialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsmultisendwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingssignmessagewidgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingswalletoptionswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingswalletrepairwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/welcomecontentwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/splash.cpp
        )

# Workaround until the old rpcconsole UI window is fully removed
set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings/settingsconsolewidget.cpp PROPERTY SKIP_AUTOMOC ON)
execute_process(
        COMMAND ${MOC_BIN} -o moc_settingsconsolewidget.cpp settingsconsolewidget.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings
)

execute_process(
        COMMAND ${MOC_BIN} -o moc_pfborderimage.cpp pfborderimage.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin
)
list(APPEND QT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/moc_pfborderimage.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    list(APPEND QT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/macdockiconhandler.mm)
    list(APPEND QT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/macnotificationhandler.mm)
endif()

add_library(qt_stuff STATIC ${BitcoinHeaders} ${QtHeaders} ${QT_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(qt_stuff PUBLIC ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/leveldb/include
        ${CMAKE_SOURCE_DIR}/src/univalue/include
        ${CMAKE_SOURCE_DIR}/src/secp256k1/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin
        ${CMAKE_CURRENT_SOURCE_DIR}/pengolincoin/settings
        ${OPENSSL_INCLUDE_DIR}
        ${BerkeleyDB_INCLUDE_DIRS}
        )
set_property(TARGET qt_stuff PROPERTY CXX_STANDARD 11)

file(GLOB QT_TRANSLATIONS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/locale/*.ts)

get_filename_component(QM_FILES_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/locale" ABSOLUTE)
set_source_files_properties(${QT_TRANSLATIONS_FILES} PROPERTIES OUTPUT_LOCATION "${QM_FILES_BINARY_DIR}")

QT5_ADD_TRANSLATION(QM ${QT_TRANSLATIONS_FILES})
add_custom_target(translations_target ALL DEPENDS ${QM})

QT5_ADD_RESOURCES(QRC_RESOURCE pengolincoin.qrc)
QT5_ADD_RESOURCES(QRC_LOCALE_RESOURCE pengolincoin_locale.qrc)

add_executable(pengolincoin-qt pengolincoin.cpp ${QM} ${QRC_RESOURCE} ${QRC_LOCALE_RESOURCE})
add_dependencies(pengolincoin-qt translations_target libunivalue libsecp256k1 leveldb leveldb_sse42 memenv)
target_include_directories(pengolincoin-qt PUBLIC ${ENDIAN_INCLUDES})
target_link_libraries(pengolincoin-qt
        qt_stuff
        univalue
        SERVER_A UTIL_A WALLET_A CLI_A COMMON_A BITCOIN_CRYPTO_A ZEROCOIN_A
        leveldb leveldb_sse42 memenv secp256k1
        ${BerkeleyDB_LIBRARIES} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} ${LIBEVENT_LIB}
        pthread
        )
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(pengolincoin-qt "-framework Cocoa")
endif()
if(GMP_FOUND)
    target_link_libraries(pengolincoin-qt ${GMP_LIBRARY})
    target_include_directories(pengolincoin-qt PUBLIC ${GMP_INCLUDE_DIR})
endif()
if(ZMQ_FOUND)
    target_link_libraries(pengolincoin-qt ZMQ_A ${ZMQ_LIB})
    target_include_directories(pengolincoin-qt PUBLIC ${ZMQ_INCLUDE_DIR})
endif()
if (QRCODE_FOUND)
    target_link_libraries(pengolincoin-qt ${QRCODE_LIB})
    target_include_directories(pengolincoin-qt PUBLIC ${QRCODE_INCLUDE_DIR})
endif()
if(MINIUPNP_FOUND)
    target_compile_definitions(pengolincoin-qt PUBLIC "-DSTATICLIB -DMINIUPNP_STATICLIB")
    target_link_libraries(pengolincoin-qt ${MINIUPNP_LIBRARY})
    target_include_directories(pengolincoin-qt PUBLIC ${MINIUPNP_INCLUDE_DIR})
endif()

target_link_libraries(pengolincoin-qt Qt5::Gui Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg ${QT_LIBRARIES})
if (Qt5DBus_FOUND)
    target_link_libraries(pengolincoin-qt Qt5::DBus ${QT_LIBRARIES})
endif()
if (Qt5Charts_FOUND)
    target_link_libraries(pengolincoin-qt Qt5::Charts ${QT_LIBRARIES})
endif()
