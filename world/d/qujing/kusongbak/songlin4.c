inherit ROOM;

void create ()
{
  set ("short", "黑松林");
  set ("long", @LONG

松林中一片漆黑，头顶上密密麻麻的松针遮住了光线，让人难辩
东西南北。大风吹过，带来阵阵热气，却不禁让人发颤。
LONG);
  set("exits", ([ /* sizeof() == 4 */
  "north" :  __DIR__"kusongjian",
  "northeast" : __DIR__"songlin2",
  "northwest" : __DIR__"songlin3",
  "southwest" : __DIR__"songlin2",
  "southeast" : __DIR__"songlin3",
]));



  setup();
}

