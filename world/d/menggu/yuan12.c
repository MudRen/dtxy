//changan city
// Cracked by 凌惊雪 1-3-2003

inherit ROOM;
#include <ansi.h>

void create ()
{
        set ("short", "忘忧园");
        set ("long", @LONG
这儿就是关外的忘忧园。周围阴森森的，只有四个黑乎乎的洞口，
也不知通向何处。

LONG);
	set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/shouwei.c" : 1,
]));

        set("exits", 
        ([ //sizeof() == 4
                "north" : __DIR__"yuan11",
                "southeast" : __DIR__"yuan13",
        ]));
        setup();
}
int valid_leave(object me, string dir)
{
	if ( present("wangyou shouwei") )
		return notify_fail("守卫伸手拦住了你的去路。\n");
    	return ::valid_leave(me, dir);
}
void init()
{
  add_action("do_cast",({"cast"}));
}
int do_cast(string arg) {
    string *banned_cast=({"chuqiao","qiankun","jieti"});
    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2) ;
    if(member_array(arg,banned_cast)==-1) return 0;
    write("这个地方没法使用"+arg+"。\n");
    return 1;
}

