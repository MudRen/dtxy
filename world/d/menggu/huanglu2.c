// Cracked by 凌惊雪 4-15-2002
inherit ROOM;

void create()
{
	set("short", "荒路");
	set("long", @LONG
这是条连接关内外的荒路，由于远离城镇，人烟稀少。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"huanglu1",
  "northeast" : __DIR__"huanglu3",
]));
	set("outdoors", "menggu");
	setup();
	replace_program(ROOM);
}

