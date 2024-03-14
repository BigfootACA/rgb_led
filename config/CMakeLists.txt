install(FILES 99-leds-access.rules DESTINATION lib/udev/rules.d)
install(FILES rgb-led-ayn-odin2.desktop DESTINATION share/applications)
install(DIRECTORY data/ DESTINATION share/rgb-led)
install(FILES data/ayn-odin2/icon.png DESTINATION share/pixmaps RENAME ayn-odin2.png)
