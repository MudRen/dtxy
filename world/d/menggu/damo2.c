// Cracked by 凌惊雪 4-15-2002
inherit ROOM;

void create()
{
  set ("short", "大漠");
  set ("long", @LONG
四周是一望无际的沙漠，在烈日的照射下，你几乎要虚脱了。西北
通向蒙古草原，东边则是洛阳方向。
LONG);

  set("exits", ([ /* sizeof() == 3 */
  "southeast":__DIR__"huanglu1",
  "northwest":__DIR__"lvzhou",
]));
  set("outdoors", "menggu");
  setup();
  replace_program(ROOM);
}

