inherit ROOM;

void create ()
{
  set ("short", "������");
  set ("long", @LONG

         �������������

LONG);

  set("objects", ([ /* sizeof() == 2 */
  "/d/wiz/npc/paimaishi" : 1,
    "/d/city/npc/laipi" : 1,
  ]));
  set("outdoors", 1);
set("no_fight", 1);
set("no_magic", 1);
  set("exits", ([ /* sizeof() == 2 */
"down" : "/d/city/center",
"up":"/u/yekai/zspfm/zsshendian.c",
  //"north" : __DIR__"damen",
]));

  setup();
}

