#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
 set("short", "魔界小路");
 set("long", @LONG
这里就是魔界了，遍地都是熔岩湖，中间有一条弯弯曲曲的小路，不知道通向何方。
LONG
 );
 set("exits", ([
  "south" : "/d/penglai/mojie/zhaoze5",
  "west" : "/d/penglai/mojie/zhaoze7",
]));
 set("objects", ([
                __DIR__"npc/monster2" : 1,
       ]) );
 setup();
}
void init()
{ 
	object ob;
	object mo;
 	if( interactive( ob = this_player()))
 	{
 		call_out("blowing", random(10) + 1, ob);
 		if( ob->query_temp("jueqing/binghun") == 2 && objectp(mo = present("mo shou",environment(ob))) )
 		{
 			mo->copy_status(mo,ob,8);
 		}
	}
}
int blowing(object ob)
{
 	int i;
 	if( ob && environment(ob) == this_object() )
 	{
 		tell_object(this_object(), HIR "\n\n湖中岩浆一阵沸腾翻滚，部分岩浆溅落在你身上，冒出股股黑烟！！\n\n" NOR);
 		ob->receive_wound("kee",ob->query("max_kee")/20);
              	ob->receive_wound("sen",ob->query("max_sen")/20);
 		COMBAT_D->report_status(ob,1);
 		COMBAT_D->report_sen_status(ob,1);
 		if( environment(ob) == this_object())
 			call_out("blowing",random(10)+1, ob);
 	}
 	else
 		return 1;
}

int valid_leave(object me, string dir)
{
        object mo;
  	if( !mo=present("mo shou",environment(me)) )
  	{
  		remove_call_out("blowing");
    		return ::valid_leave(me,dir);
    	}
  	else if(!living(mo)) 
  	{
  		remove_call_out("blowing");
  		return ::valid_leave(me,dir);
  	}
  	else return notify_fail("想跑？来不及啦！！！\n");
}