Route108_MapObjects:: @ 8381A74
	object_event 1, MAP_OBJ_GFX_SWIMMER_M, 0, 17, 0, 13, 0, 1, 45, 51, 0, 1, 0, 3, 0, Route108_EventScript_14F476, 0, 0, 0
	object_event 2, MAP_OBJ_GFX_SWIMMER_F, 0, 8, 0, 6, 0, 1, 13, 17, 0, 1, 0, 3, 0, Route108_EventScript_14F4A4, 0, 0, 0
	object_event 3, MAP_OBJ_GFX_SWIMMER_M, 0, 50, 0, 10, 0, 1, 24, 0, 0, 1, 0, 3, 0, Route108_EventScript_14F48D, 0, 0, 0
	object_event 4, MAP_OBJ_GFX_SWIMMER_F, 0, 36, 0, 12, 0, 1, 51, 54, 0, 1, 0, 3, 0, Route108_EventScript_14F4BB, 0, 0, 0

Route108_MapWarps:: @ 8381AD4
	warp_def 29, 6, 3, 0, MAP_ABANDONED_SHIP_DECK

Route108_MapBGEvents:: @ 8381ADC
	bg_hidden_item_event 38, 14, 3, ITEM_RARE_CANDY, FLAG_HIDDEN_ITEM_56

Route108_MapEvents:: @ 8381AE8
	map_events Route108_MapObjects, Route108_MapWarps, 0x0, Route108_MapBGEvents
