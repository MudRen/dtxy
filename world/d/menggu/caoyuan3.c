// Room: /d/menggu/caoyuan3.c

inherit ROOM;

void create()
{
	set("short", "漠北草原");
	set("long", @LONG
漠北的这片荒原,土地贫瘠,只能以畜牧为生,生活在这片土地上的
漠北各个部落之间为争夺牛羊,奴隶,土地,财帛而互相厮杀。
LONG
	);
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/heijiu.c" : 2,
]));
	set("exits", ([ /* sizeof() == 3 */
  "northwest" : __DIR__"caoyuan2",
  "east" : __DIR__"river",
  "south" : __DIR__"mobei",
]));
	set("outdoors", "menggu");
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}

