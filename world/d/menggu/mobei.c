// Room: /d/menggu/mobei
inherit ROOM;

void create ()
{
  set ("short", "漠北");
  set ("long", @LONG
漠北苦寒之地,风刀霜剑,就在这片贫瘠的土地上,漠北的部落
正在崛起,向北过去就是漠北的草原,东南方向是中原的所在.
LONG);

  set("outdoors", "menggu");
  set("exits", ([ /* sizeof() == 2 */
  "southeast":__DIR__"damo",
  "north" : __DIR__"caoyuan3",
]));

  setup();
}

