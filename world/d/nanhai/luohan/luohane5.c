//Cracked by Roath
inherit ROOM;

void create ()
{
  set ("short", "罗汉塔");
  set ("long", @LONG


			佛


LONG);

          set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/luohan5" : 1,
]));

  set("exits", ([ /* sizeof() == 4 */
  "southup" : __DIR__"luohane6",
  "eastdown":__DIR__"luohane4",
]));
  setup();
}
int valid_leave(object me, string dir)
{

        if( (string)me->query("family/family_name")=="南海普陀山" ) return 1;
        if( wizardp(me)) return 1;


        if (dir == "southup") {
        if (objectp(present("luo han", environment(me))))

        return notify_fail("罗汉伸手挡住了你的去路。\n");
        }   
        return ::valid_leave(me, dir);
}


