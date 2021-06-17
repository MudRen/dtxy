#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
 set("short", "ħ��С·");
 set("long", @LONG
�������ħ���ˣ���ض������Һ����м���һ������������С·����֪��ͨ��η���
LONG
 );
 set("exits", ([
  "east" : "/d/penglai/mojie/zhaoze2",
  "south" : "/d/penglai/mojie/zhaoze4",
]));
set("objects", ([
                __DIR__"npc/monster1" : 1,
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
 			mo->copy_status(mo,ob,7);
 		}
	}
}
int blowing(object ob)
{
 	int i;
 	if(  ob && environment(ob) == this_object())
 	{
 		tell_object(this_object(), HIR "\n\n�����ҽ�һ����ڷ����������ҽ������������ϣ�ð���ɹɺ��̣���\n\n" NOR);
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
  	else return notify_fail("���ܣ���������������\n");
}