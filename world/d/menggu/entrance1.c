// Cracked by 凌惊雪 3-18-2003

inherit ROOM;
#include <ansi.h>

void create ()
{
        set ("short", "忘忧园入口");
        set ("long", @LONG
这儿就是关外的忘忧园。周围阴森森的，只有四个黑乎乎的洞口，
也不知通向何处。

LONG);
	set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/shouwei.c" : 5,
]));
    	set("in",1);

        set("exits", 
        ([ //sizeof() == 4
                "1" : __DIR__"yuan11",
                "2" : __DIR__"yuan21",
                "3" : __DIR__"yuan31",
                "4" : __DIR__"yuan41",
        ]));
        setup();
}
void init()
{
	if ( (int)this_object()->query("in") > 1 && !(this_object()->query("is_reset")) )
	        {
	        this_object()->set("is_reset",1);
	        remove_call_out("create");
        	call_out("create",3600);
		}
  add_action("do_cast",({"cast"}));
}
int valid_leave(object me, string dir)
{
	int i;
	object *inv;
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                {	if (inv[i]->is_character() )
				return 1;
                }
	if ( present("wangyou shouwei") )
		return notify_fail("守卫伸手拦住了你的去路。\n");
//        if ( (int)this_object()->query("in") > 5 )
        if ( (int)this_object()->query("in") > 8 )
//        if ( (int)this_object()->query("in") > 8 )
		return notify_fail("好象没什么必要再进去了。\n");
    	add("in",1);
    	return ::valid_leave(me, dir);
}
int do_cast(string arg) {
    string *banned_cast=({"chuqiao","qiankun","jieti"});
    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2) ;
    if(member_array(arg,banned_cast)==-1) return 0;
    write("这个地方没法使用"+arg+"。\n");
    return 1;
}


