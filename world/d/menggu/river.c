// Room: /d/menggu/river
inherit ROOM;

void create()
{
  set ("short", "水塘");
  set ("long", @LONG
一个浑浊的小水塘,边上的水草都长到了岸边,水中依稀有鱼在游动.
几头牛羊在塘边旁若无人地喝水,似乎把谁都不看在眼里,西面天空中一
片乌云正向这边移动,看来要下雨了.
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"caoyuan3",
  "northeast" : __DIR__"byriver",
]));
  set("outdoors", "menggu");
  setup();
  replace_program(ROOM);
}

