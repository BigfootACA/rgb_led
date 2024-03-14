set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(
	Qt6 COMPONENTS
	Core
	Gui
	Svg
	Widgets
	SvgWidgets
	REQUIRED
)
add_executable(
	rgb-led
	main.cpp
	main_window.cpp
	device.cpp
	leds_intf.cpp
)
target_link_libraries(
	rgb-led
	rgb-led-lib
	Qt::Core
	Qt::Gui
	Qt::Svg
	Qt::Widgets
	Qt::SvgWidgets
)
install(TARGETS rgb-led)
